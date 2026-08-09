# Exercise_008_AX: Flasher with E_CYCLE, E_SWITCH, and E_SR

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_008_AX`.
----
Implementation of a continuously running flasher as a basic function block.

-----

## Ziel der Übung

## Description and Components

The subapplication `Uebung_008_AX.SUB` is a variant that uses the `AX_AE_MERGE` function block to correctly combine the events.

The `AE_CYCLE` runs continuously (or is initialized once). The `AX_AE_MERGE` combines the clock signal (`AE_CYCLE.EO`) with the feedback signal (`AX_SR.Q`). The logic with `E_SWITCH` and `AX_SR` handles the toggling. Since no external intervention is possible, this output blinks continuously as long as the controller is running.

-----


**Heartbeat Signal**: An LED that blinks on the circuit board or control cabinet to indicate: "The CPU is still active and the program is running."
## Beschreibung und Komponenten

## Anwendungsbeispiel