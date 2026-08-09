# logiBUS_2_CAN_IXA

<img width="2031" height="363" alt="image" src="https://github.com/user-attachments/assets/d06a9404-82e0-4172-9321-7677d642f03f" />
* * * * * * * * * *
## Introduction

The logiBUS_2_CAN_IXA is a composite function block for processing Boolean input data via CAN bus interfaces. The block serves as an interface between logiBUS systems and CAN-based input devices and enables the initialization and querying of digital inputs.
![logiBUS_2_CAN_IXA](logiBUS_2_CAN_IXA.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization (with QI and PARAMS)
- **REQ**: Service Request (with QI)

### **Event Outputs**

- **INITO**: Initialization Acknowledgement (with QO and STATUS)

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL)
- **PARAMS**: Service Parameters (STRING)
- **Input**: Input Identification Input_Q1..Q8 (logiBUS_2_CAN_DI_S)

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL)
- **STATUS**: Service Status (STRING)

### **Adapters**

- **IN**: Unidirectional AX-type adapter for the Data Communication

## Functionality

The composite function block internally uses the logiBUS_2_CAN_IX module to process CAN-based input data. During INIT initialization, the service parameters are passed and the module is configured. Input data can be queried via the REQ event. Processing is performed via the IN adapter, which enables communication with CAN input devices.

## Technical Features

- Uses specific logiBUS data types for CAN communication
- Supports up to 8 digital inputs (Input_Q1 to Input_Q8)
- Initial value for input is "Invalid"
- Integrated error handling via STATUS output

## State Overview

The function block goes through the following states:

1. **Not Initialized**: Before INIT call
2. **Initialization**: During INIT processing
3. **Ready**: After successful initialization (INITO confirmed)
4. **Query**: During REQ processing

## Application Scenarios

- Connecting CAN-based sensors and switches to logiBUS systems
- Industrial automation with digital input signals
- Control systems in agricultural technology
- Distributed I/O systems via CAN bus

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital input function blocks, this offers logiBUS_2_CAN_IXA:

- CAN bus communication capability
- Extended parameterization options
- Integrated status feedback
- Specific logiBUS integration

## Conclusion

The logiBUS_2_CAN_IXA is a specialized composite function block for the reliable integration of CAN-based digital inputs into logiBUS systems. Its structured initialization and query mechanisms make it particularly suitable for industrial applications requiring robust and configurable I/O interfaces.
