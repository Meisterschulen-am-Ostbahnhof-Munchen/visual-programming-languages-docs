# OR_8

<img width="1295" height="419" alt="OR_8" src="https://github.com/user-attachments/assets/796c2ebd-f9a4-4c89-a96d-3cd2962919f4" />
* * * * * * * * * *
## Introduction

The OR_8 function block is a generic function block for calculating a bitwise OR operation. It supports up to 8 inputs and is classified according to the IEC 61131-3 standard. This function block is particularly suitable for applications where multiple binary signals need to be logically combined.
![OR_8](OR_8.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. It is linked to all data inputs.

### **Event Outputs**

- **CNF**: Signals the successful execution of the function block. It is linked to the data output `OUT`.

### **Data Inputs**

- **IN1** to **IN8**: Each of these inputs accepts an arbitrary bit type (`ANY_BIT`). These represent the operands for the OR operation.

### **Data Outputs**

- **OUT**: Returns the result of the bitwise OR operation of inputs `IN1` to `IN8`. The data type corresponds to that of the inputs (`ANY_BIT`).

### **Adapters**

This function block does not have any adapters.

## Functionality

The OR_8 function block performs a bitwise OR operation on the values at inputs `IN1` to `IN8`. The result is output at `OUT` as soon as the event `REQ` is received. Execution is confirmed by the event `CNF`.

## Technical Features

- **Generic Implementation**: The function block is generic and can work with different bit types (`ANY_BIT`).
- **Flexible Number of Inputs**: Supports up to 8 inputs, making it suitable for complex logic operations.

## State Overview

1. **Idle State**: Waits for the event `REQ`.
2. **Execution State**: Performs the OR operation and sets the output `OUT`.
3. **Acknowledgement State**: Sends the event `CNF` to confirm execution.

## Application Scenarios

- Logical combination of multiple sensor data.
- Control logic in industrial automation systems.
- Combination of binary control signals.

## ⚖️ Comparison with Similar Function Blocks

- **OR_2/OR_4**: Similar function blocks with fewer inputs (2 or 4, respectively). OR_8 offers greater flexibility for more complex applications.
- **GEN_OR**: Generic base implementation that is further specialized by OR_8.

## Conclusion

The OR_8 function block is a powerful tool for bitwise OR operations in industrial automation. Its generic nature and support for up to 8 inputs make it particularly versatile.
