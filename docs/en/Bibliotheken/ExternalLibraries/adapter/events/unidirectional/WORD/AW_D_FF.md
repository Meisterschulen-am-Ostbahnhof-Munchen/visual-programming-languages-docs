# AW_D_FF

![AW_D_FF](./AW_D_FF.svg)

* * * * * * * * * *
## Introduction

The function block **AW_D_FF** implements a data-controlled flip-flop (D-latch) according to IEC 61499. It accepts a binary data value at its input and outputs it in a clock-controlled manner. The interface is exclusively via adapters, which enables modular and flexible integration into existing components.
## Interface Structure

### **Event Inputs**

No direct event inputs at the FB level. Event control is handled via the input adapter **I**.

### **Event Outputs**

No direct event outputs at the FB level. Event output is handled via the output adapter **Q**.

### **Data Inputs**

No direct data inputs at the FB level. Data is transferred via the input adapter **I**.

### **Data Outputs**

No direct data outputs at the FB level. Data output is via the output adapter **Q**.

### **Adapters**

| Adapter | Type | Description |
|---------|-----|--------------|
| **I** (Socket) | `adapter::types::unidirectional::AW` | Input adapter – receives the data to be latched (D1) and the clock signal (E1). |
| **Q** (Plug) | `adapter::types::unidirectional::AW` | Output adapter – outputs the latched data (D1) and an acknowledgment event (E1). |

Both adapters are of the same unidirectional type and each encapsulates one event and one data value.

## Functionality

The component internally uses the IEC 61499 standard component `E_D_FF_ANY`.

On a rising edge of the clock signal (event `E1` at adapter **I**), the current data value (`D1`) is taken and made available at the output. The output value remains until a new rising clock edge takes over a new value.

The logic table (D flip-flop) is as follows:

| Clock (E1) | Input D | Output Q (after clock) |
|-----------|-----------|----------------------|
| ↑ | 0 | 0 |
| ↑ | 1 | 1 |
| otherwise | arbitrary | unchanged |

## Technical Features

- **Adapter-Based Interface**: The function block uses adapters exclusively for communication, enabling loose coupling and easy reuse in various contexts.
- **Standard Compliance**: Developed according to IEC 61499-1 Annex A and licensed under the Eclipse Public License 2.0 (EPL-2.0).
- **Internal Implementation**: Utilizes the predefined function block `E_D_FF_ANY`, which provides a general-purpose D flip-flop.
- **Unidirectional Data Flow**: The adapters are designed to be unidirectional, meaning that data and event flow is defined in only one direction.

## State Overview

A D flip-flop has two stable states for the output Q (logic 0 or 1). The state change occurs exclusively on a rising edge of the clock signal:

- **State 0**: Output Q = 0 (as long as no clock signal with D=1 arrives)
- **State 1**: Output Q = 1 (after a clock signal with D=1, until a clock signal with D=0 arrives)

There is no other internal state machine; the functionality is purely storage-based.

## Application Scenarios

- **Synchronization of Asynchronous Signals**: A stable data value is acquired at a defined time (clock signal).
- **State Register**: As a 1-bit memory in simple control logic circuits.
- **Data Buffer**: Short-term storage of a binary value for subsequent processing steps.
- **Clock-Controlled Threshold Decisions**: An input value is considered valid only on a clock edge.

## Comparison with Similar Components

| Component | Property | Difference to AW_D_FF |
|----------|-------------|------------------------|
| **RS Flip-Flop** | Sets/resets asynchronously | AW_D_FF requires a clock signal, no separate set/reset inputs. |
| **T Flip-Flop** | Toggles on clock signal | AW_D_FF takes the value from D, no toggle function. |
| **JK Flip-Flop** | Universal (Set, Reset, Toggle) | AW_D_FF is simpler (only D input), no toggle mode. |
| **E_D_FF_ANY** | Directly usable with events/data | AW_D_FF encapsulates this function block and provides an adapter interface. |

## Conclusion

The **AW_D_FF** is a compact and standards-compliant D flip-flop device that, thanks to its adapter interface, is particularly flexible for use in modular IEC 61499 applications. It offers reliable clock-controlled data acquisition and is ideally suited for synchronized memory operations in industrial control systems.
