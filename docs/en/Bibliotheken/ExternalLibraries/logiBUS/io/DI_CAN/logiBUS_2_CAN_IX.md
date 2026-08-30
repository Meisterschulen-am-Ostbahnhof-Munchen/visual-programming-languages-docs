# logiBUS_2_CAN_IX

<img width="1949" height="337" alt="image" src="https://github.com/user-attachments/assets/dfea6f34-2a15-48ff-87b0-54e6821f2c0d" />
* * * * * * * * * *
## Introduction

The function block `logiBUS_2_CAN_IX` is a service interface function block for Boolean input data, specifically designed for integrating logiBUS systems with CAN bus communication. It serves as an input interface for digital signals and enables communication between the control system and connected CAN-enabled devices.
![logiBUS_2_CAN_IX](logiBUS_2_CAN_IX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- Linked to: QI, PARAMS, Input
- **REQ**: Service Request Event
- Linked to: QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Service Request
- Linked to: QO, STATUS, IN
- **IND**: Indication from Resource
- Linked to: QO, STATUS, IN

### **Data Inputs**

- **QI**: BOOL - Event Input Qualifier
- **PARAMS**: STRING - Service Parameter
- **Input**: logiBUS_2_CAN_DI_S - Identifies the Input Input_Q1..Q8
- Initial value: logiBUS_2_CAN_DI::Invalid

### **Data Outputs**

- **QO**: BOOL - Event output qualifier
- **STATUS**: STRING - Service status
- **IN**: BOOL - Input data from the resource

### **Adapter**

No adapter interfaces available.

## Functionality

This function block operates as an input service interface for digital CAN signals. During initialization (INIT event), the service parameters are configured and the input channel is identified. Service requests can be made via the REQ event, while IND events signal incoming data from the resource. The block manages the communication status and outputs the received Boolean input data via the IN output.

## Technical Features

- Special data types for logiBUS-CAN integration
- Initialization with invalid state as standard
- Separate acknowledgment and indication events for different operating states
- String-based status feedback for detailed fault diagnosis

## State Overview

The function block goes through the following main states:

1. **Not Initialized**: Before INIT event
2. **Initialized**: After successful INIT acknowledgment
3. **Service Ready**: Can process REQ and IND events
4. **Fault State**: In case of communication problems (signaled via STATUS)

## Application Scenarios

- Integration of logiBUS I/O modules into 4diac controllers
- CAN-based digital input signal processing
- Industrial automation systems with distributed I/Os
- Robot controllers with CAN peripherals

## ⚖️ Comparison with Similar Blocks

Compared to standard digital input blocks, this offers `logiBUS_2_CAN_IX` features dedicated CAN integration and enhanced status feedback. While simple DI blocks only offer direct signal processing, this block supports more complex protocol handling and error handling for industrial CAN networks.

## Conclusion

The `logiBUS_2_CAN_IX` function block provides a robust and reliable interface for integrating CAN-based digital input signals into 4diac control systems. Its enhanced error handling and status feedback make it particularly suitable for demanding industrial applications where reliable communication with distributed I/O systems is required.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
