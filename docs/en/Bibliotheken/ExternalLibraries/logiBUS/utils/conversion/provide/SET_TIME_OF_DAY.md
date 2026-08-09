# SET_TIME_OF_DAY

![SET_TIME_OF_DAY](./SET_TIME_OF_DAY.svg)

* * * * * * * * * *
## Introduction

The function block `SET_TIME_OF_DAY` is used to write a time of day value provided via the data input `IN` to a target variable `OUT`, which is declared as an InOut variable. The block is implemented as a simple FB (SimpleFB) and complies with the IEC 61499-1 standard.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Normal execution request (bound to `IN` and `OUT`) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Execution confirmation (bound to `OUT`) |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| IN | TIME_OF_DAY | The time of day value to be written |

### **Data Outputs**

No explicit data outputs are available. The target value is stored as an InOut variable.

### **Adapters**

None.

## Functionality

When an event arrives at input `REQ`, the algorithm `REQ` is executed:

- The value of `IN` is assigned to the InOut variable `OUT`: `OUT := IN`.
- After successful assignment, the event `CNF` is output to acknowledge the completion of the operation.

## Technical Details

- The target variable `OUT` is declared as an **InOut variable**. This means that it serves as both input and output and must be passed externally by reference. The value of `OUT` is overwritten by the assignment.
- The function block contains only one state and one algorithm, ensuring very simple, deterministic execution.
- The data type `TIME_OF_DAY` follows the IEC 61499 data type definition for times of day (e.g., `TOD#12:30:00`).

## State Overview

The function block has a single state:

- **REQ**: Activated on the event `REQ`. After the algorithm is executed, `CNF` is sent, and the state remains active (no state change).

| State | Action | Output Event |
|---------|--------|------------------|
| REQ | Algorithm `REQ` | CNF |

## Application-Specific Scenarios

- **Setting a Global Time of Day**: In a controller, the current time can be retrieved from a higher-level system and written to a central InOut variable.
- **Configuring Time Parameters**: A user enters a time of day via an HMI, which is then written to a configuration variable using `SET_TIME_OF_DAY`.
- **Passing Time Values**: If a time value needs to be read from a source and passed to multiple subsequent function blocks, this function block can serve as a simple write access.

## Comparison with Similar Function Blocks

- **MOVE for Elementary Types**: Similar function blocks exist for basic types such as `BOOL`, `INT`, `REAL`, etc. `SET_TIME_OF_DAY` is the specific variant for `TIME_OF_DAY`.
- **Standard MOVE Blocks**: Many IEC 61499 libraries contain generic function blocks such as `MOVE` or `ASSIGN`. The block presented here is a dedicated and type-safe implementation for `TIME_OF_DAY`.

## Conclusion

SET_TIME_OF_DAY` is a minimal yet useful function block for overriding a `TIME_OF_DAY` InOut variable. Its simple structure makes it reliable and easy to understand. It can be effectively used in combination with other function blocks in timing and configuration applications.
