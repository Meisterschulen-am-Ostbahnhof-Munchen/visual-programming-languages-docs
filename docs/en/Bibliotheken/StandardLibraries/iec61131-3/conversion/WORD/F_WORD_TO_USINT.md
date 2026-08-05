# F_WORD_TO_USINT

<img width="1455" height="214" alt="F_WORD_TO_USINT" src="https://github.com/user-attachments/assets/d4f29908-e033-443c-b917-5bb34d0d6283" />

* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_USINT` converts a `WORD` data type to a `USINT` data type. It is part of the `iec61131::conversion` package and is suitable for applications where type conversion between these two data types is required.

![F_WORD_TO_USINT](F_WORD_TO_USINT.svg)

## Interface Structure
### **Event Inputs**
- `REQ` (Event): Starts the execution of the function block. This input is linked to the data input `IN`.


### **Event Outputs**

- `CNF` (Event): Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (WORD): The input value to be converted.

### **Data Outputs**

- `OUT` (USINT): The converted output value.

### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion from `WORD` to `USINT` as soon as the event `REQ` is received. The conversion is performed using the function ``WORD_TO_USINT``, which converts the input value ``IN`` into the output value ``OUT``. Upon completion of the conversion, the event ``CNF`` is triggered.

## Technical Features

- The function block is a simple function block (SimpleFB) and uses an ST algorithm for the conversion.

- The conversion occurs directly and without any additional delay.

## State Overview

1. **Idle State**: The function block waits for the event ``REQ``.

2. **Execution State**: Upon receiving ``REQ``, the conversion is performed.

3. **Confirmation State**: After successful conversion, `CNF` is triggered, and the function block returns to its idle state.

## Application Scenarios

- Type conversion in control applications where a `WORD` value needs to be converted to a `USINT` value.

- Integration into larger control systems that need to process different data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion function blocks such as `F_INT_TO_REAL` or `F_BOOL_TO_STRING`, `F_WORD_TO_USINT` specializes in converting `WORD` to `USINT`.

- Similar building blocks could be `F_USINT_TO_WORD`, which performs the reverse conversion.

## Conclusion
The function block `F_WORD_TO_USINT` offers a simple and efficient way to convert `WORD` values to `USINT` values. Its clear interface structure and simple functionality make it ideal for applications requiring such type conversion.