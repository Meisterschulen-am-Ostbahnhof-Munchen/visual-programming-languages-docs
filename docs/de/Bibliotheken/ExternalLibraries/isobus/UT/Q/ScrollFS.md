# ScrollFS

![ScrollFS](ScrollFS.svg)

* * * * * * * * * *

## Einleitung

`ScrollFS` ist die reine Positions-Engine einer scrollbaren VT-Liste: er hält die aktuelle
Zeilen-Position (0…`i32PosMax`), reagiert auf Navigations-Ereignisse (Zeile/Seite hoch/runter,
Anfang/Ende, absolute Position) und schreibt die passende Y-Verschiebung sowohl für den
Listen-Inhalt als auch für den Scrollbalken-Thumb über zwei `Q_ChildPosition`-Aufrufe
(ISO 11783-6 F.16, „Change Child Location“) an den VT. Er liest **keine** physischen Tasten oder
Eingabefelder — dafür ist [ScrollFS_PHYS](ScrollFS_PHYS.md) bzw.
[ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.md) zuständig, die `ScrollFS` intern kapseln. Details
zur Herleitung siehe `Workspace_Scroll/SCROLL_KONZEPT.md` im Projekt `4diac_training1`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `INIT`: Übernimmt die Konfiguration (`stObj`) per Snapshot.
- `FIRST`: Springt zur ersten Zeile (Position 0).
- `PAGE_UP`: Eine Seite nach oben (schnell, um `stObj.i32Step` Zeilen).
- `LINE_UP`: Eine Zeile nach oben.
- `LINE_DOWN`: Eine Zeile nach unten.
- `PAGE_DOWN`: Eine Seite nach unten (schnell, um `stObj.i32Step` Zeilen).
- `LAST`: Springt zur letzten Zeile (Position `stObj.i32PosMax`).
- `GOTO`: Springt zu einer absoluten Zeilen-Position (`SET_POS`), geklemmt auf
  `0…stObj.i32PosMax`.

### **Ereignis-Ausgänge**

- `CNF`: Bestätigt eine Positionsänderung, liefert `OUT`, `qAtFirst` und `qAtLast`.

### **Daten-Eingänge**

- `stObj` (`isobus::utils::scroll::ScrollObjectPool_S`): Listen-/Balken-Geometrie (Container-IDs,
  Zeilenhöhe, Balken-Offsets, `i32PosMax`, `i32Step`) — wird bei `INIT` einmalig geschnappt.
- `SET_POS` (DINT): Zielposition für `GOTO`.

### **Daten-Ausgänge**

- `OUT` (DINT): Aktuelle Scroll-Position (0…`stObj.i32PosMax`, in Zeilen).
- `qAtFirst` (BOOL): `TRUE`, wenn `OUT` bei Zeile 0 steht (Listenanfang erreicht).
- `qAtLast` (BOOL): `TRUE`, wenn `OUT` bei `stObj.i32PosMax` steht (Listenende erreicht).

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

`ScrollFS` verdrahtet vier Bausteine zu einer fertigen Positions-Engine:

1. **`Snap`** (`F_MOVE`, `DataType = ScrollObjectPool_S`): schnappt `stObj` bei `INIT` einmalig,
   danach stehen alle neun Geometrie-Felder als `Snap.OUT.<Feldname>` dauerhaft zur Verfügung.
2. **`Ramp`** (`RampLimitFS`, Paket `eclipse4diac::signalprocessing`): die eigentliche
   Positions-Zustandsmaschine, direkt wiederverwendet (kein eigener Zustandsautomat nötig).
   Die acht `ScrollFS`-Events sind 1:1 auf `RampLimitFS`-Events gemappt:

   | `ScrollFS`-Event | `RampLimitFS`-Event | Wirkung auf `OUT` |
   | --- | --- | --- |
   | `FIRST` | `ZERO` | `OUT := 0` |
   | `PAGE_UP` | `DOWN_FAST` | `OUT -= stObj.i32Step` (geklemmt bei 0) |
   | `LINE_UP` | `DOWN_SLOW` | `OUT -= 1` (geklemmt bei 0) |
   | `LINE_DOWN` | `UP_SLOW` | `OUT += 1` (geklemmt bei `i32PosMax`) |
   | `PAGE_DOWN` | `UP_FAST` | `OUT += stObj.i32Step` (geklemmt bei `i32PosMax`) |
   | `LAST` | `FULL` | `OUT := stObj.i32PosMax` |
   | `GOTO` | `LOAD` (mit `PV := SET_POS`) | `OUT := SET_POS`, geklemmt auf `0…i32PosMax` |

   `VAL_ZERO := 0`, `VAL_FULL := Snap.OUT.i32PosMax`, `SLOW := 1`, `FAST := Snap.OUT.i32Step`.
