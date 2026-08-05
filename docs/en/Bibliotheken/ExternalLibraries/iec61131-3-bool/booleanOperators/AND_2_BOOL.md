# AND_2_BOOL
<img width="1383" height="250" alt="image" src="https://github.com/user-attachments/assets/10df4f18-5ed8-46f2-aaae-c0c787c2731e" />
* * * * * * * * * *
## Introduction
The function block `AND_2_BOOL` is a standard function block for calculating the logical AND operation (conjunction) of two Boolean input values. It complies with the IEC 61131-3 standard for basic Boolean functions and is designed for use in the 4diac IDE. The function block waits for a trigger event, executes the operation, and signals the completion of the calculation with an acknowledgment event.
![AND_2_BOOL](AND_2_BOOL.svg)
## Interface Structure
The interface of the `AND_2_BOOL` function block is simple and clearly structured, consisting of an event input, an event output, and the associated data connections.

### **Event Inputs**
* **REQ (Normal Execution Request):** This event triggers the execution of the function block. Upon its arrival, the current values at data inputs `IN1` and `IN2` are read, and the AND operation is calculated.

### **Event Outputs**
* **CNF (Execution Confirmation):** This event is generated after the calculation is complete. It signals that the result has been output to data output `OUT` and is now valid.

### **Data Inputs**
* **IN1 (AND input 1):** First Boolean operand (Type: `BOOL`).

### * **IN2 (AND input 2):** Second Boolean operand (Type: `BOOL`).

### **Data Outputs**
* **OUT (AND result):** Result of the logical AND operation of `IN1` and `IN2` (Type: `BOOL`). The output value is `TRUE` (1) if both `IN1` and `IN2` have the value `TRUE`. In all other cases, the output is `FALSE` (0).

### **Adapters**
This function block has no adapter interfaces.

### ## Functionality
The `AND_2_BOOL` block functions deterministically and follows classic Boolean logic:

1. **Trigger:** The occurrence of the event `REQ` starts the execution.

2. **Read Input:** The current values of the data inputs `IN1` and `IN2` are retrieved.

3. **Calculation:** The logical AND operation `OUT := IN1 AND IN2` is performed.

4. **Output:** The calculated result is written to the data output `OUT`.

5. **Confirmation:** Immediately after output, the confirmation event `CNF` is generated to inform downstream blocks about the availability of the new result.

The operation can be described by the following truth table:

| IN1 | IN2 | OUT (IN1 AND IN2) |

|:---:|:---:|:-----------------:|

| 0 | 0 | 0 |

| 0 | 1 | 0 |

| 1 | 0 | 0 |

| 1 | 1 | 1 |

## Technical Details
* **Generic Block:** The block is implemented as an instance of a generic AND block (`GEN_AND`), which can be specialized for different data types. In this specific instance, it is defined for the data type `BOOL`.

| IN1 | IN2 | OUT (IN1 AND IN2) |

| 0 | 0 | 0 |

| 1 | 1 | 1 |

## Technical Details

**Generic Block:** The block is implemented as an instance of a generic AND block (`GEN_AND`), which can be specialized for different data types. In this specific instance, it is defined for the data type `BOOL`.

| IN1 | IN2 | OUT (IN1 AND IN2) ... * **Event-driven:** As is typical for 4diac function blocks, execution is strictly event-driven. A change in the input values alone does not trigger a calculation; this only occurs upon the arrival of the `REQ` event.

* **Low latency:** The execution time is negligible, so the `CNF` event follows the `REQ` event practically immediately.

## State overview
The function block has no internal state in the sense of a memory for previous values. It is a purely combinational block whose output depends solely on the current input values at the time of triggering. Its "state" is therefore always "waiting for REQ" or "executing," with the execution phase being very short.

## Application Scenarios

The `AND_2_BOOL` block is a fundamental building block in control and automation technology. Typical applications include:

* **Safety Conditions:** Linking multiple safety signals (e.g., "Safety door closed" AND "Emergency stop not pressed") to generate a machine enable signal.
* **Two-Hand Operation:** Ensuring that two buttons must be pressed simultaneously to initiate a hazardous operation.
* **Chaining of Switching Conditions:** Combining multiple sensor or switch states to control an actuator signal (e.g., "Material present" AND "Position reached" -> gripper close).
* **Signal Masking:** Selectively switching a signal (`DATA`) through or blocking it with an enable signal (`ENABLE`) using `OUT := DATA AND ENABLE`.

## ⚖️ Comparison with similar building blocks
* **`AND_n` (generic):** The generic `GEN_AND` building block can be configured for more than two inputs and other data types (e.g., `WORD`, `DWORD`). `AND_2_BOOL` is a specific instance of this, fixed to two Boolean inputs, which can be used more easily and directly in Boolean logic circuits. See: [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md)
* **`OR_2_BOOL` / `XOR_2_BOOL`:** These blocks implement other basic Boolean operations (OR and exclusive OR, respectively). They have the same event-driven interface (`REQ`/`CNF`), but perform a different logical operation on the inputs `IN1` and `IN2`.
* **Combinatorial Logic in SFC/ST:** The AND function could also be directly encoded in Structured Text (ST) using the `&` or `AND` operator. The advantage of the `AND_2_BOOL` function block lies in its standardized, reusable, and graphically linkable form within the 4diac function block network (FBN).
* **Combinatorial Logic in SFC/ST:** The AND function could also be directly encoded in Structured Text (ST) using the `&` or `AND` operator. ## 🛠️ Related Exercises
* [Exercise_002a4](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a4.md)]
* [Exercise_002b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b3.md)]
* [Exercise_006a3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3.md)]

## Conclusion
The `AND_2_BOOL` function block is an essential, reliable, and easy-to-use building block for implementing Boolean logic in 4diac-based control applications. Its clear, event-driven interface and deterministic functionality make it the ideal building block for safety operations, control conditions, and general logical operations. It is the first choice for pure Boolean binary operations.

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]