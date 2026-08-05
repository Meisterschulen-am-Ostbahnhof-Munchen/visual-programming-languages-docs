# logiBUS_PI_S

* * * * * * * * * *
## Introduction
The function block `logiBUS_PI_S` is a structured data type used to configure a digital input (PI - likely "Peripheral Input") within the logiBUS framework. It defines the necessary parameters to address a specific physical pin of an I/O module or controller. This data type is typically used as an input parameter for corresponding I/O function blocks.

## Interface Structure
As a data type (STRUCT), `logiBUS_PI_S` does not have event-driven interfaces, but defines only data fields.

### **Data Inputs**
Not applicable – this is a data type, not an executable function block.

### **Data Outputs**
Not applicable – this is a data type, not an executable function block.


### **Internal Structure (Variables)**

The structure consists of a single member:

* **`Pin`** (USINT, initial value: 255): This variable specifies the hardware pin number to be used as a digital input. The data type `USINT` (Unsigned Short Integer) allows values from 0 to 255. The default initial value of 255 is often used to represent an inactive or undefined state.

### **Adapter**
Not present.

## Functionality
The data type `logiBUS_PI_S` functions purely as a configuration container. It encapsulates the information about which physical pin should be addressed. The actual logic for querying the pin state lies within the function blocks that expect a variable of this type as an input (e.g., `logiBUS_PI` or similar). These blocks read the value from the `Pin` field and use it to control the corresponding hardware interface.

## Technical Features
* **Initial Value:** The initial value of 255 for `Pin` is common practice to indicate an unconfigured or faulty state, as pin numbers in practice are usually significantly lower.

* **Package Assignment:** This data type is part of the `logiBUS::io::PI` package, which assigns it to the peripheral input category within the logiBUS library.

* **Type Hash:** The attribute `eclipse4diac::core::TypeHash` with an empty value indicates that an automatically generated hash is used for type compatibility within the system.

## State Overview
Since this is a passive data type, there is no state machine or active states.

## Application Scenarios
This structured data type is used to centralize and ensure type safety in the configuration of digital input channels in control applications with logiBUS-compatible hardware. Typical applications include:

* Configuration of push-button, switch, or sensor signals (e.g., limit switches, light barriers).

* Parameterization of function blocks that read digital inputs in a distributed I/O system (such as logiBUS).

* Simplification of code reuse and readability, as the pin configuration is bundled in a named structure.


## ⚖️ Comparison with Similar Components

* **Simple Data Types (e.g., USINT directly):** Using a structured `logiBUS_PI_S` variable is preferable to directly using a `USINT` variable for the pin number because it is semantically clearer and can be more easily extended when the configuration is expanded (e.g., to include filter time or inversion) without having to change all call points.

* **logiBUS_PO_S (Digital Output):** A complementary data type `logiBUS_PO_S` for configuring digital outputs (PO - Peripheral Output) with an identical or very similar structure likely exists.


* **logiBUS_PO_S (Digital Output):** ## Conclusion

The `logiBUS_PI_S` data type is a fundamental, specific configuration block for connecting digital input signals in logiBUS-based IEC 61499 applications. Its simple, single-parameter structure enables clear and centralized hardware configuration and forms the basis for the corresponding functionality in the executing I/O function blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```