# Uebung_010c3: SoftKey_F1 auf DigitalOutput_Q1 mit GreenWhiteBackground mit Typed Subapp




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_010c3`.

----


## Übersicht

[cite_start]Hier wird die Kapselung konsequent zu Ende geführt: Aus der Sub-Applikation wird ein echter Typ `Uebung_010c3_sub` erstellt[cite: 1]. Dieser Baustein kann nun wie ein Standard-Baustein aus der Bibliothek verwendet werden. Er verlangt lediglich die Angabe der Softkey-ID und des Hardware-Ausgangs als Parameter und erledigt die gesamte interne Verschaltung von Logik und Feedback automatisch.