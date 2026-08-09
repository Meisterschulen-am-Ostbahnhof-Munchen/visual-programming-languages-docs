# AX_TO_OFF

![AX_TO_AUS](./AX_TO_AUS.svg)

* * * * * * * * * *
## Introduction

The **AX_TO_OFF** function block is a composite function block that converts a Boolean input adapter (type `AX`) into an integer output adapter (type `AUS`). It serves as a bridge between components that operate with different data types and enables seamless integration into control applications according to IEC 61499.
## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs; however, the incoming adapter `AX_IN` provides the event `E1`. This triggers the conversion.

### **Event Outputs**

There are no direct event outputs here either. The outgoing adapter `AUS_OUT` provides the event `E1`, which is triggered after successful conversion.

### **Data Inputs**

Data is received via the adapter `AX_IN` as a Boolean value (`D1` of type `BOOL`).

### **Data Outputs**

The converted value is output via the adapter `AUS_OUT` as an unsigned 8-bit integer (`D1` of type `USINT`).

### **Adapter**

| Direction | Name | Type | Description |
|----------|----------|-------------------------------|-----------------------------|
| Socket | `AX_IN` | `adapter::types::unidirectional::AX` | Boolean Input Adapter |
| Plug | `AUS_OUT`| `adapter::types::unidirectional::AUS` | USINT Output Adapter |

## Functionality

Internally, the function block uses the predefined conversion function block `iec61131::conversion::F_BOOL_TO_USINT`. The process is as follows:

1. An incoming event at the adapter `AX_IN.E1` triggers the internal function block via its input `REQ`.
2. The Boolean value of `AX_IN.D1` is forwarded to the input `IN` of the internal function block.
3. The internal function block converts the value of `BOOL` into a value of `USINT` (`false` → 0, `true` → 1) and places it at its output `OUT`.
4. The confirmation event `CNF` of the internal function block is forwarded to the adapter output `AUS_OUT.E1`.
5. The converted value from output `OUT` is transferred to the data output `AUS_OUT.D1`.

## Technical Features

- **Composite Function Block**: The function block encapsulates the conversion logic and provides a clean, reusable interface via adapters.
- **Plug/Socket Coupling**: The function block uses the adapter pattern (socket for input, plug for output), enabling flexible connectivity in an IEC 61499 application.
- **Dependency**: It imports the function block `iec61131::conversion::F_BOOL_TO_USINT`, which is part of the IEC 61131 conversion library.

## State Overview

The function block does not have its own state machine. All functionality is implemented by the internal `F_BOOL_TO_USINT` function block, which operates in an event-driven manner and does not store internal states.

## Application Scenarios

- **Signal Adaptation**: When a sensor or a Boolean adapter (e.g., switch, limit switch) needs to be connected to a component that expects an integer adapter.
- **Protocol Conversion**: In heterogeneous systems that use different data formats, this function block can serve as a simple converter.
- **Test and Simulation Environments**: To convert Boolean values into numerical values that can be more easily processed by analysis tools.

## Comparison with Similar Function Blocks

Numerous conversion blocks exist in the IEC 61499 library, such as `F_BOOL_TO_INT`, `F_BOOL_TO_WORD`, and `F_BOOL_TO_BYTE`. The difference with `AX_TO_AUS` lies in the adapter interface: This block encapsulates the conversion not only at the data level but also at the event level in a compact adapter pair. Other blocks typically work with simple input/output data and require additional event wiring.

## Conclusion

The **AX_TO_AUS** function block is a practical tool for converting Boolean adapter signals to the USINT format. By using adapters, it integrates seamlessly into the event-driven architecture according to IEC 61499 and significantly reduces wiring effort. It is particularly suitable for applications where a clean separation between the Boolean and numeric domains is desired.
