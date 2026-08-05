# logiBUS_DI
![logiBUS_DI](./logiBUS_DI.svg)
* * * * * * * * * *
## Introduction
The logiBUS_DI GlobalConstants definition provides a collection of predefined constants for digital inputs of the logiBUS system. These constants define the pin assignments for various digital input channels and are used to configure logiBUS_DI function blocks.

## Interface Structure

### **Event Inputs**
*No event inputs available - this is a constant definition*

### **Event Outputs**
*No event outputs available - this is a constant definition*

### **Data Inputs**
*No data inputs available - this is a constant definition*

### **Data Outputs**
*No data outputs available - this is a constant definition*

### **Adapters**
*No adapters available - this is a constant definition*

## Functionality

The GlobalConstants definition logiBUS_DI provides structured constants of type `logiBUS_DI_S`, each containing a specific pin value:

- **Input_I1** to **Input_I9**: Defines digital inputs 1 to 9 with corresponding pin numbers
- **Invalid**: Defines an invalid pin with the Value 255

These constants are used as initialization values for configuring digital inputs in the logiBUS system.

## Technical Features
- **Structure Type**: All constants use the structured data type `logiBUS_DI_S`
- **Pin Range**: Valid pins range from 1 to 9; invalid configurations are indicated by pin 255
- **Package Membership**: The constants are organized in the package `logiBUS::io::DI`
- **Initialization**: All constants are initialized with their pin values upon declaration

## State Overview

Since this is a pure constant definition, there are no state transitions or state machines.

## Application Scenarios
- Configuration of digital input modules in logiBUS systems
- Parameterization of function blocks that process digital inputs
- Type-safe pin assignments in control programs
- Error handling through the use of the invalid constant

## ⚖️ Comparison with similar function blocks

Unlike function blocks with active logic, this is a pure constant definition that:

- Does not perform any active processing
- Does not process any events
- Provides only configuration data
- Is evaluated at compile time

## Conclusion

The logiBUS_DI GlobalConstants offer a structured and type-safe method for configuring digital inputs in the logiBUS system. The predefined constants reduce the susceptibility to errors in pin assignment and improve the maintainability of control programs.
