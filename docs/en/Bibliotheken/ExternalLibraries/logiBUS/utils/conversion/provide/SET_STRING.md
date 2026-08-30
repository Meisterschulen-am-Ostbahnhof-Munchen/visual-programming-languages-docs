# SET_STRING

![SET_STRING](./SET_STRING.svg)

* * * * * * * * * *

## Introduction

The function block `SET_STRING` is used to write a string value (STRING) provided via the data input `IN` to an input-output variable `OUT`. Execution is triggered by an event at the input `REQ`. After writing, an acknowledgment event is sent at the output `CNF`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |
|------|-------|-------------------------------|---------------|
| REQ | Event | Normal execution command | IN, OUT |

### **Event Outputs**

| Name | Type | Comment | With variables |
|------|-------|--------------------------------|---------------|
| CNF | Event | Execution confirmation | OUT |

### **Data Inputs**

| Name | Type | Comment |
|------|--------|----------------------|
| IN | STRING | The value to be written |

### **Data Outputs**

| Name | Type | Comment |
|------|--------|---------------------------------|
| OUT | STRING | Target variable (In-Out) – identical to IN after execution |

> **Note:** `OUT` is declared as an In-Out variable. It serves simultaneously as an input (the current value before execution) and as an output (the new value after execution). When `REQ` is received, `OUT := IN` is set, overwriting the previous value.

### **Adapters**

No adapters are available.

## Functionality

1. An incoming event at input `REQ` starts the processing.
2. The code stored in algorithm `REQ` is executed:

- `OUT := IN;`

The value of the input variable `IN` is copied to the input-output variable `OUT`.

1. Subsequently, the event at output `CNF` is sent to signal successful execution.

## Technical Features

- The function block contains only a single state (`REQ`) in which all processing takes place. It is a **simple function block** (SimpleFB) without sequential state machines.
1. The event is then sent at output `CNF` to signal successful execution. - The input-output variable ``OUT`` allows the function block to be directly linked to a persistently writable variable (e.g., a global data object or a linked hardware address) without requiring a separate output variable.

- The algorithm is trivial and performs no type or range checks.

## State Overview

The function block has exactly one state:

| State | Action | Output Event | Description |
|---------|----------------------|-----------------|------------------------------------------------|
| ``REQ`` | ``OUT := IN`` | ``CNF`` | Copies the input value to the input-output variable and acknowledges |

A start state is not explicitly defined; The function block expects an external event pulse on `REQ`.

## Application Scenarios

- **String Parameterization in Controllers**: Setting a string value in a global variable, e.g., a device name or IP address.
- **Initialization of Text Blocks**: Overwriting a standard string in a higher-level function block network.
- **Test and Debugging Environments**: Precisely specifying values for subsequent processing steps.

## Comparison with Similar Function Blocks

- **SET_BOOL, SET_INT, SET_REAL**: Similarly structured function blocks for other data types. `SET_STRING` differs from `STRING` only in its data type.
- **MOVE**: A generic function block that can copy values of different data types. In contrast, `SET_STRING` is strictly specialized for `STRING` and works with an input/output variable, while `MOVE` uses separate inputs and outputs.
- **WRITE_STRING**: Blocks with similar functionality found in some libraries, but often equipped with additional control or error outputs.

## Conclusion

The `SET_STRING` function block is a simple yet effective tool for precisely setting a string value to an input/output variable. It is particularly suitable for applications where a value needs to be written directly to an existing variable without requiring any readback or comparison logic. Due to its minimal interface and clear semantics, it can easily be integrated into more complex automation solutions.
