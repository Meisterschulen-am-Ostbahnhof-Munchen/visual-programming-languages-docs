# AND_3_BOOL

<img width="1383" height="275" alt="image" src="https://github.com/user-attachments/assets/e4d9d0a5-5b7b-41c6-9187-4cb9a9380a03" />

* * * * * * * * * *
## Introduction
The function block `AND_3_BOOL` is a standardized building block for calculating the logical AND operation for three Boolean input signals. It complies with the IEC 61131-3 standard for basic Boolean functions and operates according to the 4diac real-time execution control model, where the calculation is triggered by an incoming event.

![AND_3_BOOL](AND_3_BOOL.svg)

## Interface Structure
The interface of the `AND_3_BOOL` block is clear and simple, consisting of one event input, one event output, three data inputs, and one data output.

## **Event Inputs**
* **REQ (Normal Execution Request):** This incoming event triggers the execution of the function block. Upon the arrival of `REQ`, the current values at data inputs `IN1`, `IN2`, and `IN3` are read, and the logical AND operation is performed.

### **Event Outputs**

* **CNF (Execution Confirmation):** This event is generated after the calculation is complete. It signals that the result has been output to data output `OUT` and is now valid.

### **Data Inputs**

* **IN1 (BOOL):** First Boolean input signal for the AND operation.

* **IN2 (BOOL):** Second Boolean input signal for the AND operation.

* **IN3 (BOOL):** Third Boolean input signal for the AND operation.

### **Data Outputs**

* **OUT (BOOL):** The result of the logical AND operation of all three inputs. `OUT` is only `TRUE` (1) if **all** inputs `IN1`, `IN2`, and `IN3` are simultaneously `TRUE`. In all other cases, `OUT` is `FALSE` (0).

### **Adapters**
This function block has no adapter interfaces.


### ## Functionality

The functionality is deterministic and follows a simple sequence:

1. **Trigger:** The incoming event `REQ` activates the block.

2. **Reading the Inputs:** The current values of the three Boolean data inputs (`IN1`, `IN2`, `IN3`) are read.

3. **Calculation:** The logical AND operation is performed: `OUT := IN1 AND IN2 AND IN3`.

4. **Output:** The calculated result is written to the data output `OUT`.

5. **Acknowledgement:** The output event `CNF` is generated to signal the successful completion of the operation to subsequent blocks.

## Technical Features
* **Generic Function Block:** This block is marked as a generic function block (`GEN_AND`), meaning it can serve as a basis for creating similar AND blocks with a different number of inputs.

* **Real-Time Capable:** Due to its execution control model (event-driven control), this block is suitable for deterministic real-time applications.

* **Simple Logic:** Contains no internal states or memory. The output is a pure combinatorial function of the current inputs.

## State Overview
The `AND_3_BOOL` block is a **combinatorial** function block without internal state (stateless). Its behavior on each call (`REQ`) depends solely on the current values at the data inputs. There are no prior calculations or states that influence the result.


## Application Scenarios
Typical applications include control logics where an action may only be executed if several safety or enabling conditions are met simultaneously:

* **Two-Hand Operation:** A machine only starts when three separate buttons are pressed simultaneously (`IN1`, `IN2`, `IN3`).

* **Safety Circuit:** A process is only activated if the safety door is protected (`IN1`), the emergency stop bypass is activated (`IN2`), and material is present (`IN3`).

* **Condition Chaining:** As part of a more complex logical equation within an algorithm.


## ⚖️ Comparison with similar building blocks

* **`AND_2_BOOL`:** Performs the AND operation for only two inputs. `AND_3_BOOL` is a direct extension for three inputs.

* **`AND_n_BOOL` (theoretical):** A generic block for a variable number of inputs. `n` is a specific, hard-wired instance of `AND_3_BOOL`. See: [AND_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_3.md)

* **`OR_3_BOOL`:** Calculates the logical OR operation (output is `TRUE` if at least one input is `TRUE`). This is the complementary function.

* **Combinatorial Logic in SFC/ST:** The same function could also be implemented in Structured Text (ST) as `OUT := IN1 & IN2 & IN3;` or in an SFC action. The advantage of the function block is its reusability, clear encapsulation, and easy integration into the 4diac event system.

## Conclusion
The `AND_3_BOOL` is a fundamental, reliable, and easy-to-use building block for Boolean logic in 4diac-based control applications. Its strict event-driven control ensures deterministic behavior, and its clear interface allows for intuitive integration into function block networks. For all control tasks requiring a triple AND operation, this block is the standard solution.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]