# AB_TO_AD
![AB_TO_AD](./AB_TO_AD.svg)

* * * * * * * * * *
## Introduction
The function block **AB_TO_AD** is a composite function block (FB) that converts a BYTE adapter (type `AB`) into a DWORD adapter (type `AD`). It serves as an interface converter in unidirectional communication and enables the easy connection of components based on different data word widths.
## Interface Structure
### **Event Inputs**
- **AB_IN.E1** – Event input from the BYTE adapter. It is forwarded directly to the DWORD adapter.

### **Event Outputs**
- **AD_OUT.E1** – Event output to the DWORD adapter. Corresponds to the forwarded event of **AB_IN.E1**.

### **Data Inputs**
- **AB_IN.D1** – Data input from the BYTE adapter (1 byte data width). Passed directly to the DWORD adapter.

### **Data Outputs**
- **AD_OUT.D1** – Data output to the DWORD adapter (4 bytes data width). Contains the same value as the input **AB_IN.D1**, but in DWORD (Double Word) format.

### **Adapters**
- **AB_IN** (Socket) – Unidirectional BYTE adapter (type `AB`) that serves as an input.
- **AD_OUT** (Plug) – Unidirectional DWORD adapter (type `AD`) that serves as an output.

## Functionality

This function block connects the interfaces of a BYTE adapter (input) to those of a DWORD adapter (output). Every incoming event (**E1**) is forwarded to the output without delay or processing. Similarly, the incoming data value (**D1**) is passed to the output unchanged, but as a 4-byte DWORD. The function block has no logic of its own; it functions solely as a passthrough between the two adapter types.

## Technical Features
- **Unidirectionality:** The function block supports only one direction of data flow, from the BYTE adapter to the DWORD adapter. Reverse data transfer is not supported.
- **Data Width Adjustment:** The incoming BYTE value (1 byte) is embedded within a DWORD value (4 bytes). The least significant byte of the DWORD corresponds to the incoming BYTE; the more significant bytes are set to zero (or remain unchanged, depending on the implementation of the target adapter).
- **Simple Coupling:** The FB is a pure connection block in the FBNetwork and does not require its own state machine or algorithms.

## State Overview

The block has no state logic of its own, as it functions solely as a connection between the adapters. Its behavior is event-driven: Every event at the input is immediately passed on to the output.

## Application Scenarios
- **System Integration:** If a subsystem uses BYTE adapters, but a subsequent subsystem expects DWORD adapters, `AB_TO_AD` can be used as an intermediary converter.
- **Data Aggregation:** Several such blocks can be used to combine individual bytes into a DWORD if the source adapters each only supply one byte.
- **Protocol Adaptation:** In fieldbus or sensor connections where the data width varies between components, the block serves as a simple adaptation layer.

## Comparison with Similar Modules
Analog converter modules exist for other data widths, e.g., `AB_TO_WORD` (BYTE to WORD) or `WORD_TO_DWORD`. This module specializes in the combination `AB` → `AD` and is therefore ideal for directly replacing or coupling corresponding adapters. Unlike more complex converters with data manipulation or buffers, it operates without delay and without additional logic.

## Conclusion
AB_TO_AD` is a lean, clearly structured converter module that enables the unidirectional conversion of a BYTE adapter to a DWORD adapter. Its simple pass-through makes it ideal for the rapid integration of different interfaces into IEC 61499-based control systems without introducing additional functional complexity.
