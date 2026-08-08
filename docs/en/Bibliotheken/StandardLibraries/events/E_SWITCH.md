# E_SWITCH
## 🎧 Podcast
![E_SWITCH_ecc](./E_SWITCH_ecc.svg)

* [E_SWITCH: The Switch of Automation – Why Simplicity Revolutionizes IEC 61499 ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_SWITCH-Die-Weiche-der-Automatisierung--Warum-Einfachheit-IEC-61499-revolutioniert-e3681fl)
* [E_SWITCH: The Unsung Hero of Industrial Automation's Modular Design ](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/E_SWITCH-The-Unsung-Hero-of-Industrial-Automations-Modular-Design-e367npq)
The `E_SWITCH` (Event Switch) is a basic function block according to IEC 61499 that functions as a conditional event switch or 1-to-2 demultiplexer. It forwards a single input event (`EI`) to one of two outputs based on the state of a Boolean control variable (`G`).

`` ![E_SWITCH](E_SWITCH.svg)


- **EI (Event Input)**: The input event to be forwarded.
- **Associated Data**: `G`

- **EO0**: The first event output.
- **EO1**: The second event output.

- **G (Guard)**: The Boolean condition that controls the switch (data type: `BOOL`).

### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
## Functionality

1. **Event Reception**: The function block waits for an event at input `EI`.


3. **Conditional Forwarding**:

- **If `G` = `FALSE`**: The event is forwarded to output `EO0`.
- **If `G` = `TRUE`**: The event is forwarded to output `EO1`.

The event at input `EI` is always routed to exactly one of the two outputs, depending on the control condition `G`.

- **Event Switch**: Serves as a fundamental "switch" or "if-else" construct for the event flow.
- **Stateless**: The block itself has no internal memory; its decision is based solely on the value of `G` at the moment of the `EI` event.

- **Conditional Logic**: Execution of alternative actions based on a condition. If `G` is true, execute action A (`EO1`); otherwise, execute action B (`EO0`).
- **Mode-Dependent Processing**: Route commands to different processing paths depending on whether the system is in "Automatic" mode (`G=TRUE`) or "Manual" mode (`G=FALSE`).
- **Error Handling**: Route a sensor event either to the normal processing logic (`G=FALSE` for "no error") or to an error handling routine (`G=TRUE` for "error detected").


| Feature | E_SWITCH | E_SELECT | E_DEMUX |
|---------------|----------|----------|----------|
| Selection Criterion | Boolean (`G`) | Boolean (`G`) | Index (`K`) |
| Direction | 1:2 (Demultiplexer) | 2:1 (Multiplexer) | 1:n (Demultiplexer) |
| State Model | BasicFB | BasicFB | BasicFB/Generic |

* [Uebung_004b](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b.md)
* [Uebung_004b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b2.md)
* [Uebung_004b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b3.md)
* [Uebung_005](../../../Uebungen/test_B/Uebungen_doc/Uebung_005.md)
* [Uebung_006a3_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3_sub.md)
* [Uebung_007a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_008](../../../Uebungen/test_B/Uebungen_doc/Uebung_008.md)
* [Uebung_009](../../../Uebungen/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_019c](../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
* [Uebung_020a](../../../Uebungen/test_B/Uebungen_doc/Uebung_020a.md)
* [Uebung_020b](../../../Uebungen/test_B/Uebungen_doc/Uebung_020b.md)
* [Uebung_020c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
* [Uebung_020d](../../../Uebungen/test_B/Uebungen_doc/Uebung_020d.md)
* [Uebung_020e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e2.md)
* [Uebung_020f2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
* [Uebung_020i](../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
* [Uebung_025](../../../Uebungen/test_B/Uebungen_doc/Uebung_025.md)
* [Uebung_026_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_026_sub.md)
* [Exercise_039a_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)
* [Exercise_086](../../../Uebungen/test_B/Uebungen_doc/Uebung_086.md)
* [Exercise_088](../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)
* [Exercise_089](../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)

The `E_SWITCH` block is a fundamental and widely used block for implementing conditional branching in the event-driven logic of IEC 61499. Its simplicity and clear function as an "if-else" switch for events make it an indispensable tool for creating flexible and robust control software.

## Technical Features
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## 🛠️ Zugehörige Übungen
## Conclusion