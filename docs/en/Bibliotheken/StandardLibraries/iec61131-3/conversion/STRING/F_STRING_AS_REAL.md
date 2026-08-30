# F_STRING_AS_REAL

<img width="1467" height="213" alt="F_STRING_AS_REAL" src="https://github.com/user-attachments/assets/2ab258e3-0671-4f5c-8975-303faeef5972" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_REAL` converts a `STRING` value to a `REAL` value. It is particularly useful when data from a string needs to be converted into a numerical representation, for example, when processing user input or interpreting text files.
![F_STRING_AS_REAL](F_STRING_AS_REAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event is triggered, the algorithm for converting the `STRING` value to a `REAL` value is executed.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. This event is output along with the converted `REAL` value.

### **Data Inputs**

- **IN** (`STRING`): The input value to be converted to a `REAL` value.

### **Data Outputs**

- **OUT** (`REAL`): The result of the conversion.

### **Adapters**

This function block does not use adapters.

## Functionality

When the `REQ` event is triggered, the function block converts the `STRING` value (`IN`) into a `REAL` value. The conversion is performed using the built-in function `STRING_AS_REAL`. After successful conversion, the `CNF` event is triggered, and the result is output via `OUT`.

## Technical Features

- The conversion can fail if the input `STRING` is not a valid `REAL` number. In this case, a runtime error may occur.
- The function block is simple and does not include any additional error handling.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Completed**: Sends the `CNF` event with the result.

## Application Scenarios

- Processing user input in string form.
- Interpreting data from text files or network communication.
- Converting configuration values stored as strings.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_STRING_AS_REAL` specializes in converting `STRING` to `REAL`.
- Other blocks might offer additional features such as error handling or formatting, but they are more complex.

## Conclusion

The `F_STRING_AS_REAL` function block is a simple and efficient tool for converting strings to floating-point numbers. Its strength lies in its simplicity and direct applicability, although it lacks integrated error handling. For robust applications, additional security measures should be implemented.
