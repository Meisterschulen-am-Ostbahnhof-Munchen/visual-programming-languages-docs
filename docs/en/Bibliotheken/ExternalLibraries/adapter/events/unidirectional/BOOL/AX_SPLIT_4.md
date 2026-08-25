# AX_SPLIT_4

<img width="705" height="331" alt="image" src="https://github.com/user-attachments/assets/66b5a8a2-0227-4af4-8d00-17e48bfbe98c" />
* * * * * * * * * *
## Introduction

The AX_SPLIT_4 function block is a generic function block that splits one AX adapter input into four separate AX adapter outputs. The block acts as a distributor for unidirectional AX adapters and enables the transmission of data and events to multiple receivers.
![AX_SPLIT_4](AX_SPLIT_4.svg)

## Interface Structure

### **Event Inputs**

No direct event inputs available (event processing is handled via adapters)

### **Event Outputs**

No direct event outputs available (event processing is handled via adapters)

### **Data Inputs**

No direct data inputs available (data processing is handled via adapters)

### **Data Outputs**

No direct data outputs available (data processing is handled via adapters)

### **Adapters**

**Input Adapter:**

- `IN` - AX Adapter (Socket) - Receives unidirectional AX data and events

**Output Adapter:**

- `OUT1` - AX Adapter (Plug) - First output channel
- `OUT2` - AX Adapter (Plug) - Second Output Channel
- `OUT3` - AX Adapter (Plug) - Third Output Channel
- `OUT4` - AX Adapter (Plug) - Fourth Output Channel

## Functionality

The AX_SPLIT_4 block receives data and events via the input adapter `IN` and distributes them in parallel to all four output adapters (`OUT1` to `OUT4`). All incoming information is forwarded to all outputs simultaneously, thus achieving a 1:4 distribution.

## Technical Features

- Generic implementation for maximum reusability
- Uses unidirectional AX adapters for data transmission
- No buffering or delay in data transmission
- Parallel distribution without output prioritization

## State Overview

The function block operates statelessly – incoming data and events are immediately forwarded to all outputs without storing any internal state.

## Application Scenarios

- Distribution of control commands to multiple actuators
- Broadcasting of sensor data to various processing units
- Distribution of control information in distributed systems
- Redundant data distribution for safety applications

## ⚖️ Comparison with Similar Function Blocks

Compared to simple split function blocks, AX_SPLIT_4 offers a specific 1:4 split for AX adapters. Other split variants may support different numbers of outputs or other adapter types.

Comparison with [E_SPLIT](../../../../../StandardLibraries/events/E_SPLIT.md)

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AX_SPLIT_4 function block offers a simple and efficient solution for distributing AX adapter data to four parallel outputs. Its generic nature and the use of standardized adapters make it versatile for use in various automation applications.