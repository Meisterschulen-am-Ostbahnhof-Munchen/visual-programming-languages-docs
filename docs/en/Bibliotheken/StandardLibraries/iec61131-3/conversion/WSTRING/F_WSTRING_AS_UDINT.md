# F_WSTRING_AS_UDINT

<img width="1494" height="214" alt="F_WSTRING_AS_UDINT" src="https://github.com/user-attachments/assets/80526643-8f3a-4829-a9c8-7fec610340b8" />

* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_UDINT` is used to convert a WSTRING value to a UDINT value. This block is particularly useful in scenarios where strings need to be converted into numeric values, for example, when processing user input or interpreting data from external sources.

![F_WSTRING_AS_UDINT](F_WSTRING_AS_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This input triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. This output signals the completion of the conversion.

### **Data Inputs**

- **IN**: WSTRING. The input string to be converted to a UDINT value.

### **Data Outputs**

- **OUT**: UDINT. The converted numeric value.

### **Adapters**
This function block does not use any adapters.

## Operation
The function block performs the conversion when the event `REQ` is received. The conversion is carried out using the function `WSTRING_AS_UDINT`, which converts the WSTRING input `IN` into a UDINT value and outputs the result to `OUT`. Upon completion of the conversion, the event `CNF` is triggered.

## Technical Features

- The function block is simple and efficient because it directly utilizes the built-in conversion function.

- There is no additional error handling for invalid input; the conversion is performed according to the rules of IEC 61131-3.

## State Overview
The function block has a simple state machine:

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Complete**: Sends the `CNF` event and returns to the idle state.

## Application Scenarios

- **Data Processing**: Converts user input or external data into numeric values.

- **Logging**: Converts strings into numeric IDs for storage or further processing.

- **Interface Communication**: Prepares data for transmission via protocols that require numeric values.


## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_AS_UDINT**: Similar function block, but for STRING instead of WSTRING.

- **F_UDINT_AS_WSTRING**: Performs the reverse conversion (UDINT to WSTRING).

## Conclusion
The `F_WSTRING_AS_UDINT` function block is a simple and effective tool for converting WSTRING values to UDINT. Its clear interface and direct functionality make it ideal for applications that require such conversions.