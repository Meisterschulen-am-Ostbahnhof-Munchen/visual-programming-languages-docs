# F_LWORD_TO_ULINT

<img width="1463" height="212" alt="F_LWORD_TO_ULINT" src="https://github.com/user-attachments/assets/f5071900-017b-4af7-80c6-b542df47d0dc" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_ULINT` is used to convert an LWORD data type to a ULINT data type. This conversion is particularly necessary in scenarios where data of different bit lengths needs to be processed or transmitted.
![F_LWORD_TO_ULINT](F_LWORD_TO_ULINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: This event input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: This event output signals the successful completion of the conversion. It is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a variable of type `LWORD`, which is to be converted.

### **Data Outputs**

- **OUT**: The output returns the result of the conversion as `ULINT`.

### **Adapters**

This function block has no adapters.

## Functionality

When the event input `REQ` is triggered, the algorithm is started, which converts the value of `IN` of type `LWORD` to type `ULINT` and outputs the result as `OUT`. The event `CNF` is then triggered to signal the successful conversion.

## Technical Features

- This function block is particularly efficient because it directly utilizes the built-in function `LWORD_TO_ULINT`.
- There are no special constraints or limitations when using this function block.

## State Overview

This function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Data conversion in control systems where different data types need to be processed.
- Integration into larger systems that require type conversion between `LWORD` and `ULINT`.

## ⚖️ Comparison with Similar Function Blocks

Compared to other conversion blocks, `F_LWORD_TO_ULINT` specializes in converting `LWORD` to `ULINT` and therefore offers an optimized solution for this specific use case.

## Conclusion

The `F_LWORD_TO_ULINT` function block is a simple and efficient building block for converting between the data types `LWORD` and `ULINT`. Its clear interface structure and direct functionality make it a reliable component in control applications.
