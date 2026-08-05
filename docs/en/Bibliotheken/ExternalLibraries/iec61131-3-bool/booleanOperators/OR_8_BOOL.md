# OR_8_BOOL
<img width="1370" height="426" alt="image" src="https://github.com/user-attachments/assets/a2fa1484-476e-4e8f-b817-9aa20ff38361" />
* * * * * * * * * *
## Introduction
The function block `OR_8_BOOL` is a standardized block for calculating the logical OR operation. It performs the OR operation on eight separate Boolean input values and outputs the result on a single Boolean output. This block is part of the IEC 61131-3 compliant library for bitwise operations and is used for simple and structured logic processing in control applications.
![OR_8_BOOL](OR_8_BOOL.svg)
## Interface Structure
### **Event Inputs**
* **REQ** (Normal Execution Request): This event triggers the execution of the function block. Upon its arrival, all eight data inputs (`IN1` to `IN8`) are read and the OR operation is calculated.

### **Event Outputs**
* **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is output along with the calculated result at data output `OUT`.

### **Data Inputs**
* **IN1** (BOOL): OR input 1.
* **IN2** (BOOL): OR input 2.
* **IN3** (BOOL): OR input 3.
* **IN4** (BOOL): OR input 4.
* **IN5** (BOOL): OR input 5.
* **IN6** (BOOL): OR input 6.
* **IN7** (BOOL): OR input 7.
* **IN8** (BOOL): OR input 8.

### **Data Outputs**
* **OUT** (BOOL): Result of the OR operation of all eight inputs. The output is `TRUE` (1) if at least one of the inputs `IN1` to `IN8` has the value `TRUE`. Otherwise, the output is `FALSE` (0).

### **Adapter**
This function block does not use any adapter interfaces.

## Operation
The operation is event-driven and follows a simple request-confirm cycle:

1. The arrival of the event `REQ` starts execution.

2. The block reads the current values of all eight Boolean inputs (`IN1` to `IN8`).

3. The logical OR operation is calculated across all eight inputs: `OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5 OR IN6 OR IN7 OR IN8`.

4. The result is output at `OUT`, and simultaneously, the confirmation event `CNF` is triggered to signal the successful completion of the operation.

## Technical Features
* **Generic Block:** This block is marked as a generic block (`GEN_OR`), meaning it can serve as a basis for creating similar OR blocks with a different number of inputs.
* **Standard Compliant:** It is classified according to the IEC 61131-3 standard and implements a standardized Boolean function.
* **Deterministic Behavior:** Execution is deterministic and does not result in any internal state storage between calls.

## State Overview
The function block `OR_8_BOOL` is stateless (combinatorial logic). It has no internal memory. The output `OUT` is, at any given time, solely a direct function of the current input values read in by the last `REQ` event.

## Application Scenarios
Typical applications include:

* **Monitoring Logic:** Combining multiple error or warning signals (e.g., from different sensors or subsystems) into a single alarm output.
* **Enable Logic:** Checking whether at least one of several possible enable conditions (e.g., "Manually enabled" OR "Automatically enabled") is met.
* **Linking Button Inputs:** In control panels to trigger an action when one of several buttons is pressed.

## ⚖️ Comparison with similar function blocks
* **`OR_2_BOOL`, `OR_4_BOOL`:** These are structurally identical function blocks, but they only connect two or four inputs, respectively. `OR_8_BOOL` offers a higher number of inputs without having to cascade multiple instances of blocks with fewer inputs. See: [OR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_8.md)
* **`AND_n_BOOL`:** Performs the logical AND operation. The result is only `TRUE` if *all* inputs are `TRUE`, whereas for the OR operation, a single `TRUE` input is sufficient.
* **`XOR_n_BOOL`:** Performs an exclusive OR (XOR) operation. The result is `TRUE` if there is an odd number of inputs; it is `TRUE`, which differs from inclusive OR logic.

## Conclusion
The `OR_8_BOOL` function block is a fundamental, reliable, and easy-to-use building block for Boolean logic processing. Its strength lies in its clear, standards-compliant interface and efficient processing of up to eight signals into a single statement. It is the first choice for applications requiring an inclusive OR operation across multiple signals.