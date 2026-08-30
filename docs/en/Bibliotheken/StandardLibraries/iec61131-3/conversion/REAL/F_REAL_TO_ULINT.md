# F_REAL_TO_ULINT

<img width="1447" height="213" alt="F_REAL_TO_ULINT" src="https://github.com/user-attachments/assets/4390420b-31fd-4ff4-a89b-ec4feaf6f353" />
* * * * * * * * * *
## Introduction

The function block `F_REAL_TO_ULINT` converts a `REAL` value (floating-point number) to a `ULINT` value (64-bit unsigned integer). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_REAL_TO_ULINT](F_REAL_TO_ULINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Input for the `REAL` value to be converted.

### **Data Outputs**

- **OUT**: Output for the converted `ULINT` value.

### **Adapters**

- No adapters are present.

## Functionality

The function block performs the conversion as soon as the `REQ` event is triggered. The `REAL` value is converted at input `IN` to a `ULINT` value and output as `OUT`. The conversion is confirmed by the `CNF` event.

## Technical Details

- The conversion is performed using the function `REAL_TO_ULINT`.
- This function block is part of the `iec61131::conversion` package.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion and outputs the result.
3. **Acknowledgement State**: Sends the `CNF` event to confirm the conversion.

## Application Scenarios

- Type conversion in control applications where floating-point numbers need to be converted to unsigned integers.
- Data processing in industrial automation systems.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_REAL_TO_INT` or `F_REAL_TO_LINT` perform conversions to other integer types. `F_REAL_TO_ULINT` is specific to 64-bit unsigned integers.

## Conclusion

The `F_REAL_TO_ULINT` function block offers a simple and efficient way to convert `REAL` values into `ULINT` values. Its clear interface structure and simple functionality make it a valuable component in industrial automation.
