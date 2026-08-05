# PKP_2200_LI_IXA

<img width="1960" height="384" alt="image" src="https://github.com/user-attachments/assets/1b07f3e6-433e-4e24-be44-50268e3eb4f4" />

* * * * * * * * * *
## Introduction
The PKP_2200_LI_IXA is a composite function block for processing Boolean input data. It serves as an interface for digital inputs and provides standardized initialization and query functions for input signals.


``` ![PKP_2200_LI_IXA](PKP_2200_LI_IXA.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization (with QI, PARAMS, u8SAMember, Input)
- **REQ**: Service Request (with QI)

### **Event Outputs**
- **INITO**: Initialization Acknowledgement (with QO, STATUS)

### **Data Inputs**
- **QI**: Event Input Qualifier (BOOL)
- **PARAMS**: Service Parameters (STRING)
- **u8SAMember**: Node SA (USINT) - Default Value: PKP_2200::PKP_2200_DEFAULT
- **Input**: Input Identifier (BlinkMarine::io::DI::PKP_2200_LI_DI_S) - Default Value: Invalid

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL)

- **STATUS**: Service Status (STRING)

### **Adapters**

- **IN**: Unidirectional Adapter of Type AX

## Functionality
The function block initializes itself via the INIT event and confirms successful initialization with INITO. Service requests can be made via the REQ event. The input data is processed via the IN adapter, and the results are provided via the corresponding outputs.


## Technical Features
- Uses standardized initialization procedures according to EInit type
- Supports configuration via SA member (default: 21h)
- Provides error handling via STATUS output
- Implements qualified event processing

## State Overview
The function block goes through the following states:

1. **Not Initialized**: Before INIT event

2. **Initialization**: During INIT processing
3. **Ready**: After successful initialization (INITO)
4. **Service Request**: During REQ processing

## Application Scenarios
- Digital input signal processing in automation systems
- I/O communication with PKP-2200-compatible devices
- Integration into distributed control systems
- Boolean signal processing with quality monitoring

## ⚖️ Comparison with Similar Blocks
Compared to simple digital input blocks, PKP_2200_LI_IXA offers extended functionality through:

- Parameterizable SA Member Configuration

- Detailed status feedback
- Standardized initialization procedures
- Adapter-based interface

## Conclusion
The PKP_2200_LI_IXA is a robust and flexible function block for processing digital input signals with advanced configuration and diagnostic capabilities. Its standardized interface enables easy integration into complex automation systems.