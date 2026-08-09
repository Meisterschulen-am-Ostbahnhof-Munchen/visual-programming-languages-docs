# AD_TO_AX

![AD_TO_AX](./AD_TO_AX.svg)

* * * * * * * * * *
## Introduction

The function block `AD_TO_AX` serves as a composite function block for converting an AD adapter (data word – DWORD) into an AX adapter (Boolean value – BOOL). It encapsulates a comparison mechanism that checks whether the incoming DWORD value is non-zero and forwards the result as a BOOL to the output adapter. This block simplifies adapter communication in control systems by converting signal types between different components.
## Interface Structure

### **Event Inputs**

No standalone event inputs. The event is provided via the socket adapter `AD_IN` (see section **Adapters**).

### **Event Outputs**

No standalone event outputs. The result event is provided via the plug adapter `AX_OUT` (see section **Adapters**).

### **Data Inputs**

No standalone data inputs. The input data is provided via the socket adapter `AD_IN` (see section **Adapters**).

### **Data Outputs**

No standalone data outputs. The output data is provided via the plug adapter `AX_OUT` (see section **Adapters**).

### **Adapters**

| Adapter | Direction | Type | Comment |
|---------|----------|-----|-----------|
| `AD_IN` | Socket | `adapter::types::unidirectional::AD` | DWORD input adapter – provides an event and DWORD data. |
| `AX_OUT` | Plug | `adapter::types::unidirectional::AX` | BOOL output adapter – outputs an event and a Boolean result. |

The adapters follow a unidirectional pattern and each provides an event output (`E1`) and a data output (`D1`):

- **AD_IN.E1** → initiates processing.
- **AD_IN.D1** → contains the DWORD source value.
- **AX_OUT.E1** → signals the end of processing.
- **AX_OUT.D1** → contains the Boolean result value.

## Functionality

The FB `AD_TO_AX` is implemented as a composite FB. It contains an instance of the comparison block `F_NE` ("not equal") from the IEC 61131 library.

1. An incoming event at `AD_IN.E1` triggers the input `F_NE.REQ`.
2. The block `F_NE` compares the value of `AD_IN.D1` with the constant value `DWORD#0`.
3. The comparison result (BOOL) is provided at the output `F_NE.OUT`.
4. This result is transmitted to `AX_OUT.D1` via a data connection.
5. Simultaneously, `F_NE.CNF` signals the end of the calculation and triggers `AX_OUT.E1`.

Thus, a BOOL value is derived from a DWORD value:

- `DWORD = 0` → Output `FALSE`
- `DWORD ≠ 0` → Output `TRUE`

## Technical Features

- **Composite Function Block**: The function block consists of an internal network that implements the actual logic – this facilitates reuse and encapsulation.
- **Use of `F_NE`**: The comparison function block used, from the IEC 61131 library, is standardized and platform-independent.
- **Adapter-based communication**: Instead of individual inputs/outputs, adapters are used, enabling structured connections to other adapter-compatible modules.
- **Unidirectional adapters**: Both input and output adapters are unidirectional, meaning they only transport data and events in one direction – this avoids feedback loops and simplifies the design.

## State overview

The function block (FB) does not have an explicit state machine, as it consists solely of a logical operation. The internal process is event-driven:

- **Idle state**: Waiting for an event at input `AD_IN.E1`.
- **Execution**: After the event, `F_NE` performs the calculation and forwards the result – this happens in one step without intermediate states.

## Application scenarios

- **Adapter conversion**: A system uses DWORD adapters, but a connected module expects BOOL signals. The `AD_TO_AX` function block handles the conversion.
- **Threshold Check**: Checks whether a DWORD value deviates from zero (e.g., active signal, counter reading > 0).
- **Signal Conditioning**: Simplifies the integration of sensors or actuators whose output is encoded as a DWORD into Boolean control logic.

## Comparison with Similar Function Blocks

- **Direct `DWORD_TO_BOOL` Converter**: Such a function block would typically only perform the data conversion but would not offer an adapter structure or event handling. `AD_TO_AX`, on the other hand, encapsulates both event and data paths in adapters.
- **General Adapter Converters**: Similar function blocks exist for other data types (e.g., `AD_TO_AX` for WORD, INT, etc.). This function block is specifically designed for converting DWORD to BOOL.
- **Composite vs. Basic Function Block**: As a composite function block, this block is easily adaptable because the internal network can be modified as needed.

## Conclusion

The function block `AD_TO_AX` offers an elegant and standardized way to convert DWORD adapter signals into BOOL adapters. By using the established comparison function block `F_NE`, the logic is robust and traceable. The adapter structure facilitates integration into modular automation systems and promotes reusability. This function block is particularly suitable for scenarios requiring event-driven conversion of digital values to Boolean states.
