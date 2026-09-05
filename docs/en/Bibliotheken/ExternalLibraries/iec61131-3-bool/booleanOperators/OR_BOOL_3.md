# OR_BOOL_3

<img width="1370" height="281" alt="image" src="https://github.com/user-attachments/assets/b7317e35-c6b5-4925-bc67-76e89bd63323" />
* * * * * * * * * *
## Introduction

The function block `OR_BOOL_3` is a standardized block according to IEC 61131-3 for performing a logical OR operation. It calculates the logical OR (disjunction) of three Boolean input signals. The block is implemented as a generic function and is executed on every trigger event.
![OR_BOOL_3](OR_BOOL_3.svg)

## Interface Structure

The function block has one event input, one event output, three data inputs, and one data output. No adapter interfaces are available.

### **Event Inputs**

- **REQ** (Normal Execution Request): This event triggers the calculation of the OR function. Upon receiving `REQ`, the current values at inputs `IN1`, `IN2`, and `IN3` are read, and the result is calculated.

### **Event Outputs**

- **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is output along with the calculated result at output `OUT`.

### **Data Inputs**

- **IN1** (BOOL): First OR input signal.
- **IN2** (BOOL): Second OR input signal.
- **IN3** (BOOL): Third OR input signal.

### **Data Outputs**

- **OUT** (BOOL): Result of the OR operation (`IN1` OR `IN2` OR `IN3`).

### **Adapters**

No adapter interfaces are available.

## Functionality

Whenever the event `REQ` occurs, the function block performs a logical OR operation on the three Boolean inputs `IN1`, `IN2`, and `IN3`. The result of this operation is output to data output `OUT`. Immediately after the calculation, the confirmation event `CNF` is triggered to signal the successful completion of the operation.

The logical function can be described by the following truth table:

| IN1 | IN2 | IN3 | OUT (IN1 OR IN2 OR IN3) |
| :---: | :---: | :---: | :-----------------------: |
| 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 |
| 0 ... | 0 | 1 | 1 | 1 | 1 |
| 0 | 0 | 1 | 1 | 1 | 1 |
| The output `OUT` is `TRUE` (1) if and only if at least one of the three inputs is `TRUE`.

## Technical Features

- **Generic Block:** The block is implemented as an instance of a generic OR block (`GEN_OR`), enabling consistent integration into libraries.
- **Event-Driven Execution:** Function execution is strictly linked to the occurrence of the `REQ` event, ensuring deterministic control in real-time systems.
- **Standard Compliance:** Conforms to the "standard boolean function" classification according to IEC 61131-3.

## State Overview

The function block has no internal state (memory-free, combinatorial). Its output depends solely on the current values of the inputs at the time of the trigger event `REQ`.

## Application Scenarios

- **Safety and Monitoring Logic:** Combination of multiple fault sensors (e.g., temperature too high, pressure too low, level critical), where each sensor can trigger an alarm.
- **Control Logic:** Activation of an actuator (e.g., a pump or motor) when at least one of several conditions is met (e.g., manual start command OR automatic setpoint reached OR emergency start active).
- **Chaining of Logic Operations:** As part of more complex logical expressions in conjunction with AND and NOT blocks.

## ⚖️ Comparison with Similar Blocks

- **OR_BOOL_2:** Combines only two inputs. `OR_BOOL_3` extends this functionality to include a third input. See also: [OR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_3.md)
- **GEN_OR:** The underlying generic function block, which can be configured for a variable number of inputs. `OR_BOOL_3` is a specific instance of this, fixed to three inputs.
- **AND_n_BOOL:** Performs a logical AND operation. The result is `TRUE` only if **all** inputs are `TRUE`, whereas for the OR operation, **just one** `TRUE` input is sufficient.

## 🛠️ Related Exercises

- [Exercise_002a5b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a5b.md)

## Conclusion

The `OR_BOOL_3` is a fundamental, reliable, and standards-compliant function block for the logical OR operation of three signals. Its event-driven, stateless operation makes it ideal for use in clearly structured control sequences in automation technology. It represents an essential component for implementing monitoring, safety, and control logic.
