# AUS_TO_AS

![AUS_TO_AS](./AUS_TO_AS.svg)

* * * * * * * * * *
## Introduction

The function block **AUS_TO_AS** is a composite function block (FB) for converting a unidirectional OFF adapter (based on the USINT data type) into a unidirectional AS adapter (based on the SINT data type). It serves as a standardized interface between components that use different unsigned/signed integer types.
## Interface Structure

The FB has no direct event or data inputs/outputs, but only two adapter interfaces:

### **Event Inputs**

No directly visible event inputs. Event control is handled via the socket adapter `AUS_IN`.

### **Event Outputs**

No directly visible event outputs. Event feedback is provided via the plug adapter `AS_OUT`.

### **Data Inputs**

No directly visible data inputs. The data is provided via the socket adapter `AUS_IN`.

### **Data Outputs**

No directly visible data outputs. The data is output via the plug adapter `AS_OUT`.

### **Adapters**

| Name | Type | Direction | Comment |
|----------|-----------------------------------------------|----------|------------------------------|
| `AUS_IN` | `adapter::types::unidirectional::AUS` (Socket) | Input | USINT Adapter Input |
| `AS_OUT` | `adapter::types::unidirectional::AS` (Plug) | Output | SINT Adapter Output |

The interface of the adapters themselves contains:

- `AUS_IN.E1` (Event), `AUS_IN.D1` (USINT)
- `AS_OUT.E1` (Event), `AS_OUT.D1` (SINT)

## Functionality

The function block is implemented as a composite and contains an internal function block `Convert` of type `iec61131::conversion::F_USINT_TO_SINT`, which performs the actual value conversion.

1. **Data Acquisition:** An incoming USINT value is provided via socket `AUS_IN.D1`.
2. **Triggering:** An event at output `AUS_IN.E1` triggers input `REQ` of the conversion block.
3. **Conversion:** The internal function block `F_USINT_TO_SINT` converts the USINT value into a corresponding SINT value (value range 0..255 → -128..127; if this range is exceeded, a range limitation according to IEC 61131 applies).
4. **Feedback:** After the conversion is complete, the internal function block signals an event to plug `AS_OUT.E1` via its output `CNF`.
5. **Data Transfer:** The converted SINT value is output to the connected plug via `AS_OUT.D1`.

The connections in the FBNetwork are:

- Event: `AUS_IN.E1` → `Convert.REQ`
- Event: `Convert.CNF` → `AS_OUT.E1`
- Data: `AUS_IN.D1` → `Convert.IN`
- Data: `Convert.OUT` → `AS_OUT.D1`

## Technical Features

- **Adapter-Based:** The module functions as a pure adapter converter and can be seamlessly integrated into existing adapter-oriented systems.
- Event: `AUS_IN.D1` → `Convert.IN`
- Data: `Convert.OUT` → `AS_OUT.D1`
- **Adapter-Based:** The module functions as a pure adapter converter and can be seamlessly integrated into existing adapter-oriented systems.
- Event: `AUS_IN.E1` → `Convert.IN`
- Event: `Convert.OUT` → `AS_OUT.D1`
- **Adapter-Based:** - **Composite Structure:** Conversion is performed by an internal, standardized IEC 61131 converter, ensuring reliable and certified conversion.
- **Unidirectional Interface:** Data and event flows are strictly unidirectional (from input to output).
- **No Explicit State Machine:** Control is purely event-driven via adapter events. There are no internal states.

## State Overview

The function block (FB) has no visible state machine. It behaves like a transparent gateway that triggers the conversion upon each input event and provides the result at the output.

## Application Scenarios

- **Integration of components** with different data types, e.g., when a sensor delivers USINT data, but a subsequent controller expects SINT values.
- **Adapter Conversion** in modular control systems based on unidirectional adapters (e.g., according to IEC 61499).
- **Safety-critical systems** where precise type conversion (without overflow) is essential – the internal function block `F_USINT_TO_SINT` is specification-compliant.

## Comparison with similar function blocks

- **Simple converters like `F_USINT_TO_SINT`:** Only convert scalar values but do not use adapters. `AUS_TO_AS` encapsulates this conversion in an adapter-based function block.
- **`INT_TO_DINT` adapter:** Other type conversions (e.g., INT to DINT) follow the same pattern but differ in bit width and sign handling.
- **Bidirectional adapters:** Unlike bidirectional variants, this function block is designed for only one data flow, which reduces complexity.

## Conclusion

The **AUS_TO_AS** function block offers a clean, adapter-based solution for converting USINT to SINT values. Thanks to its composite structure and the use of a standardized IEC 61131 converter, it is easy to maintain, reliable, and readily integrated into industrial control networks. It is particularly suitable for systems that rely on unidirectional adapters and require explicit type conversion.
