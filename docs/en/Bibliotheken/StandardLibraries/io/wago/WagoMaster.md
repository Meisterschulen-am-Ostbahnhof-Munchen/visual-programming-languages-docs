# WagoMaster
<img width="1355" height="250" alt="image" src="https://github.com/user-attachments/assets/61908fc9-2e56-4e6d-bb65-c71c1a08d10f" />
* * * * * * * * * *
## Introduction
The WagoMaster is a Service Interface Function Block for controlling and monitoring Wago bus systems. This block serves as the master component for communication with Wago I/O systems and enables the initialization and management of the bus connection.
![WagoMaster](WagoMaster.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization
- Linked to: QI, UpdateInterval

### **Event Outputs**
- **INITO**: Initialization Confirmation
- Linked to: QO, STATUS
- **IND**: Indication Event
- Linked to: STATUS, QO

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier - Controls service activation
- **UpdateInterval** (UINT): Defines the update interval for bus communication

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier - Displays the service execution status
- **STATUS** (WSTRING): Service Status - Contains status information and error messages

### **Adapters**
- **BusAdapterOut**: WagoBusAdapter - Establishes the connection to the Wago bus system

## Functionality
The WagoMaster initializes and manages communication with Wago bus systems. Upon activation via the INIT event, the service is started, and bus communication is performed periodically according to the defined UpdateInterval. The function block reports successful initialization via INITO and continuously provides status information via IND events.

## Technical Features
- Supports WSTRING for detailed status messages
- Configurable update interval for flexible adaptation to various application requirements
- Integrated qualifier variables (QI/QO) for reliable service control
- Specialized WagoBusAdapter for optimized bus communication

## State Overview
The function block goes through the following states:

1. **Inactive**: Before initialization
2. **Initialization**: Upon INIT event with QI=TRUE
3. **Active**: After successful initialization (QO=TRUE)
4. **Error**: In case of communication problems (STATUS with error message)

## Application Scenarios
- Control of Wago 750 series I/O modules
- Integration into automation systems with Wago controllers
- Monitoring and diagnostics of Wago bus networks
- Industry 4.0 applications with distributed Wago I/O systems

## ⚖️ Comparison with Similar Function Blocks
Compared to generic The WagoMaster bus master module offers specific optimizations for Wago bus systems and integrated status diagnostics via WSTRING. Its specialized adapter interface enables more efficient communication than universal bus adapters.

## Conclusion
The WagoMaster is a reliable and specialized module for integrating Wago bus systems into 4diac-based control systems. Its configurable parameters and detailed status feedback make it particularly suitable for demanding industrial automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
