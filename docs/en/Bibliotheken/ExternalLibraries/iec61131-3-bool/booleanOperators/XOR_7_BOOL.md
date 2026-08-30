# XOR_7_BOOL

<img width="1378" height="391" alt="image" src="https://github.com/user-attachments/assets/731f9ca4-e163-4c46-8eda-5b826a199574" />
* * * * * * * * * *
## Introduction

The function block `XOR_7_BOOL` is a generic block for calculating the logical exclusive OR (XOR) operation. It processes seven Boolean input signals and returns the result of the XOR operation as a Boolean output signal. The block complies with the IEC 61131-3 standard and is designed for use in control applications where odd parity checking or logical antivalence across multiple signals is required.
![XOR_7_BOOL](XOR_7_BOOL.svg)
## Interface Structure

### **Event Inputs**

- **REQ (Normal Execution Request):** This event triggers the execution of the function block. Upon its arrival, all seven data inputs (`IN1` to `IN7`) are read and the XOR calculation is performed.

### **Event Outputs**

- **CNF (Execution Confirmation):** This event signals the completion of the calculation. It is output along with the calculated data output `OUT`.

### **Data Inputs**

- **IN1 (XOR input 1):** Boolean input 1.
- **IN2 (XOR input 2):** Boolean input 2.
- **IN3 (XOR input 3):** Boolean input 3.
- **IN4 (XOR input 4):** Boolean input 4.
- **IN5 (XOR input 5):** Boolean input 5.
- **IN6 (XOR input 6):** Boolean input 6.
- **IN7 (XOR input 7):** Boolean input 7.

### **Data Outputs**

- **OUT (XOR result):** Boolean result of the XOR operation of all seven inputs.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

When the event `REQ` occurs, the block performs the logical XOR operation on all seven Boolean inputs `IN1` to `IN7`. The result `OUT` is `TRUE` (1) if and only if an odd number of the inputs have the value `TRUE`. If the number of `TRUE` inputs is even (0, 2, 4, 6), the result is `FALSE` (0).

Mathematically expressed: `OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5 XOR IN6 XOR IN7`

Immediately after the calculation, the completion event `CNF` is triggered along with the valid result `OUT`.

## Technical Features

- **Generic Block:** The block is implemented as a generic function block (`GEN_XOR`), which allows for flexible reuse in different contexts.
- **Fixed Number of Inputs:** Unlike blocks with a variable number of inputs, this block has exactly seven fixed inputs.
- **Event-Driven Execution:** The operation is triggered exclusively by an incoming event (`REQ`), which enables deterministic and energy-efficient processing in the real-time system.

## State Overview

The function block does not have an internal state in the sense of a memory. Its behavior is purely combinatorial and depends solely on the current values at the inputs at the time of the ``REQ`` event. After the output of ``CNF``, the block remains in a waiting state until the next ``REQ`` event.

## Application Scenarios

- **Parity Check:** Monitoring whether an odd number of sensors (e.g., limit switches, light barriers) are in a specific state (``TRUE``).
- **Safety-Critical Logic:** In safety circuits where an antivalence condition across multiple safety devices is required.
- **Control Logic:** Implementation of special logic operations in sequence controls or logic controllers that require an XOR function with exactly seven operands.

## ⚖️ Comparison with similar building blocks

- **`XOR` (2 inputs):** The standard XOR block only combines two inputs. To combine seven signals, this block would have to be nested multiple times, which reduces program readability. `XOR_7_BOOL` offers a direct and clear solution. See: [XOR_7](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_7.md)
- **`GEN_XOR` (Generic, n inputs):** The underlying generic block `GEN_XOR` can be instantiated with a variable number of inputs. `XOR_7_BOOL` is a specific, pre-configured instance with seven inputs that can be used directly without having to parameterize the number of inputs.
- **`PARITY_CHECK`:** A pure parity check block could deliver similar results, but is often conceptually designed for error detection in data streams, whereas `XOR_7_BOOL` serves as a general-purpose logical operator in control logic.

## Conclusion

The `XOR_7_BOOL` function block is a specialized and efficient building block for the logical anti-valence operation of seven Boolean signals. Its event-driven, stateless operation and clear interface make it ideal for use in structured IEC 61131-3-based control programs where such a fixed operation is required. It simplifies programming compared to nesting multiple two-input XOR blocks and provides a ready-to-use, reliable component.
