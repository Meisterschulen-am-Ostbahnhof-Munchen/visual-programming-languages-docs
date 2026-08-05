# AX_SPLIT_5

<img width="705" height="370" alt="image" src="https://github.com/user-attachments/assets/cccee27c-e0ef-4c16-8e20-6ba612d866e5" />

* * * * * * * * * *

## Introduction
The AX_SPLIT_5 function block is a generic function block used to split an AX adapter into five separate AX outputs. The block enables the distribution of an input signal to multiple output channels and is particularly useful in control applications where signals need to be distributed to different components.


![AX_SPLIT_5](AX_SPLIT_5.svg)

## Interface Structure

### **Event Inputs**
No direct event inputs available (event processing is handled via adapters)

### **Event Outputs**
No direct event outputs available (event processing is handled via adapters)

### **Data Inputs**
No direct data inputs available

### **Data Outputs**
No direct data outputs available

### **Adapters**
**Input Adapters:**
- **IN** - AX unidirectional adapter (socket)

**Output Adapters:**
- **OUT1** - AX unidirectional adapter (plug)
- **OUT2** - AX unidirectional adapter (plug)
- **OUT3** - AX unidirectional adapter (plug)
- **OUT4** - AX unidirectional adapter (plug)
- **OUT5** - AX Unidirectional Adapter (Plug)

## Functionality
The AX_SPLIT_5 function block receives signals via the input adapter IN and simultaneously distributes them to all five output adapters (OUT1 to OUT5). Every event received at the IN adapter is forwarded to all outputs in parallel, thus achieving a 1:5 distribution.

## Technical Features
- Generic function block with the class 'GEN_AX_SPLIT'
- Uses unidirectional AX adapters for communication
- No data processing or transformation
- Pure event distribution without delay

## State Overview
The block has a simple state: In its idle state, it waits for incoming events at the IN adapter. Upon receiving an event, all five output adapters are immediately activated.


## Application Scenarios

- Distribution of control signals to multiple actuators
- Distribution of sensor values to different processing units
- Parallel activation of multiple subsystems
- Signal distribution in decentralized control architectures

## ⚖️ Comparison with similar components
Compared to simple split components, the AX_SPLIT_5 offers a fixed number of five outputs. Other split variants can offer different numbers of outputs or configurable distribution logics. The focus here is on the simple, fixed 1:5 distribution.

Comparison with [E_SPLIT](../../../../../StandardLibraries/events/E_SPLIT.md)]

## Conclusion
The AX_SPLIT_5 is a specialized distribution component whose simple and deterministic operation makes it ideal for applications where a signal needs to be distributed to exactly five receivers. The use of standardized AX adapters ensures compatibility within existing control systems.