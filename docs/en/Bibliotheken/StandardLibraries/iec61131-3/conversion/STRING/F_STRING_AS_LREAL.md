# F_STRING_AS_LREAL

<img width="1478" height="213" alt="F_STRING_AS_LREAL" src="https://github.com/user-attachments/assets/880cb73d-8178-4d13-866b-ef55bab0ae2a" />

* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_LREAL` converts a STRING value to an LREAL value (64-bit floating-point number). This block is particularly useful when strings need to be converted into numeric values, for example, when processing user input or reading data from external sources.

![F_STRING_AS_LREAL](F_STRING_AS_LREAL.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (STRING): The string value to be converted.

### **Data Outputs**

- `OUT` (LREAL): The result of the conversion as a 64-bit floating-point number.

### **Adapters**
This function block does not use any adapters.

## Operation
When the `REQ` event is triggered, the value at the input `IN` is read as a string and converted into an LREAL value. The result is output as `OUT`, and the `CNF` event signals successful execution.

The conversion algorithm is implemented as ST code:

```ST
ALGORITHM REQ
OUT := STRING_AS_LREAL(IN);
END_ALGORITHM
```
## Technical Features

- The conversion follows the standard rules for converting STRING to LREAL in IEC 61131-3.

- For invalid input values (e.g., non-numeric strings), the behavior may vary depending on the runtime environment.


## State Overview

The function block has a simple state machine:

1. Waits for the `REQ` event

2. Performs the conversion

3. Sends the `CNF` event

4. Returns to wait state

## Application Scenarios

- Processing user input in numeric controllers
- Converting text data from files or network sources
- Interfaces to systems that transmit numeric data as strings

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, this function block specializes in STRING-to-LREAL conversion.

- Other similar blocks might offer additional parameters for number formatting.


## Conclusion

The `F_STRING_AS_LREAL` function block offers a simple and efficient way to convert strings to 64-bit floating-point numbers. Its clear interface and simple functionality make it particularly suitable for standard conversion tasks in automation projects.