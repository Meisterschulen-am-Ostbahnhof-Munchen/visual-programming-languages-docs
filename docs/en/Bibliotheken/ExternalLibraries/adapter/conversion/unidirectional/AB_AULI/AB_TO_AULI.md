# AB_TO_AULI
![AB_TO_AULI](./AB_TO_AULI.svg)
* * * * * * * * * *
## Introduction
The function block **AB_TO_AULI** is a composite function block (FB) that converts a unidirectional adapter of type `AB` (BYTE) into a unidirectional adapter of type `AULI` (ULINT). It serves as a converter between different data types in adapter communication according to IEC 61499-2. The FB internally uses the standardized conversion block `F_BYTE_TO_ULINT` from the IEC 61131 library.
## Interface Structure

### **Event Inputs**
- **AB_IN.E1** – Event input of the AB adapter socket. Triggered by the incoming adapter protocol, this starts the conversion.

### **Event Outputs**
- **AULI_OUT.E1** – Event output of the AULI adapter plug. Signals the completion of the conversion to the downstream adapter path.

### **Data Inputs**
- **AB_IN.D1** (Data type: BYTE) – Receives the value to be converted via the AB adapter.

### **Data Outputs**
- **AULI_OUT.D1** (Data type: ULINT) – Provides the converted ULINT value via the AULI adapter.

### **Adapters**
- **Socket "AB_IN"** – Type: `adapter::types::unidirectional::AB`

Unidirectional input adapter for the BYTE data type.

- **Plug “AULI_OUT”** – Type: `adapter::types::unidirectional::AULI`

Unidirectional output adapter for the ULINT data type.

## Functionality

The function block (FB) waits for an event at the input adapter `AB_IN`. As soon as the event arrives, the BYTE value at `AB_IN.D1` is forwarded to the internal conversion block `F_BYTE_TO_ULINT` and converted into a ULINT value. After the conversion is complete, the resulting value is output to `AULI_OUT.D1`, and the completion event is sent to `AULI_OUT.E1`. The entire process is event-driven and does not use state machines.

## Technical Features
- The function block does not implement any states or algorithms of its own – it is simply a standard conversion FB interconnect.
- The conversion is performed according to the rules of IEC 61131-3: The BYTE value is interpreted as an 8-bit representation of a ULINT and converted into an unsigned 64-bit integer.
- The adapters are based on a unidirectional communication pattern, meaning that data and events flow only in one direction (from the socket to the plug).
- The function block (FB) is not stateful; each request is processed independently.

## State Overview

The function block does not have its own state machine. Execution follows a simple event-driven sequence:

1. Wait for an input event (`AB_IN.E1`).

2. Convert the data value.

3. Output the result and trigger the output event (`AULI_OUT.E1`).

## Application Scenarios
- **Connecting BYTE-based sensors** to a controller that uses ULINT as a uniform data type for longer measured values.
- **Data format conversion** in adapter chains when a protocol communicates at the BYTE level, but the application expects a ULINT value.
- **Test and debugging setups** where a BYTE test adapter needs to be converted to a ULINT interface.

## Comparison with Similar Function Blocks
- **Direct conversion without adapters** (e.g., `F_BYTE_TO_ULINT`): These function blocks operate at the data level, not the adapter level. The `AB_TO_AULI` encapsulates the conversion, including the adapter interfaces.
- **Adapter converters for other data types** (e.g., `AB_TO_AUDINT`): These are structurally similar but differ in the target data type and, if applicable, in the conversion function used.
- **Bidirectional adapter converters**: If required, two unidirectional converters (e.g., `AB_TO_AULI` and `AULI_TO_AB`) would need to be combined.

## Conclusion

The function block `AB_TO_AULI` provides a simple, standards-compliant way to convert a BYTE adapter to a ULINT adapter. By using an established IEC 61131 conversion block, the conversion is reliable and easily traceable. The block is ideal for adapter-based communication chains that require a data type change at the adapter level.
