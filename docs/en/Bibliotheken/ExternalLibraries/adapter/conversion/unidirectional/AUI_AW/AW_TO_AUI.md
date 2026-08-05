# AW_TO_AUI
![AW_TO_AUI](./AW_TO_AUI.svg)

* * * * * * * * * *
## Introduction
The function block **AW_TO_AUI** is a composite function block (FB) that converts an **AW (WORD)** adapter into an **AUI (UINT)** adapter. It enables the seamless integration of components that use different data types via unidirectional adapters. Internally, it uses the standard conversion block `F_WORD_TO_UINT` for type conversion.
## Interface Structure

### **Event Inputs**

The FB does not have its own independent event inputs. The event `E1` is provided via the **socket (input adapter) `AW_IN`** and triggers the data conversion.

### **Event Outputs**

The FB does not have any standalone event outputs. The event `E1` is output via the **plug (output adapter) `AUI_OUT`** after successful conversion.

### **Data Inputs**

The FB does not have any standalone data inputs. The date `D1` of type `WORD` is provided via the **socket `AW_IN`**.

### **Data Outputs**

The FB does not have any standalone data outputs. The date `D1` of type `UINT` is output via the **plug `AUI_OUT`**.

### **Adapter**

| Name | Direction | Type | Description |
|----------|----------|-----------------------------------------|----------------------------------|
| `AW_IN` | Input | `adapter::types::unidirectional::AW` | WORD Adapter Input (Socket) |
| `AUI_OUT`| Output | `adapter::types::unidirectional::AUI` | UINT Adapter Output (Plug) |

## Functionality

This function block acts as a conversion layer between two different adapter types. Internally, a single function block, `F_WORD_TO_UINT`, is embedded:

1. **Event Control**:

- An incoming event at socket `AW_IN.E1` triggers the conversion process (`Convert.REQ`).
- After the conversion is complete, the internal block generates an acknowledgment event (`Convert.CNF`), which is forwarded to plug `AUI_OUT.E1`.

2. **Data Flow**:

- The value `WORD`, provided by socket `AW_IN.D1`, is passed to input `Convert.IN`.
- The output `Convert.OUT` returns the converted `UINT` value, which is then passed to the plug `AUI_OUT.D1`.

The conversion is performed according to the IEC 61131-3 standard conversion `WORD_TO_UINT`.

## Technical Features
- **Pure Composite Structure**: The function block (FB) does not have its own state machine or logic, but delegates all functionality to the embedded standard function block.
- **Unidirectional Adapters**: Both the input and output adapters are designed as unidirectional types, enabling simple and directional data transfer.
- **Reusability**: The function block can be used in projects where interface adaptation between WORD- and UINT-based components is required.

## State Overview

Since this is a composite function block without its own state machine, there are no internal states. The function block behaves strictly event-driven: Every input event is followed—after conversion is complete—by an output event.

## Application Scenarios
- **System Integration**: Connecting a component that provides data as `WORD` via an AW adapter to another component that expects `UINT` via an AUI adapter.
- **Protocol Adaptation**: Use in middleware or gateway functions to harmonize different data formats within a control architecture.
- **Modular Extension**: Easy integration into existing 4diac networks without requiring changes to adjacent function blocks.

## Comparison with Similar Modules

Other conversion modules (e.g., `F_WORD_TO_DWORD` or `F_INT_TO_UINT`) operate directly on data ports. In contrast, `AW_TO_AUI` is specifically designed for adapter-based communication and encapsulates both the type conversion and the adapter logic in a single unit. This simplifies the handling of adapter interfaces and keeps network design clear.

## Conclusion

The `AW_TO_AUI` function block offers a compact and reliable solution for adapter conversion from `WORD` to `UINT`. Thanks to the use of a standardized IEC 61131 conversion module and clear event control, it is easy to understand and maintain. It is particularly suitable for projects that require a clean separation between different data types at the adapter level.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
