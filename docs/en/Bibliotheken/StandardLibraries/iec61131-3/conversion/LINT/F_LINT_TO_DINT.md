# F_LINT_TO_DINT

<img width="1435" height="214" alt="F_LINT_TO_DINT" src="https://github.com/user-attachments/assets/a682b68b-2ee9-48bc-ad3e-b7a8d15353a8" />

* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_DINT` converts a 64-bit integer value (LINT) to a 32-bit integer value (DINT). This conversion is useful when data needs to be exchanged between systems with different word widths or when memory space needs to be optimized.

![F_LINT_TO_DINT](F_LINT_TO_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (LINT): The 64-bit integer value to be converted.

### **Data Outputs**

- **OUT** (DINT): The resulting 32-bit integer value after conversion.

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion by calling the algorithm `REQ` as soon as the event `REQ` occurs. The algorithm uses the function `LINT_TO_DINT` to convert the value from `IN` to `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block is part of the package `iec61131::conversion`.

- It is a simple function block without internal states or complex logic.

- The conversion can result in data loss if the original LINT value is outside the representable range of a DINT.

## State Overview
Because it is a simple function block, there are no state transitions or internal states. The logic is executed directly upon the arrival of the `REQ` event.

## Application Scenarios

- Data compatibility between systems with different word widths.

- Memory optimization when 64-bit values are not required.

- Integration into larger control systems that require DINT values.


## ⚖️ Comparison with Similar Blocks
- Unlike generic conversion blocks, `F_LINT_TO_DINT` specializes in converting LINT to DINT.

- Other blocks might offer additional features such as range checks or error handling, which is not the case here.

## Conclusion
The `F_LINT_TO_DINT` function block provides a simple and efficient way to convert 64-bit integer values to 32-bit integer values. Its simplicity makes it reliable and easy to integrate; however, users should be aware of potential data loss when converting large values.