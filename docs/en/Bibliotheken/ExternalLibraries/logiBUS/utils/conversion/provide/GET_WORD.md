# GET_WORD

![GET_WORD](./GET_WORD.svg)

* * * * * * * * * *
## Introduction

The **GET_WORD** function block is used to read a WORD value from an InOut variable and make it available as a buffered output. It is typically used to capture a current value from a hardware peripheral or a shared memory location and make it available for further processing in the control program.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Normal execution request; clears the read operation and outputs the result at output `OUT`. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Execution confirmation; signals that the value from `IN` was successfully transferred to `OUT`. |

### **Data Inputs**

The function block (FB) does not have explicit data inputs in the traditional sense, but uses an **InOut variable**:

| Variable | Type | Description |

|----------|-------|--------------|

| IN | WORD | Source variable (InOut) from which the read value originates. The FB accesses it for reading. |

### **Data Outputs**

| Output | Type | Description |

|---------|-------|------------------------------------------------|

| OUT | WORD | Buffered output value – Copy of `IN` at the time of the last `REQ` execution. |

### **Adapter**

No adapters available.

## Functionality

1. The function block starts with a **REQ** event at the input.

2. The **REQ** algorithm is executed:

- The current value of the input variable `IN` is copied to the output `OUT`.

3. After successful assignment, the **CNF** event is sent at the output.

Thus, the value read once remains at the output `OUT` until another **REQ** pulse triggers an update. This corresponds to a buffered read operation.


## Technical Features

- **InOut Usage** – The function block reads an InOut variable, which is typically connected to a memory or hardware register.

- **Buffering** – The read value is held in the output `OUT`, even if the source `IN` changes later. Only a subsequent **REQ** call updates the buffer.

- **Initialization** – `IN` and `OUT` are pre-set to 0 by default.

## State Overview

The function block implements a simple state machine with only one state:

| State | Description |

|---------|--------------|

| REQ | Always active when **REQ** is received; Performs the assignment `OUT := IN` and sends **CNF**. |

There are no other states such as IDLE or WAIT, as the logic is strictly event-driven without branching.

## Application Scenarios

- **Reading a Hardware Register** – For example, reading an analog-to-digital converter value or a counter value stored as a WORD.

- **Saving a Volatile Value** – If the source is only stable for a short time (e.g., after an interrupt), the function block can freeze the value at a defined moment.

- **Accessing Shared Variables** – In multi-call environments, the current value of a global WORD variable is retrieved and processed locally.

## Comparison with Similar Function Blocks

| Function Block | Difference |

|----------|-------------|

| **MOVE** | Copies a value from a data input to an output. `GET_WORD`, on the other hand, reads from an InOut variable, which often represents a connection to an external resource. |

**READ** | Often standardized for IEC 61499, reads from a process image. `GET_WORD` is more specific for a buffered WORD takeover from an InOut location. |

**LATCH** | Holds a value after a set pulse. `GET_WORD` only updates on each **REQ**, thus resembling a clocked latch, but is not set/resettable. |

## Conclusion

**GET_WORD** is a simple but useful function block for selectively reading and buffering a WORD value from an InOut variable. It is particularly suitable for applications where the current state of a source needs to be captured at a specific event time and then made available in a stable manner. The function block (FB) is easy to understand, resource-efficient, and can be seamlessly integrated into event-driven processes.