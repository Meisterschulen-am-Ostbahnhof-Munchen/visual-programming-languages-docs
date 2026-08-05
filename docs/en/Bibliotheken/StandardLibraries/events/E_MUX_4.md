# E_MUX_4

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## Introduction
The `E_MUX_4` (Event Multiplexer) is a function block according to IEC 61499 that combines four event inputs (`EI1` to `EI4`) into a single event output (`EO`). In addition to combining the inputs, the block outputs a data output, `K`, indicating which input triggered the event. It is the counterpart to the `E_DEMUX_4`.

![E_MUX_4](E_MUX_4.svg)

## Interface Structure

### **Event Inputs:**

- **EI1**: First input channel. - **EI2**: Second input channel.

- **EI3**: Third input channel.

- **EI4**: Fourth input channel.

### **Event Outputs:**

- **EO (Event Output)**: The common event output.

- **Associated Data**: `K`

### **Data Outputs:**

- **K**: The index of the triggering input channel (data type: `UINT`).

- `K = 0` if `EI1` was triggered.

- `K = 1` if `EI2` was triggered.

- `K = 2` when `EI3` is triggered.

- `K = 3` when `EI4` is triggered.

## Functionality

1. **Event Receipt**: The function block waits for an event at one of its four inputs.

2. **Forwarding and Identification**: When an event arrives at `EIn` (where `n` represents 1 to 4), the data output `K` is set to `n-1`, and the `EO` event is immediately triggered.


In this way, the event flow is merged while preserving information about the event's origin.

## Technical Features
- **4-to-1 Multiplexer**: Merges four event streams into one.

- **Origin Index**: Indicates which input triggered the event.

- **Stateless**: The function block has no internal memory.

- **Generic Function Block**: The functionality is provided by the generic class `GEN_E_MUX`.

## Application Scenarios

- **Command Grouping**: Four different buttons trigger the same process, but the process needs to know which of the four buttons was pressed.

- **Combined Alarms**: Four different alarms are routed to a central alarm routine, which then displays the specific alarm text based on `K`.

- **Mode Selection**: Combines the startup events from four different operating modes.

## 🛠️ Related Exercises

* [Exercise_087a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a2.md)

## Conclusion
The `E_MUX_4` is a useful component for bundling event streams from up to four sources while simultaneously identifying the event's source. It is the standard counterpart to the `E_DEMUX_4` and is frequently used to reduce wiring complexity and centralize logic.