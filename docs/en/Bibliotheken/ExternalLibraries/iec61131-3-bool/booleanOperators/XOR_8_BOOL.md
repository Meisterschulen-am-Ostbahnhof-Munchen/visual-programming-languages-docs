# XOR_8_BOOL

<img width="1381" height="423" alt="image" src="https://github.com/user-attachments/assets/6d43c16c-0360-452c-bd8f-8caac2a5b590" />
* * * * * * * * * *
The function block `XOR_8_BOOL` is a generic block for calculating the logical exclusive OR (XOR) operation on up to eight Boolean input values. It complies with the IEC 61131-3 standard and is designed for use in the 4diac IDE. The block executes its operation in an event-driven manner and returns the result via a single Boolean output.
![XOR_8_BOOL](XOR_8_BOOL.svg)

- **REQ** (Normal Execution Request): This event triggers the calculation. It is associated with all eight data inputs (`IN1` to `IN8`).
- **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is linked to the data output `OUT`.
- **IN1** (BOOL): XOR input 1.
- **IN2** (BOOL): XOR input 2.
- **IN3** (BOOL): XOR input 3.
- **IN4** (BOOL): XOR input 4.
- **IN5** (BOOL): XOR input 5.
- **IN6** (BOOL): XOR input 6.
- **IN7** (BOOL): XOR input 7.
- **IN8** (BOOL): XOR input 8.
- **OUT** (BOOL): The result of the XOR operation of all active inputs.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block does not use adapters.

## Functionality

Upon the occurrence of the event `REQ`, the function block reads the values of all eight Boolean inputs (`IN1` to `IN8`). It then calculates the logical exclusive OR operation on all these input values. The result of this calculation is output at the data output `OUT`, and simultaneously, the confirmation event `CNF` is set to signal the completion of the operation.

The logical function can be described as follows:

OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5 XOR IN6 XOR IN7 XOR IN8`

An XOR (exclusive OR) operation returns `TRUE` (1) as the result if and only if there is an odd number of inputs connected, and `TRUE` (1) is the result. If there is an even number of inputs, the result is `FALSE` (0).

- **Generic Block:** The block is marked as a generic block (`GEN_XOR`), indicating its reusability and possible parameterization for other data types. In this specific instance, however, it is fixed to the data type `BOOL`.
- **Generic Block:** The block is marked as a generic block (`GEN_XOR`), which indicates its reusability and possible parameterization for other data types. In this specific instance, however, it is fixed to the data type `BOOL`.

- **Event-driven execution:** The operation is only performed upon an incoming `REQ` event, enabling efficient and deterministic control.

- **Fixed number of inputs:** The block provides exactly eight inputs. Unused inputs should be set to a defined logical value (e.g., `FALSE`).

The function block does not have an internal state in the sense of a memory. Its behavior is purely combinatorial and event-driven:

1. **Idle state:** Waits for the arrival of the `REQ` event.
2. **Computation state:** Upon `REQ`, all inputs are read and the XOR operation is performed.
3. **Output State:** The result is output to `OUT`, and the `CNF` event is generated. The block then returns to its idle state.
- **Parity Check:** Detects whether an odd number of signals (e.g., error messages, limit exceedances) are active in a group.
- **Toggle Logic:** Control where an action is only executed if exactly one of several possible control signals is active (e.g., selection between manual and automatic mode).
- **Basic Encryption and Coding Functions:** As a basic building block for simple cryptographic operations or error detection codes.
- **Comparison of Two or More States:** Determines whether at least one signal in a group differs from its expected state.
- **`OR_8_BOOL` / `AND_8_BOOL`:** These blocks calculate the logical OR and AND operations, respectively. Unlike XOR, OR (`TRUE`) returns true if *at least* one input is true, and AND (`TRUE`) returns true only if *all* inputs are true. XOR is more specific and responds to the *parity* (even/odd) of the true inputs.
- **`XOR` (with 2 inputs):** A standard XOR block with only two inputs. `XOR_8_BOOL` extends this functionality to up to eight inputs without the need to chain multiple blocks together. See: [XOR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_8.md)
- **Combinatorial Logic in SFC/ST:** The function could also be programmed directly in Structured Text (ST) (e.g., `OUT := IN1 XOR IN2 XOR ...;`). The advantage of this function block lies in its standardized, reusable, and graphically representable interface within FBD networks.

The `XOR_8_BOOL` is a specialized, reliable, and easy-to-use function block for logical XOR operations with up to eight inputs. Its event-driven architecture makes it ideal for integration into control-typical flowcharts in the 4diac IDE. It is particularly suitable for applications where the parity of signal groups is important and offers a clearly defined alternative to basic OR and AND operations.

[Following the previous sentence about the function block, the `XOR_8_BOOL` is not relevant to the context and should be omitted.] ---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
