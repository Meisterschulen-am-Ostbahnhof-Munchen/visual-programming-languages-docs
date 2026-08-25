# AI_SPLIT_4

![AI_SPLIT_4](./AI_SPLIT_4.svg)

* * * * * * * * * *
## Introduction

The function block **AI_SPLIT_4** is a generic block that splits a unidirectional analog input (AI) into four separate analog outputs. It serves as a signal distributor for analog signals and allows a single AI signal to be passed on to various subsequent blocks. The block is entirely adapter-based and has no built-in event or data interfaces. It is available under the Eclipse Public License 2.0.
## Interface Structure

### **Event Inputs**

- None

### **Event Outputs**

- None

### **Data Inputs**

- None

### **Data Outputs**

- None

### **Adapters**

| Direction | Name | Type | Description |
|----------|-----|-----|--------------|
| **Socket (Input)** | `IN` | `adapter::types::unidirectional::AI` | Input of the analog signal to be distributed |
| **Plug (Output)** | `OUT1` | `adapter::types::unidirectional::AI` | First output (copy of the input signal) |
| **Plug (Output)** | `OUT2` | `adapter::types::unidirectional::AI` | Second output (copy of the input signal) |
| **Plug (Output)** | `OUT3` | `adapter::types::unidirectional::AI` | Third output (copy of the input signal) |
| **Plug (output)** | `OUT4` | `adapter::types::unidirectional::AI` | Fourth output (copy of the input signal) |

## Functionality

This module provides a simple 1:4 distribution of an analog signal. The signal present at adapter `IN` is passed unchanged to all four output adapters (`OUT1` … `OUT4`). No scaling, filtering, or conversion takes place – the signal is copied 1:1 at the fieldbus level. The number of channels is fixed at four.

## Technical Features

- **Pure Adapter Block**: The function block contains no event or data interfaces; all communication takes place via adapters.
- **Generic Type**: The block is identified as generic via the attribute `GenericClassName` (`'GEN_AI_SPLIT'`). A specific type can be derived from this in the 4diac IDE.
- **Unidirectional**: The adapter type used, `unidirectional::AI`, only transmits data in one direction (from the socket to the plugs).
- **No State Machine**: Since there are no events, there is no ECC (Execution Control Chart). The function block is purely data flow-oriented.

## State Overview

The function block does not have a state machine – it is event-free and continuously passes the input signal to all outputs. Therefore, a state overview is not available.

## Application Scenarios

- **Analog Signal Distribution**: A single sensor value (e.g., temperature, pressure, fill level) is to be sent to multiple control logics or visualization components simultaneously.
- **Redundancy or Monitoring**: The signal is forwarded in parallel to a main controller and an independent monitoring module.
- **Decoupling of Subsystems**: In a modular control system, different subsystems can receive the same analog value without requiring multiple access to the sensor.

## Comparison with Similar Modules

- **AI_SPLIT_2 / AI_SPLIT_8**: Similar modules with 2 or 8 outputs, respectively. The choice depends on the required number of parallel signals.
- **AI_SELECT** or **AI_MUX**: These modules select one input from several, while the AI_SPLIT multiplies the input signal.
- **Standard Adapter Split**: Some libraries offer generic split function blocks, but these often require additional event or data interfaces. The AI_SPLIT_4, with its pure adapter approach, is particularly easy to integrate into adapter chains.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AI_SPLIT_4** function block is a specialized yet easy-to-use function block for multiplying analog signals. Thanks to its pure adapter interface, it can be seamlessly integrated into 4diac projects without additional event logic. It is particularly suitable for modular and scalable automation solutions where a single measured value needs to be distributed to multiple devices.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
