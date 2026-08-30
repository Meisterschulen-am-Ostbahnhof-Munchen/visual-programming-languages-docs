# IDs

![IDs](./IDs.svg)

* * * * * * * * * *
## Introduction

The global constant package `IDs` provides a collection of predefined, immutable values (constants) that can be used within function blocks of the IEC 61499 runtime environment. These constants primarily serve to improve the readability and maintainability of the source code by replacing magic numbers with meaningful identifiers. The package is defined in the namespace `isobus::UT::Q::const`.
## Interface Structure

Because it is a package of global constants, it does not have event- or data-flow-based interfaces in the conventional sense of a function block. The constants are static and can be referenced directly by their names.

### **Event Inputs**

Not present.

### **Event Outputs**

Not present.

### **Data Inputs**

Not present.

### **Data Outputs**

Not present.

### **Adapters**

Not present.

## Functionality

The constants are replaced by their predefined values when the application is compiled. They behave like literals but have a semantic name. The constants included in the package are:

- `ID_NULL`: Represents an invalid or uninitialized identifier (ID) of type `UINT` with the hexadecimal value `16#FFFF` (decimal 65535).
- `ID_OFF`: Represents a special identifier value that signals "Off" or "Inactive," of type `UINT` with the value `16#0` (decimal 0).
- `GLOBAL`: An identifier of type `USINT` with the value `16#FF` (decimal 255), typically used for global or broadcast addressing.
- `OFF`: A simple status value of type `USINT` for the "Off" state with the value `16#0` (decimal 0).

## Technical Features

- **Typing:** The constants are strongly typed (`UINT`, `USINT`). This ensures type safety when using them in assignments and comparisons.
- **Initial Value:** Each constant is assigned a fixed, unchanging initial value upon declaration.
- **Namespace:** The constants are encapsulated in the package `isobus::UT::Q::const`, preventing name conflicts with other libraries.

## State Overview

Since these are static, constant values, there is no state machine.

## Application Scenarios

- **Initialization:** Assigning a defined initial value (e.g., `ID_NULL`) to variables that will later receive a valid ID.
- **Comparison:** Checking whether a received or read ID corresponds to a specific value (e.g., `IF receivedID = IDs.ID_OFF THEN ...`).
- **Parameterization:** Using constants as meaningful parameters in function blocks instead of direct numerical values.
- **Command and Status Values:** Using `OFF` and `GLOBAL` to control processes or address devices in a network.

## ⚖️ Comparison with Similar Blocks

Unlike function blocks (FBs) with algorithms and event handling, this package simply provides data. It is comparable to:

- **ENUM Data Types:** While ENUMs define a list of named integer values of a type, this package defines individual, loose constants of various types.
- **#define-Preprocessor Directives (in C):** Both replace a name with a value. However, the constants in `IDs` are type-safe and manageable in the 4diac IDE.

## Conclusion

The global constant package `IDs` is a simple yet useful tool for structured programming in 4diac. It improves code quality, reduces typos in numeric values, and makes the programmer's intent explicit. Its use is especially recommended in larger projects or when working with protocols like ISOBUS, where special identifier values are common.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
