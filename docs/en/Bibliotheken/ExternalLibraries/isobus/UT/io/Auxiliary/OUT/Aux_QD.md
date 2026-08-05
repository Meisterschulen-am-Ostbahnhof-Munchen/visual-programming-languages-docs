# Aux_QD
<img width="1484" height="176" alt="image" src="https://github.com/user-attachments/assets/ddafadb6-6b79-43d3-9d30-dc888d6fca95" />
* * * * * * * * * *
## Introduction
The Aux_QD function block is an output service interface module for processing double-word output data (DWORD). It serves as an interface for auxiliary output functions and supports various auxiliary types for flexible data output.
![Aux_QD](Aux_QD.svg)

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
- **OUT** (DWORD): Output Data for the Resource
- **iInpNr** (INT): Auxiliary Array Number (corresponds to the order in the pool, initial value: 0)

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status Information

### **Adapters**
No adapter interfaces are available.

## Functionality
The Aux_QD block processes double-word data (32-bit) and outputs it via auxiliary interfaces. During initialization (INIT), the service parameters are configured. The output data is sent to the corresponding resource via the REQ event. The block supports multiple auxiliary types and allows the parallel output of both values in a single operation.

``` ## Technical Features
- Supports Auxiliary Types: 0, 1, 2, 3, 4, 6, 11, 12, 13
- Processes 32-bit DWORD data
- Initial value for iInpNr is 0 (first auxiliary array in the pool)
- Parallel output of both values is possible in one operation

## State Overview
The block has two main states:

1. **Initialization State**: Processing the INIT request with parameter configuration

2. **Operating State**: Processing REQ requests with data output

## Application Scenarios
- ISOBUS-compatible control systems
- Agricultural machine controls
- Industrial automation systems
- Embedded systems with auxiliary interfaces

## ⚖️ Comparison with Similar Blocks
Compared to simple output blocks, Aux_QD offers extended functionality for auxiliary interfaces and supports specific ISOBUS-compatible data types. Its parallel output capability distinguishes it from sequential output blocks.

## Conclusion
The Aux_QD function block represents a powerful solution for outputting double-word data via auxiliary interfaces. Its ISOBUS compatibility and support for various auxiliary types make it particularly suitable for demanding automation applications in industrial and mobile systems.