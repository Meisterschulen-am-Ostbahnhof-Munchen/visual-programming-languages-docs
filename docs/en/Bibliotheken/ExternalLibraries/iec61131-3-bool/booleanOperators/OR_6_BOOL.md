# OR_6_BOOL

<img width="1370" height="361" alt="image" src="https://github.com/user-attachments/assets/2144a80e-12ae-4dc2-8412-36059eace342" />
* * * * * * * * * *
## Introduction

The function block `OR_6_BOOL` is a generic block for calculating the logical OR operation. It performs an OR operation on six separate BOOL inputs and outputs the result on a single output. The block complies with the IEC 61131-3 standard and is designed for use in control applications where multiple conditions must be combined to trigger an action.
![OR_6_BOOL](OR_6_BOOL.svg)
## Interface Structure

### **Event Inputs**

* **REQ (Normal Execution Request):** This event triggers the calculation of the OR function. It is linked to all six data inputs (`IN1` to `IN6`).

### **Event Outputs**

* **CNF (Execution Confirmation):** This event signals the completion of the calculation. It is output along with the calculated result at data output `OUT`.

### **Data Inputs**

* **IN1 (BOOL):** OR input 1.
* **IN2 (BOOL):** OR input 2.
* **IN3 (BOOL):** OR input 3.
* **IN4 (BOOL):** OR input 4.
* **IN5 (BOOL):** OR input 5.
* **IN6 (BOOL):** OR input 6.

### **Data Outputs**

* **OUT (BOOL):** Result of the OR operation on all six inputs. The output is `TRUE` if at least one of the inputs is `TRUE`.

### **Adapter**

This function block has no adapter interfaces.

## Operation

The operation is deterministic and event-driven. Upon each occurrence of the input event `REQ`, the current values of all six BOOL inputs (`IN1` to `IN6`) are read. The logical OR operation of these values is then calculated. The result of this operation is immediately set at the data output `OUT`, and simultaneously, the acknowledgment event `CNF` is triggered to signal the completion of the operation to subsequent blocks.

The logical operation corresponds to the formula: `OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5 OR IN6`

## Technical Features

* **Generic Block:** The block is marked as a generic block (`GEN_OR`). This means it can serve as the basis for creating similar blocks with a different number of inputs.
* **Event-Driven Execution:** The calculation only occurs when requested by an event, enabling efficient and demand-driven processing in the control system.
* **Fixed Number of Inputs:** This specific instance is defined for exactly six inputs.

## State Overview

The function block has no internal state or memory. Its behavior is purely combinatorial and depends solely on the current values of the inputs at the time of the `REQ` event. After outputting `CNF`, the block remains in a waiting state until the next `REQ`.

## Application Scenarios

Typical applications include monitoring and safety logic where an action should be triggered when one of several possible conditions is met.

* **Emergency Stop Logic:** The block can be used to monitor multiple emergency stop buttons. If any of the buttons is pressed (`TRUE`), a shutdown signal (`OUT = TRUE`) is generated.
* **Alarm Aggregation:** Multiple sensors, each capable of detecting a fault condition, are interconnected. A general alarm is triggered as soon as at least one sensor reports a fault.
* **Multiple Operator Control:** In a machine, multiple operator stations can start a process. The block combines all start commands into a single start signal.
*
## ⚖️ Comparison with similar function blocks

* **AND_6_BOOL:** Performs a logical AND operation. The result is only `TRUE` if **all** inputs are `TRUE`. In contrast, `OR_6_BOOL` requires only **one** true input.
* **XOR_BOOL:** Performs an exclusive OR (XOR) operation. The result is `TRUE` if there is an odd number of inputs, `TRUE`. `OR_6_BOOL` does not distinguish between one or more true conditions. See: [OR_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_6.md)
* **Blocks with Variable Number of Inputs:** OR blocks with two (`OR`) or other numbers of inputs exist. `OR_6_BOOL` offers a fixed interface with six inputs, optimized for specific applications.

## Conclusion

The `OR_6_BOOL` function block is a simple, robust, and standards-compliant building block for logical signal combination. Its strength lies in its clear, event-driven interface and the fixed number of six inputs, making it ideal for applications that require precisely this number of conditions to be combined. As a generic building block, it also supports reuse and customization within the 4diac IDE.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
