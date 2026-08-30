# AL_TO_AUI

![AL_TO_AUI](./AL_TO_AUI.svg)

* * * * * * * * * *
## Introduction

The **AL_TO_AUI** function block is a composite component that converts an LWORD adapter (AL) into a UINT adapter (AUI). It enables the seamless integration of LWORD-based interfaces into systems that expect UINT data by encapsulating the conversion within a standardized adapter structure.
## Interface Structure

### **Event Inputs**

No standalone event inputs. The **AL_IN** socket provides the trigger signal for the conversion via its event output `E1`.

#### **Event Outputs**

No standalone event outputs. The plug **AUI_OUT** provides confirmation of the completed conversion via its event input `E1`.

### **Data Inputs**

No standalone data inputs. The socket **AL_IN** provides the value to be converted to `LWORD` via its data output `D1`.

### **Data Outputs**

No standalone data outputs. The plug **AUI_OUT** provides the converted `UINT` value via its data input `D1`.

### **Adapter**

| Type | Direction | Name | Description |
|-----|----------|------|--------------|
| Socket | Input | **AL_IN** | Adapter type `adapter::types::unidirectional::AL` – provides an LWORD data and an event to trigger the conversion. |
| Plug | Output | **AUI_OUT** | Adapter type `adapter::types::unidirectional::AUI` – receives the converted UINT data and forwards the confirmation event. |

## Functionality

The module consists of an internal network with a single conversion module `F_LWORD_TO_UINT` from the IEC 61131 library. The process is strictly event-driven:

1. An event at socket `AL_IN.E1` is forwarded to the `REQ` input of the conversion module.
2. The conversion block reads the date from `AL_IN.D1` (type `LWORD`) and converts it to a `UINT` value according to IEC 61131 rules.
3. After the conversion is complete, the block generates an event at its `CNF` output, which is directly passed to the plug `AUI_OUT.E1`.
4. Simultaneously, the converted value is passed from the data output `OUT` to the data input `AUI_OUT.D1`.

This completes the entire conversion in a single, unidirectional pass.

...
## Technical Features

- **Bit-reinterpretation**, value-preserving only if the source value fits the narrower destination width (otherwise the upper bits are silently dropped).

- **Composite Structure**: The function block (FB) does not contain its own state machine but delegates all functionality to the embedded conversion block.
- **Unidirectional Adapters**: Both the input and output adapters are of type `unidirectional`. Only forward conversion takes place; reverse conversion and status feedback are not supported.
- **Package Assignment**: The FB is located in the package `adapter::conversion::unidirectional`, indicating its use in modular adapter chains.
- **Reusability**: The function block can be used as a universal converter in any IEC 61499 application that requires LWORD-to-UINT conversion via adapters.

## State Overview

Since this is a composite block without its own state machine, the state logic is entirely determined by the internal block `F_LWORD_TO_UINT`. This block operates according to a simple REQ/CNF scheme:

- **Waiting for REQ**: Inactive, no event at the input.
- **Conversion active**: The conversion is performed upon receipt of `REQ`.
- **Output CNF**: Upon completion, `CNF` is set and the output data is updated.

A detailed state description of the conversion block can be found in the IEC 61131 documentation.

## Application Scenarios

- **Sensor Data Connection**: A sensor provides values in LWORD format (e.g., 64-bit counter readings), which are fed into the system via an AL adapter. The `AL_TO_AUI` function block converts these values into UINT (16-bit) for transmission to a controller with a UINT interface.
- **Protocol Conversion**: In modular adapter chains, the function block serves as an intermediate stage to switch from LWORD-based to UINT-based subsystems without requiring changes to the original adapter logic.
- **Data Reduction**: If the upper 48 bits of an LWORD value are not needed, the function block can selectively extract only the lower 16 bits as UINT (according to IEC 61131 conversion rules).

## Comparison with Similar Function Blocks

| Function Block | Output Type | Special Feature |
|----------|--------------|--------------|
| `AL_TO_AUI` | UINT | Direct Adapter Converter, Unidirectional, Composite |
| `AL_TO_AUD` | DINT | Converts LWORD to DINT (32-bit) |
| `AUI_TO_AL` | LWORD | Reverse conversion from UINT to LWORD (not included, would need to be implemented separately) |

Compared to directly using `F_LWORD_TO_UINT`, `AL_TO_AUI` offers the advantage of easy integration into adapter interfaces without the need to manually establish event and data connections.

## Conclusion

The **AL_TO_AUI** is a convenient, standardized adapter converter for converting LWORD to UINT. Thanks to its composite structure and the use of proven IEC 61131 conversion logic, it integrates seamlessly into modular adapter chains. It is particularly suitable for applications where heterogeneous data types need to be connected via uniform adapter interfaces.
