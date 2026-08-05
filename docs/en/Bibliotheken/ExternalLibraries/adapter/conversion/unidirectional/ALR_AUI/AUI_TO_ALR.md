# AUI_TO_ALR
![AUI_TO_ALR](./AUI_TO_ALR.svg)

* * * * * * * * * *
## Introduction
The AUI_TO_ALR function block is a composite module that enables interface conversion between an AUI adapter (data type UINT) and an ALR adapter (data type LREAL). It acts as a simple pass-through, transmitting both event and data signals from the input to the output adapter.
## Interface Structure

### **Event Inputs**
- **Event via Socket AUI_IN (E1)** – Event input from the AUI adapter.

Internally, this is directly connected to the event output of the ALR adapter.

### **Event Outputs**
- **Event via Plug ALR_OUT (E1)** – Event output to the ALR adapter.

Corresponds to the passed-through event from socket AUI_IN.

### **Data Inputs**
- **Data value via socket AUI_IN (D1)** – Data input from the AUI adapter (type UINT).

Internally, it is directly connected to the data output of the ALR adapter.

### **Data Outputs**
- **Data value via plug ALR_OUT (D1)** – Data output to the ALR adapter (type LREAL).

Corresponds to the passed-through data value from socket AUI_IN.

### **Adapters**
- **Socket: AUI_IN** – Source (type `adapter::types::unidirectional::AUI`)

Accepts the input signals (event + UINT data).

- **Plug: ALR_OUT** – Sink (Type `adapter::types::unidirectional::ALR`)

Provides the output signals (event + LREAL data).

## Functionality

The FB AUI_TO_ALR functions purely as a coupling point. Events and data are forwarded directly from the socket AUI_IN to the plug ALR_OUT. The actual conversion from UINT to LREAL is not performed within this block, but rather implicitly through the adapter type definitions used (unidirectional protocols). Thus, the composite functions as a standardized interface to connect two different adapter protocols.

## Technical Features
- **Composite Type:** The FB does not have its own Execution Control Chart (ECC), but consists solely of a network connection between its two adapters.
- **Direct Pass-Through:** No internal logic, delays, or state changes – the function block is purely passive.
- **Adapter-Based:** The adapters used are defined as unidirectional interfaces, each carrying one event and one data value.

## State Overview

The function block has no states of its own, as it is implemented as a composite without ECC. Its behavior is entirely determined by the connected adapters.

## Application Scenarios
- **Protocol Adaptation in Agricultural Technology:** Use in controllers that need to mediate between different sensor or actuator interfaces.
- **Retrofit or Migration:** Enables the use of an ALR-compatible device on an existing AUI connection without having to implement the actual conversion itself.
- **Modular Cabling:** As a simple connecting link in a chain of adapter function blocks, e.g., in a fieldbus or communication hierarchy.

## Comparison with Similar Function Blocks

Similar converter function blocks exist for other adapter pairs (e.g., `AUI_TO_AREAL`, `AUI_TO_BOOL`). Unlike these, AUI_TO_ALR does not perform active data conversion but relies on implicit type conversion through the adapter definition. This makes it particularly lightweight and suitable for simple pass-through tasks.

## Conclusion

AUI_TO_ALR is a minimal yet clearly defined composite function block that establishes the connection between an AUI and an ALR adapter. Due to its simplicity and transparency, it is ideally suited for structured cabling in IEC 61499-based automation systems, especially in environments where different adapter protocols need to be coordinated.
