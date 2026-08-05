# Exercise_007a3_AX: Turn Signal with E_CYCLE, E_SWITCH, and E_SR
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_007a3_AX`. This exercise demonstrates the "clean" solution for a switchable turn signal.
----
## Objective of the Exercise
Ensure that the turn signal always stops in the "OFF" state.

-----

## Description and Components

[cite_start]The subapplication `Uebung_007a3_AX.SUB` uses more complex logic[cite: 1]:

* **`AX_CYCLE`**: The clock generator (starts/stops).
* **`E_SR`**: A memory location ("Blinker is active").
* **`AX_SPLIT_2`**: Distributes the signal from the memory location (to the lamp and the feedback loop).
* **`AX_AE_MERGE`**: Combines the clock signal (`AE_CYCLE.EO` - event only) and the feedback signal (`E_SR.Q` - event and BOOL). The data bit from `E_SR.Q` is retained.
* **`E_SWITCH`**: The actual "heart" of the circuit. It uses the merged signal to toggle the `AX_SR` flip-flop.

But most importantly: The `STOP` input is **additionally** directly connected to `E_SR.R`.

------

## Functionality

1. **Start/Blinking**: `START` presses the button and starts `AE_CYCLE`. When `E_SR.Q` is active, the loop through `E_SWITCH` (triggered by `AX_AE_MERGE`) causes the toggling.

2. **Stop**: When `STOP` is pressed:

* `AE_CYCLE` stops (no new clock cycles).
* The `E_SR` is **reset**. This forces the output `Q`, and therefore the lamp `Q1`, to be set to FALSE.

-----

## Application Example

**Professional Indicator**: An industrial fault indicator must flash when a fault is present and be **off** when the fault has been acknowledged. It must never remain illuminated (this would often indicate "operational" or something else).