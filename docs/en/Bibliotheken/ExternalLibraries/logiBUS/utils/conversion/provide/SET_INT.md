# SET_INT

![SET_INT](./SET_INT.svg)

* * * * * * * * * *
## Introduction

The function block **SET_INT** is used to write a value of data type `INT` from an input directly into an InOut variable. This block is a simple, event-driven function block and is typically used to set global parameters or variables of other function blocks via a defined event pulse. Its functionality is reduced to the minimal task of value assignment.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Description | With Data |
|----------|-----------|---------------|------------|
| `REQ` | Event | Normal Execution Request. Triggers the transfer of the value from `IN` to `OUT`. | `IN`, `OUT` |

### **Event Outputs**

| Event | Data Type | Description | With Data |
|----------|----------|---------------|------------|
| `CNF` | Event | Execution Confirmation. Sent after the value has been successfully written to `OUT`. | `OUT` |

### **Data Inputs**

| Variable | Data Type | Description | Initial Value |
|----------|----------|---------------|-------------|
| `IN` | INT | The value to be copied to the InOut variable. | 0 |

### **Data Outputs**

The function block does not have a dedicated data output. Output is provided via the InOut variable (see below).

### **Adapter**

None.

### **InOut Variable**

| Variable | Data Type | Description | Initial Value |
|----------|-----------|---------------|-------------|
| `OUT` | INT | Target variable into which the value of `IN` is written. This variable is declared as InOut, meaning it is referenced from outside the function block and can be directly manipulated. | 0 |

## Functionality

The function block operates according to a very simple, direct principle:

1. An event is received at input `REQ`.
2. The algorithm `REQ` executes the assignment `OUT := IN`. The current value of the data input `IN` is thus copied into the InOut variable `OUT`.
3. After successful assignment, the event `CNF` is sent to signal completion to the calling environment. The `CNF` event is linked to the InOut variable `OUT`, ensuring data consistency.

Execution occurs without delay or conditions – the value is overwritten immediately upon each `REQ` event.

## Technical Features

- **InOut Variable**

The function block uses an InOut parameter (`OUT`) that represents a direct reference to an external variable (e.g., a global data block or a variable of a parent function block). This eliminates the need for an explicit connection back to another function block. The function block writes its value directly to the referenced memory location.

- **No Buffering**

The function block (FB) does not buffer data. The value is immediately overwritten with each `REQ-Ereignis` event.

- **Initial Values**

The data inputs and InOut variables are initialized with `0`. This value is used in case of a lost connection.

## State Overview

The FB has a single ECC state (`REQ`) that executes the action and immediately triggers the output event `CNF`. There are no branches, timers, or error states.

| State | Action | Trigger |
|---------|--------|----------|
| `REQ` | Execution of the algorithm `REQ` (OUT := IN) and sending of `CNF` | Event `REQ` |

## Application Scenarios

- **Setting a Constant Value**

An external sensor or logic provides a setpoint (`IN`), which is transferred to a global setpoint variable (`OUT`) at a clock signal (`REQ`).

- **Initializing Variables**

When an application starts, `SET_INT` can be used to set multiple InOut variables to defined initial values.

- **Parameter Override**

A higher-level controller or user interface overrides the current value of another function block upon a specific event, without having to modify the function block itself (the InOut connection allows direct access).

## Comparison with Similar Function Blocks

- **SET_BOOL / SET_REAL**

Similar to `SET_INT`, but for the data types `BOOL` and `REAL`, respectively. The functionality is identical.

- **MOVE**

A general MOVE function block copies a value from a data input to a data output. In contrast, `SET_INT` uses an InOut variable and writes directly to an external location, resulting in tighter coupling. `MOVE` requires a separate connection from the output to the destination.

- **LATCH**

A latch function block can store a value and output it when needed. In contrast, `SET_INT` overwrites without a hold function – each call overwrites the previous value.

## Conclusion

The `SET_INT` function block is a minimalist yet effective building block for directly setting an INT variable via an InOut interface. Its strength lies in its simple logic and the ability to access external variables. It is particularly suitable for flat control structures where fast and direct value assignments are required. Due to its simplicity, it is robust and reliable, but requires a well-thought-out variable concept to avoid unwanted side effects.
