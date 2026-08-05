# AUI_TO_ADI
![AUI_TO_ADI](./AUI_TO_ADI.svg)

* * * * * * * * * *
## Introduction
The AUI_TO_ADI function block is a composite module that converts a unidirectional AUI adapter (data type UINT) into a unidirectional ADI adapter (data type DINT). It serves as a standardized interface between components that use different data types for analog input or output values.
## Interface Structure
### **Event Inputs**
None. Event control is handled via the connected AUI adapter (socket AUI_IN).

### **Event Outputs**
None. Event output is handled via the ADI adapter (plug ADI_OUT).

### **Data Inputs**
None. Data input is handled via the connected AUI adapter.

### **Data Outputs**
None. Data output is handled via the ADI adapter.

### **Adapter**

| Name | Direction | Type | Description |

|------|----------|-----|--------------|

| AUI_IN | Socket (Input) | `adapter::types::unidirectional::AUI` | UINT adapter for receiving input data and events. |

| ADI_OUT | Plug (Output) | `adapter::types::unidirectional::ADI` | DINT adapter for sending the converted data and events. |

## Functionality
The function block receives an event and a UINT value via the AUI_IN socket. This event triggers the internal conversion block `F_UINT_TO_DINT`, which converts the value from type UINT to type DINT. After successful conversion, an event is output via the ADI_OUT plug, along with the converted DINT value. The conversion is performed according to the IEC 61131 standard and is lossless, as the entire value range of UINT (0…65535) can be mapped to DINT.

## Technical Features
- The function block (FB) is implemented as a **composite block**, meaning its functionality is based on an integrated IEC 61131 block (`F_UINT_TO_DINT`).
- Communication occurs exclusively via **unidirectional adapters** – no separate event or data inputs/outputs are required at the top level.
- The internal converter operates **event-driven**: Every incoming event at the AUI_IN adapter triggers a conversion.

## State Overview
The FB does not have its own state machine. The state logic is fully implemented by the internal function block `F_UINT_TO_DINT`, which performs a one-time conversion for each REQ event and acknowledges it with CNF.

## Application Scenarios
- **Interface Adaptation**: A sensor provides measured values via a UINT-based AUI adapter, but the downstream logic requires DINT values (e.g., for arithmetic operations or visualization).
- **System Integration**: In heterogeneous automation systems where different components use different adapter types, the function block can be used as an intermediary layer.
- **Migration**: Existing systems with UINT data paths are to be gradually converted to DINT.

## Comparison with Similar Function Blocks
- **F_UINT_TO_DINT**: Direct IEC 61131 converter, but without adapter encapsulation. Requires separate event and data lines.
- **AUI_TO_ABOOL**: Analog converter for binary outputs (UINT → BOOL), not for numeric types.
- **ATO_TO_ADI**: Converts ATO adapters (DWORD) to ADI, different data width.

This function block stands out due to its complete adapter integration and unidirectional design, which facilitates its use in adapter-based architectures.

## Conclusion
The `AUI_TO_ADI` function block offers a clean, encapsulated solution for type conversion from UINT to DINT via standardized adapters. It reduces wiring effort and increases reusability in modular automation solutions. The use of a proven IEC 61131 function block ensures the correctness of the conversion.
