# SET_WORD

![SET_WORD](./SET_WORD.svg)

* * * * * * * * * *

## Introduction

The SET_WORD function block writes a WORD value from its data input IN to an InOut variable OUT. It is used to overwrite an output or a globally accessible WORD variable with a specific value.

## Interface Structure

### **Event Inputs**

- **REQ** (Event): Normal execution command. The block is triggered when an event arrives at this input.

Connected to the variables `IN` and `OUT`.

### **Event Outputs**

- **CNF** (Event): Confirmation of execution. Sent after successful assignment.

Connected to the variable `OUT`.

### **Data Inputs**

- **IN** (WORD): The value to be written to the target variable. Initial value: `0`.

### **Data Outputs**
No data outputs are available. Output is exclusively via the InOut variable `OUT`.

### **Adapters**
None.

## Functionality

When an event occurs at the **REQ** input, the following algorithm is executed:

`OUT := IN;`
Subsequently, an acknowledgment event is sent at the **CNF** output. The function block overwrites the current value of `OUT` with the value of `IN`.


## Technical Features

- `OUT` is declared as an **InOut variable**. It serves as both input (read) and output (write). The previous value of `OUT` is overwritten by the assignment.

- There are no separate data outputs – the change directly affects the associated variable.

- The function block is type-specific to `WORD`. Corresponding variants are available for other data types.

## State Overview

The function block has one active state:

- **REQ**: Upon entering this state, the assignment `OUT := IN` is executed, and the **CNF** event is triggered.

There are no other states or branches.

## Application Scenarios

- Setting a WORD output to a calculated or fixed value.

- Overwriting a global WORD variable in a PLC.

- One-time initialization of a WORD variable by an external function block.

## Comparison with similar function blocks

- **MOVE**: Copies a value from an input to an output (separate inputs/outputs). SET_WORD uses an InOut variable instead.

- **SET_BOOL**: Analogous functionality for the BOOL data type.

- **F_MOVE**: Function block for general data transfer, often with multiple inputs/outputs. SET_WORD is more specific and direct.

## Conclusion

SET_WORD is a simple and efficient function block for writing a WORD value directly to an InOut variable. By using an InOut parameter, it reduces the number of variables required and is particularly useful in scenarios where a value needs to be overwritten without using a separate output.