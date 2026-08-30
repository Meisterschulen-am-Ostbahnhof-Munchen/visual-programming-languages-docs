# AUS_TO_AD

![AUS_TO_AD](./AUS_TO_AD.svg)

* * * * * * * * * *
## Introduction

The function block **AUS_TO_AD** is a composite block that performs a simple conversion from a USINT adapter (type AUS) to a DWORD adapter (type AD).
It encapsulates the conversion of an unsigned 8-bit value (USINT) to a 32-bit DWORD value and makes this accessible via standardized adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| `E1` | Event (from socket `AUS_IN`) | Starts the conversion of the incoming USINT value. The input is provided via socket `AUS_IN`. |

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| `E1` | Event (to plug `AD_OUT`) | Signals successful conversion and the presence of the DWORD value at the output. The output is provided via plug `AD_OUT`. |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
| `D1` | USINT (from socket `AUS_IN`) | The 8-bit value to be converted, in the range 0…255. |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|--------------|
| `D1` | DWORD (to plug `AD_OUT`) | The converted 32-bit value (direct type conversion of the USINT to DWORD). |

### **Adapter**

| Role | Name | Type | Direction | Description |
|-------|------|-----|----------|--------------|
| Socket | `AUS_IN` | `adapter::types::unidirectional::AUS` | Input | Receives the USINT value and the associated event. |
| Plug | `AD_OUT` | `adapter::types::unidirectional::AD` | Output | Provides the DWORD value and the acknowledgment event. |

## Functionality

This function block implements a simple, end-to-end data conversion:

1. An incoming event at the adapter input `AUS_IN.E1` triggers the internal conversion.
2. The connected USINT value (`AUS_IN.D1`) is converted into a DWORD value using the standardized IEC 61131 function block `F_USINT_TO_DWORD`.
3. After successful conversion, the output event `AD_OUT.E1` is sent, and the DWORD value is made available as `AD_OUT.D1`.

The function block operates without its own state logic – it performs the conversion immediately for each event (transparent behavior).

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Composite Design:** The function block consists solely of an internal network with a single function block (`F_USINT_TO_DWORD`) and direct event and data connections.
- **Reuse:** The conversion uses the IEC 61131-3 standard function `F_USINT_TO_DWORD`, which is included in the library `iec61131::conversion`.
- **Adapter Interfaces:** The interfaces are implemented as unidirectional adapters (`adapter::types::unidirectional::AUS` and `AD`, respectively). Each adapter consists of exactly one event channel and one data channel.
- **No State Machine:** Since this is a pure composite device without its own ECC, no states are managed.

## State Overview

The device does not have its own state machine. Its behavior is purely data flow-driven: For each incoming event, exactly one conversion is performed, and the event is forwarded without delay.

## Application Scenarios

- **Interface Adaptation:** When a USINT value (e.g., a byte sensor) needs to be used in a system that internally only processes DWORD values.
- **Adapter Bridging:** Use in modular control architectures where adapter types are not directly compatible and conversion between AUS and AD adapters is required.
- **Prototype/Test Environments:** Fast connection of two components with different adapter definitions without requiring their own conversion logic.

## Comparison with Similar Function Blocks

- **F_USINT_TO_DWORD:** The underlying conversion block is a pure data converter without an adapter interface. It requires direct data and event connections.

AUS_TO_AD`, on the other hand, encapsulates this function and offers a standardized adapter interface.

- **Other adapter converters (e.g., BYTE_TO_DWORD, WORD_TO_DWORD):** Similar function blocks exist for other data types, but usually require different adapter types. `AUS_TO_AD` is specifically optimized for the combination of the adapters `AUS` (USINT) and `AD` (DWORD).

## Conclusion

The function block `AUS_TO_AD` offers a simple and robust way to convert a unidirectional USINT adapter into a DWORD adapter. By using the standardized conversion module and adapter interfaces, it can be seamlessly integrated into IEC 61499-based automation systems. It reduces the manual effort required for type conversions and ensures clean, reusable interface adaptation.
