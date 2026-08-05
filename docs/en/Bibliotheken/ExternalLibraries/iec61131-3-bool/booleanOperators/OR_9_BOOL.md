# OR_9_BOOL

<img width="1370" height="457" alt="image" src="https://github.com/user-attachments/assets/8371b695-a421-40f0-9019-239b40fdc3ee" />

* * * * * * * * * *
## Introduction
The function block `OR_9_BOOL` is a standardized building block according to IEC 61131-3 for calculating the logical OR operation. It performs the OR operation via nine separate Boolean inputs. The block follows the event-driven execution model of the 4diac IDE: The calculation is triggered by an incoming event, and the result is output along with an acknowledgment event.

![OR_9_BOOL](OR_9_BOOL.svg)

## Interface Structure
### **Event Inputs**
* **REQ**: Triggers the execution of the function block. Upon arrival of this event, all nine input values (`IN1` to `IN9`) are read, and the OR operation is calculated.

### **Event Outputs**

* **CNF**: This event is generated after the calculation is complete. It signals that the result is valid and available at the data output `OUT`.


### **Data Inputs**
* **IN1** (BOOL): OR input 1.
* **IN2** (BOOL): OR input 2.
* **IN3** (BOOL): OR input 3.
* **IN4** (BOOL): OR input 4.
* **IN5** (BOOL): OR input 5.
* **IN6** (BOOL): OR input 6.
* **IN7** (BOOL): OR input 7.
* **IN8** (BOOL): OR input 8.
* **IN9** (BOOL): OR input 9.

### **Data Outputs**
* **OUT** (BOOL): Result of the logical OR operation of all nine inputs. The output is `TRUE` (1) if at least one of the inputs is `TRUE`. It is only `FALSE` (0) if all nine inputs are `FALSE`.

### **Adapter**
This function block has no adapter interfaces.

## Operation
The `OR_9_BOOL` block operates according to the following algorithm:

1. **Trigger**: The incoming event `REQ` activates the block.

2. **Input Collection**: The current values of all nine Boolean inputs (`IN1` to `IN9`) are read.

3. **Calculation**: The logical OR function is applied to the input values. The operation can be described as `OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5 OR IN6 OR IN7 OR IN8 OR IN9`.

4. **Output**: The calculated result is set to the data output `OUT`.

5. **Acknowledgement**: Immediately after the output is set, the acknowledgement event `CNF` is generated to inform downstream blocks about the availability of the new result.

## Technical Features
* **Generic Function Block**: The block is implemented as a generic function block (attribute `eclipse4diac::core::GenericClassName` is set to `'GEN_OR'`). This means it can serve as the basis for deriving similar OR blocks with a different number of inputs.

* **Standard Compliance**: It is explicitly classified as a standardized Boolean function according to IEC 61131-3.

* **Deterministic Behavior**: The execution time is constant and predictable, as it is a simple logical operation.

## State Overview

The block has no internal state or memory. Its behavior is purely combinatorial and depends solely on the current input values at the time of the `REQ` event. Previous calculations have no influence on the current result.

## Application Scenarios

* **Monitoring Logic**: Combination of multiple error or status messages (e.g., from nine sensors), where even a single message (`TRUE`) triggers a collective alarm message (`OUT = TRUE`).

* **Enable Logic**: In safety circuits, where one of several possible enable conditions is sufficient to start a process step.

* **Simplification of Logic Networks**: Replaces multiple cascaded two-input OR gates, improving clarity in a function block diagram (FBD).


* ## ⚖️ Comparison with similar building blocks

* **`OR_2_BOOL`, `OR_4_BOOL` etc.**: These blocks offer the same OR functionality, but for a smaller number of inputs (2, 4, ...). `OR_9_BOOL` is optimized for applications with nine signals to be combined. See: [OR_9](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_9.md)

* **`AND_9_BOOL`**: Performs the logical AND operation. The result is only `TRUE` if *all* inputs are `TRUE`, unlike OR, where *at least one* input must be `TRUE`.


* **`XOR_9_BOOL`**: Calculates the exclusive OR (antivalence). The result is `TRUE` if there is an odd number of inputs, resulting in `TRUE`.

## Conclusion
The `OR_9_BOOL` is a robust and easy-to-use standard block for the logical OR operation of nine Boolean signals. Its event-driven, stateless architecture makes it a reliable and efficient component for control and monitoring logic in 4diac-based automation systems. Using this specialized block instead of a cascade of basic gates improves the readability and maintainability of the application code.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```