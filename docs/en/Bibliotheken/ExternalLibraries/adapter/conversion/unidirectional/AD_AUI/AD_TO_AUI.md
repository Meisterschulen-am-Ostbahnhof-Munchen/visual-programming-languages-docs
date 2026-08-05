# AD_TO_AUI
![AD_TO_AUI](./AD_TO_AUI.svg)
* * * * * * * * * *
## Introduction
The function block `AD_TO_AUI` is a composite block that converts an AD adapter (DWORD-based) into an AUI adapter (UINT-based). It enables the seamless integration of components that work with different data types by converting incoming DWORD values to UINT values and forwarding the corresponding events.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-----|---------------|

| (none of its own) | - | The function block does not have its own event inputs. Event control is handled via the adapter socket `AD_IN`. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|--------------|

| (none built-in) | - | The function block has no built-in event outputs. Event forwarding is handled via the adapter plug `AUI_OUT`. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| (none built-in) | - | All data is provided via the adapter socket `AD_IN`. |

### **Data Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| (No custom) | - | All data is output via the adapter plug `AUI_OUT`. |

### **Adapter**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| `adapter::types::unidirectional::AD` | `AD_IN` | Socket (Input) | Accepts DWORD values and associated events. |

| `adapter::types::unidirectional::AUI` | `AUI_OUT` | Plug (Output) | Outputs converted UINT values and associated events. |

The adapter `AD_IN` provides an event `E1` and a data element `D1` (type DWORD).

The adapter `AUI_OUT` expects an event `E1` and a data element `D1` (type UINT).

The mapping is performed as described in the Functionality section.

## Functionality
The function block contains an instance of the standard conversion module `iec61131::conversion::F_DWORD_TO_UINT`. Internal Circuitry:

1. **Event Control**:

- The event `AD_IN.E1` is forwarded directly to the conversion block (`Convert.REQ`).
- After successful conversion, `Convert.CNF` signals the event to `AUI_OUT.E1`.

2. **Data Flow**:

- The data value `AD_IN.D1` (DWORD) is passed to the input `Convert.IN`.
- The output `Convert.OUT` delivers the converted value (UINT) to `AUI_OUT.D1`.

The function block thus performs an event-driven, unidirectional type conversion from DWORD to UINT. The conversion is performed according to the IEC 61131-3 standard function `DWORD_TO_UINT`.

## Technical Features
- **Composite Block**: The function block encapsulates an existing standard conversion block and two adapter interfaces. This simplifies reuse in larger applications.
- **Data Type Conversion**: The conversion from `DWORD` (32-bit, unsigned) to `UINT` (16-bit, unsigned) can lead to information loss depending on the value range (e.g., if the DWORD value is greater than 65535). The user is responsible for monitoring the value range.
- **Unidirectional Interface**: Both the input and output adapters are unidirectional (only one event/data direction).
- **License**: This function block is available under the Eclipse Public License 2.0 (EPL-2.0).

## State Overview
The `AD_TO_AUI` function block does not have its own internal state. Its behavior is purely combinatorial in conjunction with the event-driven execution of the included conversion block. There are no initialization or error states; the conversion occurs immediately upon each incoming event.

## Application Scenarios
- **Interface Adaptation**: When an existing function block or subsystem only supports an AUI adapter (UINT), but the data source provides an AD adapter (DWORD).
- **Data Reduction**: Targeted reduction of a 32-bit value to 16 bits for downstream processing logic.
- **Integration into Existing Controllers**: Exchange of adapters between different bus systems or communication protocols that use different data types.

## Comparison with Similar Function Blocks
- **AUI_TO_AD**: Performs the reverse conversion (UINT to DWORD). Both function blocks are symmetrically structured and utilize the corresponding standard conversion functions.
- **Direct Type Conversion**: Manual implementation using a `F_DWORD_TO_UINT` function block and adapters would be possible, but the composite function block offers an encapsulated, reusable solution.

## Conclusion
The `AD_TO_AUI` function block provides a simple and reliable way to convert between two common adapter types. It reduces development effort by encapsulating the necessary circuitry and conversion and providing it as a reusable component. Despite the potential value range limitation (DWORD → UINT), it is a useful tool for integrating heterogeneous system components in control engineering.