# Exercise_003b2: Wireless 16 Buttons to DataPanel 16
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_003b2`. This exercise demonstrates the system's scalability by mapping 15 buttons of a wireless remote control to 15 digital outputs of a DataPanel.
----
## Objective of the Exercise
The objective of this exercise is the efficient management of a large number of hardware interfaces. By using standardized sub-applications with exposed parameters, the complete mapping between wireless inputs and CAN bus outputs can be performed centrally in the main application without having to modify the internal logic.

## Description and Components

[cite_start]The subapplication `Uebung_003b2.SUB` instantiates the specialized subtype `Uebung_003b2_sub` (named `F1` to `F15`) 15 times [cite: 1].

### Typed Subapplication: `Uebung_003b2_sub`

[cite_start]This component serves as a universal "channel driver" for radio-to-CAN communication [cite: 2]. It has the following parameters:

* **`Input`**: The name of the radio button (e.g., `Key_01`, `START`, `STOP`).
* **`u8SAMember`**: The CAN address of the DataPanel (here fixed to `MI_00`).
* **`Output`**: The name of the physical output on the DataPanel (e.g., `DigitalOutput_1A`).

Internally, the module contains a `Funk_IX` for receiving radio signals and a `DataPanel_MI_QX` for sending CAN messages.

### Channel Configuration

In `Uebung_003b2`, the assignments are clearly defined:

* `F1`: `STOP` ➡️ `Output_1A`
* `F2`: `START` ➡️ `Output_1B`
* `F3` to `F15`: `Key_01` to `Key_13` ➡️ `Output_2A` to `Output_8A`

-----

## Functionality

The signal path is event-driven via the CAN bus infrastructure:

1. The user presses a button on the remote control.

2. The instance of type `Funk_IX` within the corresponding sub-application detects the button press and triggers a `IND` event.

3. This event is routed directly to the `REQ` input of the `DataPanel_MI_QX` module.

4. The output module then generates a CAN message for the DataPanel to switch the assigned physical output on or off.

Since all 15 instances operate in parallel and independently, any number of buttons can be operated simultaneously.

-----

## Application Example

**Retrofitting a Radio Remote Control**:

An existing machine is to be equipped with a radio remote control for 15 different hydraulic functions. Instead of reprogramming the entire logic, the DataPanel is used as an I/O node, and the radio buttons are mapped to the valve outputs purely parametrically. This enables extremely fast commissioning and easy adaptation to customer requirements (e.g., changing button assignments).