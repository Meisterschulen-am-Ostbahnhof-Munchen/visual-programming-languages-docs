# SET_TIME

![SET_TIME](./SET_TIME.svg)

* * * * * * * * * *
## Introduction
The function block **SET_TIME** is used to write a time value (type `TIME`) provided via the data input `IN` to a variable `OUT` passed as an InOut parameter. The block is implemented as a simple, event-driven block and confirms execution via the event output `CNF`.

## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Normal execution request. Trigger the algorithm that copies the value from `IN` to `OUT`. Associated data: `IN`, `OUT`. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirmation of successful execution. Sent after the algorithm completes. Associated data: `OUT`. |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|-------------|--------------|

| `IN` | `TIME` | `T#0s` | The time value to be written to the target variable. |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|--------------|

| `OUT` | `TIME` (InOut) | `T#0s` | Target variable passed as an InOut parameter during the call. The value of `IN` is copied into this variable. |

> **Note:** `OUT` is an **InOut** parameter, meaning it serves as both an input and an output. The caller must provide a writable variable.

### **Adapter**
None available.

## Functionality

1. The function block waits for an event at input `REQ`.

2. When `REQ` occurs, the algorithm is executed: The current value of the data input `IN` is assigned to the InOut variable `OUT` (`OUT := IN`).


``` 3. After successful assignment, the event `CNF` is triggered to signal completion to the calling function block.

Execution takes place in a single EC state (`REQ`), which runs the algorithm exactly once.

## Technical Features

- **InOut Parameter:** `OUT` is an InOut data point. This allows the function block to write directly to a variable provided by the caller without requiring an additional data output. The caller must ensure that the referenced variable exists and is writable.

- **Simple Logic:** The function block consists of only one EC state and one ST algorithm. There are no branches, timers, or internal state machines.

- **Typing:** Both `IN` and `OUT` are of type `TIME`, meaning only time values are processed.

## State Overview
The function block has exactly one state:

| State | Description |

|---------|--------------|

| `REQ` | Initial state upon initialization. Activated when `REQ` occurs. Executes the algorithm and sends `CNF`. |

There are no other states. The function block returns to the initial state after completing the algorithm and waits for the next `REQ` event.


## Application Scenarios

- **Setting Timer Parameters:** A higher-level control block passes a specific delay time (e.g., for a `TON` or `TOF` block) via an InOut parameter.

- **Initializing Time Variables:** In a startup sequence, predefined time values are written to global or instance-specific variables.

- **Copying Time Values:** A time variable is overwritten once with a calculated or configured value.

- **Real-Time Parameter Updates:** Dynamically changes a time reference shared by multiple blocks.


## Comparison with Similar Blocks

- **Simple MOVE blocks (e.g., `MOVE` for generic types):** SET_TIME is specifically optimized for the `TIME` type and uses an InOut parameter, which saves memory and makes data transfer more efficient.

- **Direct assignment via IEC 61499 connections:** A simple connection from a `OUT` port of another block to the `IN` port of a target block could also set a value, but often requires additional event coupling. SET_TIME simplifies this through explicit `REQ`/`CNF` control.

- **Setting via global variables:** Other blocks write directly to global variables via service interfaces. SET_TIME, on the other hand, typically operates on instance-specific InOut parameters, which improves encapsulation.

## Conclusion
The **SET_TIME** function block is a simple yet useful building block for writing a TIME value to a variable referenced as an InOut. Its clear event handling, minimal resource consumption, and direct coupling of input and output via the InOut mechanism make it ideal for time-critical assignment tasks in automation technology. The use of standard IEC 61499 mechanisms ensures interoperability and easy integration into existing control projects.