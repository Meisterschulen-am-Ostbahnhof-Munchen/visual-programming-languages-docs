# ALI_TO_AUI
![ALI_TO_AUI](./ALI_TO_AUI.svg)
* * * * * * * * * *
## Introduction
The function block **ALI_TO_AUI** is a composite block for converting an ALI adapter (LINT data type) into an AUI adapter (UINT data type). It allows the seamless integration of components with different adapter definitions in a 4diac environment. The block is based on the internal conversion block `F_LINT_TO_UINT` from the IEC 61131 library.
## Interface Structure
### **Event Inputs**
Not present – event control is handled by the adapters.

#### **Event Outputs**
Not present – event control is handled by the adapters.

#### **Data Inputs**
Not present – data transfer is handled by the adapters.

#
# ### **Data Outputs**
Not present – data is transferred via the adapters.

### **Adapters**

| Type | Name | Comment |

|------|------|-----------|

| Socket | `ALI_IN` | Input adapter of type `adapter::types::unidirectional::ALI` – provides LINT value and associated event. |

| Plug | `AUI_OUT` | Output adapter of type `adapter::types::unidirectional::AUI` – provides the converted UINT value and associated event. |

## Functionality
Internally, this function block connects socket `ALI_IN` to the input of the conversion function block `F_LINT_TO_UINT`.

- The converter's `E1` event output from `ALI_IN` controls the `REQ` input.
- The data value `D1` from `ALI_IN` (LINT) is placed on the converter's `IN` input.
- After successful conversion, the converter signals the event to the plug `AUI_OUT` with `CNF`, and the converted value (UINT) is written to its `D1` output.

`` The event output `E1` from `ALI_IN` is controlled via the converter's `REQ` input.

`` The data value `D1` from `ALI_IN` (LINT) is placed on the `IN` input. ... The entire process is event-driven: An incoming event at the ALI adapter triggers the conversion and generates a corresponding output event at the AUI adapter.

## Technical Features
- **Data Type Conversion:** The internal module converts a 64-bit signed integer (LINT) to a 16-bit unsigned integer (UINT). Since the value range of UINT (0…65535) is significantly smaller than that of LINT, values outside this range result in an overflow/loss.
- **Dependency:** The module requires the library `iec61131::conversion` (specifically the module `F_LINT_TO_UINT`).
- **Adapter-Free Interface:** All data exchange occurs exclusively via adapters, enabling modular and reusable integration into larger networks.

## State Overview

The function block itself does not have its own state machine. The state logic is fully implemented by the internal function block `F_LINT_TO_UINT`. This typically has the states **IDLE** (waiting for REQ) and **BUSY** (performing conversion). Upon completion, the result is provided and the CNF event output is activated.

## Application Scenarios
- **Adapter Bridge:** A sensor that provides data in ALI format (LINT) is to be connected to an actuator that expects an AUI input (UINT).
- **System Integration:** In heterogeneous automation systems where different adapter definitions are used, the function block serves as a simple converter without manual programming.
- **Prototyping:** Quickly replace adapters during the development phase without having to change the underlying data flow logic.

**Prototyping:**
## Comparison with Similar Components
Analog converter components exist, such as `ALI_TO_UDI` (LINT → UDINT) or `DINT_TO_UINT`. This component specializes in combining the unidirectional ALI and AUI adapters. Unlike directly connecting the adapters via data type conversion at the network layer, this composite function block offers a compact, reusable solution with clearly defined event signals.

## Conclusion
The ALI_TO_AUI component is a practical and easy-to-understand tool for converting between ALI and AUI adapters. Its composite structure encapsulates the necessary data conversion and event forwarding, allowing it to integrate seamlessly into existing 4diac projects. Its ease of use and clear interface separation make it a valuable tool for adapter integration.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
