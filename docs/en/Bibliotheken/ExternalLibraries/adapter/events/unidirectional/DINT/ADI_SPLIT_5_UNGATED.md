# ADI_SPLIT_5_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ADI_SPLIT_5`](ADI_SPLIT_5.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ADI_SPLIT_5_UNGATED](./ADI_SPLIT_5_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **ADI_SPLIT_5_UNGATED** is used to split an incoming ADI adapter (unidirectional) into five identical output adapters. It is designed as a generic function block (Generic FB) and can be used in IEC 61499-based systems to forward a signal or data stream to multiple subsequent function blocks.

## Interface Structure

### **Event Inputs**

None

#### **Event Outputs**

None

#### **Data Inputs**

- **IN** (Socket, Type: `adapter::types::unidirectional::ADI`)

Input adapter that provides the signal to be distributed.

### **Data Outputs**

- **OUT1** (Plug, Type: `adapter::types::unidirectional::ADI`)
- **OUT2** (Plug, Type: `adapter::types::unidirectional::ADI`)
- **OUT3** (Plug, Type: `adapter::types::unidirectional::ADI`)
- **OUT4** (Plug, Type: `adapter::types::unidirectional::ADI`)
- **OUT5** (Plug, Type: `adapter::types::unidirectional::ADI`)

All outputs are independent instances of the same adapter type and receive identical data.

### **Adapters**

This module operates exclusively via adapter interfaces. No event or data inputs/outputs in the traditional sense are used. All communication takes place via the ADI adapters, which implicitly control signal and data forwarding.

## Functionality

The function block **ADI_SPLIT_5_UNGATED** receives an ADI adapter via the socket **IN** and forwards the data and events it contains in parallel to the five plugs **OUT1** to **OUT5**. No processing or transformation of the data takes place – the block functions as a passive distributor (fan-out).

Since these are unidirectional ADI adapters, the signal is only passed from the input side to the output side; feedback from the outputs is not intended.

## Technical Features

- **Generic Function Block**: The class `GEN_ADI_SPLIT` allows for flexible reuse, e.g., by parameterizing the type or number of outputs (here fixed at five).
- **Adapter-based**: No direct event or data inputs/outputs – all signal transmission occurs via the adapter interfaces.
- **Unidirectional**: The adapters are defined as `unidirectional`, meaning data flows only in one direction (from IN to OUT1-5).
- The function block contains no internal state logic or timing control.

## State Overview

The **ADI_SPLIT_5_UNGATED** has no states of its own. It is a purely combinational function block that reacts immediately to incoming adapter data and passes it on unchanged to all outputs.

## Application Scenarios

- **Signal Cascade**: Distribution of a sensor signal (e.g., temperature, pressure) to multiple evaluation and control blocks.
- **Diagnostics and Monitoring**: Simultaneous distribution of a data stream to processing and logging modules.
- **Load Balancing**: Parallel processing of the same input using different algorithms (e.g., filters, limit monitoring, visualization).

## Comparison with Similar Components

In the IEC 61499 environment, variants such as **SPLIT_2**, **SPLIT_3**, or **SPLIT_N** are common, providing a different number of outputs. **ADI_SPLIT_5_UNGATED** is a specific implementation for exactly five outputs using unidirectional ADI adapter interfaces. Unlike event-based split components (e.g., `E_SPLIT`), distribution here is achieved via adapters, enabling type-based and typically data-oriented communication.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **ADI_SPLIT_5_UNGATED** is a simple yet useful function block for distributing a unidirectional ADI signal to up to five subsequent function blocks. It is particularly suitable for modular automation solutions where an input signal needs to be used multiple times without requiring additional control logic. Its generic implementation allows it to be reused in various contexts.
