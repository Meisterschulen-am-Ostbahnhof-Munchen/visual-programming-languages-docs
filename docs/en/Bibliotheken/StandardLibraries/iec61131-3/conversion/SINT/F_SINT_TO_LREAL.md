# F_SINT_TO_LREAL

<img width="1448" height="213" alt="F_SINT_TO_LREAL" src="https://github.com/user-attachments/assets/68877ca6-0d50-4534-9301-8bdead3b94f2" />

* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_LREAL` converts an integer value of type `SINT` (8-bit integer) to a floating-point value of type `LREAL` (64-bit floating-point). This block is particularly useful in applications where type conversion between these two data types is required.

![F_SINT_TO_LREAL](F_SINT_TO_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Input for the `SINT` value to be converted.

### **Data Outputs**

- **OUT**: Output for the converted `LREAL` value.

### **Adapters**
No adapters are available.

## Functionality
The function block performs a direct type conversion. Upon the arrival of a `REQ` event, the value of `IN` is read, converted to the type `LREAL`, and output to `OUT`. Subsequently, the `CNF` event is triggered.

## Technical Features
- The conversion is performed without any additional scaling or rounding.

- The function block is implemented simply and efficiently, as it requires only one assignment.

## State Overview

The function block has no internal states. It reacts exclusively to the `REQ` event with an immediate conversion and output.


## Application Scenarios

- Type conversion in control applications where `SINT` values need to be used in calculations with `LREAL` values.

- Data preparation for visualization or logging where higher accuracy is required.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_INT_TO_REAL` or `F_DINT_TO_LREAL` offer conversions between other data types, but not specifically from `SINT` to `LREAL`.

- This function block specializes in converting 8-bit integers to 64-bit floating-point numbers.


## Conclusion

The `F_SINT_TO_LREAL` function block is a simple and efficient tool for type conversion in the 4diac IDE. Its clear interface and direct functionality make it a reliable component in control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```