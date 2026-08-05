# AQ_TO_AX
![AQ_TO_AX](./AQ_TO_AX.svg)
* * * * * * * * * *
## Introduction
The function block `AQ_TO_AX` converts an AQ adapter (Quarter Byte) to an AX adapter (BOOL) using STATUS logic. It enables the easy integration of AQ-based signals into systems that operate exclusively with AX interfaces. Internally, it uses the block `QUARTER_TO_BOOL` to perform the data conversion.
## Interface Structure
### **Event Inputs**
- No direct event inputs are available. Events are received via the AQ adapter (socket `IN`).

## **Event Outputs**
- No direct event outputs are available. Events are sent via the AX adapter (plug `OUT`).

### **Data Inputs**
- No direct data inputs are available. Data is received via the AQ adapter (socket `IN`).

### **Data Outputs**
- No direct data outputs are available. Data is sent via the AX adapter (plug `OUT`).

### **Adapter**
- **`IN` (Socket)**: Type `adapter::types::unidirectional::AQ` – AQ input (Quarter Byte)
- **`OUT` (Plug)**: Type `adapter::types::unidirectional::AX` – BOOL output (AX)

## Functionality
The `AQ_TO_AX` module does not have its own event or data inputs/outputs, but performs the conversion exclusively via two adapter interfaces. Internally, an instance of the function block `QUARTER_TO_BOOL` is used:

1. **Event Forwarding**: The event `E1` of the incoming AQ adapter is connected to the `REQ` input of `QUARTER_TO_BOOL`. Its `CNF` event is output to the `E1` output of the AX adapter.

2. **Data Forwarding**: The data word `D1` of the AQ adapter (quarter byte) is forwarded to the `IB` input of `QUARTER_TO_BOOL`. The converted BOOL value from the output `Q` of `QUARTER_TO_BOOL` is passed to the `D1` output of the AX adapter.

The entire sequence control and data conversion thus takes place transparently within the function block.

## Technical Features
- The function block functions purely as an adapter converter and has no states or application logic of its own; all functionality is provided by the embedded `QUARTER_TO_BOOL`.
- The use of adapters (socket/plug) allows for loose coupling in the 4diac IDE and facilitates the exchange of communication interfaces.
- The comment "using STATUS logic" indicates that the conversion may be based on a status query (e.g., valid/invalid data), which is implemented within the internal function block.

## State Overview

This function block does not define its own states. The state logic is entirely contained within the internal function block `QUARTER_TO_BOOL`.

## Application Scenarios
- **Interface Adaptation**: Integration of an AQ-based sensor or actuator into a system that only supports AX-compatible adapters.
- **Adapter Transformation**: Use in hierarchies where different adapter types need to be coordinated without changing the underlying data logic.
- **Prototypes and Migration**: Rapid switching between AQ and AX variants during the development or testing phase.

## Comparison with Similar Function Blocks
- **`QUARTER_TO_BOOL`**: Direct conversion of a quarter-byte value to a BOOL value with its own event interface; `AQ_TO_AX` encapsulates this function block in an adapter context.
- **`BYTE_TO_BOOL` or `WORD_TO_BOOL`**: Similar converters for other bit widths, but not specifically designed for adapter coupling.
- **Direct coupling of AQ and AX**: A connection would not be possible without conversion, as the adapter types are incompatible.

## Conclusion
AQ_TO_AX` is a lean yet essential adapter converter that bridges the gap between AQ and AX interfaces. It simplifies the integration of quarter-byte signals into BOOL-based controllers and contributes to the reusability of function blocks in different adapter environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
