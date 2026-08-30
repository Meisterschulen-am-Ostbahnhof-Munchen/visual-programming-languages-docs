# AR_SPLIT_8

![AR_SPLIT_8](./AR_SPLIT_8.svg)

* * * * * * * * * *

## Introduction

The AR_SPLIT_8 function block is used to split a single unidirectional AR adapter signal into eight identical AR outputs. It is implemented as a generic function block and enables simple signal distribution without additional logic.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Name | Type | Direction |
| ------------- | ----- | ---------- |
| **IN** | `adapter::types::unidirectional::AR` | Socket (Input) |
| **OUT1** – **OUT8** | `adapter::types::unidirectional::AR` | Plug (Output) |

## Functionality

The function block receives the complete interface of a unidirectional AR adapter via the **IN** socket. Events and data present at this interface are replicated to all eight output adapters (**OUT1** to **OUT8**) without delay or modification. Thus, a single data/event stream can be distributed in parallel to up to eight downstream components.

## Technical Features

- The function block is generic (generic FB) and is identified as such by the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AR_SPLIT'`.
- There is no internal state diagram (ECC) – the forwarding is direct and stateless at all times.
- The implementation is designed for unidirectional AR adapters; use with bidirectional adapters is not supported.

## State Overview

The function block has no explicit state diagram and operates statelessly. Adapter distribution occurs continuously, without any time dependencies or internal logic.

## Application Scenarios

- **Distribution of Control Signals**: A central control algorithm (e.g., a PID controller) distributes its output via AR to several parallel actuators.
- **Broadcast in Star-Shaped Plant Sections**: Signals from a higher-level controller are distributed to eight identical substations.
- **Test and Simulation Environments**: A signal generator feeds several test objects simultaneously with the same adapter signal.

## Comparison with Similar Function Blocks

- **AR_SPLIT_2, AR_SPLIT_4**: Analog function blocks with 2 and 4 outputs, respectively; AR_SPLIT_8 extends the number to eight outputs.
- **AR_MERGE_X**: Combines multiple AR signals into one – opposite function.
- **SPLIT_* for other adapter types**: Split blocks exist for other unidirectional and bidirectional adapter definitions that implement a similar splitting logic.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AR_SPLIT_8 is a simple yet extremely useful block for distributing unidirectional AR adapter signals across up to eight parallel paths. Its generic implementation allows for flexible use in various automation projects without requiring the implementation of additional signal multiplication logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
