# Uebung_004c3: Toggle Flip-Flop mit IE mit BUTTON_LONG_PRESS_UP




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_004c3`.

----


## Ziel der Übung

Nutzung des Ereignisses `BUTTON_LONG_PRESS_UP`.

-----

## Funktionsweise

[cite_start]Der Baustein `DigitalInput_CLK_I1` in `Uebung_004c3.SUB` erkennt das Ende eines langen Drucks[cite: 1].


![Uebung_004c3_network](./Uebung_004c3_network.svg)

Im Gegensatz zum `START`-Event feuert `LONG_PRESS_UP` erst dann, wenn der Nutzer den Taster **wieder loslässt**, sofern dieser vorher lange genug gedrückt wurde. Dies ermöglicht es, Aktionen genau am Ende einer Interaktion auszulösen.

-----

## Anwendungsbeispiel

**Bestätigungs-Dialog**: Der Nutzer muss eine Taste lange gedrückt halten, um sicherzugehen, dass er die Aktion will. Die Ausführung (z.B. "Motor starten") erfolgt erst beim Loslassen als finale Bestätigung.