# OR_2_BOOL
<img width="1568" height="281" alt="image" src="https://github.com/user-attachments/assets/8ebdc4b4-c155-45d6-81bb-875ba03dc816" />
* * * * * * * * * *
## Introduction
The function block `OR_2_BOOL` performs a logical OR operation (disjunction) on two Boolean input values. It is a generic function block classified according to the IEC 61131-3 standard for standard Boolean functions. The block waits for an execution request, calculates the result, and signals its availability.
![OR_2_BOOL](OR_2_BOOL.svg)
## Interface Structure
### **Event Inputs**
* **REQ** (Normal Execution Request): This event triggers the execution of the function block. Upon its arrival, the values at data inputs `IN1` and `IN2` are read, and the OR operation is performed.

### **Event Outputs**
* **CNF** (Execution Confirmation): This event is generated after the calculation is complete. It indicates that the result has been output to data output `OUT` and is valid.

### **Data Inputs**
* **IN1** (BOOL): First operand for the OR operation.
* **IN2** (BOOL): Second operand for the OR operation.

### **Data Outputs**
* **OUT** (BOOL): Result of the logical OR operation of `IN1` and `IN2`. The output value is `TRUE` if at least one of the two inputs is `TRUE`. Otherwise, it is `FALSE`.

### **Adapter**
This function block has no adapter interfaces.

## Operation
The operation is event-driven and follows a simple request-acknowledgment cycle:

1. The arrival of the event `REQ` starts the execution.

2. The current values of the data inputs `IN1` and `IN2` are retrieved.

3. The logical OR operation `OUT := IN1 OR IN2` is calculated.

4. The result is placed at the data output `OUT`.

5. The event `CNF` is generated to indicate the completion of the operation.

The truth table of the operation is:

| IN1 | IN2 | OUT (IN1 OR IN2) |
|:---:|:---:|:----------------:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

## Technical Features
* **Generic Block:** The block is marked as a generic block (`GEN_OR`), which means it can serve as a basis for deriving similar blocks with other data types.
* **Simple Runtime:** The execution time is constant and very short, as it involves a simple logical operation.
* **No Internal State:** The block is stateless (combinatorial). The result depends solely on the current input values at the time of the `REQ` request.

## State Overview
The function block has no persistent internal state. Its behavior is purely combinatorial and is fully described by the interface events and data.

## Application Scenarios
* **Logical Connections in Control Logic:** Combination of two conditions where an action is to be executed if at least one of the conditions is met (e.g., "Start motor if button is pressed OR remote control signal is received").
* **Error Aggregation:** Summarizing multiple error signals into a single error status. If at least one error is present (`TRUE`), the combined error status is activated.
* **Lever Logic:** Creates a allow when one of several possible sources is active.
* **Basic Building Block in More Complex Logic Circuits:** As part of AND-OR logic gates (SOPs - Sum of Products) to implement switching functions.

## ⚖️ Comparison with Similar Building Blocks
* **AND_2_BOOL:** Performs a logical AND operation. The result is `TRUE` only if **both** inputs are `TRUE`.
* **XOR_2_BOOL:** Performs an exclusive OR operation (antivalence). The result is `TRUE` if exactly **one** input is `TRUE`.
* **NOT_BOOL:** Performs a logical NOT operation (negation) on a single input.
* **OR_n_BOOL:** A generic OR gate that can combine a variable number of inputs (n), whereas `OR_2_BOOL` has exactly two fixed inputs. See: [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md)

## 🛠️ Related Exercises
* [Exercise_002b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b3.md)
* [Exercise_160](../../../../Uebungen/test_B/Uebungen_doc/Uebung_160.md)
* [Exercise_160b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b.md)
* [Exercise_160b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)

## Conclusion
The `OR_2_BOOL` is a fundamental, reliable, and easy-to-use function block for implementing the basic logical OR function in 4diac IDE applications. Its event-driven, stateless architecture makes it predictable and easily integrated into the data flow of IEC 61499 systems. It is an indispensable component for implementing control logic and conditional evaluation.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]