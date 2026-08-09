# logiBUS_ID

<img width="1903" height="313" alt="image" src="https://github.com/user-attachments/assets/52ce1d6d-0a92-42d7-8fd0-ce51ed902a2b" />
* * * * * * * * * *
## Introduction

The logiBUS_ID function block is an input service interface module for double-word input data (DWORD). It serves as an interface for communication with logiBUS input devices and enables the processing of digital input signals in 4diac control systems.
![logiBUS_ID](logiBUS_ID.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block with parameters and configuration
- **REQ**: Service Request - Triggers a query of the current input data

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Confirmation of Requested Service - Acknowledges a REQ request
- **IND**: Indication from Resource - Signals asynchronous events from the input device

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL) - Enables/Disables the service
- **PARAMS**: Service Parameters (STRING) - Configuration parameters for the service
- **Input**: Input Identifier (logiBUS_DI_S) - Identifies the input (I1..I8)
- **InputEvent**: Event Identifier (logiBUS_DI_Events_S) - Identifies the event (currently only REPEAT supported)

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL) - Service output status
- **STATUS**: Service Status (STRING) - Service status information
- **IN**: Input Data from the Resource (DWORD) - Current input data from the device

### **Adapter**

No adapter interfaces are available.

## Functionality

The logiBUS_ID function block acts as a bridge between the 4diac system and logiBUS input devices. Device parameters are configured during initialization (INIT). The block can process both synchronous queries (REQ/CNF) and asynchronous events (IND). Input data is provided as a 32-bit double word (DWORD).

## Technical Features

- Supports double-word input data (32-bit)
- Uses specific logiBUS data types for input and event configuration
- Offers both synchronous and asynchronous communication modes
- Initial values for input parameters are defined as "Invalid"

## State Overview

The function block has the following operating states:

- Not initialized (before INIT)
- Initialized and ready (after successful INITO)
- Query mode (during REQ/CNF cycle)
- Event mode (during IND signaling)

## Application Scenarios

- Connecting logiBUS input devices in automation systems
- Processing digital input signals in control applications
- Integration of button inputs (BUTTON_PRESS_UP, BUTTON_LONG_PRESS_HOLD, BUTTON_LONG_PRESS_UP)
- Monitoring of state changes at digital inputs

## ⚖️ Comparison with Similar Blocks

Compared to standard digital input blocks, logiBUS_ID:

- Specific logiBUS integration
- Advanced event handling
- Configurable parameters via STRING parameters
- Asynchronous event indication

## 🛠️ Related exercises

* [Exercise_011a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a2.md)

## Conclusion

The logiBUS_ID function block represents a specialized interface for logiBUS input devices in 4diac systems. Its flexible configuration and support for various operating modes make it ideal for applications requiring reliable processing of digital input signals with advanced event handling.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
