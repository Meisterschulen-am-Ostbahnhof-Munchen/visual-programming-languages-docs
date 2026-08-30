# AB_D_FF

No image available.
![AB_D_FF](./AB_D_FF.svg)

* * * * * * * * * *

## Introduction

The function block **AB_D_FF** implements an asynchronous data latch (D flip-flop) based on an adapter concept according to IEC 61499. It receives a data value via the input adapter **I** as soon as an event occurs and outputs this value via the output adapter **Q**. The internal state of the flip-flop is represented by a standardized `E_D_FF_ANY` function block.

## Interface Structure

### **Event Inputs**

- **I.E1** (via adapter `I`): Initiates the data value acquisition.

### **Event Outputs**

- **Q.E1** (via adapter `Q`): Signals the output of the latched data value.

### **Data Inputs**

- **I.D1** (via adapter `I`): The data value to be latched (any type, depending on the adapter type used, `adapter::types::unidirectional::AB`).

### **Data Outputs**

- **Q.D1** (via adapter `Q`): The latched and output data value.

### **Adapters**

- **I** (Socket): Input adapter of type `adapter::types::unidirectional::AB` – receives the value to be latched and the control event.
- **Q** (Plug): Output adapter of the same type – outputs the stored value and the associated event.

## Functionality

The function block operates in an event-driven manner:

1. As soon as an event arrives at the input adapter **I.E1**, the current value at the data input **I.D1** is transferred to the internal D flip-flop (`E_D_FF_ANY`).
2. Subsequently, the stored value is output at **Q.D1**, and an event is simultaneously generated at the output **Q.E1**.

Thus, the component behaves like a classic edge-triggered D latch, where the transfer and output occur synchronously with the input event.

## Technical Features

- **Adapter Interface**: The component uses only adapters (`adapter::types::unidirectional::AB`) for input and output, which allows for flexible typing and loose coupling with other components.
- **Internal Implementation**: The latching core is implemented using the standardized function block `E_D_FF_ANY` from the IEC 61499 library `iec61499::events`. This stores the data value and generates the output event.
- **Event and data paths** are strictly separated: The event triggers the data transfer; data flows independently.

## State Overview

The function block does not have an explicit internal state machine but relies on the implicit state of the embedded `E_D_FF_ANY`:

- **Idle**: Waiting for an event on `I.E1`.
- **Latching**: After receiving the event, the data value is transferred and output.
- The internally stored value is retained until the next event.

## Application Scenarios

- **Data Synchronization**: Reliable transfer of measured values or control data at defined times (e.g., clock pulse).
- **Buffering**: Intermediate storage of values in sequence control systems between different function blocks.
- **Register Creation**: Construction of shift registers or memory cells in modular automation systems.

## Comparison with Similar Function Blocks

| Function Block | Description |
| ---------- | -------------- |
| **AB_SR_FF** | Set-Reset Flip-Flop, stores two states (Set/Reset) without a data value. |
| **AB_T_FF** | Toggle Flip-Flop, changes the output state with each event. |
| **E_D_FF** | Standard D Flip-Flop without an adapter interface, direct event and data pins. |

The **AB_D_FF** offers type-safe and reusable encapsulation through its adapter interface, whereas comparable devices often rely on fixed data types.

## Conclusion

The **AB_D_FF** is a compact and flexible D-latch device that leverages the advantages of the IEC 61499 architecture. Its adapter interface allows it to be used in a wide variety of contexts without being restricted to a specific data type. Together with the internal standard flip-flop, it ensures reliable and event-driven data storage.
