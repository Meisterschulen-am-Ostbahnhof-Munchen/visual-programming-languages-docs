# ALI_TO_AD

![ALI_TO_AD](./ALI_TO_AD.svg)

* * * * * * * * * *
## Introduction

The function block `ALI_TO_AD` is a composite block for converting a LINT adapter interface (ALI) to a DWORD adapter interface (AD). It serves as a unidirectional translator between two different data types within an adapter-based communication structure.
## Interface Structure

The block has no independent event or data inputs/outputs. All communication takes place exclusively via predefined adapters.

### **Event Inputs**

None. Event control is handled via the incoming socket adapter `ALI_IN`.

### **Event Outputs**

None. The output events are provided via the outgoing plug adapter `AD_OUT`.

### **Data Inputs**

None. Input data is transmitted via the socket adapter `ALI_IN`.

### **Data Outputs**

None. Output data is transmitted via the plug adapter `AD_OUT`.

### **Adapters**

| Direction | Name | Type | Description |
|----------|---------|----------------------------------------|----------------------------------------|
| Socket | ALI_IN | `adapter::types::unidirectional::ALI` | Input adapter of type LINT |
| Plug | AD_OUT | `adapter::types::unidirectional::AD` | Output Adapter of Type DWORD |

## Functionality

Inside the function block, a single instance of the function block `iec61131::conversion::F_LINT_TO_DWORD` is used. The event and data connections are wired as follows:

1. An event from socket `ALI_IN.E1` triggers the input `REQ` of the converter.
2. The converter reads the LINT value from input `ALI_IN.D1` and converts it to a DWORD value.
3. After successful conversion, the converter generates the confirmation event `CNF`, which is forwarded to plug `AD_OUT.E1`.
4. Simultaneously, the converted DWORD value is transferred from output `Convert.OUT` to data output `AD_OUT.D1`.

The entire conversion process is event-driven: An incoming event triggers the conversion, and the result is acknowledged with an output event.

## Technical Features

- The module is fully implemented as a composite and requires no dedicated runtime logic.
- The internal converter `F_LINT_TO_DWORD` is an IEC 61131-3 module that performs a bit-perfect conversion of a 64-bit integer value (LINT) to a 32-bit double-word value (DWORD).
- The adapters are defined as unidirectional, meaning that data flows exclusively from the input to the output adapter.

`` - This function block is designed for use in automation systems that utilize adapter interfaces according to the IEC 61499 standard.

## State Overview

The function block does not have its own explicit state machine. Its behavior is entirely determined by event propagation and the internal logic of the converter block. From the user's perspective, it behaves like a transparent data conversion that is executed once for each incoming event.

## Application Scenarios

- **Integration of Heterogeneous Field Devices** – When a device or subnetwork provides data in LINT format (e.g., as a counter value or timestamp), but the target system expects DWORD values.
- **Adapter Bridge Between Subsystems** – In a distributed control system according to IEC 61499, `ALI_TO_AD` can be used to connect two subsystems with different adapter definitions.
- **Data Format Adaptation in Migration Projects** – When modernizing systems where older components still provide LINT adapters, but newer components require DWORD adapters.

## Comparison with Similar Components

- **`INT_TO_DWORD`** – Converts a 16-bit integer value to DWORD, but is not offered at the adapter level.
- **`DWORD_TO_LINT`** – Reverses the conversion described here and converts DWORD back to LINT.
- **Custom Combination Components** – Instead of a hardwired adapter converter, the conversion could also be performed manually using a `F_LINT_TO_DWORD` and separate adapters. The composite component offers a compact and reusable solution.

## Conclusion

ALI_TO_AD` is a simple yet useful composite component that enables the unidirectional conversion of a LINT adapter to a DWORD adapter. It allows for a clean separation of data types at the adapter level and simplifies the integration of different systems in an IEC 61499 environment. The use of a standardized IEC 61131 converter ensures defined and reproducible data conversion.
