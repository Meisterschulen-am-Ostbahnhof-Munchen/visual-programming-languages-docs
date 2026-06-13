# Uebung_020f3: DigitalInput_I1 auf DigitalOutput_Q1; BLINKER




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_020f3`.

----


## Übersicht

[cite_start]Verwendung des spezialisierten Blinker-Bausteins `E_BLINK`[cite: 1]. Dieser Baustein fasst die gesamte Logik der Übung 007a3 zusammen.
Über getrennte Parameter für `TIMELOW` und `TIMEHIGH` können asymmetrische Blinkmuster (z.B. kurzes Blitzen) einfach realisiert werden. Ein Ereignis am Eingang `START` setzt den Blinker in Gang.

![Uebung_020f3_network](./Uebung_020f3_network.svg)
