# AE_MUX_4
![AE_MUX_4](./AE_MUX_4.svg)

* * * * * * * * * *
The function block **AE_MUX_4** implements a 4-way multiplexer for AE adapters ("Analog Events"). Depending on an index **K**, it selects exactly one of the four input adapters (IN1..IN4) and forwards its signal to the output adapter **OUT**. The function block is designed as a generic (template-based) block and is instantiated as `GEN_AE_MUX`.


| Event | Description |
|----------|-------------|
| **REQ** | Request to switch to the input determined by **K** |


| Event | Description |
|----------|-------------|
| **CNF** | Confirmation that the index **K** has been adopted and the corresponding input has been set to **OUT** |


| Name | Type | Description |
|------|-----|-------------|
| **K** | UINT | Index for selecting the active input (values 0…3) |


No data outputs. Values are forwarded exclusively via the adapter interfaces.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**

| Adapter | Direction | Type | Description |


| Adapter | Direction | Type | Description |



| Adapter | Direction | Type | Description |


**OUT** | Plug | `adapter::types::unidirectional::AE` | Output adapter – provides the signal of the selected input |
**IN1** | Socket | `adapter::types::unidirectional::AE` | Input 1 (K = 0) |
**IN2** | Socket | `adapter::types::unidirectional::AE` | Input 2 (K = 1) |
**IN3** | Socket | `adapter::types::unidirectional::AE` | Input 3 (K = 2) |
**IN4** | Socket | `adapter::types::unidirectional::AE` | Input 4 (K = 3) |
**IN1** | Socket | `adapter::types::unidirectional::AE` | Input 4 (K = 3) |
**IN2** | Socket | `adapter::types::unidirectional::AE` | Input 4 (K = 3) |
**IN3** | Socket | `adapter::types::unidirectional::AE` | Input 4 (K = 3) |
**IN4** | Socket | `adapter::types::unidirectional::AE` | Input 4 (K = 3) |
**IN1** | Socket | `adapter::types::unidirectional::AE` |
## Functionality

The module operates in an event-driven manner:

1. After startup (or reset), no specific input is assigned to the output.

2. A **REQ** event reads the current value of the data input **K** (allowed values: 0, 1, 2, 3).

3. Depending on **K**, the corresponding socket adapter is switched to the plug adapter **OUT**:

- K = 0 → IN1
- K = 1 → IN2
- K = 2 → IN3
- K = 3 → IN4

4. After successful switching, the **CNF** event is output. The output adapter then continuously updates all further signal updates of the selected input.

The module itself does not perform any signal processing – it functions solely as a selective connection.

- **Generic Type**: The function block (FB) is implemented as a generic class (`eclipse4diac::core::GenericClassName = 'GEN_AE_MUX'`). A user-defined type hash can be specified during declaration.
- **No State Machine Implementation Visible**: The logic is presumably generated automatically by the 4diac IDE based on the interfaces or provided via a separate ECC file.
- **Component-Based Use**: The inputs and outputs are defined as adapters, allowing the function block to be integrated into standardized AE transmission paths.
- **Value Range of K**: The index is declared as `UINT`; values outside the range 0 to 3 are undefined and can lead to undefined behavior.


Since there is no explicit state machine (ECC) in the XML, the behavior is simplified as:

- **IDLE** – Waiting for a REQ event.
- **ACTIVE** – Upon receipt of REQ: Multiplexer switching, output of CNF, return to IDLE.

There are no persistent states that can be observed externally.

- **Selection of an analog signal** from up to four sources (e.g., sensors) for further processing in a subsequent AE component.
- **Switching of measurement ranges** in a control engineering application without signal loss.
- **Redundancy switching** to a substitute signal if the current input fails (due to a change in K).

- **MUX function blocks for simple data types** (e.g., `MUX` for `INT`, `REAL`) operate analogously, but with data inputs/outputs instead of adapters.
- **`AE_MUX_2` / `AE_MUX_8`** would be extensions with fewer or more inputs – the function block presented here covers four channels.
- Compared to a **data multiplexer**, the adapter approach allows the transmission of complex, event-driven signal structures (events + data), as are common in IEC 61499.


The **AE_MUX_4** is a compact, generic multiplexer for AE adapters. It enables clean, event-driven switching between four analog signal sources and integrates seamlessly into a 61499 control environment. Its simple interface and the use of adapters make it a flexible component for selection tasks in industrial automation solutions.

---

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de