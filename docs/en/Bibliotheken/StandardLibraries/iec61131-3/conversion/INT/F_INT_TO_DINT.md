# F_INT_TO_DINT
<img width="1222" height="182" alt="F_INT_TO_DINT" src="https://github.com/user-attachments/assets/0ef12508-b16b-40c8-87b4-378ff5776647" />
* * * * * * * * * *
## Introduction
The function block `F_INT_TO_DINT` is used to convert a 16-bit integer value (`INT`) to a 32-bit integer value (`DINT`). This conversion is useful when exchanging data between systems or components that use different integer formats.
![F_INT_TO_DINT](F_INT_TO_DINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`INT`): The 16-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`DINT`): The resulting 32-bit integer value after the conversion.

### **Adapters**
This function block does not use adapters.

## Operation
The function block performs a direct type conversion. When the `REQ` event occurs, the value of `IN` is copied to `OUT`. The 16-bit `INT` value is automatically expanded to a 32-bit `DINT` value. After the conversion is complete, the `CNF` event is triggered.

## Technical Features
- The conversion is lossless, as a `INT` value can be converted to a `DINT` value without any issues.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. It reacts exclusively to the `REQ` event with an immediate conversion and output of the `CNF` event.

## Application Scenarios
- Data communication between systems that use different integer formats.
- Extending integer values for further calculations or storage.
- Compatibility with libraries or functions that require `DINT` values.

## ⚖️ Comparison with Similar Building Blocks
- Compared to generic conversion blocks, `F_INT_TO_DINT` is specialized and optimized for converting `INT` to `DINT`.
- Other conversion blocks might offer additional features such as overflow checks or scaling, which are not necessary here.

## Conclusion
The `F_INT_TO_DINT` function block is a simple and efficient building block for lossless conversion of 16-bit to 32-bit integer values. It is particularly useful in scenarios where type conversion without additional calculations is required.