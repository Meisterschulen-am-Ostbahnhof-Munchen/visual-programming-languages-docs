# F_NOT_BOOL
<img width="1572" height="241" alt="image" src="https://github.com/user-attachments/assets/b637a4d2-b75e-4f3d-b5a9-99b2c93d33eb" />
* * * * * * * * * *
## Introduction
The function block `F_NOT_BOOL` implements the logical NOT function (negation) for the data type `BOOL`. It inverts the logical state of a binary input signal. This block belongs to the standard bit operators according to IEC 61131-3 and is designed for use in control applications where logical operations are required.
![F_NOT_BOOL](F_NOT_BOOL.svg)
## Interface Structure
### **Event Inputs**
* **REQ (Service Request)**: This event triggers the execution of the logical negation. Upon its arrival, the current value at data input `IN` is processed, and the result is output to `OUT`.

### **Event Outputs**
* **CNF (Confirmation of Requested Service)**: This event signals the completion of the operation. It is generated simultaneously with the output of the calculated value at data output `OUT`.

### **Data Inputs**
* **IN (Input)**: Data type `BOOL`. This is the binary input value to be negated. Valid values are `TRUE` (1) or `FALSE` (0).

### ### **Data Outputs**
* **OUT (Output)**: Data type `BOOL`. This is the result of the logical negation. The output value is the logical opposite of the input value `IN`.

### **Adapters**
This function block does not use any adapter interfaces.

## Operation
The operation is deterministic and simple: Upon each occurrence of a `REQ` event, the function block reads the current value at the data input `IN`. It then calculates the logical negation and writes the result to the data output `OUT`. Simultaneously, a `CNF` event is generated to signal the completion of the operation.

The logical operation can be described by the following table:

| Input (IN) | Output (OUT) |

| :----------- | :------------ |

| FALSE (0) | TRUE (1) |

| TRUE (1) | FALSE (0) |

## Technical Features
* **Standard Compliance**: The function block is classified as a standard function according to IEC 61131-3.
* **I/O Delay**: The processing of `REQ` up to the output of `CNF` and `OUT` takes place within one cycle of the executing resource. There are no inherent delays.
* **Initialization**: The output variables are set to their default values (`FALSE` for `BOOL`) during the initialization of the function block.

## State Overview
The function block does not have an internal state in the sense of a state machine. Its behavior is purely combinatorial and depends solely on the current input values when triggered by a `REQ` event. No previous values are stored.

## Application Scenarios
* **Sensor Signal Inversion**: Conversion of an active low sensor signal (e.g., "Button pressed" = FALSE) into an active high signal for further logic.
* **Safety Logic**: Generation of a block signal from an enable signal or vice versa.
* **Control Logic**: As a fundamental building block in more complex logical expressions and conditions within sequential control systems.
* **Status Display**: Inversion of an internal status for controlling a lamp (e.g., "Machine Ready" = TRUE, but "Fault Lamp Lights Up" if FALSE).

## ⚖️ Comparison with Similar Function Blocks
Within the `iec61131::bitwiseOperators` library, other basic logical operators exist, such as `F_AND`, `F_OR`, and `F_XOR`. Unlike these function blocks, which combine two or more inputs, `F_NOT_BOOL` has only a single data input. Its function is essential for completing logical expressions and performing direct inversions. Implementing it as a standalone function block (rather than as an integrated operator within an expression) improves clarity in graphical programming environments like FBD. See: [F_NOT](../../../StandardLibraries/iec61131-3/bitwiseOperators/F_NOT.md)

## Conclusion
The `F_NOT_BOOL` function block is an essential, robust, and easy-to-use basic building block for binary logic in IEC 61131-3-based control programs. Its clear interface and deterministic operation make it the first choice for inverting Boolean signals in automation technology.