# F_INT_TO_ULINT

<img width="1232" height="183" alt="F_INT_TO_ULINT" src="https://github.com/user-attachments/assets/55a69d83-7b80-4166-9e24-3160c0e9d1b1" />

* * * * * * * * * *
## Introduction
The function block `F_INT_TO_ULINT` converts an integer value of data type `INT` into an unsigned 64-bit integer value of data type `ULINT`. This conversion is particularly useful when values need to be exchanged between different systems or components that use different data types.

![F_INT_TO_ULINT](F_INT_TO_ULINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion of the input value. This event input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion and outputs the converted value via the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of data type `INT` to be converted.

### **Data Outputs**

- **OUT**: The converted output value of data type `ULINT`.

### **Adapters**
This function block does not use any adapters.

## Operation
The function block performs the conversion as soon as the event `REQ` is received. The algorithm within the function block converts the `INT` value at input `IN` into a `ULINT` value and outputs the result at `OUT`. Successful conversion is signaled by triggering the `CNF` event.

## Technical Features
- The conversion is performed directly and without any additional delay.

- The function block is suitable for use in real-time systems.

- The implementation complies with the IEC 61131-3 standard.

## State Overview

The function block has no internal states. The conversion is performed each time the `REQ` event is received.


## Application Scenarios

- Conversion of sensor values for processing in systems that require `ULINT` values.

- Integration of components that use different data types.

- Use in control systems that require type conversion.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion blocks such as `F_DINT_TO_ULINT` or `F_SINT_TO_ULINT`, this function block is specifically optimized for converting `INT` to `ULINT`.

- Similar function blocks might offer additional features such as range checks or error handling, which this function block does not.


## Conclusion

The function block `F_INT_TO_ULINT` is a simple and efficient building block for converting `INT` values to `ULINT` values. It is particularly useful in scenarios where direct and fast type conversion is required. Its clear interface structure and simple functionality make it a reliable tool in automation technology.