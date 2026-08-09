# F_LREAL_AS_STRING

<img width="1267" height="182" alt="F_LREAL_AS_STRING" src="https://github.com/user-attachments/assets/88c6651f-c602-4b8e-b6cf-f3d9c6907ff0" />
* * * * * * * * * *
## Introduction

The function block `F_LREAL_AS_STRING` is used to convert an LREAL value (64-bit floating-point number) into a STRING. This functionality is particularly useful when numeric values are needed as strings for display, logging, or communication.
![F_LREAL_AS_STRING](F_LREAL_AS_STRING.svg)
## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- `IN` (LREAL): The input value to be converted to a STRING.

### **Data Outputs**

- `OUT` (STRING): The resulting STRING after conversion.

### **Adapters**

This function block does not use any adapters.

## Operation

When the `REQ` event is triggered, the algorithm is executed, which converts the LREAL value `IN` to a STRING and outputs the result via `OUT`. The `CNF` event signals the successful completion of the conversion.

## Technical Features

- The conversion is performed using the function `LREAL_AS_STRING`.
- The function block is simple and has no internal states or complex logic.

## State Overview

Since it is a simple function block, there are no state transitions or machines.

## Application Scenarios

- Displaying floating-point numbers in user interfaces.
- Logging measured values to text files or databases.
- Preparing data for communication via text protocols.

## ⚖️ Comparison with Similar Function Blocks

- Unlike `F_STRING_TO_LREAL`, this function block performs the reverse conversion.
- Compared to generic conversion function blocks, this one specializes in LREAL-to-STRING conversions.

## Conclusion

The `F_LREAL_AS_STRING` function block offers a simple and efficient way to convert floating-point numbers into strings. Its clear interface and straightforward functionality make it a useful component in many automation applications.