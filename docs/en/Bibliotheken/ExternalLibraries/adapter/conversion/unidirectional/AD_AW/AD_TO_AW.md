# AD_TO_AW
![AD_TO_AW](./AD_TO_AW.svg)
* * * * * * * * * *
## Introduction
The function block **AD_TO_AW** is a composite function block that converts a DWORD adapter (type `AD`) into a WORD adapter (type `AW`). It encapsulates the conversion of a DWORD value to a WORD value and provides the corresponding event and data forwarding. The implementation is based on an internal call to the standard conversion block `F_DWORD_TO_WORD` from the IEC 61131 library.
## Interface Structure
The block has no direct input/output events or data ports. All signals are routed via the connected adapters (socket and plug).

### **Event Inputs**
- **AD_IN.E1** (via socket `AD_IN`): This event triggers the conversion of the incoming DWORD value.

### **Event Outputs**
- **AW_OUT.E1** (via plug `AW_OUT`): This event is sent after successful conversion.

### **Data Inputs**
- **AD_IN.D1** (via socket `AD_IN`): Input data of type `DWORD`, which is converted into a WORD value.

#
## ### **Data Outputs**
- **AW_OUT.D1** (via Plug `AW_OUT`): Output data of type `WORD`, containing the result of the conversion.

### **Adapters**

| Role | Name | Type | Direction | Comment |

|-------|-------|-----|----------|-----------|

| Socket | AD_IN | `adapter::types::unidirectional::AD` | Input (DWORD) | Returns DWORD data and event. |

| Plug | AW_OUT| `adapter::types::unidirectional::AW` | Output (WORD) | Provides WORD data and event. |

Both adapters are of type *unidirectional*, i.e., Communication is unidirectional.

## Functionality

1. As soon as the event `E1` arrives at socket `AD_IN`, the value of `AD_IN.D1` (DWORD) is passed to the internal conversion module `F_DWORD_TO_WORD`.

2. The internal module performs the conversion and creates the result (WORD) at its output `OUT`.

3. The converted value is immediately forwarded to plug `AW_OUT.D1`.

4. Simultaneously, the event `E1` is triggered at plug `AW_OUT` to inform the downstream logic.

The entire process is event-driven and synchronous.

## Technical Features
- **Encapsulation**: The function block uses the standardized IEC 61131 function `F_DWORD_TO_WORD`, which ensures clean and portable conversion.
- **Adapter-based**: Inputs and outputs are implemented exclusively via adapters – there are no separate event/data ports at the block level.
- **Unidirectional**: The adapters used support only one direction of data flow, which simplifies handling in simple conversion chains.
- **Composite Design**: The function block does not have its own ECC (Execution Control Chart); control is handled entirely by the internal block.

## State Overview
As a composite block without its own ECC, **AD_TO_AW** has no internal states. Execution is purely event-driven and occurs atomically with each incoming event at the socket.

**AD_TO_AW**
## Application Scenarios

- **Adapter Adaptation**: When a control system provides data via a DWORD adapter, but a connected module or component expects a WORD adapter.
- **Data Reduction**: Targeted truncation of a DWORD value to the lower 16 bits (WORD) for subsequent processing steps.
- **Bridging**: Use in heterogeneous system landscapes where different adapter types interact.

## Comparison with Similar Components
- **WORD_TO_DWORD**: Performs the reverse conversion (WORD → DWORD) and appends the value (usually by adding zeros).
- **AD_TO_AD (e.g., AD_TO_AD with other types)**: Other composite components can encapsulate similar adapter conversions for additional data types (e.g., BYTE, INT, REAL).
- **Direct use of `F_DWORD_TO_WORD`**: Instead of a composite block, the conversion function could be directly integrated into a function block network – however, the composite offers a reusable, encapsulated solution.

## Conclusion
The **AD_TO_AW** function block is a simple yet useful composite block for converting a DWORD adapter to a WORD adapter. It uses a standardized conversion function, is easy to understand, and can be used in many adapter-based automation systems. Encapsulating it in its own function block makes the network topology clearer and increases reusability.
