# E_MUX_2

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction

The `E_MUX_2` (Event Multiplexer) is a function block according to IEC 61499 that combines two event inputs (`EI1`, `EI2`) into a single event output (`EO`). In addition to combining the inputs, the block outputs a data output, `K`, indicating which input triggered the event. It is the counterpart to the `E_DEMUX_2`.
![E_MUX_2](E_MUX_2.svg)

## Interface Structure

### **Event Inputs:**

- **EI1**: First input channel. - **EI2**: Second input channel.

### **Event Outputs:**

- **EO (Event Output)**: The common event output.
- **Associated Data**: `K`

### **Data Outputs:**

- **K**: The index of the triggering input channel (data type: `UINT`).
- `K = 0` if `EI1` was triggered.
- `K = 1` if `EI2` was triggered.

## Functionality

1. **Event Receipt**: The function block waits for an event at one of its inputs (`EI1` or `EI2`).
2. **Forwarding and Identification**:
- When an event arrives at `EI1`, the data output `K` is set to `0`, and the `EO` event is immediately triggered.
- When an event arrives at `EI2`, the data output `K` is set to `1`, and the `EO` event is immediately triggered.

In this way, the event flow is merged while preserving information about the event's origin.

## Technical Features

- **2-to-1 Multiplexer**: Merges two event streams into one.
- **Origin Index**: Indicates which input triggered the event.
- **Stateless**: The function block has no internal memory.
- **Generic Function Block**: The functionality is provided by the generic class `GEN_E_MUX`.

## Application Scenarios

- **Command Combining**: Two different buttons (e.g., "Start Forward" and "Start Reverse") trigger the same process, but the process needs to know which button was pressed.
- **Combined Alarms**: Two different alarms are routed to a central alarm routine, which then displays the specific alarm text based on `K`.
- **Simplified Logic**: Instead of having two separate paths for similar logic, the triggering events are merged, and the index `K` is used as a parameter for subsequent logic.

## 🛠️ Related Exercises

* [Exercise_172](../../../Uebungen/test_B/Uebungen_doc/Uebung_172.md)]

## Conclusion

The `E_MUX_2` is a useful component for bundling event streams while simultaneously identifying the event source. It is the standard counterpart to `E_DEMUX_2` and is frequently used to reduce wiring complexity and centralize logic.
