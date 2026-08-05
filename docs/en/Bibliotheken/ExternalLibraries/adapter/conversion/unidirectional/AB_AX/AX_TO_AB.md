# AX_TO_AB
![AX_TO_AB](./AX_TO_AB.svg)

* * * * * * * * * *
## Introduction
The composite function block `AX_TO_AB` converts a BOOL adapter signal of type `AX` into a BYTE adapter signal of type `AB`. It encapsulates the type conversion and event passing in a reusable unit.
## Interface Structure

### **Event Inputs**

| Name | Description |
|------|--------------|
| `E1` (from `AX_IN`) | Event input received via the BOOL adapter and passed on unchanged to the output. |

### **Event Outputs**

| Name | Description |
|------|--------------|
| `E1` (from `AB_OUT`) | Event output that provides the event passed through from the input. |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|---------------|
| `D1` (from `AX_IN`) | `BOOL` | The Boolean signal to be converted (TRUE or FALSE). |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|---------------|
| `D1` (from `AB_OUT`) | `BYTE` | The converted signal: `TRUE` becomes `1`, `FALSE` becomes `0`. |

### **Adapter**

| Type | Direction | Identifier | Comment |
|-----|----------|------------|-----------|
| `adapter::types::unidirectional::AX` | Socket (Input) | `AX_IN` | BOOL adapter that provides the input data and events. |
| `adapter::types::unidirectional::AB` | Plug (Output) | `AB_OUT` | BYTE adapter that outputs the converted data and events. |

## Functionality

Internally, the function block consists only of connections that route the event and data from the socket `AX_IN` to the plug `AB_OUT`.

- The event `E1` is passed on without delay or modification.
- The data value `D1` is converted from type `BOOL` to type `BYTE`. The Boolean value `TRUE` is converted to the byte `1`, and `FALSE` is converted to the byte `0`. This conversion is performed implicitly by the 4diac runtime environment.

Since this is a composite function block, all internal connections are defined at design time; there is no dynamic logic or state machines.

## Technical Features

- **Composite Type**: The function block is a pure network function block without its own algorithms. Conversion is achieved by connecting two different adapter types.
- **Type Conversion**: The conversion from `BOOL` to `BYTE` is standards-compliant and uses the implicit cast function of the 4diac IDE. This eliminates the need for a separate conversion function block.
- **Versioning**: The function block is version `1.0` dated February 17, 2026, and is intended for use in the package `adapter::conversion::unidirectional`.

## State Overview

The function block has no internal states – it operates purely combinatorially. The output values are a direct function of the input values at any given time.

## Application Scenarios
- **Connecting Sensors/Actuators**: If a device or controller operates as a BOOL signal, but the target system expects a BYTE adapter format, `AX_TO_AB` can be used as an intermediary.
- **Adapter Bridges**: In heterogeneous automation networks where different adapter protocols are used, the function block (FB) allows for a simple and type-safe connection.
- **Testing and Simulation**: The FB can be used as a simple converter in test environments to translate signals between different logic layers.

## Comparison with Similar Function Blocks

Special conversion FBs exist, such as `BOOL_TO_BYTE` or `BYTE_TO_BOOL`, but these are usually implemented as basic function blocks (FBs) with an algorithm. In contrast, `AX_TO_AB` is a composite function block at the adapter level and encapsulates all communication (events and data). It is useful when entire adapter interfaces need to be implemented, not just individual data points.

## Conclusion

The composite function block `AX_TO_AB` offers a compact and elegant solution for converting a BOOL adapter to a BYTE adapter. Through implicit type conversion and direct event forwarding, it reduces manual adjustments and increases reusability in modular automation projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
