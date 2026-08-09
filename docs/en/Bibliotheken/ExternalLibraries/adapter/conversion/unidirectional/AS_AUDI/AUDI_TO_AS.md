# AUDI_TO_AS

![AUDI_TO_AS](./AUDI_TO_AS.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_TO_AS** is a composite block that converts an AUDI adapter (data type `UDINT`) into an AS adapter (data type `SINT`). It serves as a bridge between two different adapter interfaces and enables the lossy conversion of an unsigned 32-bit value into a signed 8-bit value. The conversion is event-driven using the internal conversion function `F_UDINT_TO_SINT`.
## Interface Structure

### **Event Inputs**

The function block does not have its own dedicated event inputs. Event control is handled via the **socket adapter `AUDI_IN`**, which provides an event `E1`.

### **Event Outputs**

The function block (FB) does not have its own independent event outputs. The result event is output via the **plug adapter `AS_OUT`** using the event `E1`.

### **Data Inputs**

Data inputs are available exclusively via the **socket adapter `AUDI_IN`**:

- **`D1`** (data type `UDINT`): The 32-bit value to be converted.

### **Data Outputs**

Data outputs are provided via the **`AS_OUT`** plug adapter:

- **`D1`** (data type `SINT`): The converted 8-bit value (value range -128…127).

> Note: A `UDINT` value greater than 127 is either truncated or interpreted during conversion (depending on the implementation of `F_UDINT_TO_SINT`).

### **Adapter**

| Name | Type | Direction | Description |
|-----------|-------------------------------------------|----------|----------------------------------|
| `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Socket | Input adapter (UDINT) |
| `AS_OUT` | `adapter::types::unidirectional::AS` | Plug | Output adapter (SINT) |

## Functionality

This function block acts as a transparent conversion stage between two unidirectional adapters. An incoming event on `AUDI_IN.E1` triggers the internal function block `F_UDINT_TO_SINT`, which converts the `UDINT` value at `AUDI_IN.D1` into a `SINT` value. After the conversion is complete, an event is output to `AS_OUT.E1`, and the converted value is made available to `AS_OUT.D1`.

The internal process is purely causal and requires no separate states or timings – the response occurs immediately after the input event.

## Technical Features

- **Adapter-based interface**: The function block communicates exclusively via special adapters, enabling loose coupling and reusability in different environments.
- **Data loss possible**: Since `SINT` only contains 8 bits, over 127 bits of information are lost with a `UDINT` input value. The exact mapping (e.g., clipping or modular reduction) depends on the internal conversion function.
- **No Internal Logic**: The function block consists entirely of the interconnection of the existing conversion function block and two adapters – a pure composition type.

## State Overview

The function block does not have its own state machine. It behaves statelessly: Each incoming event at the socket triggers exactly one output at the plug. Processing is deterministic and event-synchronous.

## Application Scenarios

- **Protocol Adaptation**: When a subsystem delivers data as `UDINT` via an AUDI adapter, but the target system only accepts `SINT` via an AS adapter (e.g., with 8-bit actuator controllers).
- **Value Range Reduction**: Explicitly restricting a large number range to a smaller one to ensure compatibility with older or resource-constrained components.
- **Testing and Simulation**: Use in test environments where adapter interfaces of different data types interact.

## Comparison with similar function blocks

- **`UDINT_TO_SINT` (direct)**: The pure conversion function block without adapter integration. `AUDI_TO_AS` encapsulates this function block and adds the specific adapters.
- Other adapter converters (e.g., `DINT_TO_AS`, `AUDI_TO_INT`) handle different data type combinations. This function block is specifically optimized for the combination `AUDI` ↔ `AS`.

## Conclusion

The composite function block `AUDI_TO_AS` provides a simple yet effective way to convert a `UDINT`-based adapter to a `SINT`-based adapter. Thanks to its clear event control and the use of a proven conversion function, it is suitable for all scenarios where lossy data type conversion between these two adapter standards is required.
