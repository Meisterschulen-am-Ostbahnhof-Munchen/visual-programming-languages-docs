# AB_TO_AW
![AB_TO_AW](./AB_TO_AW.svg)
* * * * * * * * * *
## Introduction
The function block **AB_TO_AW** is a composite block that performs a unidirectional conversion from an AB adapter (BYTE-based) to an AW adapter (WORD-based). It serves as an interface converter when a system component delivers data in BYTE format, but the downstream component expects a WORD format.
## Interface Structure
The block does not have any classic event or data inputs/outputs at the top level, but uses only adapter interfaces.

### **Event Inputs**
- No direct event inputs are available. Events are received via the **AB_IN** adapter.

### **Event Outputs**
- No direct event outputs are available. Events are sent via the **AW_OUT** adapter.

### **Data Inputs**
- No direct data inputs are available. Data is received via the **AB_IN** adapter.

### **Data Outputs**
- No direct data outputs are available. Data is sent via the **AW_OUT** adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Input (Socket) | **AB_IN** | `adapter::types::unidirectional::AB` | BYTE adapter input, provides a BYTE date and an event |

| Output (Plug) | **AW_OUT** | `adapter::types::unidirectional::AW` | WORD adapter output, provides a WORD date and an event |

## Functionality

This function block forwards the incoming signals from the **AB_IN** adapter directly to the **AW_OUT** adapter:

- The **E1** event of the **AB_IN** is linked to the **E1** event of the **AW_OUT**.
- The **D1** (BYTE) data of the **AB_IN** is linked to the **D1** (WORD) data of the **AW_OUT**.

Since this is a simple pass-through, no data conversion in the sense of a value change occurs; the BYTE data is interpreted as WORD data (implicit type conversion via the data connection). The actual conversion (e.g., extending the value range) depends on the implementation of the underlying adapters.

## Technical Features
- The function block is implemented as a **composite function block**, meaning its behavior is entirely defined by the internal network (FBNetwork).
- The conversion is unidirectional: only from the AB adapter to the AW adapter.
- The connection is established at the event and data level without intermediate storage or synchronization.
- The function block is part of the package structure `adapter::conversion::unidirectional`.

## State Overview
The function block does **not have its own state machine**. Its behavior is purely combinatorial: Every incoming event is immediately forwarded to the output, as is the data.

## Application Scenarios
- **Connecting Sensors/Actuators**: A module provides a BYTE value (e.g., via an AB adapter), but downstream logic expects WORD format.
- **Protocol Adaptation**: In heterogeneous systems where different adapter types interact.
- **System Integration**: When an existing BYTE-based sequence control needs to be integrated into a WORD-based environment.

## Comparison with Similar Components
- **WORD_TO_BYTE**: An analogous component may exist for the reverse direction (WORD → BYTE).
- **Direct Adapter Connection**: Without this component, the programmer would have to manually link the event and data in the network; **AB_TO_AW** encapsulates this connection and increases reusability.
- **Type Converter**: Pure data converters (e.g., `BYTE_TO_WORD`) often operate without event forwarding; here, the event is also passed through.

## Conclusion
The **AB_TO_AW** is a simple but useful interface component for the unidirectional conversion of a BYTE adapter to a WORD adapter. By encapsulating the connection logic, clarity in the application network is improved and the reuse of standardized conversion patterns is promoted.