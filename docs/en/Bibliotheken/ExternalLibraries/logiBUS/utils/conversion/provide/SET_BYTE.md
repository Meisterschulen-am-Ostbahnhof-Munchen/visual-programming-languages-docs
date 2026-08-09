# SET_BYTE

![SET_BYTE](./SET_BYTE.svg)

* * * * * * * * * *
## Introduction

The function block **SET_BYTE** is used to easily overwrite a BYTE variable. It reads the value of the data input `IN` and writes it to the InOut variable `OUT` as soon as an event arrives at the input `REQ`. The event `CNF` is then output.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| `REQ` | Event | Normal execution job (start write operation) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of successful assignment |

### **Data Inputs**

| Name | Type | Value Range | Initial Value | Comment |
|------|-----|--------------|-------------|------------|
| `IN` | BYTE | 0…255 | 0 | Value to be written to the target variable |

### **Data Outputs**

The function block uses an **InOut** variable. Therefore, there are no separate data outputs – the output value is identical to the value of the InOut variable `OUT`.

### **Adapter**

_None present._

## Functionality

When an event occurs at input `REQ`, the algorithm `REQ` is executed. This assigns the value of `IN` to the InOut variable `OUT`:

OUT := IN;
Immediately after the assignment, the event `CNF` is sent. The InOut variable can be both read and written from outside the function block (e.g., via a connection in the application model). After the write operation, it has the value `IN`.

## Technical Features

- **Simplest Assignment**: The algorithm consists of only one line – no delays, conditions, or filters.
- **InOut Variable**: `OUT` is declared as InOut, meaning it can be connected externally to a variable that can be both read and written. This allows direct manipulation of a global or linked BYTE variable.
- **No State Machine**: The function block has only one implicit state (`REQ`) and requires no additional state logic.

## State Overview

The function block (FB) has no explicit states. Action is initiated immediately upon the event `REQ`. There are neither error nor delay states.

## Application Scenarios

- **Initialization or Reset**: A specific initial value is to be written to an existing byte variable.
- **Switching/Setting Bit Patterns**: An external signal (e.g., from a communication block) is passed to an output or memory location via `IN`.
- **Testing/Diagnostics**: Temporarily overwriting a value in a control application.

## Comparison with Similar Function Blocks

- **MOVE** (general): The simple MOVE function block for arbitrary data types usually works with an input and an output, not with InOut. `SET_BYTE` is specifically optimized for BYTE and uses InOut, so the value is written directly to the target variable (no separate output is needed).
- **SET_BOOL** (if available): Analogous for BOOL – both function blocks follow the same simple principle but are limited to their respective data types.

## Conclusion

SET_BYTE` is a minimalist, clearly defined function block for writing to a BYTE variable once. Its strength lies in its simplicity and the use of an InOut interface, which allows for direct value assignment without additional wiring of a data output. It is particularly suitable for applications where a predefined value needs to be written to a persistent variable at a specific time.
