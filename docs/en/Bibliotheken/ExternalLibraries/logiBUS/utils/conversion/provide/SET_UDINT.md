# SET_UDINT

![SET_UDINT](./SET_UDINT.svg)

* * * * * * * * * *
## Introduction

The function block **SET_UDINT** is used to write a value from the data input `IN` to the InOut variable `OUT`. The operation is triggered by an event at the input `REQ`, and after successful assignment, the output `CNF` is activated. The function block is specifically designed for the UDINT data type, thus enabling efficient and type-safe data transfer to a shared variable.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `REQ` | Event | Normal execution job; triggers writing the input value to the output variable. |

*Data associated with `REQ`:* `IN`, `OUT`

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `CNF` | Event | Execution confirmation; outputs once the value has been successfully assigned. |

*Data associated with `CNF`:* `OUT`

### **Data Inputs**

| Identifier | Data Type | Initial Value | Comment |
|------------|----------|-------------|-----------|
| `IN` | UDINT | 0 | Value to be written to the target variable. |
| `OUT` (InOut) | UDINT | 0 | Target variable that functions as both an input (readable) and an output (writable). |

### **Data Outputs**

| Identifier | Data Type | Comment |
|------------|----------|-----------|
| `OUT` (InOut) | UDINT | Same variable as the input; after execution, it contains the value of `IN`. |

### **Adapters**

No adapters available.

## Functionality

The function block works very simply:

1. An event at the input `REQ` starts the processing.
2. The ST code implemented in the algorithm `REQ` executes the assignment `OUT := IN;`.
3. After the assignment, the event at the output `CNF` is sent to signal successful completion.

The InOut variable `OUT` is both readable and writable. The assigned value remains until another ``REQ`` assigns a new value or the variable is modified externally.

## Technical Features

- **Using an InOut Variable**: ``OUT`` is declared as an InOut variable. This allows the function block to directly access and modify an external variable without requiring a separate data output. The value is visible both inside and outside the function block after the write operation.
- **Simple Logic**: No intermediate storage, no delays – the process is atomic and occurs in a single step.
- **Type Binding**: The function block is defined exclusively for the type ``UDINT`` (unsigned 32-bit integer), guaranteeing type-safe operation.

## State Overview

The function block contains a single state, `REQ` (event handling):

| State | Action | Output Event |
|---------|--------|------------------|
| `REQ` | Execute algorithm `REQ` (OUT := IN) | CNF |

After `CNF` is executed, the function block returns to its initial state and waits for the next `REQ` event.

## Application Scenarios

- **Variable Initialization**: Setting a UDINT value to a predefined starting value at runtime.
- **Parameter Control**: Overriding configuration values in a running application (e.g., setpoints, counter values).
- **Data Passing Between Logic Blocks**: Using a shared InOut variable to update data without additional intermediate storage.
- **Replacement for Simple Move Functions**: Similar to a MOVE block, but with explicit UDINT focus and InOut mechanics.

## Comparison with Similar Blocks

- **MOVE (Generic)**: A general-purpose MOVE block can copy values of any type, but requires separate inputs and outputs. `SET_UDINT`, on the other hand, uses InOut, which reduces wiring and allows access to the original variable.
- **SET_BOOL, SET_INT, etc.**: Type variants of the same concept for different data types. `SET_UDINT` is specifically optimized for 32-bit unsigned integers.
- **R_TRIG / F_TRIG**: These edge detections do not set values, but rather detect changes. `SET_UDINT` directly writes values.

## Conclusion

The function block `SET_UDINT` is a lean, reliable component for writing an InOut variable with a UDINT value. Its simple structure (one event, one assignment) makes it easy to understand and debug. Using an InOut interface saves on wiring and allows direct manipulation of external variables. Typical of IEC 61499, it is ideal for automation projects where fast and type-safe value assignments are required.
