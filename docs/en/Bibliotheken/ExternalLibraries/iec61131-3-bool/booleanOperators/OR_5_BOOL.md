# OR_5_BOOL

<img width="1370" height="337" alt="image" src="https://github.com/user-attachments/assets/d3d2531f-35f3-4013-86ae-fbe3da61ed57" />
* * * * * * * * * *
## Introduction

The function block `OR_5_BOOL` is a standard function block for calculating the logical OR operation. It performs an OR operation on five separate Boolean input signals. The function block belongs to the category of standard Boolean functions according to IEC 61131-3 and is implemented as a generic function block.
![OR_5_BOOL](OR_5_BOOL.svg)
## Interface Structure

### **Event Inputs**

* **REQ (Normal Execution Request):** This event triggers the execution of the function block. Upon receiving `REQ`, the values of all five inputs (IN1 to `IN5`) are read, and the OR operation is calculated.

### **Event Outputs**

* **CNF (Execution Confirmation):** This event signals the completion of the calculation. It is output along with the calculated result `OUT`.

### **Data Inputs**

* **IN1 (BOOL):** OR Input 1.
* **IN2 (BOOL):** OR Input 2.
* **IN3 (BOOL):** OR Input 3.
* **IN4 (BOOL):** OR Input 4.
* **IN5 (BOOL):** OR Input 5.

### **Data Outputs**

* **OUT (BOOL):** The result of the OR operation on all five inputs. The output is `TRUE` if at least one of the inputs `IN1` to `IN5` has the value `TRUE`.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

The functionality is deterministic and event-driven:

1. The arrival of the event `REQ` starts the execution.
2. The block reads the current values of the five Boolean inputs `IN1` to `IN5`.
3. The logical OR operation `OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5` is calculated.
4. The result is provided at the data output `OUT`, and simultaneously the confirmation event `CNF` is triggered to signal the successful completion of the operation to subsequent blocks.

## Technical Features

* **Generic Block:** The block is marked with the attribute `eclipse4diac::core::GenericClassName` as `'GEN_OR'`. This indicates that it is part of a family of generic OR gates with varying numbers of inputs.
* **Package:** The gate is included in package `iec61131::bitwiseOperators`.
* **Event-driven execution:** Computation only occurs when requested by a `REQ` event, enabling energy-efficient and deterministic execution.

## State overview

The function block has no internal state in the sense of a memory. Its behavior is purely combinatorial and depends solely on the current input values at the time of the `REQ` event. The block returns to a passive wait state after the `CNF` event is triggered.

## Application Scenarios

Typical applications can be found in control logic, where a condition is considered fulfilled if one of several possible subconditions is met:

* Monitoring: Alarm triggering when at least one of several monitoring sensors exceeds a threshold.
* Enabling logic: Starting a machine when at least one of several safety devices is activated.
* Selection or prioritization logic in interconnected control systems.

## ⚖️ Comparison with Similar Function Blocks

In contrast to this function block with five fixed inputs, 4diac often also includes:

* **OR_2_BOOL, OR_3_BOOL, etc.:** Same functionality, but with a smaller, fixed number of inputs (e.g., 2, 3, 4). See: [OR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_5.md)
* **GEN_OR (Generic OR):** A higher-level, configurable function block that can have a variable number of inputs depending on its instantiation. `OR_5_BOOL` is a specific instantiation of this principle.
* **AND_5_BOOL:** Performs a logical AND operation across all five inputs (the result is only `TRUE` if *all* inputs are `TRUE`).

## Conclusion

The `OR_5_BOOL` is a simple, robust, and standards-compliant function block for implementing an OR operation with five inputs. Its event-driven architecture integrates seamlessly with 4diac's function block networks and is ideally suited for clear and concise logic connections in automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
