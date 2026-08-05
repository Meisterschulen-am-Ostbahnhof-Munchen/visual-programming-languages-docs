# ButtonActivationCode_S
* * * * * * * * * *
## Introduction
The data type `ButtonActivationCode_S` is a structured data structure (struct) used to configure the activation of a button in a control system. It defines an activation code and a control flag for the repeat logic. This data type is part of the `isobus::UT::io::Button` package.
## Interface Structure
Since this is a data type and not a function block, there are no event or adapter interfaces. The structure consists exclusively of data fields.
### **Data Inputs**
*(Not applicable - This is a data type, not a function block)*

### **Data Outputs**
*(Not applicable - This is a data type, not a function block)*

### **Structured Data Fields**
The following fields form the internal structure of the data type `ButtonActivationCode_S`:

| Name | Data Type | Initial Value | Comment |

| :------- | :------- | :--------- | :-------- |

| `code` | `USINT` | 255 | Defines the specific activation code for the button. |

| `bCyclic`| `BOOL` | TRUE | Controls the cyclic behavior. If set to `FALSE`, activation is not repeated every 200 ms. |

## Functionality
The structure `ButtonActivationCode_S` serves as a container for configuration data.

* The field `code` uniquely identifies the button within the system. The default value of 255 can be interpreted as an inactive or undefined state.
* The field `bCyclic` determines the timing behavior when the button is continuously pressed. With `TRUE` (default), the corresponding event is repeatedly triggered at a fixed interval (e.g., every 200 ms). With `FALSE`, the event is triggered only once when the button is pressed (and possibly released), even if the button is held down.
* ## Technical Features
* **Initial Values:** Both fields of the structure have predefined initial values, ensuring reliable initialization.
* **Comment:** The field `bCyclic` contains a helpful comment that explains the specific effect (`do not repeat every 200ms`) directly in the declaration.
* **Type Hash:** The data type contains an attribute (`eclipse4diac::core::TypeHash`) used for type checking and versioning within the 4diac environment.

## State Overview
*(Not applicable - This is a static data type without state machines.)*

## Application Scenarios

This struct is typically used as an input or configuration parameter for function blocks that process button inputs, e.g.:

* In a human-machine interface (HMI) for configuring softkeys.
* * In machine controls for parameterizing physical control buttons.
* Wherever a distinction needs to be made between a single and repeated action upon button press.

## ⚖️ Comparison with similar function blocks
As a pure data type, `ButtonActivationCode_S` is comparable to other structured data types (STRUCTs) in 4diac, such as `DATE_AND_TIME`. Its specific purpose is to bundle the parameters relevant for button control (`code` for identification, `bCyclic` for timing behavior) into a single, reusable unit.

## Conclusion
The data type `ButtonActivationCode_S` is a simple yet essential structure for the standardized configuration of button behavior in 4diac-based control applications. By encapsulating the code and the repetition flag, it promotes code reusability and readability. The integrated initial values and clear comments contribute to robustness and ease of use.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
