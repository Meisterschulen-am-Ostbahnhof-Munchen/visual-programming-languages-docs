# AX_SPLIT_6
<img width="705" height="397" alt="image" src="https://github.com/user-attachments/assets/1b0e2281-e41d-47e1-bad4-9690070e18e8" />
* * * * * * * * * *
## Introduction
The AX_SPLIT_6 function block is a generic component used to split a single AX adapter into six separate AX outputs. This component enables the distribution of signals and data streams from a central source to multiple devices.
![AX_SPLIT_6](AX_SPLIT_6.svg)

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
**Input Adapter:**
- **IN** (Socket): Receives incoming AX signals from the source system

**Output Adapter:**

- **OUT1** (Plug): First output channel
- **OUT2** (Plug): Second output channel
- **OUT3** (Plug): Third output channel
- **OUT4** (Plug): Fourth output channel
- **OUT5** (Plug): Fifth output channel
- **OUT6** (Plug): Sixth output channel Output Channel

All adapters use the type: `adapter::types::unidirectional::AX`

## Functionality
The AX_SPLIT_6 module functions as a signal distributor. It receives signals via the input adapter IN and forwards them in parallel to all six output adapters (OUT1 to OUT6). Since these are unidirectional AX adapters, signal transmission only occurs in one direction – from the input to the outputs.

## Technical Features
- Generic function block with the class 'GEN_AX_SPLIT'
- Uses unidirectional AX adapters for communication
- No data processing or modification, only signal distribution
- Parallel output to all six outputs

## State Overview
The block has a simple state:

- **Ready**: Receives signals from IN and distributes them to OUT1-OUT6

## Application Scenarios
- Distribution of control signals to multiple actuators
- Splitting of sensor values to different processing units
- Signal distribution in redundant systems
- Multi-casting of control commands

## ⚖️ Comparison with Similar Blocks
Compared to other splitter blocks, AX_SPLIT_6 offers a fixed number of six outputs, which is advantageous for specific applications. Other splitters can offer more or fewer outputs, but may be more complex to configure.

Comparison with [E_SPLIT](../../../../../StandardLibraries/events/E_SPLIT.md)]

## Conclusion

AX_SPLIT_6 is a specialized distribution module ideally suited for applications where a signal needs to be distributed to exactly six receivers. Its simple structure and the use of standardized AX adapters make it a reliable solution for signal distribution tasks in automation systems.
