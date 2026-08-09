# ISO_CAN_NODE

![ISO_CAN_NODE](./ISO_CAN_NODE.svg)

* * * * * * * * * *
## Introduction

The global constant file `ISO_CAN_NODE` defines a set of numeric constants for identifying CAN (Controller Area Network) nodes within a 4diac project. It serves to abstract and standardize node addresses, thereby improving the readability and maintainability of applications that operate with multiple CAN buses.
## Interface Structure

This element is a collection of global constants and does not have event- or data-flow-driven interfaces like a function block.

## **Data Constants**

The file defines the following constants of type `USINT` (Unsigned Short Integer):

| Name | Type | Initial Value | Comment |
| :------ | :---- | :---------- | :--------------- |
| `NODE1` | USINT | 0 | Identifier for CAN 1 |
| `NODE2` | USINT | 1 | Identifier for CAN 2 |
| `NODE3` | USINT | 2 | Identifier for CAN 3 |
| `NODE4` | USINT | 3 | Identifier for CAN 4 |
| `INVALID` | USINT | USINT#16#FF | Identifier for an invalid or unconfigured CAN node (decimal: 255) |

## Functionality

The constants are inserted into the code at compile time. Instead of using direct numerical values (such as `0` or `1`) in function blocks that control CAN communication, developers can use descriptive names (`NODE1`, `NODE2`, etc.). This makes the code more intuitive and facilitates future modifications, as the actual addresses are managed centrally in one location.

The value `INVALID` (255) represents a reserved value, typically used to indicate an uninitialized, faulty, or non-existent node.

## Technical Details

* **Packet Mapping:** The constants are mapped to the package `isobus::pgn`, indicating use in the context of ISOBUS (ISOBUS, agricultural machinery) and Parameter Group Numbers (PGN). * **Data Type:** All constants are of type `USINT`, which allows a value range from 0 to 255 and is common for CAN node addresses.
* **Hexadecimal Notation:** The value for `INVALID` is defined in hexadecimal notation (`16#FF`), which corresponds to the decimal number 255.

## State Overview

Since these are static constants, no state machine exists.

## Application Scenarios

* **Multi-CAN Systems:** In controllers that communicate with multiple independent CAN buses (e.g., a main bus and a drive bus) to uniquely address the buses.
* **ISOBUS Applications:** For configuring virtual terminals (VTs), task controllers (TCs), or other devices in an agricultural ISOBUS network.
* **Error Handling:** The constant `INVALID` can be used as a return value or initial value in function blocks to indicate that no valid CAN node has been selected or detected.

## ⚖️ Comparison with Similar Function Blocks

* **Direct Values:** The alternative approach would be the direct use of numeric literals (0, 1, 2, ...) in the code. Using `ISO_CAN_NODE` is superior to this approach in terms of code quality and maintainability.
* **Enumerations (ENUM):** In some programming languages or function block types, similar constructs could be defined as enumerations. Global constants are a simple and widely used means of implementing this pattern in IEC 61499.

## Conclusion

The `ISO_CAN_NODE` constant file is a simple yet valuable tool for the structured development of CAN-based control applications in 4diac. It promotes clean, self-explanatory code and centralizes configuration data, reducing errors and simplifying adjustments. Its use is particularly recommended in projects with multiple CAN nodes or in ISOBUS environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
