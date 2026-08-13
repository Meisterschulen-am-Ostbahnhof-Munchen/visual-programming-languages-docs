# ScrollFS_PHYS_Button

![ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.svg)

* * * * * * * * * *
## Einleitung

`ScrollFS_PHYS_Button` ist strukturell identisch zu [ScrollFS_PHYS](ScrollFS_PHYS.md) — derselbe
fertige, sofort einsetzbare Scroll-Baustein, dieselbe `ScrollFull_S`-Konstante, dieselbe
Anschlag-Ausblendung —, liest die 6 Bedienelemente aber als Bildschirm-`Button`-Objekte
(`Button_IE`, horcht auf `BT_PRESSED_LATCHED`) statt als physische `SoftKey`-Objekte. Gedacht für
Masken, bei denen gescrollt werden soll, ohne dass eine SoftKey-Spalte zur Verfügung steht (z. B.
Touch-Bedienung). Die 6 IDs in `ScrollControls_S` zeigen dann auf `Button`- statt auf
`SoftKey`-Objekte, sonst ist `ScrollFull_S`/`ScrollControls_S` unverändert. Siehe
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

Identisch zu [ScrollFS_PHYS](ScrollFS_PHYS.md), mit einem Unterschied: die 6 Bedienelemente sind
`Button_IE`-Instanzen (`BtnFirst`, `BtnPageUp`, `BtnLineUp`, `BtnLineDown`, `BtnPageDown`,
`BtnLast`), die auf `BT_PRESSED_LATCHED` statt `SK_PRESSED` horchen. Alles Weitere — Direkteingabe
über `NumericValue_ID`+`F_DWORD_TO_DINT`, interne [ScrollFS](ScrollFS.md)-Positions-Engine,
Anschlag-Ausblendung über `F_SEL`+`Q_NumericValue` auf die 4 ObjectPointer-IDs — ist 1:1
identisch zu `ScrollFS_PHYS`.

## Technische Besonderheiten

Siehe [ScrollFS_PHYS](ScrollFS_PHYS.md), Abschnitt „Technische Besonderheiten" — alle dort
beschriebenen Punkte (F_SEL-Richtung, ObjectPointer- vs. Key-ID, serielle Init-Kette) gelten
unverändert. Der einzige Unterschied ist der Bedienelement-Typ (`Button_IE` statt `Softkey_IE`).

## Zustandsübersicht

Wie [ScrollFS_PHYS](ScrollFS_PHYS.md) — kein eigener Zustand außer dem in `Inner`
(`ScrollFS`/`RampLimitFS`) gehaltenen.

## Anwendungsszenarien

- Scrollbare Listen auf Masken ohne SoftKey-Spalte, insbesondere bei Touch-fähigen Terminals, wo
  Bildschirm-Buttons statt physischer Softkeys bevorzugt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gegenüber `ScrollFS_PHYS`**: identisch bis auf den Bedienelement-Typ (`Button_IE`/
  `BT_PRESSED_LATCHED` statt `Softkey_IE`/`SK_PRESSED`). Siehe [ScrollFS_PHYS](ScrollFS_PHYS.md)
  für die vollständige Beschreibung.
- **Gegenüber `ScrollFS`**: `ScrollFS_PHYS_Button` ist der praxistaugliche Wrapper — `ScrollFS`
  selbst kennt keine physischen Bedienelemente, nur abstrakte Navigationsereignisse.

## 🛠️ Zugehörige Übungen

* Kein eigenständiges Übungsbeispiel — siehe `Workspace_Scroll/SCROLL_KONZEPT.md` (Projekt
  `4diac_training1`).

## Fazit

`ScrollFS_PHYS_Button` bietet dieselbe fertige Scroll-Funktionalität wie `ScrollFS_PHYS`, nur für
Bildschirm-Buttons statt Softkeys — welche Variante passt, hängt allein davon ab, mit welchem
Objekttyp die Bedienelemente im Pool angelegt sind.
