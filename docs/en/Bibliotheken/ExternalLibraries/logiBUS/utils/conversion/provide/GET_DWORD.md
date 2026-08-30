# GET_DWORD

![GET_DWORD](./GET_DWORD.svg)

* * * * * * * * * *
## Introduction

The function block `GET_DWORD` is used to read the current value of a variable of type `DWORD`, provided as an InOut parameter, and to provide this value as a buffered output. The read operation is controlled by an event.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `REQ` | `Event` | Request to read the InOut variable and provide the output value |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `CNF` | `Event` | Confirmation that the read operation has completed and the output has been updated |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `IN` | `DWORD` | Source variable (InOut). The current value of this variable is read at `REQ`. Initial value: 0 |

### **Data Outputs**

| Name | Data Type | Comment |
|-------|----------|-----------|
| `OUT` | `DWORD` | Buffered output value. Contains the value read during the last execution. Initial value: 0 |

### **Adapter**

No adapters available.

## Functionality

When an event occurs at input `REQ`, the algorithm `REQ` is executed. This assigns the current value of the input variable `IN` to the output variable `OUT`. The event `CNF` is then sent.

The function block buffers the read value; that is, `OUT` retains its value until a subsequent `REQ` updates it. The InOut variable `IN` is directly bound to a parent variable, so each read operation returns the actual current value of this variable.

## Technical Details

- **InOut Parameters:** `IN` is declared as an InOut variable. This means it serves as a reference to an external variable. The function block reads the value of this referenced variable but does not modify it (no feedback).
- **Initial Values:** Both `IN` and `OUT` are initialized to 0. The initial value of `IN` only takes effect if the referenced variable is not explicitly set or is used in an environment without an external value.
- **No State Machine Complexity:** The function block is implemented as a simple SimpleFB with only one state. There are no internal state transitions other than executing the action.

## State Overview

The function block has a single state, `REQ`:

| State | Description |
|---------|---------------|
| `REQ` | Waits for the event `REQ`. Upon its occurrence, the action `REQ` (OUT := IN) is executed, and then the event `CNF` is sent. After `CNF`, the function block remains in the same state. |

## Application Scenarios

- **Buffering a Sensor Signal:** A DWORD sensor value (e.g., counter reading) is to be sampled at specific times and temporarily stored for further processing.
- **Decomposing DWORD Data:** In combination with other function blocks such as `EXTRACT_BYTE` or `SPLIT_DWORD`, the read value can be decomposed into individual bytes or bits.
- **Updating the Process Image:** This function block is suitable for transferring the current value of an external global variable (e.g., from an industrial fieldbus) to a local buffer in a controlled manner.

## Comparison with Similar Function Blocks

- **GET_DWORD with Simple Input:** A hypothetical function block with a normal data input (`VarInput`) would not pass the value by reference, but would use the current input value with each event. In contrast, `GET_DWORD` with InOut offers a fixed binding to a specific variable, which is more consistent in scenarios with multiple accesses to the same variable.
- **SET_DWORD:** The symmetric function block `SET_DWORD` would *set* the value of an InOut variable, while `GET_DWORD` only reads it. Both use the InOut concept, but with opposite actions.
-
## Conclusion

GET_DWORD` is a simple yet useful building block for the controlled retrieval of a DWORD value from an externally referenced variable. Its strength lies in buffering the value and separating the source (InOut) from the output (OUT). Thanks to its simple state machine and the standardized `REQ`/`CNF` interface pattern, it can be easily integrated into existing 4diac applications.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
