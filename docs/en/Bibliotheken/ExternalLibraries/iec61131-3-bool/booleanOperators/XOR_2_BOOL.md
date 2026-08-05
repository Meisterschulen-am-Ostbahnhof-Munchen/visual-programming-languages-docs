# XOR_2_BOOL
<img width="1186" height="216" alt="image" src="https://github.com/user-attachments/assets/7c34009d-7063-4900-b45e-5b35629a05c0" />
* * * * * * * * * *
## Introduction
The function block `XOR_2_BOOL` is a standard function block for calculating the logical exclusive OR (XOR) operation of two Boolean input signals. It belongs to the category of bitwise operators and is implemented as a generic function block used in control applications according to IEC 61131-3. The block waits for an execution request, calculates the result, and returns it along with an acknowledgment.
![XOR_2_BOOL](XOR_2_BOOL.svg)
## Interface Structure
### **Event Inputs**
* **REQ**: Normal execution request. Triggers the calculation of the XOR operation. The data associated with this event (`IN1`, `IN2`) are read during processing.

### **Event Outputs**
* **CNF**: Execution Confirmation. This event is generated after the calculation and signals the availability of the result. It is associated with the data output `OUT`.

### **Data Inputs**
* **IN1**: Boolean input 1 for the XOR operation.
* **IN2**: Boolean input 2 for the XOR operation.

### **Data Outputs**
* **OUT**: Boolean result of the XOR operation of `IN1` and `IN2`.

### **Adapters**
This function block does not have any adapter interfaces.

### ## Functionality
The `XOR_2_BOOL` block operates in an event-driven manner. Upon the arrival of the event `REQ`, the current values at the data inputs `IN1` and `IN2` are read. The logical XOR operation (`OUT = (IN1 AND NOT IN2) OR (NOT IN1 AND IN2)`) is then performed. The calculated result is output at the data output `OUT`, and simultaneously, the confirmation event `CNF` is activated to signal the completion of the operation to subsequent blocks.

The truth table of the operation is:

| IN1 | IN2 | OUT |

|-----|-----|-----|

| 0 | 0 | 0 |

| 0 | 1 | 1 |
| 1 | 0 | 1 |

| 1 | 1 | 0 |

## Technical Features
* **Generic Block**: The block is identified with the generic class name `'GEN_XOR'`, which facilitates its reusability and potential integration into higher-level structures.
* **Event-Driven Execution**: The functionality is strictly linked to the input events, enabling deterministic and energy-efficient processing in real-time systems.
* **Simple Interface**: The block has a minimal and intuitive interface that corresponds to the classic XOR function commonly used in digital technology.

## State Overview
The function block does not have an internal state in the sense of a memory. Its behavior is combinatorial and depends solely on the current input values when the `REQ` event occurs. After outputting `CNF`, the block remains in a waiting state until the next `REQ` event arrives.

## Application Scenarios
* **Comparison and Change Detection**: Detects when exactly one of two states (e.g., two limit switches) has changed.
* **Parity Check**: Simple check for an odd number of `TRUE` signals with two inputs.
* **Control Logic**: Implementation of special branches in sequential control systems where a decision must be made when the inputs are different.
* **Safety-Critical Circuits**: Generates signals that are only active when two monitored variables contradict each other (e.g., in emergency stop circuits).
* ## ⚖️ Comparison with similar building blocks

Compared to other basic logic function blocks like `AND_2_BOOL` or `OR_2_BOOL`, `XOR_2_BOOL` is the only one that returns a `TRUE` result when the inputs are *different*. Blocks like `NOT` only invert a single input. `XOR_2_BOOL` can be considered a special case of an inequality comparison (`NE_BOOL`) for two Boolean values. See: [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md)]

## Conclusion
The `XOR_2_BOOL` is a fundamental, reliable, and easy-to-use building block for logical operation in IEC 61131-3-based control applications. Its event-driven, stateless architecture makes it particularly suitable for integration into complex, deterministic control networks. Its clear functionality and minimal interface make it an indispensable tool for every control system developer.