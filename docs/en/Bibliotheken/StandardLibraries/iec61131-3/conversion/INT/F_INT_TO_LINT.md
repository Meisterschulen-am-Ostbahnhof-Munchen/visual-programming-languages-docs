# F_INT_TO_LINT
<img width="1217" height="182" alt="F_INT_TO_LINT" src="https://github.com/user-attachments/assets/f954943f-b46e-43fd-b6c1-d3efa3135040" />
* * * * * * * * * *
## Introduction
The function block `F_INT_TO_LINT` converts a 16-bit integer value (`INT`) into a 64-bit long integer value (`LINT`). This block is particularly useful in scenarios where extending the value range or changing the type is required for subsequent processing steps.
![F_INT_TO_LINT](F_INT_TO_LINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`INT`): The 16-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`LINT`): The resulting 64-bit long integer value after the conversion.

### **Adapters**
No adapters are present.

### ## Functionality

The function block performs a direct assignment of the input value `IN` of type `INT` to the output value `OUT` of type `LINT`. The conversion is performed implicitly through type conversion, preserving the numeric value.

## Technical Features
- **Simple Implementation**: The algorithm consists of a single assignment.
- **No Data Loss**: Since `LINT` has a larger range of values than `INT`, there are no overflow problems.
- **Deterministic Behavior**: Execution is predictable and fast.

## State Overview
The function block has no internal state. Every call to `REQ` results in immediate execution and output via `CNF`.

## Application Scenarios
- **Data Processing**: Extending integer values for subsequent calculations with a larger value range.
- **Interface Adaptation**: Adapting data for components that expect `LINT`.
- **Logging**: Storing `INT` values in systems that use `LINT`.

## ⚖️ Comparison with Similar Function Blocks
- **F_INT_TO_DINT**: Converts `INT` to `DINT` (32-bit), offering a smaller value range than `LINT`.
- **F_DINT_TO_LINT**: Converts `DINT` to `LINT`, similar but with a different input type.
- **F_LINT_TO_INT**: Reverse conversion, potentially resulting in data loss.

## Conclusion
The `F_INT_TO_LINT` function block is a simple and efficient tool for type conversion in the 4diac IDE. Its strength lies in its direct and lossless conversion, making it ideal for applications with extended value requirements.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]