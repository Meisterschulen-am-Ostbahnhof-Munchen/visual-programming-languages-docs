# XOR_5_BOOL
<img width="1186" height="283" alt="image" src="https://github.com/user-attachments/assets/0d8ae9ee-ae15-400f-8e0f-459aa54db0db" />
* * * * * * * * * *
## Introduction
The function block `XOR_5_BOOL` is a standard function block for calculating the logical exclusive OR (XOR) operation for five Boolean input values. It complies with the IEC 61131-3 standard and is implemented as a generic function block. The operation is performed on each incoming execution event, and the result is output via an acknowledgment event.
![XOR_5_BOOL](XOR_5_BOOL.svg)
## Interface Structure
### **Event Inputs**
* **REQ (Normal Execution Request):** Triggers the calculation of the XOR operation. This event is associated with all five data inputs (`IN1` to `IN5`).

### **Event Outputs**
* **CNF (Execution Confirmation):** Signals the completion of the calculation. This event is linked to the data output `OUT` and returns the result.

### **Data Inputs**
* **IN1 (XOR input 1):** First Boolean operand (BOOL).
* **IN2 (XOR input 2):** Second Boolean operand (BOOL).
* **IN3 (XOR input 3):** Third Boolean operand (BOOL).
* **IN4 (XOR input 4):** Fourth Boolean operand (BOOL).
* **IN5 (XOR input 5):** Fifth Boolean operand (BOOL).

### **Data Outputs**
* **OUT (XOR result):** The Boolean result of the XOR operation of all five inputs (BOOL).

### **Adapter**

This function block has no adapter interfaces.

## Functionality
Whenever the event `REQ` occurs, the function block performs the logical XOR operation on its five Boolean inputs `IN1` to `IN5`. The result is output `OUT`, and the acknowledgment event `CNF` is triggered simultaneously.

The logical function is defined as: `OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5`.

The result is `TRUE` (1) if and only if an odd number of the inputs have the value `TRUE` (1). With an even number of `TRUE` inputs, the result is `FALSE` (0).

## Technical Features
* **Generic Block:** The block is marked as a generic implementation (`'GEN_XOR'`) by the attribute `eclipse4diac::core::GenericClassName`. This allows for flexible reuse of the core logic.
* **Event-driven:** The calculation is performed exclusively event-driven by `REQ` and is non-cyclic.
* **Five Inputs:** Unlike standard XOR blocks with typically two inputs, this block offers five hard-wired inputs, eliminating the need to chain multiple blocks for a higher number of operands.

## State Overview
The block has no internal state (memory-free). Its output depends solely on the current values of the inputs at the time of the `REQ` event.

## Application Scenarios
* **Parity Check:** Checks whether an odd number of conditions (e.g., error signals, limit exceedances) are active in a group of five signals.
* **Control Logic:** Implements special logic logic in PLC programs where exactly one, three, or five of five possible individual conditions must be met.
* **Signal Comparison:** Detects inequality in a group of five binary signals.

## ⚖️ Comparison with Similar Blocks
* **Standard XOR (2 Inputs):** Library blocks often only offer the XOR operation for two operands. For five operands, several of these blocks would have to be chained together (e.g., `((IN1 XOR IN2) XOR (IN3 XOR IN4)) XOR IN5`). `XOR_5_BOOL` summarizes this logic in a single, concise block. See: [XOR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_5.md)]
* **OR / AND Blocks:** While OR (`OR`) returns `TRUE` with at least one `TRUE` input, and AND (`AND`) only with all `TRUE` inputs, XOR specifically responds to an odd number of `TRUE` values.
* **Generic XOR Blocks:** Generic blocks could exist that handle a variable number of inputs via arrays or repeated inputs. `XOR_5_BOOL` is a fixed, specific instance for exactly five inputs.

## Conclusion
The `XOR_5_BOOL` function block is a specialized and efficient building block for calculating the exclusive OR operation across exactly five Boolean signals. Its event-driven, stateless operation and clear interface make it a reliable tool for control applications that require this specific logic function, especially in the areas of parity checking and complex conditional logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]