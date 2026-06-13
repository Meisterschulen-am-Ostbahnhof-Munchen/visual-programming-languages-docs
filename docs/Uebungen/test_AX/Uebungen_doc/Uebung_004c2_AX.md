# Uebung_004c2_AX: Toggle Flip-Flop mit IE mit BUTTON_LONG_PRESS_START




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_004c2_AX`.

----


## Ziel der Übung

Nutzung des Ereignisses `BUTTON_LONG_PRESS_START`.

-----

## Funktionsweise

[cite_start]Der Baustein `DigitalInput_CLK_I1` in `Uebung_004c2_AX.SUB` ist auf `BUTTON_LONG_PRESS_START` konfiguriert[cite: 1].




![Uebung_004c2_AX_network](./Uebung_004c2_AX_network.svg)

Das Event `IND` wird gefeuert, sobald der Taster eine bestimmte Zeit lang gedrückt *gehalten wurde* (z.B. > 500ms). Es feuert genau in dem Moment, in dem die Zeit abgelaufen ist, auch wenn der Taster noch weiter gedrückt bleibt.

-----

## Anwendungsbeispiel

**Licht dimmen**: Ein kurzer Klick schaltet Ein/Aus (siehe Übung 004a). Ein langer Druck (erkannt durch `LONG_PRESS_START`) startet den Dimm-Vorgang.