# SET_SINT

![SET_SINT](./SET_SINT.svg)

* * * * * * * * * *

## Introduction

The function block **SET_SINT** is used to write a SINT value from its data input **IN** to an InOut variable **OUT**. It is used to set a SINT value at a specific point in the control sequence. The block implements a simple, event-driven assignment.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| **REQ** | Normal execution request. Triggers the assignment from **IN** to **OUT**. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Execution confirmation. Sent after successful assignment. |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|------|--------------|--------------|
| **IN** | SINT | 0 | The value to be written. |

### **Data Outputs**

The function block has no separate data outputs. The target value is returned via the InOut variable **OUT**.

### **Adapters**

No adapters are available.

## Functionality

A **REQ** event starts the execution of the algorithm. Within the algorithm, the current value of **IN** is directly assigned to the InOut variable **OUT**:

OUT := IN;
After the assignment is complete, the **CNF** event is triggered. The InOut variable **OUT** serves as both input and output – its value is overwritten and then available for subsequent function blocks.

## Technical Features

- **InOut Variable**: The variable **OUT** is declared as `InOut`. It can be both read and written. The function block overwrites the existing value of **OUT** with the value of **IN**.
- **Simplest Algorithm**: The function block performs only a single assignment. There are no conditions, loops, or additional logic.
- **Type Safety**: Both **IN** and **OUT** are of type `SINT`, ensuring a direct, type-compliant assignment.

## State Overview

The function block has a single state (ECState) named **REQ**:

| State | Action | Output Event |
|---------|--------|-----------------|
| REQ | `OUT := IN` | CNF |

There is only this one state; after execution, the function block returns to its initial state. It is not an explicit state machine with multiple states.

## Application Scenarios

- **Setting a SINT value at runtime**: For example, overwriting a limit value or a counter in a controller.
- **Initializing SINT variables** in a specific step of the control sequence.
- **Passing a constant or calculated value** to another function block via the InOut variable, provided there is a connection to a global variable or another InOut port.

## Comparison with Similar Function Blocks

- **SET_BOOL**: Analogous function for the data type `BOOL`. Works identically, but with Boolean values.
- **SET_INT**: Corresponding function block for `INT`. The structure (event REQ/CNF, assignment) is identical.
- **MOVE (e.g., MOVE_SINT)**: A MOVE function block copies a value from an input to an output without the target variable being implemented as an InOut. **SET_SINT**, on the other hand, writes directly to an existing variable, which in some architectures offers the advantage that the variable can also be read by other function blocks without requiring a separate connection to an output.

## Conclusion

**SET_SINT** is a minimal and reliable function block for setting a SINT variable to a desired value. Its simplicity makes it ideal for situations where a value needs to be overwritten directly without additional logic. Using an InOut variable saves on separate output variables and allows direct chaining with other function blocks that read the same variable. It is an efficient solution for simple value assignments.
