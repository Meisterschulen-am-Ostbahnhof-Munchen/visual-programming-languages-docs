# GET_USINT

![GET_USINT](./GET_USINT.svg)

* * * * * * * * * *
## Introduction

The function block `GET_USINT` is used to read a `USINT` value from an InOut variable. It buffers the read value and makes it available via an output. This function block is particularly suitable when the value of a variable from a higher-level context (e.g., a group) needs to be queried once and then used as a constant intermediate value in subsequent processes.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal execution request. Trigger to read the current value of `IN` and pass it to `OUT`. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Confirmation of successful execution. Sent after reading and buffering. |

### **Data Inputs**

This function block does not have traditional data inputs. Instead, the value to be read is provided via the InOut variable `IN`.

| Variable | Data Type | Comment |
|----------|----------|-----------|
| IN | USINT | Source variable (InOut). The current value of this variable is read and buffered upon a `REQ` event. The variable can be written to and read from external sources; within the function block, access is read-only. |

### **Data Outputs**

| Variable | Data Type | Comment |
|----------|----------|-----------|
| OUT | USINT | Buffered output value. Contains the value read during the last execution of `IN`. Initial value: 0. |

### **Adapter**

None.

## Functionality

1. The function block waits for a `REQ` event.
2. Upon arrival of `REQ`, the current value of the InOut variable `IN` is read and copied to the local output variable `OUT` (`OUT := IN;`).
3. Subsequently, the acknowledgment event `CNF` is sent.
4. The value of `OUT` is retained until another `REQ` event triggers a new read operation.

Since this is a simple function block, there are no branches or timed sequences – the action is executed in a single step.

## Technical Features

- **InOut Variable `IN`** – The interface uses a variable `InOut`, which functions as both an input and an output. This is typical for 4diac function blocks that access variables of a parent group. The block does **not** modify the value of `IN`; it only reads it.
- **Buffering** – Without re-reading `REQ`, the output value remains stable, even if the source variable changes later. This decouples the value from the time it is read.
- **No State Machines** – The block consists of only one state, `REQ`, making the implementation trivial and resource-efficient.

## State Overview

The block has exactly one state:

| State | Action | Initial Event |
|---------|--------|------------------|
| REQ | Execute algorithm `REQ` (`OUT := IN;`) | CNF |

A start state is not explicitly defined; after initialization, the function block is activated by the first `REQ`.

## Application Scenarios

- **One-Time Query of a Configuration Variable** – A `USINT` value defined in a parent resource should be read exactly once at the beginning of the process and then used as a local constant.

- **Decoupling of Read and Write Access** – If a variable is both written to and read from multiple function blocks, `GET_USINT` prevents the read side from being constantly updated, as buffering only occurs on demand.

- **Testing Tool** – This function block can be used to display the current value of an InOut variable in a diagnostic branch.

## Comparison with Similar Function Blocks

| Function Block | Type | Special Feature |
|----------|-----|--------------|
| `GET_USINT` | Custom Function Block | Reads an InOut variable and buffers the value. The output remains stable until the next request. |
| `USINT_TO_*` (e.g., Converter) | Conversion Function Block | Converts a USINT to another type, but does not necessarily read from an InOut. |
| Direct data access | No function block | A value can be read over data connections without buffering, but without decoupling and without event control. |

GET_USINT` is specialized for reading InOut variables with explicit buffering and event control – a task that cannot be accomplished with standard converters or direct connections.

## Conclusion

The `GET_USINT` function block offers a simple and efficient way to read a `USINT` value from an InOut variable and provide it as a buffered output. Its clear, event-driven interface and minimal state machine make it a useful tool for decoupling and initialization tasks in 4diac applications. It is ideally suited when the value of a variable should only be retrieved on demand and any changes to the source in the meantime must be ignored.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
