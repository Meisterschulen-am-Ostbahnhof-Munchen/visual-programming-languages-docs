# GET_LINT
![GET_LINT](./GET_LINT.svg)

* * * * * * * * * *
## Introduction
The function block **GET_LINT** reads a value of type **LINT** from an InOut variable and makes this buffered value available at its output. The block is part of the library `logiBUS::utils::conversion::provide` and implements a simple read-buffer functionality.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|--------|----------------------------|

| REQ | Event | Normal Execution Command |

The event input REQ triggers the execution of the function block. The current value of the InOut variable **IN** is read and temporarily stored in the output **OUT**.

### **Event Outputs**

| Name | Type | Comment |

|------|--------|----------------------------|

| CNF | Event | Execution Confirmation |

The CNF event is sent after successful processing of the REQ event. It signals that the OUT output contains the current value of the InOut variable IN.

### **Data Inputs**

| Name | Type | Comment |

|------|------|-------------------------------------|

| IN | LINT | Source Variable (InOut) – Initial Value: 0 |

**IN** is declared as an InOut variable. It can be both read and written, but in this function block, it is only read. The passed value is copied to the OUT output with each REQ event.

### **Data Outputs**

| Name | Type | Comment |

|------|------|-------------------------------------|

| OUT | LINT | Buffered Output Value – Initial Value: 0 |

The output **OUT** holds the last value read from the InOut variable **IN**. It is updated with each REQ event.

### **Adapter**

This function block has no adapter interfaces.

## Functionality

The GET_LINT function block implements a simple buffer function. It has a single entry state **REQ**, which is activated by an event at the corresponding input. In this state, the algorithm `REQ` is executed:

OUT := IN;

The confirmation event **CNF** is then sent. The output **OUT** then contains the current value of the InOut variable **IN**. The function block then waits for the next REQ pulse.

## Technical Features
- **InOut Variable**: The function block uses an InOut parameter (`IN`). This allows direct access to a variable that can be both read and written. In the case of GET_LINT, however, the value is only read and not modified.
- **LINT Data Type**: The function block works exclusively with the 64-bit integer type LINT (Long Integer). It is intended for environments where large integer values are processed.
- **Simplest State Machine**: There is only one state with one direct action and one output. This makes the function block deterministic and resource-efficient.
- **No Error Handling**: The function block does not contain any plausibility checks or timeouts. It assumes that the InOut variable provides valid data.

## State Overview

| State | Action | Output |

|---------|------------------------------|-------------|

| REQ | Copy from IN to OUT | CNF |

The function block starts in the **REQ** state and returns to the same state after executing the action and sending CNF (endless loop on each event).

## Application Scenarios
- **Caching a LINT Value**: When a LINT value needs to be read from a global variable or another function block and held constant for a specific period (e.g., for subsequent processing).
- **Synchronization**: The function block can be used to capture the current value of an InOut variable at a specific clock cycle and pass it to other function blocks.
- **Decoupling**: The buffer decouples the reading function block from the source – changes to the source only take effect after the next REQ pulse.
- **Simple Value Transfer**: In control systems, GET_LINT can be used to retrieve an external measured value or a parameter from another function block.

## Comparison with Similar Function Blocks
- **GET_DINT / GET_BOOL**: Analogous function blocks for other data types (DINT, BOOL). The functionality is identical; only the data type differs.
- **MOVE (e.g., MOVE_INT)**: A MOVE function block also copies a value but uses input and output variables by default instead of InOut. InOut variables allow a direct reference to the source without additional data flow.
- **LINT_READER** (fictitious): A hypothetical function block that offers additional functions such as buffer timeout or read lock. GET_LINT, on the other hand, is minimalist and fast.

## Conclusion

The GET_LINT function block offers a lean and reliable method for reading a LINT value from an InOut variable and buffering it. Thanks to its simple state machine and clear interface, it is ideally suited for basic synchronization tasks in IEC 61499-based systems. The use of InOut parameters keeps the implementation flexible without requiring additional data lines or protocols.
