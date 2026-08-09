# SET_LREAL

![SET_LREAL](./SET_LREAL.svg)

* * * * * * * * * *
The function block **SET_LREAL** is used to pass a value of type LREAL to an InOut variable. The input value is written to the target variable on a rising edge of the REQ event, and the operation is acknowledged via the CNF event.

| Event | With Variables | Description |
|----------|---------------|--------------|
| REQ | IN, OUT | Normal execution request. Triggers writing the input value to the target variable. |
| Event | With Variables | Description |
|----------|---------------|--------------|
| CNF | OUT | Confirmation of successful execution. The target variable has been updated. |
| Name | Type | Initial Value | Description |
|------|-------|-------------|----------------------------------|
| IN | LREAL | 0.0 | Value to be written to the target variable. |
| OUT | LREAL | 0.0 | (InOut) Input side of the target variable. The current value can be read. |
| Name | Type | Initial Value | Description |
|------|-------|-------------|----------------------------------------|
| OUT | LREAL | 0.0 | (InOut) Output side of the target variable. After execution, the value of IN is output here. |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

No adapters available.

## Functionality

When an event occurs at the **REQ** input, the algorithm is executed, copying the value of the input variable **IN** to the InOut variable **OUT**. The **CNF** event is then sent. The function block operates purely combinatorially and has no internal state maintenance beyond execution.

- The function block uses an InOut variable. This allows direct access to an external variable without requiring an additional connection between the input and output.
- The algorithm is implemented in Structured Text (ST) and is very simple (`OUT := IN;`).

The function block consists of a single state, **REQ**:

- **REQ**: Waits for the arrival of the REQ event. Then executes the algorithm and sends CNF. After sending, it returns to the REQ state (implicitly, as no other states are defined).

There are no branches or timing controls.

- **Copying an LREAL value** to a global or cross-instance variable when a direct connection is not possible or desired.
- **Setting a setpoint** in a controller, e.g., for a PID controller where the value is received via an analog input.
- **Initialization** of variables during operation, without having to restart the entire application.
- **SET_INT** or **SET_BOOL**: Functionally equivalent function blocks for other data types.
- **MOVE**: A general MOVE function block (e.g., in IEC 61131-3) copies values without event control. SET_LREAL, on the other hand, uses event-driven execution and InOut variables.
- **WRITE_LREAL**: Some libraries offer separate function blocks for writing to an address. SET_LREAL is simpler and operates at the variable level.

The **SET_LREAL** function block is a simple yet useful tool for writing an LREAL value to an InOut variable. Its event-driven operation makes it easy to integrate into IEC 61499 applications. The clear interface with only one event input and output, one data input and one InOut variable reduces complexity and facilitates reuse.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion