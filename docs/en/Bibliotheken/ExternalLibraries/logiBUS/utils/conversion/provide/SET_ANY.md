# SET_ANY
![SET_ANY](./SET_ANY.svg)

* * * * * * * * * *
## Introduction
The function block **SET_ANY** is used to write any value from input `IN` to a variable `OUT`, declared as an InOut parameter. The operation is triggered by an event at input `REQ` and acknowledged with the output event `CNF` after successful assignment. The function block is generic and can work with any data type, as long as the types of `IN` and `OUT` are compatible.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| REQ | Event | Normal execution request – triggers the assignment. Associated with the variables `IN` and `OUT`. |

### **Event Outputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| CNF | Event | Confirmation of successful execution. Associated with the variable `OUT`. |

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| IN | ANY | Value written to the target variable. |

OUT | ANY | **InOut Parameter** – used as both an input and an output (see Data Outputs). |

> **Note:** `OUT` is declared as InOut. It functions as a data input (the original variable is read if necessary) and as a data output (overwritten with the value of `IN`).

### **Data Outputs**

| Name | Data Type | Comment |

|------|----------|-----------|

OUT | ANY | **InOut Parameter** – contains the value of the input `IN` after execution. The variable can also be used outside the function block. |

### **Adapter**
None.

## Functionality
The module has a single processing state, `REQ`. If an event occurs at the event input `REQ`, the algorithm `REQ` is executed:

OUT := IN;
After assignment, the output event `CNF` is sent. Execution is atomic – no further state logic is applied.

## Technical Features
- **Generic Data Type `ANY`:** The function block can be used with any IEC 61499 data type (e.g., BOOL, INT, REAL, STRING, structures). Type compatibility between `IN` and `OUT` must be ensured by the user.
- **InOut Mechanism:** `OUT` is declared as an InOut parameter. This means that the variable serves as both input (e.g., for read operations) and output. In the 4diac IDE, InOut is typically implemented as a reference to an external variable.
- **Simple State Machine:** The function block contains only one state, making it very lightweight and resource-efficient.

## State Overview

| State | Description |

|---------|--------------|

| REQ | Waits for a `REQ` event. Upon occurrence, the algorithm is executed, then `CNF` is sent, and the state remains active. |

There are no other states, no branches, and no time monitoring.

## Application-Specific Scenarios
- **Variable Initialization:** A one-time initial value is set for a globally or instance-specific variable.
- **Parameter Override:** At runtime, an existing value is overwritten with a new one, e.g., to change setpoints or configuration parameters.
- **Point-to-Point Data Transfer:** When a value needs to be copied from a source to a directly connected destination without requiring separate logic.

## Comparison with Similar Function Blocks

| Function Block | Difference |

|----------|-------------|

| **SET** | Is fixed to a specific data type (e.g., SET_BOOL, SET_INT). `SET_ANY` is generic. |

| **MOVE** | Also copies a value from an input to an output, but uses standard outputs. `SET_ANY` uses an InOut parameter that references a persistent variable. |

| **SELECT** | Selects between two input values and requires a control signal. `SET_ANY` operates without a condition. |

## Conclusion

SET_ANY` is a simple yet flexible function block for selectively overwriting variables in IEC 61499. The use of the generic type `ANY` and the InOut parameter makes it universally applicable, especially in scenarios where values need to be written to existing memory locations at runtime. Thanks to its minimal state logic, it is suitable for time-critical applications or as a basic building block for more complex data flow structures.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
