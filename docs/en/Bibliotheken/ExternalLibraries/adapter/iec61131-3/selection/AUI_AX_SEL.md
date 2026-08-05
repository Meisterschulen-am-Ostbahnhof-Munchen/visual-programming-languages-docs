# AUI_AX_SEL

![AUI_AX_SEL](./AUI_AX_SEL.svg)

* * * * * * * * * *

## Introduction
The AUI_AX_SEL is a binary selection block controlled via an adapter connection. It selects between two data input values (IN0 and IN1) based on a selection signal and outputs the selected value at the data output OUT. Processing is event-driven via the adapter.

## Interface Structure
### **Event Inputs**
- **EI0** (Event): Sets the data input IN0. The data value IN0 is updated upon this event.

- **EI1** (Event): Sets the data input IN1.

### **Event Outputs**

- **CNF** (Event): Confirmation that the selection has been made and the output OUT has been updated.


### **Data Inputs**

- **IN0** (UINT): First selectable input value.

- **IN1** (UINT): Second selectable input value.

### **Data Outputs**

- **OUT** (UINT): Selected value – either IN0 or IN1, depending on the selection signal.

### **Adapter**

- **G** (AX): Adapter connection for selection control. It provides an event (E1) and a data signal (D1) that serves as the selection criterion. Typically, D1 is a BOOL value: 0 selects IN0, 1 selects IN1.

## Functionality
The function block has two event inputs, EI0 and EI1, which independently set the data inputs IN0 and IN1. However, the actual selection is not triggered by these events. Instead, the event (G.E1) received from adapter G triggers the internal processing. Each time an event occurs at the adapter, the internal function block F_SEL (IEC 61131) is activated. Based on the adapter data signal (G.D1), it determines whether OUT receives the value from IN0 or IN1. After successful calculation, the output event CNF is sent.

## Technical Features

- **Adapter-Based Control:** The selection condition is not implemented via a separate data input, but rather via an adapter. This allows for flexible coupling with other function blocks that support the AX protocol.

- **Asynchronous Update:** Inputs IN0 and IN1 can be updated independently of the selection. The selection only occurs upon arrival of the adapter event, ensuring that the values are current at the time of processing.

- **No Internal State:** The function block does not store any states other than the current values of the inputs.

## State Overview
The AUI_AX_SEL does not have an explicit state machine. The functionality is purely event-driven and combinatorial: The output is recalculated with each adapter event.

## Application Scenarios

- **Sensor Data Switching:** Selection between two different sensor readings, controlled by an external switching signal (e.g., from a PLC).

- **Parameter Selection:** Dynamic selection between two configuration values (e.g., setpoints) depending on an operating mode.

- **Redundancy Switching:** Automatic switching to a backup value if a signal fails (in combination with appropriate monitoring blocks).

## Comparison with Similar Blocks
Compared to a standard multiplexer (e.g., MUX), AUI_AX_SEL offers an event-driven interface with an adapter connection. While MUX often has a direct selection input (BOOL), AUI_AX_SEL allows loose coupling via adapters, which increases reusability and modularity. The internal F_SEL function block conforms to the IEC 61131 logic for binary selection.

## Conclusion
The AUI_AX_SEL is a useful function block for binary selection tasks in IEC 61499 environments, enabling flexible integration through its adapter interface. It is particularly suitable for scenarios where the selection signal is provided by external components and asynchronous input updates are desired.