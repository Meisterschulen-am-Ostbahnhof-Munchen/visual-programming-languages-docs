# Uebung_033: LED Strip Blinkende LED




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_033`.

----


## Übersicht

[cite_start]Dies ist die modulare Variante der Übung 032[cite: 1]. Die Logik für einen farbigen LED-Kanal wurde in eine typisierte Sub-Applikation `Uebung_033_sub` ausgelagert. Das Hauptprogramm instanziiert diesen Typ viermal und weist ihm die Taster `I1` bis `I4` sowie die Zielfarben zu. Dies zeigt erneut die Vorteile der Wiederverwendbarkeit bei komplexen Hardware-Komponenten wie LED-Controllern.