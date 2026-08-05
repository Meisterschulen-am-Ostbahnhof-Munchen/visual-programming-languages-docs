# logiBUS_DO
![logiBUS_DO](./logiBUS_DO.svg)

* * * * * * * * * *
## Introduction
The logiBUS_DO GlobalConstants define a collection of constants for configuring digital outputs (DOs) in the logiBUS system. These constants are used for pin assignment to digital output channels and provide a standardized interface for hardware configuration.
## Interface Structure
### **Event Inputs**
*No event inputs available*

### **Event Outputs**
*No event outputs available*

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

### **Adapters**
*No adapters available*

## Functionality
The logiBUS_DO GlobalConstants define structured constants of type `logiBUS_DO_S`, each containing a specific pin value for digital outputs. Constants `Output_Q1` to `Output_Q10` represent the available output channels with the corresponding pin numbers 1 to 10. The constant `Invalid` with the pin value 255 serves as an indicator for invalid or unconfigured outputs.

## Technical Features
- **Constant Type**: All constants are of the structured data type `logiBUS_DO_S`
- **Pin Mapping**: Clear mapping of output names to physical pin numbers
- **Invalid Marking**: Special constant with pin value 255 for error handling
- **Package Structure**: Organized in the package `logiBUS::io::DQ`

## State Overview
Since these are constants, there are no state transitions. The values are static and unchanging during runtime.

## Application Scenarios
- Hardware configuration of logiBUS systems
- Pin assignment in function blocks for digital outputs
- Error handling for invalid output configurations
- Standardization of output designations in control applications

## ⚖️ Comparison with similar function blocks

Compared to other constant definitions, logiBUS_DO offers a specific structure for digital outputs with clear pin assignment and a defined invalid constant for robust error handling.

## Conclusion
The logiBUS_DO GlobalConstants provide a standardized and maintainable solution for configuring digital outputs in logiBUS systems. The structured definition of the output channels and the provided invalid constant enable reliable and fault-tolerant hardware configuration.
