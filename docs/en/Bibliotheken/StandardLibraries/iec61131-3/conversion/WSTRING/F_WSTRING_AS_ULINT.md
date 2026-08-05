# F_WSTRING_AS_ULINT
<img width="1492" height="214" alt="F_WSTRING_AS_ULINT" src="https://github.com/user-attachments/assets/1523dbf5-1b9f-4c01-b8af-755a1cd1c490" />
* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_ULINT` is used to convert a WSTRING data type to a ULINT data type. This function block is particularly useful in scenarios where strings need to be converted into numeric values, for example, when processing user input or parsing data from external sources.
![F_WSTRING_AS_ULINT](F_WSTRING_AS_ULINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (WSTRING): The input string to be converted to a ULINT value.

### **Data Outputs**
- **OUT** (ULINT): The converted numeric value.

#### **Adapters**
No adapters are defined for this function block.

## Functionality
The function block performs the conversion when the `REQ` event is received. The conversion is performed using the function `WSTRING_AS_ULINT`, which converts the string `IN` to an unsigned 64-bit integer (`ULINT`). After successful conversion, the `CNF` event is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The conversion is strictly typed, meaning the input must contain a valid numeric representation in the string to produce correct results.
- The function block does not support error handling for invalid input. It is the user's responsibility to ensure that the input is correctly formatted.

## State Overview
1. **Idle**: The function block waits for the `REQ` event.

2. **Processing**: The conversion is performed upon receipt of `REQ`.

3. **Completed**: After the conversion, the `CNF` event is triggered, and the function block returns to its idle state.

## Application Scenarios
- Converting user input to numeric values.
- Parsing data from external sources (e.g., files, network) into numeric formats.
- Use in control applications where strings need to be converted to control values.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion function blocks, `F_WSTRING_AS_ULINT` specializes in converting WSTRING to ULINT and therefore offers an optimized and type-safe solution for this specific use case.
- Other function blocks, such as `F_STRING_AS_INT` or `F_WSTRING_AS_LINT`, offer similar functionality, but for different data types.

## Conclusion
The `F_WSTRING_AS_ULINT` function block is an efficient tool for converting strings to unsigned 64-bit integer values. Its simplicity and specialization make it ideal for applications requiring fast and type-safe conversion. However, note that it lacks built-in error handling for invalid input.