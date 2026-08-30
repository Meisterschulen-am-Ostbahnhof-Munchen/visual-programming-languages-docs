# ScrollFS_PHYS

![ScrollFS_PHYS](ScrollFS_PHYS.svg)

* * * * * * * * * *

## Einleitung

`ScrollFS_PHYS` ist der fertige, sofort einsetzbare Baustein für eine scrollbare VT-Liste mit
Softkey-Bedienung: eine `ScrollFull_S`-Konstante hinein (wie sie `GcfScript.py` aus dem
ISO-Designer-Pool erzeugt), fertig — er verdrahtet die 6 physischen Softkeys, das
Direkteingabe-Feld und die interne Positions-Engine [ScrollFS](ScrollFS.md) selbst, inklusive
automatischer Ausblendung der Scroll-Tasten am jeweiligen Listenanschlag. Zwei Listen auf einer
Maske = zwei Instanzen, jede mit eigener `ScrollFull_S`-Konstante. Siehe
`Workspace_Scroll/SCROLL_KONZEPT.md` (Projekt `4diac_training1`) für die vollständige
Herleitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Übernimmt die komplette Konfiguration (`stObj`) per Snapshot.

### **Ereignis-Ausgänge**

- `CNF`: Bestätigt eine Positionsänderung, liefert `OUT`.

### **Daten-Eingänge**

- `stObj` (`isobus::utils::scroll::ScrollFull_S`): komplette Konfiguration (Geometrie +
  Bedienelemente-IDs), bei `INIT` geschnappt.

### **Daten-Ausgänge**

- `OUT` (DINT): Aktuelle Scroll-Position (0…`stObj.stGeometry.i32PosMax`, in Zeilen).

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

1. **`Snap`** (`F_MOVE`, `DataType = ScrollFull_S`): schnappt `stObj` bei `INIT`, danach stehen
   Geometrie und alle Bedienelemente-IDs als `Snap.OUT.stGeometry`/`Snap.OUT.stControls.<Feld>`
   zur Verfügung.
2. **6× `Softkey_IE`** (`BtnFirst`, `BtnPageUp`, `BtnLineUp`, `BtnLineDown`, `BtnPageDown`,
   `BtnLast`), je auf `SK_PRESSED` horchend, `u16ObjId` aus dem jeweiligen
   `Snap.OUT.stControls.u16Btn*Id` — ihr `IND`-Ereignis löst direkt das passende
   [ScrollFS](ScrollFS.md)-Navigationsereignis auf `Inner` aus.
3. **`GotoInput`** (`NumericValue_ID`) + **`GotoConv`** (`F_DWORD_TO_DINT`): liest das
   Direkteingabe-Feld (`u16GotoInputId`) und speist den Wert als `SET_POS` in `Inner.GOTO`.
4. **`Inner`** (`ScrollFS`): die eigentliche Positions-Engine, siehe [ScrollFS](ScrollFS.md).
   `Inner.OUT` wird direkt als eigenes `OUT` durchgereicht.
5. **Anschlag-Ausblendung** — pro Richtung (Up-Seite: `BtnPageUp`+`BtnLineUp`, Down-Seite:
   `BtnPageDown`+`BtnLineDown`) je eine Kette aus `F_SEL` + `Q_NumericValue`, ausgelöst bei jeder
   Positionsänderung (`Inner.CNF`):
   - `F_SEL.G := Inner.qAtFirst` (Up-Seite) bzw. `Inner.qAtLast` (Down-Seite)
   - `F_SEL.IN0 :=` echte SoftKey-ID (`Snap.OUT.stControls.u16Btn*Id`) — Wert, wenn **kein**
     Anschlag
   - `F_SEL.IN1 := ID_NULL` — Wert, wenn Anschlag erreicht (`F_SEL.OUT := G ? IN1 : IN0`)
   - `Q_NumericValue.u16ObjId :=` die zugehörige ObjectPointer-ID
     (`Snap.OUT.stControls.u16Btn*PtrId`), `.u32NewValue := F_SEL.OUT`
   - Ergebnis: der ObjectPointer der SoftKeyMask zeigt bei Anschlag auf `ID_NULL` (Taste
     verschwindet), sonst auf den echten `SoftKey` (Taste sichtbar).

