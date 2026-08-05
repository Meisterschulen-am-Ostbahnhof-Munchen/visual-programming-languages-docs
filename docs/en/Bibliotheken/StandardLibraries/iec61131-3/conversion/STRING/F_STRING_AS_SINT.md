# F_STRING_AS_SINT
<img width="1467" height="213" alt="F_STRING_AS_SINT" src="https://github.com/user-attachments/assets/13cacff9-d6b7-49e3-93b4-b4ca9c36ab3b" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_SINT` converts a `STRING` value into a `SINT` value (8-bit signed integer). This block is particularly useful when strings need to be converted into numeric values, for example, when processing user input or interpreting text data.
![F_STRING_AS_SINT](F_STRING_AS_SINT.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Triggers the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- `CNF`: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- `IN` (`STRING`): The string to be converted into a `SINT` number.

### **Data Outputs**
- `OUT` (`SINT`): The result of the conversion as an 8-bit signed integer.

### **Adapters**
This function block does not use any adapters.

### **Adapters**

### **Adapters**

#
## **Data Inputs ... ## Functionality
When the `REQ` event is triggered, the function `STRING_AS_SINT` is applied to the value of the `IN` input. The result is stored in the `OUT` output, and the `CNF` event signals the successful completion of the operation.

## Technical Features
- The conversion is performed according to the IEC 61131-3 specification for converting strings to numeric values.
- The function block is part of the `iec61131::conversion` package.

## State Overview
1. **Idle**: Waiting for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Completed**: Signals completion with `CNF` and returns to the idle state.

## Application Scenarios
- Interpreting user input into numerical control commands.
- Processing text data from external sources (e.g., files or network communication).
- Converting configuration values into control parameters.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_STRING_AS_SINT` specializes in conversion to 8-bit integers.
- Similar blocks like `F_STRING_AS_INT` or `F_STRING_AS_DINT` offer conversions to larger integer types.

## Conclusion

`F_STRING_AS_SINT` is an efficient and specialized function block for converting strings to 8-bit integers. Its simple interface and clear functionality make it ideal for control applications that work with text-based input.
