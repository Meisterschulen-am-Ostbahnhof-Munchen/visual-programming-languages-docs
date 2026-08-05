# SET_WSTRING
![SET_WSTRING](./SET_WSTRING.svg)

* * * * * * * * * *
## Introduction
The function block **SET_WSTRING** is used to transfer a value of data type `WSTRING` to an InOut parameter. It is typically used to write a calculated or externally specified string value to a higher-level variable (e.g., of another instance or a higher-level function block).
## Interface Structure
### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Normal execution call: The assignment of the input value to the InOut variable is triggered. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Execution confirmation. Sent after successful assignment. |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
| `IN` | `WSTRING` | Source value to be written to the target variable. |

### **Data Outputs**
This function block does not have traditional data outputs. The value is passed via the **InOut variable** `OUT`.

### **Adapters**
None.

## Functionality
If the event input `REQ` is activated, the function block executes the following assignment:

OUT := IN;
The value `WSTRING`, which is present at input `IN`, is copied unchanged to the InOut variable `OUT`. Then, the event `CNF` is sent to signal the completion of the operation to the calling function block.

## Technical Features
- **InOut Variable**: `OUT` is declared as an InOut parameter. This means that the variable can be both read and written, and its lifetime is outside the function block. The function block overwrites the current content of `OUT` with the value of `IN`.

`` - **Data type `WSTRING`**: This is a string type that supports wide characters (Unicode). The function block does not perform any length checks or conversions – the assignment is direct.

- **Simplest State Machine**: The state machine consists of a single state (`REQ`) that covers all functionality. There are no branches or time delays.

## State Overview
The function block contains exactly one state:

| State | Description |
|---------|---------------|
| `REQ` | Becomes active after the event `REQ` occurs. Executes the assignment `OUT := IN` and sends `CNF`. The function block then returns to its initial state. |

## Application Scenarios
- **Passing a Formatted String**: Suppose a function block generates an error message as `WSTRING` and wants to write it to a parent variable. `SET_WSTRING` handles this assignment upon a trigger.
- **Parameterization**: In a controller, an external parameter (e.g., a product name) can be copied to a global data block using `SET_WSTRING`.
- **Debugging**: Temporarily setting a WSTRING variable using test or initialization logic.

## Comparison with Similar Function Blocks
- **SET_BOOL**: Works analogously, but with the data type `BOOL`. Both use an InOut to write values to external variables.
- **MOVE (IEC Function Block)**: The standard MOVE function block copies data from an input to an output. In contrast, `SET_WSTRING` uses an InOut parameter, which allows connection to existing variables without an additional output port.
- **WRITE_STRING**: Some libraries offer special Write function blocks with length checks. `SET_WSTRING` is deliberately kept simple and does not include any checks.

## Conclusion
The **SET_WSTRING** function block is a minimalist yet effective solution for writing to a WSTRING InOut variable. Its simple state machine and clear interface make it easy to understand and use wherever a trivial assignment to an event is needed. For tasks with additional functions (conversion, length constraints), specialized building blocks are preferable.
