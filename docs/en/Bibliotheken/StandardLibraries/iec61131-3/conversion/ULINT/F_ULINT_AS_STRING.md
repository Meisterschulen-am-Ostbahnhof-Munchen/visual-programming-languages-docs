# F_ULINT_AS_STRING
<img width="1479" height="214" alt="F_ULINT_AS_STRING" src="https://github.com/user-attachments/assets/7f40d872-343a-4628-a23d-a9ba54f7314b" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_AS_STRING` converts a `ULINT` value (64-bit unsigned integer) into a `STRING` value. This functionality is particularly useful when numeric values are needed as strings for output, logging, or further processing.
![F_ULINT_AS_STRING](F_ULINT_AS_STRING.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`ULINT`): The 64-bit unsigned integer value to be converted.

### **Data Outputs**
- **OUT** (`STRING`): The result string after the conversion.

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion when the event `REQ` is received. The `ULINT` value at input `IN` is converted to `STRING` and output at `OUT`. Successful conversion is signaled by the event `CNF`.

## Technical Features
- The function block has a simple structure and contains only one algorithm that performs the conversion.
- The conversion is performed directly without additional parameters or complex logic.

## State Overview

The function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios
- **Logging**: Conversion of numeric values for output to log files.
- **User Interfaces**: Display of numeric values as text in user interfaces.
- **Data Communication**: Preparation of numeric values for transmission as strings.

## ⚖️ Comparison with similar building blocks
- **F_INT_AS_STRING**: Converts a `INT` value to a `STRING` value. In contrast, `F_ULINT_AS_STRING` supports the larger `ULINT` data type.
- **F_DINT_AS_STRING**: Converts a `DINT` value to a `STRING` value. Similar, but for 32-bit signed integers.

## Conclusion

The function block `F_ULINT_AS_STRING` offers a simple and efficient way to convert `ULINT` values to `STRING` values. Its clear interface and direct functionality make it ideal for applications requiring such a conversion.