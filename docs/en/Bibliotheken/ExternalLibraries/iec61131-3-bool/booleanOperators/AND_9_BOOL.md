# AND_9_BOOL

<img width="1383" height="452" alt="image" src="https://github.com/user-attachments/assets/2b74e859-7af1-4a33-9ae1-94290210600c" />
* * * * * * * * * *
## Introduction

The function block `AND_9_BOOL` is a standard building block for calculating the logical AND operation. It performs a bitwise AND operation across nine separate Boolean inputs. The block complies with the IEC 61131-3 standard and is designed for use in the 4diac IDE.
![AND_9_BOOL](AND_9_BOOL.svg)
## Interface Structure

The block has an event-driven input/output model.

### **Event Inputs**

* **REQ (Normal Execution Request):** Triggers the calculation of the AND operation. This event reads all data inputs (`IN1` to `IN9`) and calculates the result.

### **Event Outputs**

* **CNF (Execution Confirmation):** Triggered after the calculation is complete, this indicates that the result is available at data output `OUT`.

### **Data Inputs**

* **IN1 (BOOL):** AND Input 1.
* **IN2 (BOOL):** AND Input 2.
* **IN3 (BOOL):** AND Input 3.
* **IN4 (BOOL):** AND Input 4.
* **IN5 (BOOL):** AND Input 5.
* **IN6 (BOOL):** AND Input 6.
* **IN7 (BOOL):** AND Input 7.
* **IN8 (BOOL):** AND Input 8.
* **IN9 (BOOL):** AND Input 9.

### **Data Outputs**

* **OUT (BOOL):** Result of the AND operation. The output is only `TRUE` if **all** nine inputs (`IN1` to `IN9`) have the value `TRUE`. In all other cases, the output is `FALSE`.

### **Adapters**

This function block does not use any adapters.

## Operation

When an event occurs at input `REQ`, the block reads the current values of all nine Boolean inputs (`IN1` to `IN9`). Then, a logical AND operation is performed on all nine values. The result of this operation is immediately output at data output `OUT`. Simultaneously, an acknowledgment event is generated at output `CNF` to signal the successful completion of the operation.

The logical function can be described as follows:

OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5 AND IN6 AND IN7 AND IN8 AND IN9`

## Technical Features

* **Generic Block:** The block is implemented as an instance of a generic AND block (`GEN_AND`) that has been specialized for a fixed number of inputs (here, 9).
* **Event-driven:** The operation is only executed upon an incoming `REQ` event, enabling resource-efficient and deterministic processing.
* **Fixed Number of Inputs:** Unlike variable functions, this block operates with exactly nine inputs.

## State Overview

The block does not have an internal state in the sense of a memory. Its behavior is combinatorial and depends solely on the current values of the inputs at the time of the `REQ` event. The output `OUT` retains its value until the next execution cycle.

## Application Scenarios

* **Safety Chain:** Linking multiple safety switches (e.g., emergency stop, safety guard, two-hand control) that must all be closed to start a machine.
* **Multiple Conditions:** Checking whether multiple conditions are met simultaneously in a process step.
* **Logic Chaining:** As part of a larger logic circuit where the results from nine sources must be evaluated together.

## ⚖️ Comparison with Similar Function Blocks

* **`AND` (2 inputs):** The standard AND block with only two inputs. `AND_9_BOOL` is a special, extended version for exactly nine inputs. See: [AND_9](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_9.md)
* **`GEN_AND`:** The underlying generic function block that can be instantiated with a configurable number of inputs. `AND_9_BOOL` is a predefined instance of it.
* **`OR_*` / `XOR_*` function blocks:** Perform other basic logic operations (OR, exclusive OR) with a fixed number of inputs.

## Conclusion

The `AND_9_BOOL` is a robust and easy-to-use standard function block for applications requiring a logical AND operation across exactly nine Boolean signals. Its event-driven nature and clear interface make it easily integrated into 4diac-based control applications. For a different number of inputs, the corresponding specialized blocks (`AND_2_BOOL`, `AND_3_BOOL`, etc.) or the generic `GEN_AND` should be used.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
