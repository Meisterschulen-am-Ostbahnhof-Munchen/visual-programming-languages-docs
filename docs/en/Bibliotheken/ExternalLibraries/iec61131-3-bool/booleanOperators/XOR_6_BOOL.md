# XOR_6_BOOL
<img width="1388" height="365" alt="image" src="https://github.com/user-attachments/assets/e444cbc7-8866-4570-abc8-581742ad6b98" />
* * * * * * * * * *
## Introduction
The function block `XOR_6_BOOL` is a generic block for calculating the logical exclusive OR (XOR) operation for up to six Boolean input values. It complies with the IEC 61131-3 standard and is designed for use in control and automation applications. The block waits for a trigger event, calculates the result of the XOR operation across all active inputs, and outputs it along with an acknowledgment event.
![XOR_6_BOOL](XOR_6_BOOL.svg)
## Interface Structure
The function block has an event-driven input/output mechanism with six Boolean data inputs and one Boolean data output.

## **Event Inputs**

**REQ** (Normal Execution Request): This event triggers the calculation. Upon arrival of `REQ`, the values at inputs `IN1` to `IN6` are read, and the XOR operation is performed.

### **Event Outputs**
* **CNF** (Execution Confirmation): This event is triggered after the calculation is complete and signals that the result is available at output `OUT`.

### **Data Inputs**
* **IN1** (BOOL): XOR input 1.
* **IN2** (BOOL): XOR input 2.
* **IN3** (BOOL): XOR input 3.
* **IN4** (BOOL): XOR input 4.
* **IN5** (BOOL): XOR input 5.
* **IN6** (BOOL): XOR input 6.

### **Data Outputs**
* **OUT** (BOOL): The result of the XOR operation of all six inputs.

### **Adapters**
This function block does not have any adapter interfaces.

#
## ## Functionality
When triggered by the `REQ` event, the function block calculates the logical XOR value across all six inputs `IN1` to `IN6`. The XOR operation yields `TRUE` (1) if and only if an odd number of inputs have the value `TRUE`. If there are zero, two, four, or six inputs `TRUE`, the result is `FALSE` (0). Formally, this corresponds to the calculation: `OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5 XOR IN6`. After the calculation, the result is output at data output `OUT`, and the confirmation event `CNF` is simultaneously activated.

## Technical Features
* **Generic Block:** The function block is marked as a generic block (`GEN_XOR`). This allows it to be reused in different contexts or used as a basis for specialized versions.
* **Fixed Number of Inputs:** Unlike blocks with a variable number of inputs, `XOR_6_BOOL` has exactly six fixed inputs. Unused inputs should be set to a defined logic level (e.g., `FALSE`).
* **Package Assignment:** The block is assigned to the package `iec61131::bitwiseOperators`, which underlines its classification as a bitwise/logical operation.
* **Fixed Number of Inputs:**
## State Overview

The function block is stateless (combinatory). It has no internal memory. The output `OUT` is a pure function of the current input values at the time of the `REQ` event. There is no dependency on previous calculations or states.

## Application Scenarios
* **Parity Check:** Detects whether an odd number of conditions are active in a group of six signals.
* **Safety-Critical Logic:** In circuits where a state may only be active if exclusive conditions are met (e.g., selection between different, mutually exclusive operating modes).
* **Status Bit Combination:** Combines multiple status or error flags into a single "odd parity" signal.

## ⚖️ Comparison with Similar Blocks
* **`XOR` (2 inputs):** The standard XOR block with only two inputs. `XOR_6_BOOL` extends this functionality to six inputs without the need to connect multiple 2-input XOR blocks. See: [XOR_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_6.md)]
* **`AND_6_BOOL` / `OR_6_BOOL`:** Similar blocks for the logical AND and OR operations with six inputs. While these blocks test for "All" or "At least one," `XOR_6_BOOL` tests for "Odd number."
* **Blocks with Variable Number of Inputs:** Some implementations may offer a `XOR` block to which any number of inputs can be assigned. In contrast, `XOR_6_BOOL` offers an explicit and fixed interface.

## Conclusion
The `XOR_6_BOOL` is a specialized and easy-to-use function block for exclusive OR operation on up to six Boolean signals. Its fixed interface and event-driven execution make it easily integrated into 4diac IDE-based applications. It is particularly useful in scenarios requiring parity checking or the evaluation of exclusive conditions across a small, fixed number of signals. For applications with a variable or significantly larger number of inputs, alternative solutions should be considered.

The `XOR_6_BOOL` is a specialized and easy-to-use function block for exclusive OR operation on up to six Boolean signals. ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
