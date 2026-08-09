# F_WSTRING_AS_INT

<img width="1469" height="214" alt="F_WSTRING_AS_INT" src="https://github.com/user-attachments/assets/d83cc0b2-80c5-4d74-8885-958419a9091a" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_INT` is used to convert a WSTRING value to an INT value. This block is particularly useful when strings need to be converted into numeric values, for example, when processing user input or interpreting text data.
![F_WSTRING_AS_INT](F_WSTRING_AS_INT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: This event input triggers the execution of the function block. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: This event output signals the successful execution of the function block. It is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: This input expects a WSTRING value, which is to be converted to an INT value.

### **Data Outputs**

- **OUT**: This output provides the converted INT value.

### **Adapters**

This function block has no adapters.

## Functionality

The function block performs the conversion as soon as the event `REQ` is received. The conversion is carried out using the function `WSTRING_AS_INT`, which converts the WSTRING value from `IN` into an INT value and outputs the result to `OUT`. The event `CNF` is then triggered to signal successful execution.

## Technical Features

- The function block is a simple block without internal states or complex logic.
- The conversion is performed directly and without delay.

## State Overview

Because it is a simple function block, there are no state transitions or internal states.

## Application Scenarios

- Processing user input that is in string form but must be interpreted as numeric values.
- Interpreting text data from external sources that needs to be converted into numeric values.
- Integration into systems that need to process strings and numeric values.

## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks such as `F_STRING_AS_INT` or `F_WSTRING_AS_REAL`, this block is specifically designed for converting WSTRING to INT.

Other blocks might offer additional features like error handling or formatting, but this block is limited to basic conversion.

## Conclusion

The `F_WSTRING_AS_INT` function block is a simple and efficient tool for converting WSTRING values to INT values. Its clear interface and straightforward functionality make it ideal for applications requiring fast and uncomplicated conversion.