# F_WORD_TO_SINT

<img width="1442" height="214" alt="F_WORD_TO_SINT" src="https://github.com/user-attachments/assets/4194432e-902f-48f5-a898-c817d09cae5f" />

* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_SINT` converts a `WORD` data type to a `SINT` data type. It is part of the `iec61131::conversion` package and enables simple and efficient type conversion within 4diac IDE applications.

![F_WORD_TO_SINT](F_WORD_TO_SINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This event input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`WORD`): The input value to be converted from `WORD` to `SINT`.

### **Data Outputs**

- **OUT** (`SINT`): The converted output value of type `SINT`.

### **Adapters**
This function block has no adapters.


### ## Functionality
When the `REQ` event is triggered, the algorithm is executed. This algorithm converts the `WORD` value at input `IN` into a `SINT` value and outputs the result at output `OUT`. Subsequently, the `CNF` event is triggered to signal the successful completion of the conversion.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and performs the conversion in a single algorithm step.

- The conversion is performed using the built-in function `WORD_TO_SINT`.

## State Overview
The function block has no internal states. Execution occurs directly upon triggering the `REQ` event.

## Application Scenarios

- Type conversion in control applications where `WORD` data needs to be converted to `SINT` data.

- Integration into larger control systems that process different data types.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_INT_TO_SINT` or `F_DWORD_TO_SINT` offer conversions between other data types but are comparable in their functionality.

## Conclusion

The `F_WORD_TO_SINT` function block offers a simple and efficient way to convert `WORD` data to `SINT` data. Its clear interface structure and direct functionality make it ideal for applications requiring fast and reliable type conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```