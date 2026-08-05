# SET_DATE_AND_TIME
![SET_DATE_AND_TIME](./SET_DATE_AND_TIME.svg)

* * * * * * * * * *
## Introduction
The SET_DATE_AND_TIME function block is used to write an incoming DATE_AND_TIME value to a target variable. The target variable is passed as an InOut parameter, allowing it to be both read and written. The function block implements a simple assignment operation triggered by an event.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Normal execution request; starts writing the input value to the InOut variable. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| CNF | Confirmation of successful execution. |

### **Data Inputs**

| Name | Type | Description |
|------|---------------|--------------|
| IN | DATE_AND_TIME | The value to be written to the target variable. |

### **Data Outputs**

This function block does not have explicit data outputs. The updated value is made visible externally via the InOut parameter `OUT`.

### **Adapters**

None.

## Functionality

As soon as an event occurs at input `REQ`, the ST instruction `OUT := IN` is executed. The value of input `IN` is copied directly into the InOut variable `OUT`. Upon successful completion, output `CNF` is triggered to signal completion. Using an InOut variable allows the function block to be inserted into an existing data connection without requiring a separate output variable.

## Technical Features
- **InOut Variable:** The parameter `OUT` is declared as InOut. This allows the function block to directly overwrite the value of the associated variable while remaining externally readable.
- **Simple Assignment:** This is a simple copy operation without type conversion or validation checks.
- **No State Machines:** The function block is implemented as a SimpleFB with only one EZ state (REQ). Execution occurs strictly within a single cycle.

## State Overview

The function block has a single state:

| State | Action | Output Event |
|---------|----------------------------------|-----------------|
| REQ | `OUT := IN` | CNF |

The state machine starts in this state upon receiving `REQ`, executes the action, and immediately sends `CNF`.

## Application Scenarios
- **Initializing a System Time:** A higher-level function block can provide the current time (e.g., from an interface) via `IN` and write it to a globally or persistently stored time variable (InOut) via `SET_DATE_AND_TIME`.
- **Resetting a Time Variable:** When setting a reference time, the function block can be used to assign a predefined value to a higher-level variable.
- **Parameterization:** In control/regulation applications, the function block can be used to write target time values to data blocks.

## Comparison with Similar Function Blocks

Simple assignment function blocks for other data types (e.g., `SET_VALUE` for integer or boolean) follow the same pattern. The `SET_DATE_AND_TIME` function block is specifically designed for use with the `DATE_AND_TIME` type and does not offer advanced functions such as addition or subtraction. Unlike a `MOVE` block (which maps an input to an output), this block uses an InOut variable, eliminating the need to separate the source and destination.

## Conclusion

The `SET_DATE_AND_TIME` function block is a simple yet useful block for overriding a date and time variable within an IEC 61499 system. Its use of an InOut interface allows for easy integration into existing data flows. Due to its straightforward structure, it is efficient and suitable for all scenarios requiring the targeted assignment of a date and time value.
