# DataPanel_MI_IX
<img width="1444" height="264" alt="image" src="https://github.com/user-attachments/assets/72a89eba-1aec-4942-99dc-d2ed708c0850" />
* * * * * * * * * *
## Introduction
The DataPanel_MI_IX is a service interface function block for Boolean input data, specifically designed for communication with digital inputs in automation systems. This block enables the initialization and querying of digital input signals via standardized service interfaces.
![DataPanel_MI_IX](DataPanel_MI_IX.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service initialization with parameters QI, PARAMS, u8SAMember, and Input
- **REQ**: Service request with parameter QI

### **Event Outputs**
- **INITO**: Initialization acknowledgment with parameters QO and STATUS
- **CNF**: Acknowledgement of the requested service operation with parameters QO, STATUS, and IN
- **IND**: Indication from the resource with parameters QO, STATUS, and IN

### **Data Inputs**
- **QI**: BOOL - Event input qualifier
- **PARAMS**: STRING - Service parameter
- **u8SAMember**: USINT - Node SA 224..239 (Initial value: MI::MI_00)
- **Input**: DataPanel_MI_DI_S - Identifies digital input 5A..8B (Initial value: DataPanel_MI_DI::Invalid)

### **Data Outputs**
- **QO**: BOOL - Event output qualifier
- **STATUS**: STRING - Service status
- **IN**: BOOL - Input data from the resource

### **Adapters**
No adapter interfaces available.

## Functionality
The function block initializes communication with a specific digital input via the INIT event. After successful initialization, the input state can be queried via the REQ event. The block returns the current state of the digital input and status information via the CNF and IND output events.

#
## Technical Features
- Supports specific SA member addressing in the range 224-239
- Uses structured input identification via the DataPanel_MI_DI_S data type
- Provides both request-based (REQ/CNF) and indication-based (IND) communication
- Initialization with configurable service parameters

## State Overview
The function block goes through the following states:

1. **Not Initialized**: Before INIT call
2. **Initialized**: After successful INIT/INITO sequence
3. **Ready**: Can process REQ/CNF cycles
4. **Active**: Processes incoming IND events from the resource

## Application Scenarios
- Monitoring of digital inputs in control cabinets
- Integration into PLC controllers for binary signal acquisition
- Industrial automation with specific SA addressing requirements
- Plants with distributed I/O systems

## ⚖️ Comparison with Similar Blocks
Compared to generic digital input blocks, DataPanel_MI_IX offers:

- Specific addressing for DataPanel systems
- Extended initialization options with parameter strings
- Additional IND functionality for event-based communication
- Structured input identification

## Conclusion
DataPanel_MI_IX is a specialized function block for the reliable acquisition of digital input signals in DataPanel environments. Its flexible parameterization and dual operating modes (demand-driven and event-driven) make it ideally suited for demanding automation applications with specific addressing requirements.
