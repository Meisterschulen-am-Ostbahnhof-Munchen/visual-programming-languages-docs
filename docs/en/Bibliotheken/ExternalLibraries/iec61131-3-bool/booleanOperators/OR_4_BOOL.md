# OR_4_BOOL

<img width="1370" height="307" alt="image" src="https://github.com/user-attachments/assets/8a66daf2-c93b-4cfc-bd10-dba250315aaf" />
* * * * * * * * * *
## Introduction

The function block `OR_4_BOOL` is a standard function block for calculating the logical OR operation. It performs an OR operation with up to four Boolean input values and outputs the result as a single Boolean value. The function block follows the IPO (Event-driven Processing) principle and is designed for use in control applications according to IEC 61131-3.
![OR_4_BOOL](OR_4_BOOL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. Upon this event, the values at the data inputs `IN1` to `IN4` are read, and the OR operation is calculated.

### **Event Outputs**

- **CNF**: Confirms completion of the operation. This event is triggered after the result is calculated and outputs the value to the data output `OUT`.

### **Data Inputs**

- **IN1**: Boolean OR input 1.
- **IN2**: Boolean OR input 2.
- **IN3**: Boolean OR input 3.
- **IN4**: Boolean OR input 4.

### **Data Outputs**

- **OUT**: Boolean result of the OR operation of all active inputs.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

When the event `REQ` occurs, the current values at the four Boolean inputs `IN1`, `IN2`, `IN3`, and `IN4` are read. The function block calculates the logical OR of these four values according to the following rule:

The result `OUT` is `TRUE` (1) if at least one of the four inputs is `TRUE`. The result is `FALSE` (0) only if all four inputs are `FALSE`.

The result `FALSE` (0) is `FALSE`. After the calculation, the confirmation event `CNF` is triggered, and the calculated value is carried over to the output `OUT`.

## Technical Features

- **Generic Block**: The block is marked as a generic block (`GEN_OR`). This allows it to be used as a basis for creating OR blocks with a different number of inputs.
- **Event-driven**: The operation is only executed upon an incoming `REQ` event, ensuring resource-efficient and deterministic processing in the control system.
- **Standard-compliant**: Conforms to the IEC 61131-3 classification for standard Boolean functions.

## State Overview

The function block has no internal state (memory-free). Its behavior is combinatorial and depends solely on the current values at the inputs at the time of the `REQ` event.

## Application Scenarios

- **Linking of Alarm Signals**: Combining multiple status or fault alarms where a single signal should trigger an action (e.g., "Stop machine if sensor A OR sensor B OR emergency stop is activated").
- **Logic in Safety Controllers**: Implementing OR gates in safety circuits.
- **Simplifying Control Logic**: As a clearly defined building block for structuring programs in function block diagrams (FBDs) or sequenced function charts (SFCs).
-

## ⚖️ Comparison with similar function blocks

- **`OR_2_BOOL` / `OR_8_BOOL`**: These blocks perform the identical logical OR operation, but with a different number of inputs (2 and 8, respectively). The choice of function block depends on the required number of signals to be combined. See: [OR_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_4.md)
- **`AND_4_BOOL`**: Performs a logical AND operation. The result is only `TRUE` if *all* inputs are `TRUE`.
- **`XOR_4_BOOL`**: Performs an exclusive OR (XOR) operation. The result is `TRUE` if there is an odd number of inputs, and `TRUE` if there is an odd number of inputs.

## Conclusion

The `OR_4_BOOL` is a basic, reliable, and standards-compliant function block for implementing four-input OR logic. Its event-driven, stateless operation makes it ideal for integration into larger, event-driven control applications according to IEC 61131-3. Its generic nature also makes it a suitable basis for library extensions.
