# F_DINT_TO_LREAL

<img width="1449" height="212" alt="F_DINT_TO_LREAL" src="https://github.com/user-attachments/assets/bdda654f-6dbe-4c4a-aaba-6440c9a13e8f" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_LREAL` converts a 32-bit integer value (DINT) into a 64-bit floating-point value (LREAL). This conversion is particularly necessary in control systems where different data types need to be processed in various parts of the application.
![F_DINT_TO_LREAL](F_DINT_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `DINT`, which is to be converted to a `LREAL` value.

### **Data Outputs**

- **OUT**: The output value of type `LREAL`, which represents the result of the conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs a direct type conversion. When the event `REQ` is triggered, the value of `IN` is read and converted to the data type `LREAL`. The result is output to `OUT`, and the event `CNF` signals successful conversion.

## Technical Features

- The conversion is performed without additional scaling or offset adjustment.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of integers to floating-point numbers for mathematical calculations.
- Integration into control systems where different data types need to be processed.
- Use in control engineering where precise floating-point calculations are required.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_DINT_TO_LREAL` specializes in converting `DINT` to `LREAL`, thus offering greater efficiency and code readability.
- Other building blocks might offer additional features such as scaling or limiting, which is not the case here.

## Conclusion

The `F_DINT_TO_LREAL` function block is a simple and efficient building block for converting integers to floating-point numbers. Its clear interface and deterministic operation make it ideal for use in control systems.