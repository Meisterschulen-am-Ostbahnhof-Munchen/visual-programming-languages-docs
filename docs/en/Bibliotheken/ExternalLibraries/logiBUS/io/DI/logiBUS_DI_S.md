# logiBUS_DI_S

* * * * * * * * * *
## Introduction
The function block `logiBUS_DI_S` is a structured data type (struct) used to configure a digital input (DI) within the logiBUS framework. It defines the basic parameters necessary to control a physical or logical input point on a logiBUS-compatible I/O system. This data type is typically used as input for specific I/O function blocks.

## Interface Structure
As a structured data type, `logiBUS_DI_S` does not have event or adapter interfaces in the conventional sense. Its structure consists of a single data element.

## **Data Inputs**
The structure itself represents the configurable data inputs. It is passed as a whole to a higher-level function block.

| Name | Data Type | Initial Value | Comment |

| :--- | :--- | :--- | :--- |

| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Defines the number of the input pin or channel to be addressed. |

### **Data Outputs**
This data type has no data outputs of its own.

## Functionality
The data type `logiBUS_DI_S` is purely a data storage structure. Its function is limited to storing the value of the member `Pin`. The initial value `255` often serves as a default or invalid value (e.g., "not configured"). A specific I/O function block that expects this struct as an input reads the `Pin` value and uses it to perform hardware addressing for the digital input.

## Technical Details
* **Data type `USINT`:** The use of a `USINT` (0...255) for the pin suggests that up to 256 different input channels per device or module can be addressed.

* **Initial value 255:** This value is outside the typical usable range (0...n, where n<255) and can be interpreted by the application logic or driver as an indicator of a missing configuration.

* **StructuredType:** As `StructuredType`, this block is not an executable function block, but a pure data type used in the declaration of variables and interfaces of other function blocks.

## State Overview
Since it is a passive data type, `logiBUS_DI_S` does not have a state machine.

## Application Scenarios

* **I/O Block Configuration:** This struct primarily serves as an input parameter for function blocks such as `logiBUS_DI` or similar, which perform the actual reading operation from a digital input.

* **Parameterization via Networks:** The structure can easily be instantiated and configured (`Pin` number set) in higher-level controllers (e.g., a PLC) and passed on to subordinate I/O nodes or driver blocks.


* **Structured Programming:** Enables clean encapsulation of configuration data for digital inputs, increasing code reusability and readability.

## ⚖️ Comparison with Similar Building Blocks
* **Simple `USINT` Variable:** Instead of a struct, a `USINT` variable could be used directly. However, the struct offers semantic clarity (the name `logiBUS_DI_S` describes its purpose) and is easier to extend if further configuration parameters (such as filter time or inversion) need to be added in the future.

* **Device-Specific Structs:** Within the logiBUS ecosystem, similar structs could exist for other functions (e.g., `logiBUS_DO_S` for digital outputs, `logiBUS_AI_S` for analog inputs). This would enable a uniform configuration philosophy across different I/O types.


``` ## 🛠️ Related exercises

* [Uebung_003a_AX_sub](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003a_AX_sub.md)
* [Uebung_003a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003a_sub.md)
* [Uebung_003b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003b_sub.md)
* [Uebung_003c_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003c_sub.md)
* [Uebung_003c_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003c_sub_AX.md)
* [Uebung_033_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_033_sub.md)

## Conclusion
The `logiBUS_DI_S` is a basic and specific configuration block for the logiBUS I/O architecture. As a structured data type, it offers a standardized and clear method for defining the target address (pin) for a digital input. Its strength lies in its simplicity and its readiness for future extensions, making it a useful component for the structured configuration of fieldbus systems in 4diac FORTE.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]