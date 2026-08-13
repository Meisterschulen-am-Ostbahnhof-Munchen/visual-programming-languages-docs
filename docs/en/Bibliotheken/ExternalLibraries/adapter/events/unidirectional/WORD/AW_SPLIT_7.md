# AW_SPLIT_7

![AW_SPLIT_7](./AW_SPLIT_7.svg)

* * * * * * * * * *
## Introduction

The function block `AW_SPLIT_7` is used to distribute a single incoming AW adapter (unidirectional) to seven identical AW adapter outputs. It is designed as a generic function block and enables the simple distribution of adapter connections without data processing.
## Interface Structure

### **Event Inputs**

- None

### **Event Outputs**

- None

### **Data Inputs**

- None

### **Data Outputs**

- None

### **Adapter**

| Type | Name | Direction | Description |
|-----|------|-----------|--------------|
| `adapter::types::unidirectional::AW` | IN | Socket (Input) | Incoming AW adapter, which is distributed to the outputs. |
| `adapter::types::unidirectional::AW` | OUT1 … OUT7 | Plug (Output) | Seven outgoing adapters, each providing the same data as the input. |

## Functionality

This module does not have its own event or data ports. It functions purely as an adapter duplication: The incoming AW adapter (`IN`) is internally passed through to all seven output adapters (`OUT1` to `OUT7`) without any processing. Each module connected to one of the outputs thus receives exactly the same instance of the AW adapter.

The implementation is generic (Generic FB), so the actual adapter type can be dynamically determined by parameters. This makes the function block suitable for any unidirectional AW interface.

## Technical Features

- **Generic Type**: The function block uses the generic function block mechanism to determine the specific adapter type at runtime or during compilation. The placeholder `GEN_AW_SPLIT` is replaced by the actual adapter.
- **Pure Adapter Distribution**: No data copying or serialization takes place – the references to the AW adapter are passed on.
- **No Event Control Required**: The function block operates asynchronously and without time dependencies, as adapters are inherently data-specific.

## State Overview

The `AW_SPLIT_7` function block does not have an internal state machine. Its behavior is deterministic and consists solely of passing through the adapter. A state machine is therefore not required.

## Application Scenarios

- **Distributing sensor adapters** to multiple evaluation or control units in an automation axis.
- **Splitting a bus signal** into multiple parallel connections (e.g., for redundant monitoring).
- **Cascading adapters** in an IEC 61499 system when multiple function blocks need to access the same data stream.

## Comparison with Similar Function Blocks

- **SPLIT Function Blocks with a Limited Number of Outputs**: Other split function blocks (e.g., `SPLIT_2`, `SPLIT_4`) distribute adapters across fewer channels – here, exactly seven outputs are provided.
- **Adapter Multiplexers**: Unlike multiplexers that select between multiple inputs, the `AW_SPLIT_7` distributes a single input without selection.
- **Data Split Function Blocks**: If the function block had data and event ports, it would have to copy data. Adapter-based splits are more efficient because only references are passed on.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The `AW_SPLIT_7` is a simple yet useful generic function block for duplicating a unidirectional AW adapter to seven outputs. Its strengths lie in its flexible type adaptation and efficient, event-free routing. It is particularly suitable for modular automation systems where an adapter needs to be used multiple times.
