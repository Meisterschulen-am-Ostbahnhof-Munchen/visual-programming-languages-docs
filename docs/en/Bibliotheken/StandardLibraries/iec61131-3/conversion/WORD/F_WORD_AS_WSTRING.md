# F_WORD_AS_WSTRING

<img width="1477" height="214" alt="F_WORD_AS_WSTRING" src="https://github.com/user-attachments/assets/0501be71-0ef4-45a0-a24e-fc55d97986ca" />
* * * * * * * * * *
## Introduction

The function block `F_WORD_AS_WSTRING` converts a `WORD` data type to a `WSTRING` data type. This function block is particularly useful in scenarios where numeric values need to be converted into a string, for example, for display or logging.
![F_WORD_AS_WSTRING](F_WORD_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN** (`WORD`): The input value to be converted to `WSTRING`.

### **Data Outputs**

- **OUT** (`WSTRING`): The output value after conversion.

#### **Adapters**

This function block has no adapters.

## Functionality

When the event input `REQ` is triggered, the algorithm is executed that converts the value at input `IN` of type `WORD` to `WSTRING`. The result is provided at output `OUT`, and the event `CNF` signals successful execution.

## Technical Features

- The conversion is performed directly without intermediate steps.
- The function block is optimized for simple conversions and requires no additional configuration.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Completed**: Signals completion with `CNF`.

## Application Scenarios

- Displaying numeric values in a user interface.
- Logging `WORD` values as readable strings.
- Data conversion for communication with systems that expect `WSTRING`.

## ⚖️ Comparison with similar function blocks

- Compared to generic conversion function blocks, `F_WORD_AS_WSTRING` is specialized and therefore more efficient for this specific task.
- Other function blocks might support additional parameters or more complex conversions, which is not necessary here.

## Conclusion

The `F_WORD_AS_WSTRING` function block is a simple and efficient function block for converting `WORD` to `WSTRING`. Its strength lies in its simplicity and direct applicability for specific conversion tasks.