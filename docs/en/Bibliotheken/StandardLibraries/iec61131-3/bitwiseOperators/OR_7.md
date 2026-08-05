# OR_7

<img width="1295" height="391" alt="OR_7" src="https://github.com/user-attachments/assets/fb73db3a-416e-4f74-9f10-e46fc1e7714e" />

* * * * * * * * * *
## Introduction
The function block `OR_7` performs a bitwise logical OR operation on up to seven input variables. It is a generic function block that can work with various bit data types (`ANY_BIT`). The block is part of the `iec61131::bitwiseOperators` library and implements a standard bitwise operation according to IEC 61131-3.

![OR_7](OR_7.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This event passes all input variables (`IN1` to `IN7`).


### **Event Outputs**

- **CNF**: Signals the successful execution of the OR operation and returns the result via the variable `OUT`.

### **Data Inputs**

- **IN1** to **IN7** (`ANY_BIT`): Up to seven input variables on which the bitwise OR operation is performed. Each input can have any bit data type (e.g., `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD`).

### **Data Outputs**

- **OUT** (`ANY_BIT`): The result of the bitwise OR operation. The data type corresponds to that of the input variables.

### **Adapters**
The function block does not use any adapters.

## Functionality
When the `REQ` event is triggered, the function block performs a bitwise OR operation on the values of the input variables `IN1` through `IN7`. The result is stored in the variable `OUT`, and the `CNF` event is triggered to indicate successful computation.

## Technical Features
- **Generic Implementation**: The function block can handle various bit data types (`ANY_BIT`), making it highly versatile.

- **Scalability**: Supports up to seven input variables, enabling more complex logical operations.


## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Execution State**: Performs the OR operation and calculates the result.

3. **Acknowledgement State**: Triggers the `CNF` event and outputs the result via `OUT`.

## Application Scenarios

- **Logical Operations**: Combining multiple binary signals to produce a common result.

- **Control Engineering**: Used in control algorithms where multiple conditions must be met simultaneously (OR operation).

- **Data Processing**: Bitwise operations at the byte, word, or DWord level.


## ⚖️ Comparison with Similar Function Blocks

- **OR (Standard)**: Standard OR blocks in IEC 61131-3 typically support only two inputs. `OR_7` extends this functionality to up to seven inputs.

- **GEN_OR**: The generic OR block on which `OR_7` is based can theoretically process any number of inputs, but is less specific in its implementation.

## Conclusion
The `OR_7` function block offers a flexible and powerful solution for bitwise OR operations with up to seven input variables. Its generic nature allows its use with various bit data types, making it a versatile tool in control and automation engineering.