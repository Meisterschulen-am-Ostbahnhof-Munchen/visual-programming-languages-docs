# F_STRING_AS_LWORD

<img width="1478" height="213" alt="F_STRING_AS_LWORD" src="https://github.com/user-attachments/assets/e11ef5e8-2080-4d17-b504-b066c795a15d" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_LWORD` converts a `STRING` value to a `LWORD` value. It is part of the `iec61131::conversion` package and enables easy conversion between these two data types.
![F_STRING_AS_LWORD](F_STRING_AS_LWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`STRING`): The input string to be converted to a `LWORD` value.

### **Data Outputs**

- **OUT** (`LWORD`): The converted `LWORD` value.

### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion when the `REQ` event is received. The input string `IN` is converted into a value `LWORD` using the function `STRING_AS_LWORD` and output as `OUT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features

- The conversion is performed directly without additional parameters.
- The block is implemented as a simple function block (`SimpleFB`) containing only one algorithm.

## State Overview

The function block has no internal state. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Conversion of string data into `LWORD` values for further processing in control systems.
- Integration into systems that require `LWORD` values but receive string input.

## ⚖️ Comparison with Similar Building Blocks

- Compared to other conversion building blocks, `F_STRING_AS_LWORD` specializes in converting `STRING` to `LWORD`.
- Other building blocks, such as `F_STRING_TO_*`, may offer similar functionality for other data types.

## Conclusion

The `F_STRING_AS_LWORD` function block provides a simple and efficient way to convert string data into `LWORD` values. It is particularly useful in scenarios where such conversions are needed regularly.
