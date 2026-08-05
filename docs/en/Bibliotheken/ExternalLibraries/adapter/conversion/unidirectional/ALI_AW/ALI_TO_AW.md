# ALI_TO_AW
![ALI_TO_AW](./ALI_TO_AW.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_TO_AW** is a composite function block (FB) that converts a LINT value (ALI adapter) into a WORD value (AW adapter). It encapsulates the conversion logic of the IEC 61131-3 function block `F_LINT_TO_WORD` in an adapter-based interface. The block is designed for use in unidirectional adapter communication paths and enables a clean separation of data format and application.
## Interface Structure

The block has no direct event or data inputs/outputs at the FB level. Communication takes place exclusively via two adapters (a socket and a plug).

## **Event Inputs**

*No direct event inputs are available. The incoming event is provided via the adapter `ALI_IN.E1`.*

### **Event Outputs**
*No direct event outputs are available. The outgoing event is provided via the adapter `AW_OUT.E1`.*

### **Data Inputs**
*No direct data inputs are available. The LINT value is obtained via the adapter `ALI_IN.D1`.*

### **Data Outputs**
*No direct data outputs are available. The WORD value is output via the adapter `AW_OUT.D1`.*

### **Adapters**

| Adapter Name | Type | Direction | Comment |

|--------------|-----|-----------|-----------|

| `ALI_IN` | `adapter::types::unidirectional::ALI` | Socket (Input) | LINT adapter input; sends event to `E1` and LINT data to `D1` |

| `AW_OUT` | `adapter::types::unidirectional::AW` | Plug (Output) | WORD adapter output; sends event to `E1` and WORD data to `D1` |

## Functionality

1. The module expects an event (to `E1`) and a corresponding LINT data value (to `D1`) via socket `ALI_IN`.

2. The event is forwarded to the internal conversion module `F_LINT_TO_WORD` (type `iec61131::conversion::F_LINT_TO_WORD`) (connection `ALI_IN.E1` → `Convert.REQ`). Simultaneously, the LINT value is passed to the converter's data input `IN` (connection `ALI_IN.D1` → `Convert.IN`).

3. The internal function block performs the conversion and signals completion via its output `CNF`.

4. This event is passed to the plug `AW_OUT.E1`. The converted WORD value (output `OUT` of the converter) is simultaneously applied to the data input `AW_OUT.D1`.

Thus, the function block makes the data provided by the input adapter available in converted form at the output adapter, controlled by the event chain.

4. This event is then passed to the plug plug `AW_OUT.E1`. The converted WORD value (output `OUT` of the converter) is simultaneously applied to the data input `AW_OUT.D1`.

Thus, the function block makes the data provided by the input adapter available in converted form at the output adapter.
## Technical Features

- **IEC 61131-3 Conversion**: The actual conversion is performed using the standardized function block `F_LINT_TO_WORD`, which performs a lossy conversion from 64-bit (LINT) to 16-bit (WORD) (truncation or range checking depending on the implementation).
- **Adapter-Based Interface**: The function block is fully embedded in 4diac's adapter technology and is suitable for unidirectional communication paths (package `adapter::conversion::unidirectional`).
- **Versioning**: Version 1.0, released under the Eclipse Public License 2.0 (EPL-2.0).
- **No State Management**: The function block delegates all state logic to the inner `F_LINT_TO_WORD`.

## State Overview

Since it is a composite function block, `ALI_TO_AW` does not have its own state machine. The internal converter `F_LINT_TO_WORD` typically implements the following implicit states:

| State | Description |

|---------|--------------|

| IDLE | Waiting for an event at the input `ALI_IN.E1`. |

| CONVERT | After receiving `REQ`, the conversion is performed. |

| DONE | After the conversion is complete, `CNF` is activated and the result value is provided at the output. |

The internal function block then returns to the IDLE state.

## Application Scenarios
- **Control Engineering**: Conversion of a 64-bit counter value (e.g., from an encoder) into a 16-bit value for a simple display or a word-based interface.
- **Data Consolidation**: Use in adapter chains when a subsequent component only accepts WORD inputs, but the source provides LINT data.
- **Test and Simulation Environments**: Generation of WORD data from LINT test values to verify adapter communication paths.

## Comparison with Similar Components
- **LINT_TO_DWORD / LINT_TO_BYTE**: Other conversions with different target widths; `ALI_TO_AW` is specifically designed for use with the unidirectional adapters `ALI` and `AW`.
- **Direct use of F_LINT_TO_WORD**: `ALI_TO_AW` offers a higher level of abstraction through adapter interfaces and facilitates integration into adapter-based architectures, whereas the pure function block only has event and data interfaces.

## Conclusion

The function block `ALI_TO_AW` is a practical and reusable building block for converting LINT to WORD adapters. It encapsulates the typical IEC 61131-3 conversion in an adapter-friendly package, thus simplifying integration into existing or new 4diac projects. Its clear, unidirectional interface and adherence to the Eclipse Public License model make it a robust component for automation solutions that need to connect different data widths.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
