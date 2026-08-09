# AB_TO_AI

![AB_TO_AI](./AB_TO_AI.svg)

* * * * * * * * * *
## Introduction

The **AB_TO_AI** is a composite function block for converting an **AB adapter (BYTE)** to an **AI adapter (INT)**. It enables the seamless integration of BYTE-based adapter interfaces into systems that expect INT values. Internally, the block uses the IEC 61131 conversion block `F_BYTE_TO_INT`.
## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. The event is provided via the connected adapter **AB_IN** (socket):

- **AB_IN.E1** – Event that triggers the conversion of an incoming BYTE value.

### **Event Outputs**

The FB has no direct event outputs. The output event is sent via the connected adapter **AI_OUT** (Plug):

- **AI_OUT.E1** – Event indicating that the converted INT value is present at the output.

### **Data Inputs**

The FB has no direct data inputs. The input value is provided via the adapter **AB_IN** (Socket):

- **AB_IN.D1** – BYTE value (0…255) to be converted into an INT value.

### **Data Outputs**

The FB has no direct data outputs. The output value is provided via the adapter **AI_OUT** (Plug):

- **AI_OUT.D1** – INT value representing the converted BYTE.

### **Adapters**

| Name | Type | Direction | Description |
|-------------|-----|----------|--------------|
| **AB_IN** | `adapter::types::unidirectional::AB` | Socket (Input) | BYTE adapter that provides the value to be converted and the start event. |
| **AI_OUT** | `adapter::types::unidirectional::AI` | Plug (Output) | INT adapter that provides the converted value and the confirmation event. |

## Functionality

1. An incoming event on **AB_IN.E1** triggers the processing.
2. The BYTE value provided by **AB_IN.D1** is passed to the internal block `F_BYTE_TO_INT`.
3. `F_BYTE_TO_INT` performs the type conversion and provides the INT value at its output `OUT`.
4. After successful conversion, the event **AI_OUT.E1** is sent, and the INT value is available at **AI_OUT.D1**.

The conversion is performed without loss of value range: BYTE (0…255) is directly mapped to INT.

## Technical Features

- **Composite Function Block:** The logic is implemented entirely through an internal network consisting of a single conversion block.
- **Reusable:** The block can be integrated into projects that require unidirectional adapter conversion.
- **License:** The block and its associated materials are licensed under the **Eclipse Public License 2.0**.
- **Package:** `adapter::conversion::unidirectional`

## State Overview

The function block (FB) does not have its own internal state machine. Its behavior is determined solely by the triggering events and the embedded block `F_BYTE_TO_INT`. There are no persistent states.

## Application Scenarios

- **Sensor Connection:** A sensor delivers data as BYTE via an AB adapter; downstream processing expects INT values via an AI adapter.
- **Protocol Adaptation:** In heterogeneous communication paths, BYTE-encoded information must be converted into an INT-based data model.
- **Adapter Mediation:** As an intermediary between two system components that use different adapter types.

## Comparison with Similar Function Blocks

Direct conversion blocks like `F_BYTE_TO_INT` (IEC 61131) often exist, but these do not offer adapter event control. The **AB_TO_AI** encapsulates this conversion in a complete adapter-to-adapter transition with event propagation. Similar blocks for other data types (e.g., WORD to DINT) could be built according to the same pattern.

## Conclusion

The **AB_TO_AI** is a useful and simple function block that bridges the gap between BYTE- and INT-based adapter interfaces. It facilitates the integration of components with different data type interfaces in the 4diac IDE and follows proven design patterns of the IEC 61499 standard. Thanks to its composite structure, it is easily extensible and can serve as a template for similar adapter conversions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
