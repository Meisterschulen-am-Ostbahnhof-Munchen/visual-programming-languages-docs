# AW_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AW_SPLIT_2`](AW_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

!Image of the function block (not available)
![AW_SPLIT_2_UNGATED](./AW_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **AW_SPLIT_2_UNGATED** splits an incoming unidirectional **adapter (AW)** into two identical outgoing adapters. It is implemented as a generic block and is suitable for applications where a signal path or adapter connection needs to be split between two subsequent components.

## Interface Structure

### **Event Inputs**

No event input available.

### **Event Outputs**

No event output available.

### **Data Inputs**

No data input available.

### **Data Outputs**

No data output available.

### **Adapters**

| Name | Direction | Type | Description |
| ------------- | ---------- | ----- | -------------- |
| `IN` | Socket | `adapter::types::unidirectional::AW` | Input Adapter – the unidirectional adapter to be shared. |
| `OUT1` | Plug | `adapter::types::unidirectional::AW` | First Output – receives an identical copy of the incoming adapter. |
| `OUT2` | Plug | `adapter::types::unidirectional::AW` | Second Output – also receives an identical copy of the incoming adapter. |

## Functionality

The function block forwards the unidirectional adapter (AW) connected to **IN** unchanged to both outputs **OUT1** and **OUT2**. No data manipulation, event control, or state logic takes place – the function block functions solely as a passive distribution unit at the adapter level.

Since the adapter type is declared as generic (`GEN_AW_SPLIT`), the function block can be used with various specific implementations of the AW adapter, as long as they follow the same `unidirectional::AW` protocol.

## Technical Features

- **Generic Function Block**: The function block is defined as a generic component (GenericClassName `GEN_AW_SPLIT`). It can be used in projects with different AW adapter types without requiring any modification of the function block itself.
- **No Runtime Logic**: The partitioning is purely structural – the function block (FB) has neither a state machine (ECC) nor does it process events or data. This results in no additional computational overhead at runtime.
- **License**: The function block is licensed under the **Eclipse Public License 2.0 (EPL-2.0)**.

## State Overview

The function block has no internal state machine. The routing is static and occurs without time- or event-dependent control.

## Application Scenarios

- **Distributing a measurement or status adapter path** to two independent processing units (e.g., a main controller and a monitoring component).
- **Building redundant processing chains**, where the same adapter stream is fed in parallel into two separate logic branches.
- **Test and diagnostic architectures** that split a data stream into both production logic and an analysis path.

## Comparison with Similar Function Blocks

- **AW_MERGE_2** – combines two AW inputs into one output (counterpart to the Split function).
- **Data Split Function Blocks** (e.g., `SPLIT_INT`, `SPLIT_BOOL`) operate on data signals, not on adapters. `AW_SPLIT_2_UNGATED` is specifically designed for splitting adapter interfaces.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

AW_SPLIT_2_UNGATED` is a simple yet essential generic function block for adapter distribution. It enables clean, reusable splitting of a unidirectional AW path without additional logic or runtime costs. Especially in modular, adapter-based control systems, it simplifies signal distribution and promotes component reusability.
