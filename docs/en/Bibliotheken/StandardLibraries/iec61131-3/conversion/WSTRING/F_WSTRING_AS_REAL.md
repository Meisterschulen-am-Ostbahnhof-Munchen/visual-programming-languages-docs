# F_WSTRING_AS_REAL

<img width="1481" height="214" alt="F_WSTRING_AS_REAL" src="https://github.com/user-attachments/assets/6c4a0b16-af89-44e9-80ef-d3aff2884324" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_REAL` is used to convert a WSTRING value into a REAL value. This block is particularly useful when strings representing numeric values need to be converted into numeric data types for further calculations or control logic.
![F_WSTRING_AS_REAL](F_WSTRING_AS_REAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the WSTRING value contained in the data input `IN` is converted into a REAL value.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is activated as soon as the conversion is complete and the result value is available in the data output `OUT`.

### **Data Inputs**

- **IN**: Enter the WSTRING value to be converted into a REAL value here.

### **Data Outputs**

- **OUT**: Contains the converted REAL value after successful execution of the function block.

#### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The conversion is carried out using the internal function `WSTRING_AS_REAL`, which converts the WSTRING input `IN` into a REAL value and stores the result in the output `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features

- The function block supports WSTRING to REAL conversion, which is particularly useful in international applications because WSTRING supports Unicode characters.
- The conversion is performed in a single algorithm step, ensuring efficient execution.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event to be triggered.
2. **Conversion State**: The conversion is performed when `REQ` is triggered.
3. **Confirmation State**: After successful conversion, `CNF` is triggered, and the function block returns to the idle state.

## Application Scenarios

- **Data Processing**: Conversion of user input or read strings into numeric values for calculations.
- **Interface Communication**: Conversion of strings received via networks or interfaces into numeric values for control logic.
- **International Applications**: Processing of Unicode-encoded strings containing numeric data.

## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_AS_REAL**: Similar function block, but for the STRING data type instead of WSTRING. `F_WSTRING_AS_REAL` is preferable when Unicode support is required.
- **F_WSTRING_TO_***: Other conversion blocks for WSTRING, but they convert to other data types such as INT or BOOL.

## Conclusion

The `F_WSTRING_AS_REAL` function block is an efficient tool for converting Unicode strings into numeric REAL values. Its simple interface and reliable operation make it ideal for applications requiring international character sets or complex data processing.