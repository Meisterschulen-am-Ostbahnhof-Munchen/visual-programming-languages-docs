# AX_SPLIT_9

<img width="618" height="438" alt="image" src="https://github.com/user-attachments/assets/12cd00f4-dd8c-4d77-8da8-187b2aef4a83" />
* * * * * * * * * *
## Introduction

The AX_SPLIT_9 function block is a generic component that splits a single AX adapter into nine separate AX outputs. The block acts as a distributor for unidirectional adapter connections and allows a single input signal to be distributed across multiple output channels.
![AX_SPLIT_9](AX_SPLIT_9.svg)

## Interface Structure

### **Event Inputs**

*No direct event inputs available*

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

*No direct data inputs available*

### **Data Outputs**

*No direct data outputs available*

### **Adapters**

**Input Adapters:**

- `IN` - Unidirectional AX adapter (socket)

**Output Adapters:**

- `OUT1` to `OUT9` - Nine unidirectional AX adapters (plugs)

## Functionality

The AX_SPLIT_9 block functions as an adapter splitter, which receives incoming signals and data from the input adapter. The input signal is distributed in parallel to all nine output adapters (`IN` to `OUT9`). Each output receives an identical copy of the input signal.

## Technical Features

- Generic implementation for maximum reusability
- Unidirectional adapter architecture
- Parallel signal distribution without delay
- No data processing or modification

## State Overview

The function block has a simple state: When the input adapter is activated, all nine output adapters are activated simultaneously.

## Application Scenarios

- Distribution of control signals to multiple actuators
- Distribution of sensor values to different processing units
- Signal distribution in complex control systems
- Redundant signal routing

## ⚖️ Comparison with Similar Blocks

Compared to simpler splitter blocks, AX_SPLIT_9 offers a higher number of outputs (9 instead of the typical 2-4). Compared to serial distributors, it allows simultaneous activation of all outputs without sequential delay.

Comparison with [E_SPLIT](../../../../../StandardLibraries/events/E_SPLIT.md)]

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AX_SPLIT_9 function block represents an efficient solution for the parallel distribution of unidirectional adapter signals. Its generic nature and the high number of outputs make it particularly suitable for complex control applications where a signal needs to be distributed to multiple receivers.