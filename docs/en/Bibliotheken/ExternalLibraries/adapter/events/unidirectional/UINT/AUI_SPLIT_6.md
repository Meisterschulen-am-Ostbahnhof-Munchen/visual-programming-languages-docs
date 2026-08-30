# AUI_SPLIT_6

![AUI_SPLIT_6](./AUI_SPLIT_6.svg)

* * * * * * * * * *

## Introduction

The function block **AUI_SPLIT_6** is used to split an incoming **AUI adapter** (Application Universal Interface) into six outgoing AUI adapters. It is designed as a generic function block capable of distributing the incoming AUI signal to all six outputs without any data processing or logic.

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

The function block uses adapters exclusively for communication:

| Direction | Name | Type | Description |
| ---------- | ----- | ----- | -------------- |
| Input | **IN** | `adapter::types::unidirectional::AUI` | Incoming AUI adapter being split. |
| Output | **OUT1** | `adapter::types::unidirectional::AUI` | First outgoing AUI adapter. |
| Output | **OUT2** | `adapter::types::unidirectional::AUI` | Second outgoing AUI adapter. |
| Output | **OUT3** | `adapter::types::unidirectional::AUI` | Third outgoing AUI adapter. |
| Output | **OUT4** | `adapter::types::unidirectional::AUI` | Fourth outgoing AUI adapter. |
| Output | **OUT5** | `adapter::types::unidirectional::AUI` | Fifth outgoing AUI adapter. |
| Output | **OUT6** | `adapter::types::unidirectional::AUI` | Sixth outgoing AUI adapter. |

## Functionality

The function block forwards the AUI signal arriving at the adapter input **IN** to all six adapter outputs (**OUT1** to **OUT6**) without any delay or processing. No data manipulation takes place – the function block acts purely as a splitter for AUI signals.

## Technical Features

- The function block is declared as a **generic function block**: The attribute `eclipse4diac::core::GenericClassName` is set to `'GEN_AUI_SPLIT'`.
- There is no state management or event logic – the function block is purely combinatorial.
- The outputs are independent of each other; A fault at one output does not affect the others.
- By using AUI adapters, the function block is optimized for unidirectional signal transmission.

## State Overview

The function block has **no states**. It operates continuously without an internal state machine. The input signal is immediately and continuously mirrored to all outputs.

## Application Scenarios

- **Signal Distribution in Control Engineering**: When an AUI signal (e.g., a measured value or control command) needs to be passed on to multiple devices.
- **Redundancy or Parallel Processing**: Distribution of a signal to multiple identical downstream functional units.
- **Test and Simulation Setups**: Splitting an AUI signal for simultaneous monitoring and processing.

## Comparison with Similar Function Blocks

- **AUI_SPLIT_2 / AUI_SPLIT_4**: These function blocks split a signal across two or four outputs, respectively. **AUI_SPLIT_6** offers the largest number (6) of outputs, thus covering applications with many parallel destinations.
- **AUI_MERGE_***: Unlike splitters, merge blocks combine multiple AUI signals into one.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AUI_SPLIT_6** is a simple yet effective distribution block for AUI signals. It enables the star-shaped routing of an input signal to up to six independent outputs. Due to its generic nature and lack of logic, it is ideally suited for flexible and expandable automation solutions.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
