# GET_SINT
![GET_SINT](./GET_SINT.svg)

* * * * * * * * * *
## Introduction
The **GET_SINT** function block is used to read a value of the data type `SINT` (signed short integer) from a variable declared as `InOut` and provide it as a buffered output. It is typically used to access a shared variable or a physical input without modifying the original value. The function block operates according to the **IEC 61499** standard.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| `REQ` | Event | Normal execution request. Triggers the reading of the InOut variable. |

- **With Link**: The event input `REQ` is linked to the data variable `IN`.

### **Event Outputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| `CNF` | Event | Confirmation of execution. Sent after a successful copy operation. |

- **With Link**: The event output `CNF` is linked to the data variables `OUT` and `IN`.

### **Data Inputs**

This function block does not have traditional data inputs. Instead, it uses a variable named `InOut`.

### **Data Outputs**

| Variable | Data Type | Initial Value | Comment |

|----------|----------|-------------|------------|

| `OUT` | SINT | 0 | Buffered output value. Contains the copy of `IN` after a successful `REQ` execution. |

### **Adapter**

None.

## Functionality

The function block performs a simple copy operation:

1. An event at the input `REQ` triggers the execution of the stored algorithm.

2. The algorithm assigns the current value of the InOut variable `IN` to the output `OUT`: `OUT := IN;`.

3. After the assignment is complete, the event `CNF` is sent to signal completion to the calling function block.

The InOut variable `IN` allows direct access to an external variable or memory location without requiring it to be defined as a separate input or output. The function block buffers the read value, ensuring that the output `OUT` remains stable even after changes to the source, until the next request is made.

## Technical Features
- **Use of InOut Variables**: `IN` is declared as `InOut`, meaning it can be both read and written. In this case, it is only read, allowing for flexible coupling with the calling network.
- **Buffering**: The output `OUT` stores the read value until the next update by `REQ`. This prevents unwanted side effects from changes to the source.
- **No State Logic**: The function block consists of a single state (`REQ`) that reacts immediately to each incoming event. No delay, no waiting for conditions.
- **Initial Values**: Both `IN` and `OUT` are initialized with `0`, ensuring a defined start state.

## State Overview

The function block uses a simple ECA state machine with exactly one state:

| State | Action | Outgoing Event |

|---------|--------|----------------------|

| `REQ` | `REQ` Algorithm (OUT := IN) | `CNF` |

- Every incoming `REQ` event triggers an immediate action and sends `CNF`. There are no branches, error states, or timing issues.

## Application Scenarios
- **Reading Hardware Inputs**: When a SINT value needs to be read from an analog input chip or a programmable logic controller (PLC), `GET_SINT` can be used as an interface to capture the current value at a specific point in time.
- **Accessing Shared Variables**: In a distributed control system, `GET_SINT` can be used to transfer the value of a global or peripheral variable into a local processing chain.
- **Data Consistency**: Buffering ensures that the read value remains stable throughout the entire processing of the subsequent network, even if the source is updated asynchronously.

## Comparison with Similar Building Blocks

| Building Block | Data Type | Special Feature |

|----------|----------|--------------|

| `GET_BOOL` | BOOL | Same functionality, but for Boolean values. |

| `GET_INT` | INT | Similar to `GET_SINT`, but with 16-bit integers. |

| `GET_REAL` | REAL | For floating-point numbers. |

| `MOVE` (generic) | Any | A generic MOVE building block can also copy values, but requires separate inputs and outputs. In contrast, `GET_SINT` uses InOut variables, which can be more practical when coupling to peripheral addresses.

All `GET_*` function blocks have in common that they read a value from an InOut source and provide it as a buffered output. In contrast, `SET_*` overwrites the value of the source.

## Conclusion

GET_SINT` is a minimalist and reliable function block for reading a `SINT` value from an InOut variable. Its simplicity makes it an ideal function block for reading peripheral or shared data in IEC 61499 applications. The use of the InOut interface reduces wiring complexity and promotes a clean separation between data access and processing logic.
