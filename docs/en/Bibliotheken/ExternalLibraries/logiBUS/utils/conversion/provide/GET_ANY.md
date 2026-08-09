# GET_ANY

![GET_ANY](./GET_ANY.svg)

* * * * * * * * * *
## Introduction

The **GET_ANY** function block reads an arbitrary value (type `ANY`) from an InOut variable and provides it as a buffered output value. It serves to capture the current value of a variable source at a specific point in time and temporarily store it for subsequent processing steps.
## Interface Structure

### **Event Inputs**

| Name | Type | With Variables | Description |
|------|-----|----------------|--------------|
| REQ | Event | IN | Normal execution request; reads the current value of IN. |

### **Event Outputs**

| Name | Type | With Variables | Description |
|------|-----|---------------|--------------|
| CNF | Event | IN, OUT | Confirmation after successful execution; the values of IN and OUT are then valid. |

### **Data Inputs**

The function block has no separate data inputs. The source data is provided via the InOut variable.

### **Data Outputs**

| Name | Type | Description |
|------|-----|---------------|
| OUT | ANY | Buffered output value. Contains the value read from IN at the time of the last REQ execution. |

### **Adapter**

None.

## Functionality

1. An event at **REQ** triggers the internal algorithm `REQ`.
2. The algorithm executes the assignment `OUT := IN`.
- **IN** is an InOut variable that can be both read and written – here it is used only as a source.
- **OUT** receives the current value of **IN** and stores it temporarily.
3. After the assignment is complete, the **CNF** event is sent. At this point, both **IN** (unchanged) and **OUT** are valid.

## Technical Features

- The function block uses an **InOut variable** (`IN`) as its source. This allows direct access to another block output or a global variable without requiring a separate connection via a data input.

**IN** receives the current value of **IN** and stores it temporarily. - The **type `ANY`** makes the function block generic; it can be used with any data type (e.g., INT, REAL, BOOL, STRING).

- There is only one state, therefore execution is deterministic and occurs in a single step.

## State Overview

The function block is implemented as a **SimpleFB** with exactly one state:

| State | Description |
|---------|--------------|
| REQ | Executes the algorithm `REQ` and sends CNF. After the action, the function block returns to this state (default). |

No other states (e.g., Wait, Error) are defined.

## Application Scenarios

- **Value Sampling**: At a specific point in time (event), a current value from a sensor or calculation should be captured, e.g., for later logging or comparison.
- **Signal Decoupling**: If an output needs to be read multiple times without the value changing during processing, GET_ANY buffers the value.
- **Type-Independent Interface**: As a generic buffer in libraries that work with different data types.

## Comparison with Similar Function Blocks

- **`GET` Function Blocks** (e.g., `GET_INT`): These are type-specific and require explicit data types. In contrast, `GET_ANY` offers **type flexibility** at the expense of type safety at design time.
- **`MOVE`-FB**: A `MOVE` function block typically copies from an input to an output but does not use an InOut variable. `GET_ANY`, on the other hand, reads directly from an existing variable without requiring a separate input connection.

## Conclusion

GET_ANY` is a simple yet powerful function block for **caching any value** from an InOut source. Its generic type design and direct connection to existing variables reduce wiring complexity and increase flexibility in the control logic. It is particularly suitable for applications where a value needs to be frozen at a specific event time.
