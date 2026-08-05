# XOR_3_BOOL

<img width="1186" height="241" alt="image" src="https://github.com/user-attachments/assets/a3d5273a-10df-4b36-b9ea-460635fa84fc" />

* * * * * * * * * *
## Introduction
The function block `XOR_3_BOOL` is a standardized function block for calculating the logical exclusive OR (XOR) operation for three Boolean input values. It is implemented as a generic function block and performs its operation on every incoming execution event.

![XOR_3_BOOL](XOR_3_BOOL.svg)

## Interface Structure
### **Event Inputs**
* **REQ** (Normal Execution Request): Triggers the calculation of the XOR function. The data associated with this event (`IN1`, `IN2`, `IN3`) are read and processed.


### **Event Outputs**

* **CNF** (Execution Confirmation): Triggered after the calculation is complete. This event returns the calculated result via the corresponding data output `OUT`.

### **Data Inputs**

* **IN1** (BOOL): First Boolean operand for the XOR operation.

* **IN2** (BOOL): Second Boolean operand for the XOR operation.

* **IN3** (BOOL): Third Boolean operand for the XOR operation.

### **Data Outputs**

* **OUT** (BOOL): The result of the triple XOR operation of the inputs `IN1`, `IN2`, and `IN3`.


### **Adapter**

This function block has no adapter interfaces.

## Operation
The block operates in an event-driven manner. Upon each occurrence of the event `REQ`, the current values of the three Boolean inputs `IN1`, `IN2`, and `IN3` are read. The logical XOR operation is then calculated for all three inputs. The result is output at the data output `OUT`, and simultaneously, the confirmation event `CNF` is triggered to signal the completion of the operation.

The corresponding logical function is: `OUT = (IN1 XOR IN2) XOR IN3`. For three inputs, the result is `TRUE` (1) if and only if there is an odd number of inputs (`TRUE`) (i.e., 1 or 3 inputs).

## Technical Features
* **Generic Block:** The block is marked as a generic block (`'GEN_XOR'`) with the attribute `eclipse4diac::core::GenericClassName`. This allows for potential reuse of the logic for other data types that support the XOR operation.

* **Standard Compliance:** The block is classified as a "standard boolean function" according to the IEC 61131-3 standard.

* **Package Assignment:** The block is assigned to the package `iec61131::bitwiseOperators`.

## State Overview
The function block does not have an internal state in the sense of a memory. Its behavior is purely combinatorial and depends solely on the current input values when the `REQ` event arrives. The only "state" is the idle state, in which the block waits for the next `REQ` event.

## Application Scenarios

* **Parity Check:** Detects whether an odd number of three Boolean signals are active.

* **Control Logic:** In specialized control algorithms that require "either-or" logic with more than two conditions.

* **Encryption and Coding:** As a fundamental component in simple cryptographic or error-detecting circuits (e.g., for parity bits).

* **Signal Comparison:** Determines whether a third signal differs from the combination of two other signals.


* ## ⚖️ Comparison with Similar Blocks

* **XOR (2 Inputs):** The standard XOR block with only two inputs. `XOR_3_BOOL` extends this function to three operands. See: [XOR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_3.md)]

* **OR / AND (3 Inputs):** These blocks calculate the logical OR or AND operation of all inputs. The XOR logic is more specialized and differs, in particular, when all three inputs are `TRUE` (OR=TRUE, AND=TRUE, XOR=TRUE).

* **GEN_XOR:** This is the generic basis from which `XOR_3_BOOL` is derived as a specific instance for the data type `BOOL`.


* ## Conclusion

The `XOR_3_BOOL` function block is a specialized, standards-compliant building block for reliably calculating triple exclusive OR operations. Its clear, event-driven interface and deterministic functionality make it ideal for use in control applications that require this specific Boolean logic. As an instance of a generic building block, it also benefits from the maintenance and consistency advantages of a generic design.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```