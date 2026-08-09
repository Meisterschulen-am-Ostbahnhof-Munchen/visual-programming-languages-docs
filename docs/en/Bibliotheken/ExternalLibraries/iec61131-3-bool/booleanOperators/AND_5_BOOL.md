# AND_5_BOOL

<img width="1383" height="334" alt="image" src="https://github.com/user-attachments/assets/26c969c4-f1f2-4142-9188-57cd244d9cd6" />
* * * * * * * * * *
## Introduction

The function block `AND_5_BOOL` is a standard function block for calculating the logical AND operation. It performs a bitwise AND operation on five separate Boolean input values. The block follows the real-time and event-driven processing model of IEC 61499, where the calculation is triggered by an incoming event and confirmed by an outgoing event.
![AND_5_BOOL](AND_5_BOOL.svg)
## Interface Structure

### **Event Inputs**

* **REQ**: Triggers the execution of the function block. Upon arrival of this event, all five inputs (`IN1` to `IN5`) are read and the AND operation is calculated.

### **Event Outputs**

* **CNF**: Confirms completion of the operation. This event is output after the result is calculated and includes the calculated value `OUT`.

### **Data Inputs**

* **IN1**: Boolean input 1 for the AND operation.
* **IN2**: Boolean input 2 for the AND operation.
* **IN3**: Boolean input 3 for the AND operation.
* **IN4**: Boolean input 4 for the AND operation.
* **IN5**: Boolean input 5 for the AND operation.

### **Data Outputs**

* **OUT**: The Boolean result of the AND operation of all five inputs. The output is only `TRUE` if **all** inputs `IN1` to `IN5` have the value `TRUE`.

### **Adapters**

This function block does not use any adapters.

## Operation

The operation is deterministic and event-driven:

1. The incoming event `REQ` activates the block.
2. The current values of all five Boolean data inputs (`IN1` to `IN5`) are read.
3. The logical AND operation is calculated: `OUT = IN1 AND IN2 AND IN3 AND IN4 AND IN5`.
4. The result is provided at data output `OUT`.
5. The output event `CNF` is triggered along with the new value of `OUT` to signal the completion of the operation.

## Technical Features

* **Generic Block**: The block is implemented as an instance of a generic AND block (`GEN_AND`), which can be parameterized for a variable number of inputs. This specific instance is defined for exactly five inputs.
* **Event Chain**: The execution strictly follows the REQ/CNF pattern, which allows for easy integration into event-driven control sequences.
* **No Internal State**: The block is memory-free (combinatory). The output signal depends solely on the current input values at the time of the `REQ` request.

## State Overview

The function block has no persistent internal state. Its behavior is purely combinatorial and is fully described by the interface events and data. The "state" is the transition from waiting (`REQ` wait) to active (perform calculation and trigger `CNF`).

## Application Scenarios

Typical applications include safety and enable chains in automation technology, where multiple conditions must be met simultaneously:

* Monitoring whether all safety guards of a machine are closed.
* Checking whether all required media (pressure, vacuum, cooling) are available before a process is started.
* Linking multiple sensor or switch states to a common enable logic.

## ⚖️ Comparison with similar building blocks

* **`AND_2_BOOL` / `AND_3_BOOL` etc.**: Basic AND blocks with two, three, or four inputs. `AND_5_BOOL` extends this logic to five inputs without the need to chain multiple blocks. See: [AND_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_5.md)]
* **`GEN_AND`**: The underlying generic block. `AND_5_BOOL` is a pre-configured, unchangeable instance of it with a fixed number of inputs.
* **OR blocks**: Perform a logical OR operation. While `AND_5_BOOL` outputs `TRUE` only if all `TRUE` inputs are present, OR gates output `TRUE` even if only one `TRUE` input is present.

## Conclusion

The `AND_5_BOOL` is a robust and easy-to-use standard function block for five-input logic gates. Its event-driven, stateless architecture makes it highly predictable and easy to integrate into more complex IEC 61499 applications. It offers an optimal and readable solution for applications that need to link exactly five conditions.