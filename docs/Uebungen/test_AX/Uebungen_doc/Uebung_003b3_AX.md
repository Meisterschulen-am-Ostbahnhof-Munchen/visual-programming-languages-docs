# Uebung_003b3_AX: Funk 16 Tasten auf DataPanel 16




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_003b3_AX`. Diese Übung ist die konsequente Weiterentwicklung von `Uebung_003b2_AX`. Sie nutzt explizit parametrierte typisierte Sub-Applikationen, um 15 Funktasten auf 15 Ausgänge zu mappen.

----


## Ziel der Übung

Das Ziel ist maximale Wiederverwendbarkeit und Übersichtlichkeit. Durch die Verwendung von typisierten Sub-Applikationen mit exponierten Parametern kann die gesamte Konfiguration (welche Taste auf welchen Ausgang) direkt in der Hauptansicht vorgenommen werden, ohne in die Sub-Bausteine hineinklicken zu müssen.

-----

## Beschreibung und Komponenten

[cite_start]Die Subapplikation `Uebung_003b3_AX.SUB` instanziiert 15 mal den Typ `Uebung_003b3_sub_AX`[cite: 1].

### Typisierte Sub-Applikation: `Uebung_003b3_sub_AX`

[cite_start]Dieser Baustein ist identisch zur Funktionalität in `Uebung_003b2_sub_AX`, jedoch sind die Parameter `Input`, `Output` und `u8SAMember` sauber herausgeführt[cite: 2].

### Konfiguration der Instanzen

Die Zuweisung ist in der Datei klar lesbar:



*   **`F1`**: `STOP` -> `Output_1A` (Achtung: Logik prüfen, ob STOP ggf. invertiert oder speziell behandelt wird)
*   **`F2`**: `START` -> `Output_1B`
*   **`F3`**: `Key_01` -> `Output_2A`
*   **`F4`**: `Key_02` -> `Output_2B`
*   ...
*   **`F15`**: `Key_13` -> `Output_8A`

Alle Instanzen nutzen `MI_00` als `u8SAMember` (Adresse des DataPanels).

-----

## Funktionsweise

Die Funktionsweise ist identisch zur vorherigen Übung:
1.  Die Hauptanwendung übergibt die Parameter (z.B. "Benutze Taste 1") an die Sub-Applikation.
2.  Die Sub-Applikation konfiguriert ihren internen `Funk_IXA` Baustein entsprechend.
3.  Das Signal wird gelesen und via Adapter an den `DataPanel_MI_QXA` weitergeleitet.
4.  Der Ausgang schaltet.

Der Vorteil hier ist die Wartbarkeit: Soll Taste 1 plötzlich Ausgang 8A schalten, muss man nur den Parameter an `F3` ändern, anstatt Leitungen neu zu ziehen.

-----

## Anwendungsbeispiel

Ein Anwendungsbeispiel ist die **Serienfertigung von Sondermaschinen**:

Eine Firma baut Müllpressen, die mal mit 4, mal mit 8 oder 12 Tasten bestückt sind. Die Software ist immer gleich aufgebaut: Man nimmt den Baustein "Tasten-Kanal" und platziert ihn so oft wie nötig. Die Zuordnung, welcher Hydraulikzylinder zu welcher Taste gehört, geschieht rein über Parameterlisten. Das reduziert Fehler und beschleunigt die Inbetriebnahme enorm.