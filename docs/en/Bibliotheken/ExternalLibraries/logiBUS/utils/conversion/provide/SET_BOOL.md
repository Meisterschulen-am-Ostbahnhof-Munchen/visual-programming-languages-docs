# SET_BOOL
![SET_BOOL](./SET_BOOL.svg)

* * * * * * * * * *
## Introduction
The function block `SET_BOOL` is used to write a Boolean input value (`IN`) to an InOut variable (`OUT`). It provides simple assignment logic for BOOL data and is controlled by an event.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Normal Execution Trigger |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Execution Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|------|-----|-------------|-----------|

| IN | BOOL | FALSE | Value to be written to the target variable |

### **Data Outputs**

No separate data outputs. The output value is provided via the InOut variable `OUT`.

### **Adapters**

None.

## Functionality

When the event `REQ` is received, the function block executes the assignment `OUT := IN`. The current value of input `IN` is copied to the InOut variable `OUT`. Then, the confirmation event `CNF` is sent. The InOut variable `OUT` can be externally assigned to any BOOL variable, allowing the value to be written directly to the corresponding location in the system.

## Technical Features
- The function block uses an **InOut variable** (`OUT`) that functions as both an output and an input. This allows the value to be written directly to an external variable without requiring a separate data output.
- The initial values of `IN` and `OUT` are both `FALSE`, which ensures a defined state even without initialization.
- There is only one algorithm and one state; therefore, the execution logic is deterministic and unconcurrency-free.

## State Overview

| State | Action | Event Output | Description |

|---------|--------|----------------|--------------|

| REQ | `OUT := IN` | CNF | On the REQ event, the input value is written to the InOut variable, and execution is confirmed. |

The function block has only one active state. After execution, it waits for the next `REQ` event.

## Application Scenarios
- **Setting a Global Flag**: A Boolean flag can be set in another function block or a global variable via an InOut variable.
- **Assigning Values from a Sensor**: A Boolean sensor value (e.g., from a switch) is directly assigned to a control variable.
- **Initializing BOOL Variables**: A defined value can be written to a variable at system startup using `REQ`.

## Comparison with Similar Function Blocks
- **`MOVE` (e.g., ANY to ANY)**: `MOVE` copies values of any data type but requires separate inputs and outputs. `SET_BOOL` is BOOL-based and uses an InOut variable, enabling more compact connections.
- **`SET_BOOL` vs. direct assignment in ST**: This function block abstracts the assignment as an event-driven block and can be used in graphical editors (e.g., FBD) where direct assignment is not possible.
- **`R_TRIG` / `F_TRIG`**: These function blocks detect edges and only change the output on signal transitions. In contrast, `SET_BOOL` performs an unconditional assignment on every `REQ` event.

## Conclusion

SET_BOOL` is a simple yet practical function block for directly assigning a Boolean value to a variable using an InOut interface. It is ideally suited for control tasks where a Boolean state needs to be set and integrates seamlessly into the event-driven paradigm of IEC 61499.
