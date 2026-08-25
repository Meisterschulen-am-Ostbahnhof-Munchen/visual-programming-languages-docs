# Exercise_003b2_AX: Wireless 16 Buttons on DataPanel 16

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_003b2_AX`. This exercise demonstrates the system's scalability using the example of linking 15 wireless buttons with 15 digital outputs, implemented through untyped sub-applications (or reused typed sub-applications, which were manually placed here).
----
The objective of this exercise is to efficiently manage a large number of similar connections. Instead of drawing the same function blocks and connections 15 times in the main view, the logic is packaged into modular blocks (sub-applications). This demonstrates how IEC 61499 is used for extensive I/O mappings.

-----

## Ziel der Übung

## Description and Components

[cite_start]The subapplication `Uebung_003b2_AX.SUB` instantiates the subtype `Uebung_003b2_sub_AX` 15 times (here named `F1` to `F15`)[cite: 1].

[cite_start]This sub-module connects a radio input (`Funk_IXA`) to a DataPanel output (`DataPanel_MI_QXA`)[cite: 2]. It has the following configuration parameters:

* **`Input`**: The radio button (e.g., `DigitalInput_Key_START`).

### Sub-component: `Uebung_003b2_sub_AX`


* **`Input`**: The radio button (e.g., `DigitalInput_Key_START`).
* * **`Output`**: The physical output (e.g., `DigitalOutput_1B`).
* **`u8SAMember`**: The address of the DataPanel.

### Mapping

This exercise maps the following signals:

* `STOP` -> (not assigned/internal)
* `START` -> `F2`
* `Key_01` to `Key_13` -> `F3` to `F15`

(Note: The exact parameter mapping is not explicitly visible in the `.SUB` file for `Uebung_003b2_AX`, unlike `Uebung_003b3_AX`, because untyped or embedded subapps were used where the parameters are set internally or use default values.) (The parameters are explicitly exposed to the outside via `Uebung_003b3_AX`.)

-----

## Functionality

Each instance, `F1` to `F15`, operates independently:

1. The `Funk_IXA` module receives the signal from the corresponding button on the remote control.
2. The signal is forwarded to the `DataPanel_MI_QXA` module via an adapter connection.
3. The output on the DataPanel switches accordingly.

Since all 15 channels operate in parallel, multiple buttons can be pressed simultaneously, and the corresponding outputs react concurrently.

-----

An application example is a **control panel for a loading crane**:

The crane operator has a radio remote control with many buttons (lift, lower, rotate, extend, etc.). Each button must control a specific hydraulic valve. By using sub-applications, the circuit diagram remains clear ("One box per function"), even though 30 or more components are active in the background.

## Anwendungsbeispiel