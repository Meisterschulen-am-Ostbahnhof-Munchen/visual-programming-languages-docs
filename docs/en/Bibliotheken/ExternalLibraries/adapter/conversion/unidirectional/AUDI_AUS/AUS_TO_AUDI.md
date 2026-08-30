# AUS_TO_AUDI

![AUS_TO_AUDI](./AUS_TO_AUDI.svg)

* * * * * * * * * *

## Introduction

The composite function block **AUS_TO_AUDI** converts a unidirectional adapter of type **AUS** (based on USINT values) into an adapter of type **AUDI** (based on UDINT values). It is used to translate data between two different adapter interfaces without altering the underlying data logic. The block is implemented as a pure pass-through component, forwarding events and data directly from the input to the output side.

## Interface Structure

### **Event Inputs**

The block does not have its own event inputs. Events are provided via the connected **Socket Adapter** `AUS_IN`.

### **Event Outputs**

This function block does not have its own event outputs. Events are passed on via the connected **Plug Adapter** `AUDI_OUT`.

### **Data Inputs**

This function block does not have its own data inputs. Data is received via the **Socket Adapter** `AUS_IN`.

### **Data Outputs**

This function block does not have its own data outputs. Data is output via the **Plug Adapter** `AUDI_OUT`.

### **Adapters**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AUS` | `AUS_IN` | Socket (Input) | Unidirectional adapter that provides data in USINT format (8 bits) and an event. |
| `adapter::types::unidirectional::AUDI` | `AUDI_OUT` | Plug (Output) | Unidirectional adapter that expects data in UDINT format (32 bits) and an event. |

The internal network structure connects the event `E1` and the data value `D1` of the input adapter directly to the corresponding interfaces of the output adapter.

## Functionality

This functional block operates as a simple pass-through. As soon as the event `E1` occurs at socket `AUS_IN`, it is immediately forwarded to plug `AUDI_OUT` as the event `E1`. Simultaneously, the data value `D1` (USINT) of the input adapter is transferred to the data value `D1` (UDINT) of the output adapter. A type conversion from USINT to UDINT occurs implicitly through the data connection (expansion from 8 bits to 32 bits). No validation or range check is performed.

## Technical Features

- **Adapter-Based Interface**: The function block does not have traditional input/output variables, but uses only the standardized adapter types `AUS` and `AUDI` from the `adapter::types::unidirectional` package.
- **Simple Passthrough**: Event and data connections are implemented directly without additional logic.
- **Type Expansion**: Conversion from USINT (0–255) to UDINT (0–4294967295) is lossless, as the entire USINT value range can be mapped to the UDINT range.
- **No State Storage**: The function block is stateless; all processing occurs in the same execution instance.

## State Overview

The function block does not have an internal state machine. The functionality is limited to a direct 1:1 connection between the input and output adapters. A state description is therefore not required.

## Application Scenarios

- **Adapter Bridge**: Used in systems that utilize the AUS adapter (e.g., for simple byte values) but expect an AUDI interface (e.g., for 32-bit counters or addresses).
- **Protocol Conversion**: Used within composite function blocks to mediate between different adapter versions within a device family.
- **Data Preparation**: Prepares USINT data for function blocks that accept only UDINT inputs.

## Comparison with Similar Function Blocks

- **INT_TO_DINT**: A standard function block for converting INTEGER types, but with independent input/output variables. `AUS_TO_AUDI`, on the other hand, operates at the adapter level and is optimized for integration into adapter-based architectures.
- **AUS_TO_AUDI (simple)**: Alternative implementations could include additional overflow checks or filter functions; this function block is limited to simple pass-through.

## Conclusion

AUS_TO_AUDI` is a compact, specialized composite function block for lossless conversion between the unidirectional adapters OFF (USINT) and AUDI (UDINT). Thanks to the direct pass-through of events and data without additional logic, it is ideally suited as a building block in adapter-based control networks where simple type conversion at the communication layer is required.
