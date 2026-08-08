# AND_4_BOOL
<img width="1383" height="309" alt="image" src="https://github.com/user-attachments/assets/34d2c683-71b2-4516-bcd4-e4d1c1706dda" />
* * * * * * * * * *
The function block `AND_4_BOOL` is a standard function block for calculating the logical AND operation. It performs a bitwise AND operation on four Boolean input values. The block is implemented as a generic function block and complies with the IEC 61131-3 standard for basic Boolean functions.
![AND_4_BOOL](AND_4_BOOL.svg)
* **REQ** (Normal Execution Request): This event triggers the execution of the function block. It is associated with all four data inputs (`IN1` to `IN4`).

* **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is output along with the result at data output `OUT`.

* **IN1** (BOOL): First operand for the AND operation.
* **IN2** (BOOL): Second operand for the AND operation.
* **IN3** (BOOL): Third operand for the AND operation.
* **IN4** (BOOL): Fourth operand for the AND operation.

* **OUT** (BOOL): Result of the logical AND operation of all four inputs. The output is only `TRUE` if **all** inputs `IN1`, `IN2`, `IN3`, and `IN4` have the value `TRUE`.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
This function block does not use any adapters.

Whenever a `REQ` event occurs, the function block reads the current values at the four Boolean data inputs. It then calculates the logical AND of these four values according to the following truth table:

| IN1 | IN2 | IN3 | IN4 | OUT |
|:---:|:---:|:---:|:---:|:---:|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 |
| ... | ... | ... | ... | ... |
| 1 | 1 | 1 | 1 | 1 |

The result is set at the data output `OUT`, and simultaneously the `CNF` event is triggered to signal the completion of the operation.

* **Generic Implementation:** The function block is marked as a generic function block (`GEN_AND`), which means it can serve as the basis for similar function blocks with a different number of inputs.
* **Event-driven execution:** The operation is triggered exclusively by an incoming event (`REQ`), which is typical for the function block (FB) style in IEC 61499.
* **Standard compliance:** The block is classified as a standard Boolean function according to IEC 61131-3.

The function block does not have an internal state in the sense of a memory. Its behavior is purely combinatorial and depends only on the current input values at the time of triggering. The only "state" is the idle state, in which it waits for the next `REQ` event.

* **Safety chain:** Linking several safety switches (e.g., emergency stop, guardrail, two-hand control), all of which must be closed to start a machine.

* **Masking:** Selectively activates a function only if multiple enable signals are present.

* **AND (2 Inputs):** A basic AND block with only two inputs. `AND_4_BOOL` consolidates four such operations into a single block, improving diagram readability and maintainability. See: [AND_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_4.md)]
* **OR_4_BOOL:** Performs a logical OR operation where the result is `TRUE` if at least one input is `TRUE`. This is the logical counterpart to AND.
* **GEN_AND:** The generic base class on which `AND_4_BOOL` is built. It can be configured to create AND blocks with any number of inputs.

The `AND_4_BOOL` function block is a simple, robust, and standards-compliant block for processing logic signals. Its clear, event-driven interface and fixed number of four inputs make it particularly suitable for control tasks where multiple conditions must be met simultaneously. As part of the `iec61131::bitwiseOperators` library, it is a fundamental component for designing control logic in 4diac.

---

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
## Functionality
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de