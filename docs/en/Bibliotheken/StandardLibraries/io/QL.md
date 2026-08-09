# QL

![](https://user-images.githubusercontent.com/69573151/210781586-ad33d398-c369-4e16-b79e-20ed939fcdd6.png)

* * * * * * * * * *
## Introduction

The QL function block is an output service interface block for processing long-word output data. It serves as an interface between the control logic and external resources and enables the output of 64-bit data values.
![QL](QL.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Operation

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **OUT** (LWORD): Output Data for the Resource (64-bit)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status Information

### **Adapters**

No adapter interfaces are available.

## Functionality

The QL block processes two main operations: initialization and data output. During the INIT operation, the service parameters are configured and the connection to the resource is initialized. The REQ operation performs the actual data output of the LWORD value to the connected resource. Each operation is acknowledged by corresponding confirmation events.

## Technical Features

- Processing of 64-bit data values (LWORD)
- String-based parameter configuration
- Status feedback via STRING variable
- Qualifier for event control (QI/QO)

## State Transitions

The block has two main states:

1. **Initialization State**: Processing the INIT request with PARAMS
2. **Operating State**: Processing REQ requests with OUT data

## Application Scenarios

- Output of 64-bit control values to hardware interfaces
- Communication with external peripherals
- Integration into distributed control systems
- Connection to dedicated I/O modules

## ⚖️ Comparison with Similar Blocks

Compared to simpler output blocks, QL offers 64-bit data processing and extended parameter configuration. Compared to more general-purpose communication blocks, QL is specifically optimized for output functionality.

## Conclusion

The QL function block provides a powerful interface for the output of long-word data and, through its structured event control and status feedback, offers a reliable basis for connecting external resources in automation systems.
