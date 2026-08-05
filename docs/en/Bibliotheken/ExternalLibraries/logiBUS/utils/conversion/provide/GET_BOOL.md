# GET_BOOL
![GET_BOOL](./GET_BOOL.svg)
* * * * * * * * * *
## Introduction
The **GET_BOOL** function block reads a BOOL value from a variable declared as `InOut` and provides it as a buffered output value. This simple encapsulation allows a Boolean signal to be passed from any context without requiring direct read/write access to the source in the calling function block.
## Interface Structure
### **Event Inputs**

| Event | Description | With Variables |

|----------|---------------|---------------|

| REQ | Normal Execution Request | IN |

### **Event Outputs**

| Event | Description | With Variables |

|----------|--------------|---------------|

| CNF | Execution Confirmation | OUT, IN |

### **Data Inputs**
There are no declared data inputs (*InputVars*). Access to the source variable is exclusively via an InOut parameter.

### **Data Outputs**

| Variable | Type | Initial Value | Description |

|----------|-------|-------------|-----------------------------|

| OUT | BOOL | FALSE | Buffered Output Value |

### **Adapters**
No adapters are available.

## Operation

1. Processing is started at the **event input REQ**.

2. The internal algorithm **REQ** performs the simple assignment `OUT := IN` – the current value of the InOut variable `IN` is copied to the output `OUT`.

3. After the successful copy operation, the **CNF** event is triggered. It passes both the new value `OUT` and the (unchanged) value of `IN` to the subsequent logic.

The output `OUT` remains at the last read value until a new pulse `REQ` updates the value.

## Technical Features
- **In/Out Parameter** `IN`: This parameter allows bidirectional access to the connected variable. The function block reads the value but does not modify it. This allows direct access to a variable from the parent application without having to define a separate input variable.
- **Buffering**: The value is buffered locally in the output `OUT`. Changes to the source variable between two `REQ` calls are only applied with the next `REQ` call.
- **Initial Values**: Both `IN` and `OUT` are pre-assigned to `FALSE`, so the function block exhibits defined behavior even without prior initialization.

**Buffering**:**
## State Overview

The function block has a single state:

| State | Action | Output Event |

|---------|--------|-----------------|

| REQ | `OUT := IN` | CNF |

After the algorithm is executed, the initial state is immediately exited (no hold state). The function block is therefore event-driven and waits for the next request after processing.

## Application Scenarios
- **Signal Acquisition**: A Boolean sensor value (e.g., from a switch or limit switch) is to be used in the application and simultaneously passed to a higher-level display function block.
- **Decoupling**: A variable from another function block is to be read without the source function block establishing a direct connection. `GET_BOOL` handles the reading.
- **Buffering and Synchronization**: In clocked systems, a `REQ` pulse can be used to sample the current value and hold it for the duration of a cycle.

## Comparison with Similar Function Blocks

| Function Block | Purpose | Data Type |

|----------|-------|----------|

| GET_BOOL | Read a BOOL value via InOut | BOOL |

| GET_INT | Read an INT value via InOut | INT |

| GET_REAL | Read a REAL value via InOut | REAL |

| SET_BOOL | Write a BOOL value via InOut (write) | BOOL |

All `GET_*` function blocks share the use of an InOut parameter and event-driven value transfer. The only difference lies in the data type used. Unlike `SET_BOOL`, `GET_BOOL` does not modify the source variable.

## Conclusion
The **GET_BOOL** block is a minimalist yet useful component for reading and buffering a single Boolean value. Its strength lies in the clean decoupling of the signal source from the rest of the application code and its ease of use thanks to a single event pulse. It is particularly well-suited for modular and reusable automation solutions that require a clearly defined data flow.
