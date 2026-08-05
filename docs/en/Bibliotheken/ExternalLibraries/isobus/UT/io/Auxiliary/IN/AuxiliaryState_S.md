# AuxiliaryState_S
* * * * * * * * * *
## Introduction
The data type `AuxiliaryState_S` is a structured data structure (struct) that represents the state of an auxiliary input. It is used in the context of the ISOBUS interface (ISO 11783) for communication in agricultural and forestry machinery. This data type encapsulates both the actual value of the input and control information for its cyclic transmission.
## Interface Structure
`AuxiliaryState_S` is a structured data type (struct) and therefore does not have event or adapter interfaces in the conventional sense of a function block. Its structure consists of the following two data fields:
### **Data Inputs**
*(Not applicable – This is a data type, not a function block)*

### **Data Outputs**
*(Not applicable – This is a data type, not a function block)*

### **Structured Data Fields**

| Name | Data Type | Initial Value | Comment |

| :--- | :--- | :--- | :--- |

| `value` | `USINT` (0...255) | 255 | Represents the value of the auxiliary input. |

| `bCyclic` | `BOOL` | `TRUE` | Controls the cyclic transfer. When set to `FALSE`, the message is not repeated every 200 ms. |

## Functionality
This data type serves as a container for information about an auxiliary input. The field `value` stores the actual, read value. The initial value of 255 can represent an invalid or undefined state. The field `bCyclic` is a control flag that influences the transmission behavior in an ISOBUS network. According to the comment, when `bCyclic = TRUE` is set, the corresponding message is sent cyclically every 200 milliseconds by default. If `bCyclic` is set to `FALSE`, this regular repetition is omitted, which can reduce network traffic if the value does not change frequently.

```
## Technical Features
* **ISOBUS Context:** This data type is specifically designed for ISOBUS communication (package `isobus::UT::io::Auxiliary::IN`).
* **Cycle Control:** The integrated cyclic control (`bCyclic`) is a characteristic feature that takes bus communication efficiency into account.
* **Initial Values:** Both fields have defined initial values (`value=255`, `bCyclic=TRUE`), ensuring deterministic initialization.

## State Overview
*(Not applicable – This is a passive data type without state machines.)*

## Application Scenarios

This struct is typically used as a data input or output in function blocks (FBs) that process or control ISOBUS auxiliary inputs. Examples include:

* Function blocks (FBs) for reading the state of switches, potentiometers, or sensors configured as auxiliary inputs.
* FBs that process auxiliary input values and forward them to other system components.
* FBs that determine whether a value needs to be updated and sent based on the `bCyclic` flag.

## ⚖️ Comparison with similar function blocks
As a pure data type, a direct comparison with function blocks is not meaningful. Within the ISOBUS data types, it could be compared to simpler data types such as a pure `USINT` for the value. The advantage of `AuxiliaryState_S` lies in the extension with the meta-information for transmission control (`bCyclic`), which enables higher integration and more efficient communication in the ISOBUS network.

## Conclusion

`AuxiliaryState_S` is a specialized, structured data type for ISOBUS communication. It offers an elegant way to encapsulate not only the value of an auxiliary input, but also an important protocol attribute for its cyclic transmission. Its use promotes the clarity and maintainability of applications that implement ISOBUS I/O functionalities.
