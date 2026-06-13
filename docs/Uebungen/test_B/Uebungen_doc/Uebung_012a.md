# Uebung_012a: Numeric Value Input und Speichern NVS mit Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_012a`. Hier wird die persistente Speicherung aus Übung 012 in eine wiederverwendbare Sub-Applikation gekapselt.

----


## Übersicht

[cite_start]Die Subapplikation `Uebung_012a.SUB` nutzt den Sub-App-Typ `Uebung_012a_sub`, um die Speicher-Logik modular bereitzustellen[cite: 1]. Der Baustein `CbVtStatus` bleibt auf der obersten Ebene, um die gesamte Seite bei Bedarf zu aktualisieren.

### Typisierte Sub-Applikation: `Uebung_012a_sub`

[cite_start]Dieser Baustein bündelt die Eingabe via `NumericValue_ID`, die Konvertierung, den NVS-Zugriff und die Anzeige-Rückführung[cite: 2]. Er stellt Schnittstellen für den Speicher-Schlüssel (`KEY`) und die Objekt-ID (`u16ObjId`) zur Verfügung.

Dies ermöglicht es, viele verschiedene Einstellwerte (z.B. Druck, Durchfluss, Zeit) sehr schnell und übersichtlich in das Programm zu integrieren, ohne jedes Mal das komplexe Netzwerk aus Übung 012 neu zeichnen zu müssen.