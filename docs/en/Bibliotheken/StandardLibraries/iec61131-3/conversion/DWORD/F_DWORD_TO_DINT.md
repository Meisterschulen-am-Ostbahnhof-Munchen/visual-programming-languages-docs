# F_DWORD_TO_DINT

<img width="1248" height="184" alt="F_DWORD_TO_DINT" src="https://github.com/user-attachments/assets/118c3a3a-7bd4-4adb-a8e1-f927a4ca8bab" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_DINT` converts a `DWORD` value to a `DINT` value. This conversion is particularly necessary when exchanging data between systems that use different data types. The block is part of the `iec61131::conversion` package and conforms to standard 61499-1.

![F_DWORD_TO_DINT](F_DWORD_TO_DINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a `DWORD` value to be converted.

### **Data Outputs**

- **OUT**: The output provides the converted `DINT` value.

### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion from `DWORD` to `DINT` as soon as the event `REQ` is received. The conversion is performed using the function `DWORD_TO_DINT(IN)`. After successful conversion, the event `CNF` is triggered, and the converted value is output via the output `OUT`.

## Technical Features
- The block is implemented as a simple function block (`SimpleFB`).

- The conversion is performed directly without additional state management.

## State Overview
Since it is a simple function block, there are no explicit states. The conversion is performed with each `REQ` event.

## Application Scenarios
- Conversion of `DWORD` data supplied by one system into `DINT` data for another system.

- Use in control systems where data types need to be harmonized.

## ⚖️ Comparison with similar blocks

- Similar blocks could be `F_WORD_TO_INT` or `F_LWORD_TO_LINT`, but these convert different data types.

- Unlike more complex conversion blocks, `F_DWORD_TO_DINT` offers a direct and simple solution for this specific conversion.

## Conclusion
The `F_DWORD_TO_DINT` function block provides an efficient and simple way to convert `DWORD` values to `DINT` values. Its clear interface and direct operation make it ideal for applications requiring fast and reliable type conversion.