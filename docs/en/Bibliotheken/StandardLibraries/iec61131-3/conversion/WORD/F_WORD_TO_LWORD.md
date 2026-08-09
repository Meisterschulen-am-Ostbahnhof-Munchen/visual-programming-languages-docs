# F_WORD_TO_LWORD

<img width="1451" height="214" alt="F_WORD_TO_LWORD" src="https://github.com/user-attachments/assets/ccfea12c-64cc-4b10-91db-6d39f78fc006" />
* * * * * * * * * *
## Introduction

The function block `F_WORD_TO_LWORD` is used to convert a `WORD` data type to a `LWORD` data type. This function block is particularly useful in scenarios where an extension of the data width is required, for example, in communication between systems with different data word sizes.
![F_WORD_TO_LWORD](F_WORD_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Expects an input of type `WORD`, which is to be converted to `LWORD`.

### **Data Outputs**

- **OUT**: Outputs the converted result of type `LWORD`.

### **Adapters**

This function block has no adapters.

## Functionality

The function block performs the conversion as soon as the event `REQ` is received. The conversion is performed using the function ``WORD_TO_LWORD``, which converts the input value ``IN`` of type ``WORD`` into the output value ``OUT`` of type ``LWORD``. Upon successful conversion, the event ``CNF`` is triggered.

## Technical Features

- The conversion is direct and requires no additional parameters or state management.
- The function block is suitable for use in real-time systems because it does not involve any delays or complex calculations.

## State Overview

The function block has no internal states. The operation is stateless and is re-executed with each ``REQ`` event.

## Application Scenarios

- Extending the data width for subsequent processing steps.
- Ensuring compatibility between systems with different word sizes.
- Simple data type conversion in control and automation systems.

## ⚖️ Comparison with Similar Function Blocks

Compared to generic conversion blocks, `F_WORD_TO_LWORD` offers a specialized and efficient solution for converting `WORD` to `LWORD`. Other blocks might be more general, but less optimized for this specific task.

## Conclusion

The `F_WORD_TO_LWORD` function block is a simple yet effective block for the specific conversion of `WORD` to `LWORD`. Its simplicity and direct functionality make it a reliable choice in many automation and control scenarios.