## Technische Besonderheiten

- **`F_SEL`-Richtung ist nicht symmetrisch**: `F_SEL.OUT := G ? IN1 : IN0` — bei Verwechslung
  von `IN0`/`IN1` zeigt die Taste genau dann, wenn sie eigentlich verschwinden sollte (und
  umgekehrt). Diese Reihenfolge (`IN0` = sichtbarer Wert, `IN1` = `ID_NULL`) war in einer
  früheren Version vertauscht und musste korrigiert werden.
- **`Q_NumericValue` auf ObjectPointer statt „Hide/Show Object"**: Object Pointer werden nicht
  über das ISO-11783-6-Kommando „Hide/Show Object" (Annex F.2, nur für Container gültig)
  aus-/eingeblendet, sondern über „Change Numeric Value" (Annex F.22) direkt auf die
  ObjectPointer-ID selbst — das ändert, worauf der Pointer zeigt (`ID_NULL` = zeigt auf nichts =
  unsichtbar). Vorbild: `Uebung_015` (Projekt `4diac_training1`).
- **ObjectPointer- vs. Key-ID nicht verwechseln**: `Snap.OUT.stControls.u16Btn*Id` ist die
  **echte** `SoftKey`-Objekt-ID (Ziel für `Softkey_IE.u16ObjId` **und** für `F_SEL.IN0`),
  `Snap.OUT.stControls.u16Btn*PtrId` ist die ID des **ObjectPointers**, der auf diese SoftKey im
  SoftKeyMask-Baum zeigt (Ziel für `Q_NumericValue.u16ObjId`) — beide werden von `GcfScript.py`
  automatisch aus dem Pool aufgelöst (SoftKeyMask-Kind ist der ObjectPointer, dessen Ziel über
  eine `CProxy`-Indirektion die echte SoftKey ist).
- **Serielle Init-Kette**: `Snap.CNF → BtnFirst.INIT → … → BtnLast.INIT → GotoInput.INIT →
  PtrPageUp.INIT → PtrUp.INIT → PtrDown.INIT → PtrPageDown.INIT → Inner.INIT` — jeder Baustein
  wird erst initialisiert, wenn der vorherige fertig ist (`INITO`-Kette), analog zum
  entsprechenden Muster in [ScrollFS](ScrollFS.md).

## Zustandsübersicht

Kein eigener Zustand außer dem in `Inner` (`ScrollFS`/`RampLimitFS`) gehaltenen. Die
Anschlag-Ausblendung ist rein ereignisgetrieben — bei jeder Positionsänderung wird der
Sichtbarkeitszustand aller vier Tasten neu berechnet, nicht nur beim tatsächlichen
Anschlag-Übergang.

## Anwendungsszenarien

- Jede scrollbare Liste am VT, die über physische Softkeys bedient wird (z. B. lange
  Auswahllisten, Diagnose-/Statusübersichten) — siehe `Workspace_Scroll` im Projekt
  `4diac_training1` für ein reales, getestetes Beispiel.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gegenüber `ScrollFS`**: `ScrollFS_PHYS` ist der praxistaugliche Wrapper — `ScrollFS` selbst
  kennt keine physischen Bedienelemente, nur abstrakte Navigationsereignisse.
- **Gegenüber `ScrollFS_PHYS_Button`**: identische Struktur und Anschlag-Ausblendung, liest die
  6 Bedienelemente aber als Bildschirm-`Button`-Objekte (`BT_PRESSED_LATCHED`) statt als
  `SoftKey`-Objekte — für Masken ohne SoftKey-Spalte bzw. mit Touch-Bedienung. Siehe
  [ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.md).

## 🛠️ Zugehörige Übungen

- Kein eigenständiges Übungsbeispiel — siehe `Workspace_Scroll/SCROLL_KONZEPT.md` (Projekt
  `4diac_training1`).

## Fazit

`ScrollFS_PHYS` ist der komplette, produktionsreife Scroll-Baustein für Softkey-bediente Listen —
inklusive automatischer Anschlag-Ausblendung der Navigationstasten, ohne dass die
Steuerungsanwendung selbst Grenzwerte prüfen oder Object Pointer manuell umbiegen muss.
