# AW_SPLIT_5

![AW_SPLIT_5](./AW_SPLIT_5.svg)

* * * * * * * * * *
## Introduction

The function block **AW_SPLIT_5** is used to distribute an incoming AW adapter ("actuator/paths") to five separate, identical AW outputs. It is designed as a generic function block and can be used in control architectures where a single signal or data connection needs to be split across multiple parallel paths.
## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

#### **Data Outputs**

None

#### **Adapter**

- **IN** (Socket) – Type: `adapter::types::unidirectional::AW`

Input interface for the original AW data stream.

- **OUT1** to **OUT5** (Plugs) – Type: `adapter::types::unidirectional::AW`

Five parallel output interfaces, each providing the same signal as the input.

## Functionality

The function block passively forwards the incoming AW adapter to all five outputs. There is no active logic or state machine – the distribution is achieved structurally through the internal wiring of the function block. Changes to the input are immediately reflected at all outputs.

## Technical Features

- **Generic Function Block** – The function block is declared as a generic type (`GEN_AW_SPLIT`) and can be reused in different contexts.
- **No Event Control** – Signal transmission occurs continuously without event-driven activation.
- **Unidirectional Adapters** – The adapter type used, `AW`, is unidirectional, meaning data flows only from the input to the outputs. Feedback from the outputs is not provided.

## State Overview

The function block (FB) does not have an internal state machine (ECC). There are no defined states or state transitions – the functionality is purely data flow-oriented.

## Application Scenarios

- **Distributing a sensor signal** to multiple downstream control units.
- **Parallel control** of multiple actuators that are to receive the same setpoint or command.
- **Test Setups** – Recording a signal or simultaneously forwarding it to various simulation and analysis components.

## Comparison with Similar Function Blocks

- **AW_SPLIT_N** – Another generic split FB that can be extended to a variable number of outputs. `AW_SPLIT_5` is a specialized variant with five fixed outputs.
- **Pure Data Splitters** – These operate on data types like `INT` or `BOOL` and use different interface types. `AW_SPLIT_5` is specifically designed for the AW adapter.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The `AW_SPLIT_5` is a simple yet useful component for splitting an AW adapter signal into five parallel paths. Its generic design allows for flexible use in various control projects within the 4diac IDE. The absence of an event and data interface reduces complexity to the essentials – pure signal duplication.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