3. **`ListY`** (`F_ScrollListY`) und **`BarY`** (`F_ScrollBarY`): rechnen bei jedem
   `Ramp.CNF` aus `Ramp.OUT` die Y-Verschiebung für Liste bzw. Scrollbalken.
4. **`MoveList`** und **`MoveBar`** (je `Q_ChildPosition`): schreiben die berechneten
   Y-Werte an den VT — `MoveList` bewegt `Container_Scrolling_Content` innerhalb von
   `Container_Scrolling_Parent`, `MoveBar` bewegt `Container_Scrollbar_Content` innerhalb von
   `Container_Scrollbar_Parent`. Beide `s16Xposition := 0` fest (nur vertikales Scrollen).

`Ramp.qAtZero`/`Ramp.qAtFull` werden unverändert als `qAtFirst`/`qAtLast` durchgereicht.

## Technische Besonderheiten

- **`F_MOVE`-Snapshot für Struct-Zugriff**: `Snap.IN`/`.OUT` sind generisch `ANY`-typisiert;
  eine `ANY`-Verbindung (hier: der konkret typisierte `stObj` auf den generischen `Snap.IN`)
  läuft in 4diac grundsätzlich nur über einen `MOVE`-Baustein, nie direkt. Jedes einzelne
  Struct-Feld, das per `Snap.OUT.<Feld>` angesprochen wird, braucht dafür einen eigenen
  `Parameter Name="OUT.<Feld>"`-Eintrag mit `Attribute Name="Visible" Value="true"` auf der
  `Snap`-Instanz — fehlt der, kompiliert das Netz nicht.
- **Init-Kette seriell, nicht parallel**: `Snap.CNF` löst `Ramp.INIT` aus; erst nach
  `Ramp.INITO` werden `MoveList.INIT` und `MoveBar.INIT` angestoßen — dadurch stehen
  `VAL_ZERO`/`VAL_FULL`/`SLOW`/`FAST` in `Ramp` garantiert, bevor irgendein Positionswert an den
  VT geschrieben wird.
- **`ListY`/`BarY` sind konkret typisiert** (`DINT`/`INT`, siehe [F_ScrollListY](helpers/F_ScrollListY.md),
  [F_ScrollBarY](helpers/F_ScrollBarY.md)) — dadurch ist zwischen ihnen und `Ramp.OUT` kein
  zusätzlicher `MOVE`-Anker nötig, obwohl `Ramp.OUT` selbst aus einer generischen
  `RampLimitFS`-Instanz stammt.

## Zustandsübersicht

Die einzige Zustandshaltung steckt in `Ramp` (`RampLimitFS`): `OUT` bleibt zwischen den
Ereignissen erhalten, jedes Navigations-Event ändert ihn schrittweise oder springt direkt.
`qAtFirst`/`qAtLast` werden bei jeder Änderung neu berechnet, nie separat gepflegt.

## Anwendungsszenarien

- Wird nicht direkt verwendet, sondern immer über [ScrollFS_PHYS](ScrollFS_PHYS.md) (Softkeys)
  oder [ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.md) (Bildschirm-Buttons), die die acht
  Navigations-Events aus physischen Tastendrücken ableiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gegenüber `RampLimitFS`**: `ScrollFS` ist im Kern ein `RampLimitFS` mit VT-Anbindung — die
  Positions-Mathematik selbst (Klemmen, Grenzwert-Flags) liegt vollständig in `RampLimitFS`,
  `ScrollFS` ergänzt nur Struct-Konfiguration, Zeilen-/Balken-Umrechnung und das Schreiben an den
  VT.

## 🛠️ Zugehörige Übungen

- Kein eigenständiges Übungsbeispiel — siehe `Workspace_Scroll/SCROLL_KONZEPT.md` (Projekt
  `4diac_training1`) für die vollständige Herleitung anhand eines realen Pools.

## Fazit

`ScrollFS` bündelt Positions-Zustand, Grenzwert-Erkennung und VT-Schreibzugriff einer
scrollbaren Liste in einem einzigen, wiederverwendbaren Composite-Baustein — unabhängig davon,
ob die Bedienung später über Softkeys oder Bildschirm-Buttons erfolgt.
