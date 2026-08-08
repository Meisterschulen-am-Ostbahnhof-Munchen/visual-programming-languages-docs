# AIWS_MUX_2
![AIWS_MUX_2](./AIWS_MUX_2.svg)

* * * * * * * * * *
The AIWS_MUX_2 is a generic multiplexer for the AIWS adapter. It allows selection between two AIWS input signals (IN1, IN2) and forwards the selected signal to the output (OUT). The selection is triggered by an event using an index K.

| Event | Description | With Variables |
|----------|---------------|---------------|
| REQ | Event to Trigger Index Setting | K |


| Event | Description |
|----------|--------------|
| CNF | Selection Confirmation |


| Variable | Type | Description |
|----------|------|--------------|
| K | UINT | Selection Index (0 = IN1, 1 = IN2) |


None (signal transmission is exclusively via adapters).

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Plug (Output) | OUT | AIWS | Output signal, provides the selected AIWS signal |
| Socket (Input) | IN1 | AIWS | First AIWS Input (Selection at K=0) |
Socket (Input) | IN2 | AIWS | Second AIWS Input (Selection at K=1) |

## Functionality
When an event occurs at the **REQ** input, the current value of the index **K** is evaluated:

- If **K = 0**, the signal from **IN1** is passed through to **OUT**.
- If **K = 1**, the signal from **IN2** is passed through to **OUT**.

After successful selection, the **CNF** event is output. The function block operates in an event-driven manner and does not continuously update the output adapter values.

- **Generic Function Block**: The actual class name is `GEN_AIWS_MUX` (stored in the attribute `eclipse4diac::core::GenericClassName`). This allows the function block to be used in various forms (e.g., generated for different adapter types).
- **Adapter Technology**: The function block uses unidirectional AIWS adapters (Eclipse 4diac). The interface is purely adapter-based; no individual variables are used for the analog values.
- **Copyright**: Created by Franz Höpfinger for HR Agrartechnik GmbH (Version 1.0, 2026-05-28) under the EPL-2.0 license.
- **Compilation**: Uses the import package `eclipse4diac::core::TypeHash`.

The function block does not contain an explicit state machine (ECC) in the XML description. The implicit behavior can be described as follows:

1. **Idle State** – no REQ event is pending.

2. During REQ, K is evaluated and the switchover occurs immediately.

3. CNF is then sent, and the function block returns to its idle state.

Multiple REQ events can occur consecutively; ongoing processing is not blocked.

- **Sensor Switching**: Selection between two analog measured values (e.g., temperature or pressure) in an automation controller.
- **Operating Mode Change**: Switching between two different signal sources, such as different measuring points or redundant sensors.
- **Test and Simulation Environments**: Easy switching of the AIWS signal to be analyzed.

- **AIWS_MUX_4** (if available): Offers four inputs instead of two and requires more index bits.
- **Standard Multiplexer (Data MUX)**: Usually works with single basic variables (e.g., INT, REAL) and without an adapter. In contrast, the AIWS_MUX_2 encapsulates complex signal structures in a single adapter, simplifying reuse and reducing wiring at the function block level.
- **Event-driven vs. continuous multiplexing**: The block only updates on REQ, which is sufficient for many applications and saves resources.

The AIWS_MUX_2 is a compact, generic multiplexer for AIWS adapters. Its simple event-driven selection based on an index makes it ideal for switching between two analog signals. The use of Eclipse-4diac adapter technology ensures a clean, reusable interface and facilitates integration into complex automation solutions.


* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de