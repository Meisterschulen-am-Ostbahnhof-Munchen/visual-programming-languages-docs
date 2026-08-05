# F_UINT_AS_STRING

<img width="1465" height="216" alt="F_UINT_AS_STRING" src="https://github.com/user-attachments/assets/23074f51-da16-4e74-8d92-77a0fcbc6f67" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_AS_STRING` converts an unsigned integer value (`UINT`) into a string (`STRING`). This functionality is particularly useful when numeric values are needed as text for output, logging, or further processing.

![F_UINT_AS_STRING](F_UINT_AS_STRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is activated along with the converted value at data output `OUT`.

### **Data Inputs**

- **IN** (`UINT`): The unsigned integer value to be converted to a string.

### **Data Outputs**

- **OUT** (`STRING`): The string generated from the input value `IN`.

### **Adapters**
This function block has no adapters.


### ## Functionality
When the event input `REQ` is triggered, the algorithm is started, which converts the value of `IN` to `STRING` using the function `UINT_AS_STRING`. The result is output to `OUT`, and the event `CNF` signals successful conversion.

## Technical Features
- The conversion is performed directly and without delay.

- The function block is implemented simply and efficiently, without additional states or complex logic.

## State Overview

The function block has no internal state. Each execution is independent of previous calls.

## Application Scenarios

- Displaying numerical values in user interfaces.

- Logging measured values to text files.

- Preparing data for communication via text-based protocols.

## ⚖️ Comparison with similar building blocks

- Unlike generic conversion blocks, `F_UINT_AS_STRING` specializes in converting `UINT` to `STRING`.

- Other blocks might support additional parameters such as formatting or base (decimal, hexadecimal), which is not the case here.

## Conclusion
The `F_UINT_AS_STRING` function block is a simple and effective tool for converting unsigned integer values to strings. Its strength lies in its simplicity and direct applicability in scenarios where a fast and straightforward conversion is required.