# GET_REAL
![GET_REAL](./GET_REAL.svg)
* * * * * * * * * *
## Introduction
The **GET_REAL** function block is used to read a REAL value from an **InOut variable** and make it available in a buffered output. The read value is obtained from the InOut variable `IN` when an event is received at input `REQ` and output at output `OUT`. After execution, the acknowledgment event `CNF` is sent.
## Interface Structure
### **Event Inputs**

| Event | Description | With Variables |

|----------|----------------|----------------|

| **REQ** | Normal execution request – triggers reading the InOut variable. | `IN` |

### **Event Outputs**

| Event | Description | With Variables |

|----------|----------------|----------------|

| **CNF** | Execution Acknowledgement – sent after processing `REQ`. | `OUT`, `IN` |

### **Data Inputs**

| Variable | Type | Initial Value | Description |

|----------|------|--------------|--------------|

| **IN** | REAL | 0.0 | InOut variable whose current value is read. |

> **Note:** `IN` is declared as an *InOut variable* – it can be both read and written. However, in this function block, it is only read.

### **Data Outputs**

| Variable | Type | Initial Value | Description |

|----------|------|-------------|--------------|

| **OUT** | REAL | 0.0 | Buffered output – holds the read value of `IN` until the next update. |

### **Adapters**
No adapters available.

## Functionality

1. An incoming event at input `REQ` triggers the execution of the internal algorithm `REQ`.

2. In the algorithm, the current value of the input variable `IN` is copied to the output variable `OUT`:

```structuredtext
OUT := IN;
3. The confirmation event `CNF` is then sent. The outputs `OUT` and `IN` are associated with the event, so they are valid simultaneously.

4. The output value is retained until another `REQ` event arrives and `OUT` is rewritten.

## Technical Features
- **InOut Usage:** The function block uses an InOut variable (`IN`). This can be written to or read from externally; here, it serves exclusively as a source.
- **Initialization:** Both REAL variables are pre-assigned to `0.0`.
- **Minimal Overhead:** The function block (FB) has only one state (`REQ`) and a simple assignment algorithm – it operates without delay or additional logic.
- **Standard Compliance:** The function block is defined according to IEC 61499-1 and is intended for use in automation environments such as 4diac IDE.

## State Overview
The FB has only one state:

- **State `REQ`:**

Upon entry, the algorithm `REQ` is executed (OUT := IN) and the event `CNF` is sent. The FB remains in this state and is always ready for the next request.

There are no further states or branches – the function block is deterministic and reacts immediately to every `REQ` event.

## Application Scenarios
- **Reading a Process Value:** In a PLC, `GET_REAL` can be used to read a current sensor value, which is available as an InOut variable, and pass it to a subsequent function block (e.g., for calculations or visualization).
- **Value Comparison Between Function Blocks:** If another function block provides an InOut interface with a REAL value, `GET_REAL` can retrieve this value and make it available as a buffered output.
- **Testing and Simulation:** The function block is suitable for debugging to capture and log the current value of a variable at a specific point in time.

## Comparison with Similar Function Blocks
Similar function blocks exist for other data types, e.g., `GET_BOOL`, `GET_INT`, `GET_LREAL`, etc. They all share the same principle: reading an InOut variable and providing it as a buffered output. The difference lies solely in the data type and the associated precision or value range.

| Function Block | Data Type | Application Area |

|------------|----------|----------------|

| GET_BOOL | BOOL | Binary Signals |

| GET_INT | INT | Integers (16 bits) |

| GET_REAL | REAL | Floating-Point Numbers (32 bits) |

| GET_LREAL | LREAL | Precise Floating-Point Numbers (64 bits) |

All these function blocks can be used analogously and offer a uniform interface for accessing InOut variables.

## Conclusion
The `GET_REAL` function block is a lean and reliable block for reading a REAL InOut variable. It fulfills a fundamental task in the IEC 61499 world: forwarding a value from a bidirectional interface to a buffered output. Its simplicity and clear semantics make it suitable for both production and testing purposes. Its combination with parallel function blocks of other data types makes it a flexible tool in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
