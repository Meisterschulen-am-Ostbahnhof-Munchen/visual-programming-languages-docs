# AW_TO_AD
![AW_TO_AD](./AW_TO_AD.svg)

* * * * * * * * * *
## Introduction
The function block **AW_TO_AD** is a composite function block (FB) that converts a unidirectional WORD adapter (AW) into a unidirectional DWORD adapter (AD). It serves as an interface converter and enables the connection of components that use different adapter types. The FB forwards events and data directly from the input to the output adapter, implicitly performing a type conversion from 16-bit WORD to 32-bit DWORD.
## Interface Structure

### **Event Inputs**
- **AW_IN.E1** – Event input via socket `AW_IN`. An incoming event is forwarded directly to the output.

### **Event Outputs**
- **AD_OUT.E1** – Event output via the `AD_OUT` socket. The event passed through from the input is output here.

### **Data Inputs**
- **AW_IN.D1** – Data input (Type: WORD, 16-bit) via the `AW_IN` socket.

### **Data Outputs**
- **AD_OUT.D1** – Data output (Type: DWORD, 32-bit) via the `AD_OUT` socket. The received 16 bits are mapped to the lower 16 bits of the DWORD; the upper 16 bits are padded with zeros (implicit conversion).

### **Adapters**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| `AW_IN` | `adapter::types::unidirectional::AW` | Socket (Input) | WORD adapter providing event and data inputs |
| `AD_OUT` | `adapter::types::unidirectional::AD` | Plug (Output) | DWORD adapter providing event and data outputs |

## Functionality

This module is designed as a simple forwarder. Within the internal FB network, the event and data lines between `AW_IN` and `AD_OUT` are directly connected:

- An event at `AW_IN.E1` is immediately forwarded to `AD_OUT.E1`.
- The 16-bit data value from `AW_IN.D1` is transferred to `AD_OUT.D1`. This involves an implicit expansion to 32 bits: The WORD value is copied into the less significant 16 bits of the DWORD, and the more significant bits are set to `0`.

No processing or intermediate storage takes place – the FB functions as a simple adapter converter.

## Technical Features
- **Composite Function Block without its own state logic:** The function block does not have an ECC (Execution Control Chart) and operates statelessly. All processes are determined by the direct connections within the function block network.
- **Unidirectional operation:** Conversion only occurs in one direction (AW → AD). A separate function block would be required for the reverse direction.
- **Implicit type conversion:** Data is cast from WORD to DWORD without explicit conversion logic. If a different mapping (e.g., sign handling) is required, a separate function block must be used.
- **Package & License:** The function block is available in package `adapter::conversion::unidirectional` under the Eclipse Public License 2.0.

## State Overview

Since the function block is implemented as a composite without an ECC, there is no internal state machine. Its entire functionality is limited to the direct transmission of events and data. The function block (FB) is therefore **stateless** and reacts immediately to every incoming event.

## Application Scenarios
- **Interface Migration:** Replacing a component that expects a WORD adapter with a component that uses a DWORD adapter.
- **System Integration:** Connecting an existing WORD-based module to a DWORD-based controller.
- **Protocol Adaptation:** When a subsystem delivers data in WORD format, but the target requires a DWORD input.
- **Testing and Simulation:** Simple conversion for testing purposes without having to implement complex logic.

## Comparison with Similar Function Blocks

| Function Block | Description |
|----------|--------------|
| `WORD_TO_DWORD` | Pure data conversion without an adapter interface |
| `AW_TO_AD` | Converts complete unidirectional adapters (event + data) |
| `AD_TO_AW` (not available) | Theoretical building block for the reverse direction |

Unlike a pure data converter, `AW_TO_AD` also considers event forwarding and can be directly integrated into adapter-based architectures.

## Conclusion

AW_TO_AD` is a simple yet useful composite function block for converting adapters from WORD to DWORD. It enables quick and clean adaptation of interfaces in 4diac projects without requiring the writing of custom conversion logic. Due to its statelessness and direct passthrough, it is particularly suitable for unidirectional connections in existing automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
