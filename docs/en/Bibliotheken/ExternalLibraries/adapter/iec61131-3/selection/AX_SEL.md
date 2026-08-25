# AX_SEL

<img width="1242" height="224" alt="image" src="https://github.com/user-attachments/assets/70f03e26-14b2-40a3-9eff-056402fef00e" />
* * * * * * * * * *
## Introduction

The AX_SEL function block is a binary selector used to choose between two input values. It belongs to the category of standard selection functions according to IEC 61131-3 and enables flexible data selection based on a control signal.
![AX_SEL](AX_SEL.svg)

## Interface Structure

### **Event Inputs**

*No event inputs available*

### **Event Outputs**

- **CNF** - Confirmation of Requested Service

### **Data Inputs**

- **IN0** (ANY) - Selectable input variable
- **IN1** (ANY) - Selectable input variable

### **Data Outputs**

- **OUT** (ANY) - Selected input

### **Adapters**

- **G** (adapter::types::unidirectional::AX) - Unidirectional adapter for control

## Functionality

The AX_SEL function block selects between two input values (IN0 and IN1) and outputs the selected value at output OUT. The selection is controlled via the connected adapter G. When the CNF event is activated, the selected value is provided at output OUT.
...
## Technical Features

- Uses the ANY data type for maximum flexibility in inputs and outputs
- Implemented as a unidirectional adapter for easy control
- Supports various data types through the use of ANY

## State Overview

The function block has a simple state:

- **Ready**: Waits for a control signal from adapter G
- Upon receiving the control signal, the corresponding input is selected and the CNF event is triggered

## Application Scenarios

- Selection between two different sensors
- Switching between operating modes
- Selection of data sources depending on operating states
- Switching between manual and automatic control

## ⚖️ Comparison with Similar Function Blocks

Compared to other selection blocks, AX_SEL offers:

- Greater flexibility through the ANY data type
- Easy integration through the unidirectional adapter
- Standardized interface according to IEC 61131-3

Comparison with [F_SEL](../../../../StandardLibraries/iec61131-3/selection/F_SEL.md)

## Conclusion

The AX_SEL function block provides a simple and flexible solution for binary selection tasks in control systems. By using the ANY data type and standardized adapter interfaces, it enables versatile application in various automation projects.
