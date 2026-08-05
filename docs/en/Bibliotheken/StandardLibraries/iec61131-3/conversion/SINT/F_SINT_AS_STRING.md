# F_SINT_AS_STRING
<img width="1464" height="213" alt="F_SINT_AS_STRING" src="https://github.com/user-attachments/assets/8f81385a-a997-414c-938e-4a08f519242c" />
* * * * * * * * * *
## Introduction
The function block `F_SINT_AS_STRING` converts a `SINT` value (8-bit integer) into a `STRING` (string). This block is particularly useful when numeric values are needed as text for display or further processing.
![F_SINT_AS_STRING](F_SINT_AS_STRING.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The `SINT` value to be converted (8-bit integer).

### **Data Outputs**
- **OUT**: The converted `STRING` value.

#### **Adapters**
No adapters are available.

## Functionality
The function block performs the conversion as soon as the `REQ` event occurs. The `SINT` value at the input `IN` is converted to `STRING` and output at `OUT`. The conversion is performed using the function ``SINT_AS_STRING``. After the conversion is complete, the ``CNF`` event is triggered.

## Technical Features
- The conversion is performed directly without additional parameters.
- The function block is simple and efficient, as it only performs a basic data type conversion.

## State Overview
1. **Idle**: Waits for the ``REQ`` event.

2. **Conversion**: Performs the conversion and outputs the result.

3. **Confirmation**: Triggers the ``CNF`` event and returns to the idle state.

## Application Scenarios
- Displaying numeric values in user interfaces.
- Logging numeric data as text.
- Preparing data for communication via text-based protocols.

## ⚖️ Comparison with similar building blocks
- **F_INT_AS_STRING**: Converts a `INT` value (16-bit) to a `STRING` value.
- **F_DINT_AS_STRING**: Converts a `DINT` value (32-bit) to a `STRING` value.
- **F_LINT_AS_STRING**: Converts a `LINT` value (64-bit) to a `STRING` value.

Compared to these building blocks, `F_SINT_AS_STRING` specializes in converting 8-bit integers.

## Conclusion
The `F_SINT_AS_STRING` function block is a simple and efficient tool for converting `SINT` values to `STRING`s. Its clear interface and direct functionality make it ideal for applications where small integers need to be represented as text.