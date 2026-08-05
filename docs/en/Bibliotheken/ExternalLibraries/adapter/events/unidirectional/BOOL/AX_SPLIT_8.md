# AX_SPLIT_8
<img width="618" height="415" alt="image" src="https://github.com/user-attachments/assets/2f54eb67-b52a-498d-b27b-6225a19450fd" />
* * * * * * * * * *
## Introduction
The AX_SPLIT_8 function block is a generic function block that splits a single AX adapter into eight separate AX outputs. It is used to distribute adapter signals in complex control architectures.
![AX_SPLIT_8](AX_SPLIT_8.svg)

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
- **IN** (Socket): AX adapter input type `adapter::types::unidirectional::AX`

**Output Adapter:**

- **OUT1** (Plug): AX adapter output 1 type `adapter::types::unidirectional::AX`
- **OUT2** (Plug): AX adapter output 2 type `adapter::types::unidirectional::AX`
- **OUT3** (Plug): AX adapter output 3 of type `adapter::types::unidirectional::AX`
- **OUT4** (Plug): AX adapter output 4 of type `adapter::types::unidirectional::AX`
- **OUT5** (Plug): AX adapter output 5 of type `adapter::types::unidirectional::AX`
- **OUT6** (Plug): AX adapter output 6 of type `adapter::types::unidirectional::AX`
- **OUT7** (Plug): AX adapter output 7 of type `adapter::types::unidirectional::AX`
- **OUT8** (Plug): AX adapter output 8 of type `adapter::types::unidirectional::AX`

## Functionality
The AX_SPLIT_8 function block distributes incoming Adapter signals from the input adapter IN are simultaneously sent to all eight output adapters (OUT1 to OUT8). As a unidirectional adapter block, it forwards all incoming events and data in parallel to all connected outputs.

## Technical Features
- Generic function block with the generic class 'GEN_AX_SPLIT'
- Uses unidirectional AX adapters
- No internal signal processing or filtering
- Parallel signal distribution without delay

## State Overview
The block has no internal state and operates stateless. All incoming signals are immediately forwarded to all outputs.

## Application Scenarios
- Distribution of control signals to multiple actuators
- Distribution of sensor information to different processing units
- Signal distribution in redundant system architectures
- Cascading of adapter-based control systems

## ⚖️ Comparison with Similar Blocks
Compared to other split blocks, AX_SPLIT_8 offers a fixed number of eight outputs and operates exclusively at the adapter level. Other split components can have a variable number of outputs or operate at the data or event level.

Comparison with [E_SPLIT](../../../../../StandardLibraries/events/E_SPLIT.md)]

## Conclusion
The AX_SPLIT_8 function block provides a simple and efficient solution for distributing adapter signals in 4diac systems. Its fixed output of eight ports makes it particularly suitable for standardized distribution tasks in industrial control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)]
