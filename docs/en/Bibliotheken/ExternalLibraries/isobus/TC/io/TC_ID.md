# TC_ID
<img width="1359" height="261" alt="image" src="https://github.com/user-attachments/assets/430341ae-f535-482b-b9f2-3bfad916e8e4" />
* * * * * * * * * *
## Introduction
The TC_ID function block is an input service interface module for double-word input data. It serves as an interface for communication with tractor control (TC) input devices and enables access to specific input data via defined data words.
![TC_ID](TC_ID.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization
- Linked to: QI, PARAMS, wDevElementNumb, wDDI
- **REQ**: Service Request
- Linked to: QI

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Service Request
- Linked to: QO, STATUS, IN
- **IND**: Resource Indication
- Linked to: QO, STATUS, IN

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **wDevElementNumb** (UINT): Requested Element Number TC Input
- **wDDI** (UINT): Data Dictionary Identifier of the input

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status
- **IN** (DWORD): Input data from the resource

### **Adapter**
No adapter interfaces are available.

## Functionality
The TC_ID block enables access to TC input data via standardized service interfaces. During initialization (INIT), the device parameters are configured. Service requests (REQ) trigger data acquisition, with the results being returned via CNF or IND events. The block supports both requested and spontaneous data deliveries from the connected resource.

## Technical Features
- Processes double-word data (DWORD, 32-bit)
- Supports Data Dictionary Identifiers (DDI) for standardized data access
- Provides both requested (CNF) and spontaneous (IND) data deliveries
- Includes comprehensive status feedback via STRING parameters

## State Overview
The block goes through typical service interface states:

1. **Not Initialized**: Before an INIT event
2. **Initialized**: After successful INITO feedback
3. **Ready**: For REQ requests
4. **Active**: During data querying and processing

## Application Scenarios
- Agricultural control systems (ISOBUS environment)
- Tractor control and monitoring
- Data acquisition from TC input devices
- Automated agricultural systems with standardized data formats

## ⚖️ Comparison with Similar Blocks
Compared to simple input blocks, TC_ID offers:

- Standardized ISOBUS Interface
- DDI-based data identification
- Comprehensive status and error management
- Both requested and spontaneous data transmission

## 🛠️ Related Exercises
* [Exercise_060](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion
The TC_ID function block provides a robust and standardized interface for TC input data in ISOBUS environments. Its flexible architecture, with both requested and spontaneous data transmission mechanisms, makes it ideal for complex agricultural applications that require reliable access to specific input data.