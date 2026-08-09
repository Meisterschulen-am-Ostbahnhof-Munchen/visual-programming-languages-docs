# sequence

![sequence](./sequence.svg)

* * * * * * * * * *
## Introduction

The global constants file `sequence` defines a set of predefined constants that can be used in conjunction with sequence function blocks. It provides symbolic names for states and a special time value to improve the readability and maintainability of IEC 61499 applications. The constants are organized in the package `logiBUS::utils::sequence::const`.
## Interface Structure

Global constants do not have event or data interfaces in the conventional sense of a function block. Instead, they are exposed as named values throughout the project. Their structure is a collection of variable declarations with fixed initial values.

## **Data Inputs**

*Not applicable.* Global constants are not inputs, but rather fixed values.

### **Data Outputs**

*Not applicable.* Global constants are not outputs, but rather fixed, predefined values.

#### **Adapters**

*Not applicable.*

## Functionality

This file defines constants that are replaced by their values at compile time. They can be referenced in any function block within the project, provided the corresponding namespace (`logiBUS::utils::sequence::const`) is imported or the fully qualified name is used. Using these constants instead of direct numeric values ("magic numbers") in the code makes the logic clearer and more resistant to changes.

## Technical Specifications

* **Data Types:** The constants use the basic IEC 61131-3 data types `TIME` and `SINT` (short integers).
* **Special Value `NO_TIME`:** The constant `NO_TIME` is initialized with the very large value `TIME#49d17h2m47s295ms`. This value typically serves as a placeholder or initial value to indicate an "undefined" or "unset" time, as it lies far outside the range of normal control timings.
* **State Constants:** The constants `State_00` to `State_08` represent integer states (0-8) and are of type `SINT`. They are intended for use in state machines or step sequences.

## State Overview

*Not applicable.* This is a collection of constants and does not contain a state machine.

## Application Scenarios

1. **State Machines / Sequencers:** The `State_XX` constants can be used as return values or for comparisons in step sequence function blocks (e.g., `E_SR`, `E_CTU` in conjunction with logic) to clearly identify the current step.
2. **Timer Initialization:** The constant `NO_TIME` can be used to assign an initial "invalid" value to timer function blocks before a real duration is set.
3. **Code Readability:** Replacing numbers like `SINT#5` in the code with `State_05` improves readability and indicates the semantic meaning of the value.

## ⚖️ Comparison with Similar Building Blocks

* **ENUM Data Type:** A user-defined enumeration type (ENUM) could fulfill a similar role to the `State_XX` constants and often offers stricter type checking. However, global constants are easier to define and use in 4diac.
* **Direct Value Input:** The main advantage over directly entering values (e.g., `3`) is the centralized definition. A change to the value only needs to be made in one place (here, in the constant file) and will affect all uses.

## Conclusion

The global constant file `sequence` is a useful tool for structuring control applications. By providing descriptive names for states and a specific time value, it significantly contributes to the creation of clear, maintainable, and robust code. Their use is particularly recommended for implementing sequenced logic and state-based control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter Block on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
