# ISOUSERHOME_e
![ISOUSERHOME_e](./ISOUSERHOME_e.svg)
* * * * * * * * * *
## Introduction
The function block `ISOUSERHOME_e` is a **constant definition** (GlobalConstants) and not an executable function block in the traditional sense. It defines an enumeration of integer constants used to describe the network origin or destination of an event or message in an ISOBUS context (ISO 11783). These constants are typically used in other function blocks to identify the source or receiver of data within a controller network.
## Interface Structure
Because it is a constant definition, `ISOUSERHOME_e` does not have event- or dataflow-based interfaces like a standard function block. Instead, it provides named constants.

## **Event Inputs**
Not present.

### **Event Outputs**
Not present.

### **Data Inputs**
Not present.

### **Data Outputs**
Not present.

#### **Adapters**
Not present.

## Functionality
This block defines four symbolic constants of type `SINT` (short integer):

* `intern` (value: 0): Identifies an internal control function (CF) or an internal user within a device or logical unit.
* `network` (value: 1): Identifies an external CF or an external user on the network.
* `thisMember` (value: 2): Specifies that an event or message is intended for this specific internal CF or user.
* `notdef` (value: -1): Indicates that the value is invalid or undefined.

These constants can be imported and used throughout the application to make code more readable and maintainable, instead of directly using magic numbers (such as 0, 1, 2, -1).

## Technical Details
* **Type:** `GlobalConstants` according to IEC 61499-1.
* **Data Range:** The constants are of type `SINT` (8-bit signed integer).
* **Package:** The block is part of the `isobus::pgn` package, indicating its use in the context of ISOBUS Parameter Group Numbers (PGNs).

## State Overview
Not applicable, as this is a static constant definition without state machines or behavior.

## Application Scenarios
These constants are primarily used in ISOBUS-compliant control systems in agricultural machinery, for example, in tractors and their implements. Typical applications include:

* **Message Filtering:** A receiver block can use the `ISOUSERHOME_e` value to determine whether an incoming ISOBUS message is intended for its own device (`thisMember`), another device on the network (`network`), or for internal processing (`intern`).
* **Message Construction:** A sender block can set this value to identify the intended recipient of a sent message.
* **Status Feedback:** A block can return the status `notdef` if the origin or destination of a message cannot be determined.
* **Message Construction:** ## ⚖️ Comparison with Similar Building Blocks
* **`E_SR` or `E_RESTART`:** These are executable basic function blocks with event logic. `ISOUSERHOME_e`, on the other hand, is a pure data definition without logic.
* **User-Defined Data Types (DT):** Similar to a structured data type (STRUCT) or an enumeration (ENUM), `ISOUSERHOME_e` is used to encode semantic meaning. The difference lies in the IEC 61499 specification: `GlobalConstants` are intended for immutable values that are valid project-wide.
* **Direct Use of Numeric Values:** Using `ISOUSERHOME_e.intern` in the code is significantly more meaningful and less error-prone than directly using the number `0`.

## Conclusion
`ISOUSERHOME_e` is an essential auxiliary construct for developing clear and maintainable ISOBUS applications in 4diac. By providing meaningful constant names, it abstracts from the underlying numeric values, thus improving the readability and robustness of the system design. It is a data-level component that supports the communication logic in higher-level function blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]