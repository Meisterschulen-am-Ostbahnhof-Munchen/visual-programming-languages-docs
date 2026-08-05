# DataPanel_MI_IXA

<img width="1325" height="246" alt="image" src="https://github.com/user-attachments/assets/32729d23-7ab3-4b67-a1f0-aba3120aaa91" />

* * * * * * * * * *

## Introduction
The DataPanel_MI_IXA is a composite function block for processing Boolean input data. It serves as an interface for digital inputs and enables the initialization and querying of input data via standardized service interfaces.


``` ![DataPanel_MI_IXA](DataPanel_MI_IXA.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization with the associated data QI, PARAMS, u8SAMember, and Input

- **REQ**: Service request with the associated data QI

### **Event Outputs**

- **INITO**: Initialization acknowledgment with the associated data QO and STATUS

### **Data Inputs**

- **QI**: Event input qualifier (BOOL)

- **PARAMS**: Service parameters (STRING)

- **u8SAMember**: Node SA 224..239 (USINT) with initial value MI::MI_00

- **Input**: Identification of the digital input DigitalInput_5A..8B with initial value Invalid

### **Data Outputs**

- **QO**: Event output qualifier (BOOL)

- **STATUS**: Service status (STRING)

### **Adapter**

- **IN**: Unidirectional adapter of type AX for data communication

## Functionality
This function block acts as a wrapper for the internal DataPanel_MI_IX block and forwards all events and data accordingly. During INIT initialization, all parameters are passed to the internal block, and confirmation is provided via INITO. REQ requests are forwarded directly to the internal block.

## Technical Features

- Uses special types from the DataPanel::io::MI::DI namespace
- Supports SA members in the range 224-239
- Provides initialization with default values for u8SAMember and Input

- Implements error handling via the Invalid initial value

## State Overview
The block has an initialized state and an operating state. After successful INIT initialization, the block is operational and can process REQ requests.

## Application Scenarios
- Connecting digital inputs in automation systems
- Integration into DataPanel I/O structures
- Use in control systems with SA bus communication
- Abstraction of hardware inputs in standardized interfaces

## ⚖️ Comparison with similar modules
Compared to simple digital input modules, DataPanel_MI_IXA offers extended initialization options and parameterization via the PARAMS input. SA member numbering enables specific addressing in larger systems.

## Conclusion
The DataPanel_MI_IXA is a robust and flexible function block for integrating digital inputs into complex automation systems. Its structured interface and extended parameterization options make it particularly suitable for demanding applications in industrial environments.