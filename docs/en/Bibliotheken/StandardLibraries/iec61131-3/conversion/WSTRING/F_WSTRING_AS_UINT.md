# F_WSTRING_AS_UINT

<img width="1481" height="214" alt="F_WSTRING_AS_UINT" src="https://github.com/user-attachments/assets/4ea92136-06dd-4514-be80-70cc9b719213" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_UINT` is used to convert a WSTRING value to a UINT value. This function is particularly useful when strings need to be converted into numeric values, for example, for further calculations or control tasks.
![F_WSTRING_AS_UINT](F_WSTRING_AS_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This input triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. This output signals the completion of the conversion.

### **Data Inputs**

- **IN**: WSTRING value to be converted to a UINT value.

### **Data Outputs**

- **OUT**: UINT value resulting from the conversion of the WSTRING input.

#### **Adapters**

- No adapters available.

## Functionality

The function block converts the WSTRING input `IN` to a UINT value `OUT` as soon as the event `REQ` is triggered. The conversion is performed using the built-in function `WSTRING_AS_UINT`. After successful conversion, the event `CNF` is triggered to signal the completion of the operation.

## Technical Features

- The function block is a simple function block (SimpleFB) and performs the conversion in a single algorithm.
- The conversion is direct and occurs without additional state management.

## State Overview

Since this is a simple function block, there are no complex state transitions. The block responds to the `REQ` event, performs the conversion, and signals completion with `CNF`.

## Application Scenarios

- Converting user input to numeric values.
- Processing strings containing numeric data for control purposes.
- Integration into larger control systems that need to process both strings and numeric values.

## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks such as `F_STRING_AS_INT` or `F_WSTRING_AS_INT`, this block specifically converts to a UINT value, which is suitable for non-negative numbers.
- Using WSTRING allows for the processing of Unicode strings, which is more flexible compared to simple STRING conversions.

## Conclusion

The `F_WSTRING_AS_UINT` function block provides a simple and efficient way to convert WSTRING values to UINT values. Its straightforward operation and clear interface make it a useful component in control applications that work with strings and numeric values.
