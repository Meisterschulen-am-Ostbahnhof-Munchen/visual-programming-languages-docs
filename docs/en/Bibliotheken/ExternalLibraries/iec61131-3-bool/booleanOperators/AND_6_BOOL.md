# AND_6_BOOL

<img width="1383" height="362" alt="image" src="https://github.com/user-attachments/assets/c763f4fa-77f1-49b2-a946-396f41d8094f" />
* * * * * * * * * *
The function block `AND_6_BOOL` is a standard function block for calculating the logical AND operation. It performs a bitwise AND operation using six separate Boolean inputs. This block belongs to the category of standard Boolean functions and is designed for use in control applications according to IEC 61131-3.
![AND_6_BOOL](AND_6_BOOL.svg)

- **REQ** (Normal Execution Request): This event triggers the calculation of the AND operation. Upon receiving `REQ`, the values of all six data inputs (IN1 to `IN6`) are read and processed.
- **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is output along with the calculated result at data output `OUT`.
- **IN1** (BOOL): AND input 1.
- **IN2** (BOOL): AND input 2.
- **IN3** (BOOL): AND input 3.
- **IN4** (BOOL): AND input 4.
- **IN5** (BOOL): AND input 5.
- **IN6** (BOOL): AND input 6.
- **OUT** (BOOL): Result of the AND operation. The output is only `TRUE` if **all** six inputs (`IN1` to `IN6`) have the value `TRUE`. In all other cases, the output is `FALSE`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

This function block has no adapter interfaces.

## Functionality

The functionality is deterministic and simple: Upon each occurrence of the event `REQ`, the logical state of all six inputs is evaluated. The result of the AND operation is provided at the data output `OUT`, and simultaneously, the acknowledgment event `CNF` is triggered. The logical operation corresponds to the formula:
OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5 AND IN6`

- **Generic Block:** The block is implemented as a generic block (`GEN_AND`), meaning it is a specific instance of a more general AND function block family.
- **Fixed Number of Inputs:** Unlike blocks with a variable number of inputs, this block has exactly six fixed inputs.
- **Event-driven:** The operation is executed exclusively by an incoming event (`REQ`), which is typical for the function block (FB) architecture in 4diac.

The block has no internal state or memory. Its behavior is purely combinatorial and depends solely on the current values of the inputs at the time of triggering by `REQ`.

Typical applications include safety and enable chains in control logic, where multiple conditions must be met simultaneously before an action is executed.

- **Machine Start:** A machine will only start if all safety doors are closed (`TRUE`) and all emergency stop buttons are not pressed (`TRUE`).
- **Multiple Sensor Polling:** Evaluates multiple sensors, all of which must provide a signal to confirm a position or state.
- **AND (with 2 inputs):** The standard `AND` block typically has only two inputs. `AND_6_BOOL` offers a specialized, more compact representation for applications with exactly six inputs, without the need to chain multiple blocks together. See: [AND_6](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_6.md)
- **GEN_AND (Generic AND Block):** `AND_6_BOOL` is a concrete instance of this generic type. Other instances could have a different number of inputs (e.g., `AND_4_BOOL`).
- **OR_6_BOOL:** A similar block, but it performs a logical OR operation where the result is `TRUE` if at least one input is `TRUE`.

The `AND_6_BOOL` function block is a reliable and easy-to-use block for six-input logical AND operations. Its event-driven, stateless nature makes it predictable and easily integrated into the 4diac architecture. It is the optimal choice when a fixed set of six conditions must be met simultaneously to trigger a subsequent action.

---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
