# AD_TO_AL
![AD_TO_AL](./AD_TO_AL.svg)
* * * * * * * * * *
## Introduction
The **AD_TO_AL** function block is a composite function block that performs a unidirectional conversion of an AD adapter (DWORD) to an AL adapter (LWORD). It serves as a bridge between subsystems that use different adapter types but require the same logical connection. The function block passes event and data signals through one-to-one, thus enabling the seamless integration of heterogeneous components.
## Interface Structure

The function block has only adapter interfaces; separate event or data inputs/outputs are not available.

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Type | Direction | Name | Comment |

|-----|----------|------|-----------|

| Socket (Input) | Input | `AD_IN` | DWORD adapter input of type `adapter::types::unidirectional::AD` |

| Plug (Output) | Output | `AL_OUT` | LWORD adapter output of type `adapter::types::unidirectional::AL` |

## Functionality

This function block is a simple forwarding block. Within the composite function block, the adapter channels are directly connected:

- **Event Connection:** `AD_IN.E1` → `AL_OUT.E1`
Every incoming event at the AD adapter is passed unchanged to the AL adapter.

- **Data Connection:** `AD_IN.D1` → `AL_OUT.D1`
The incoming data value (DWORD) is passed to the output as an LWORD without transformation.

Type conversion occurs implicitly through the coupling of the adapters; no explicit data type conversion takes place. The runtime environment ensures that the values are handled according to the adapter definition.

## Technical Features
- **Composite Function Block:** The function block contains no internal logic (no state machine, no algorithms) and consists exclusively of internal connections.
- **Unidirectionality:** The adapters are designed to be unidirectional (only one data direction and one event direction).
- **Package Structure:** The function block (FB) is located in the package `adapter::conversion::unidirectional`.
- **Type Conversion:** AD (DWORD) and AL (LWORD) are defined as independent adapter types; the FB enables their interconnection without manual coding.
- **Metadata:** This function block originates from *HR Agrartechnik GmbH*, version 1.0, created on February 17, 2026.

## State Overview

The function block does not have an internal state machine. Its state is identical to the state of the connected adapters. Passing through occurs without delay or logic.

## Application Scenarios
- **System Integration:** Connecting components that use different adapter protocols (e.g., a controller with a DWORD interface and a bus coupler with an LWORD interface).
- **Test Environments:** Easy injection of test data by replacing adapters.
- **Modularization:** Separation of interface definition and data flow logic in large IEC 61499 projects.

## Comparison with Similar Blocks
- `AL_TO_AD`: Performs the reverse conversion (LWORD → DWORD).
- Direct adapter conversion blocks (e.g., `BYTE_TO_WORD`) generally do not replace adapters but convert elementary data types.
- Other "composite" blocks in the `adapter::conversion` package offer similar forwarding for other adapter types (e.g., `AI_TO_AO`, `DI_TO_DO`).

Unlike function blocks with their own logic, `AD_TO_AL` is limited to simple pass-through, ensuring maximum transparency and the lowest possible latency.

## Conclusion

The `AD_TO_AL` function block is a lean yet valuable tool for adapter conversion in the 4diac IDE. It reduces manual wiring effort and increases the reusability of components that rely on different adapter standards. Thanks to its simple structure, it is robust, performant, and easy to understand – ideal for typical work with unidirectional adapter flows.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
