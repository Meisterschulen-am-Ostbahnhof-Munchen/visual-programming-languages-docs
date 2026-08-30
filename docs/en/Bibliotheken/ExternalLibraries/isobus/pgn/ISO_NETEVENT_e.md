# ISO_NETEVENT_e

![ISO_NETEVENT_e](./ISO_NETEVENT_e.svg)

* * * * * * * * * *

## Introduction

The global constant file `ISO_NETEVENT_e` defines an enumeration of event types for network management in an ISOBUS-compatible system. It provides named, integer constants that represent various state changes and events in the network, such as adding or removing devices or address conflicts. Using these constants improves the readability and maintainability of the source code.

## Interface Structure

ISO_NETEVENT_e` is a **global constant file** and not a function block. Therefore, it does not have event or data interfaces in the conventional sense. Instead, it provides a collection of constants (`VAR_GLOBAL CONSTANT`) that can be used system-wide.

### **Data Inputs**

*Not applicable.* This resource defines constants, not inputs.

### **Data Outputs**

*Not applicable.* This resource defines constants, not outputs.

### **Event Inputs**

*Not applicable.*

### **Event Outputs**

*Not applicable.*

### **Adapters**

*Not applicable.*

## Functionality

This file declares a set of constants of type `USINT` (Unsigned Short Integer, 8-bit). Each constant is assigned a unique numeric value and a descriptive name. These constants can be imported and used in other function blocks or programs to identify network events or query states, instead of using magic numbers in the code.

## Technical Details

- **Type:** All constants are of type `USINT`.
- **Initialization:** Each constant is initialized with a unique value (0 to 9) upon declaration.
- **Conditional Compilation:** The constants `Isonet_HsiActive` and `Isonet_HsiInactive` are marked as conditional constants (originally from C code). Their use may depend on the definition of a preprocessor symbol (`CCI_HSI`).
- **Package Assignment:** The constants are assigned to the package `isobus::pgn`, indicating their use in the context of ISOBUS protocol handling (Parameter Group Number).

## State Overview

*Not applicable.* Constants have no state.

## Application Scenarios

These constants are typically used in function blocks that:

1. Implement ISOBUS network management (address claiming, network management). 2. Monitor and respond to network events (e.g., address conflicts).
2. Manage the status of other network participants (controller applications, ECUs).
3. Provide diagnostic or logging functions that record network events.

## ⚖️ Comparison with similar building blocks

Unlike function blocks (FBs) or basic function blocks (BFBs), a global constant file does not contain any executable logic or algorithms. It is comparable to a header file in C/C++ or a `ENUM` in higher-level programming languages. Its sole purpose is to define immutable values for the entire application.

## Conclusion

The `ISO_NETEVENT_e` is an essential resource for the structured development of ISOBUS applications in the 4diac IDE. It standardizes the coding of network management events, promotes code clarity, and reduces errors that can arise from the use of undifferentiated numerical values. Its integration is particularly beneficial for complex, network-based control systems in the agricultural and mobile machinery sectors.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
