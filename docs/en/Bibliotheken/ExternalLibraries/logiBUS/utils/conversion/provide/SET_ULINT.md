# SET_ULINT

![SET_ULINT](./SET_ULINT.svg)

* * * * * * * * * *

## Introduction

The **SET_ULINT** function block is used to write an unsigned 64-bit integer value (ULINT) from a data input to an InOut variable. It is typically used to set values to linked variables or global memory locations that can also be read by other function blocks.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Normal execution command. The value of `IN` is transferred to the InOut variable `OUT`, and upon completion, the event output `CNF` is sent. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| CNF | Execution confirmation. Triggered as soon as the assignment of `IN` to `OUT` is completed. |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
| IN | ULINT | The value to be written. Default: `0`. |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|--------------|
| OUT | ULINT | InOut variable – target of the assignment. It can be both read and written and is set to the new value after execution. |

### **Adapter**

None.

## Functionality

The function block is implemented as a simple state machine (SimpleFB). A single state, `REQ`, executes the algorithm `REQ` when activated:

OUT := IN;
The event output `CNF` is then sent. The passed value `IN` is therefore copied directly into the InOut variable `OUT`. Since `OUT` is declared as InOut, the function block cannot read the previous value of `OUT` – it is simply overwritten.

## Technical Features

- The function block uses an **InOut variable** (`OUT`), which functions as both an input and output port in the IEC 61499 model. This allows direct connections to variables shared by multiple function blocks.
- The `logiBUS::utils::conversion::provide` package in the CompilerInfo indicates that the function block (FB) is intended for use in the logiBUS ecosystem.
- The algorithm is very simple – just a single ST assignment – and therefore extremely fast to execute.
- The initial value of `OUT` is `0`, so a defined starting value is available upon first use without prior initialization.

## State Overview

The FB has exactly one EC state:

| State | Action | Output |
|---------|--------|---------|
| REQ | `REQ` (OUT := IN) | CNF |

After startup or reset, the function block (FB) is in state `REQ`. Each `REQ` event pulse triggers the action and subsequently generates `CNF`.

## Application Scenarios

- **Parameterized by Real-Time Systems**: Setting setpoints or configuration parameters in a variable monitored by multiple function blocks.
- **Global Status Variables**: Writing error codes or operating states to a central `ULINT` variable.
- **Testing and Diagnostic Purposes**: Targeted overwriting of values in a running controller for analysis purposes.

## Comparison with Similar Function Blocks

- **SET_INT, SET_DINT, SET_LINT**: Similar function blocks for other integer types (INT, DINT, LINT). The functionality is identical; only the data type differs.
- **MOVE_ULINT**: Many libraries include a MOVE block that copies a value from an input to an output. `SET_ULINT` differs by using an **InOut variable**, which allows direct access to an existing variable without having to use a pure output.

## Conclusion

The **SET_ULINT** function block is a simple yet effective tool for setting ULINT values in shared variables. Its InOut interface makes it particularly suitable for applications where values need to be overwritten without evaluating the previous state. Its lean implementation makes it well-suited for time-critical control applications.
