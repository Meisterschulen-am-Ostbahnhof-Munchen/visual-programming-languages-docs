# HANDLE

![HANDLE](./HANDLE.svg)

* * * * * * * * * *
## Introduction

The `HANDLE` constant is a global constant definition for the 4diac IDE, used in the context of ISOBUS protocol and parameter group number (PGN) processing. It defines special values to identify invalid or global addressing targets within an ISOBUS network. These constants serve as central reference values for function blocks that use handle-based communication.
## Interface Structure

This is a global constant definition and therefore does not have event or data interfaces in the conventional sense of a function block. Instead, it provides named constants that can be used in other blocks.

## **Event Inputs**

*Not present.* This definition does not contain any event inputs.

## **Event Outputs**

*Not present.* This definition does not contain any event outputs.

### **Data Inputs**

*Not present.* This definition does not contain any data inputs.

### **Data Outputs**

*Not present.* This definition does not contain any data outputs.

### **Adapters**

*Not present.* This definition does not contain any adapter interfaces.

## Functionality

The `HANDLE` constant defines two symbolic names for special integer values:

1. `UNVALID`: Represents an invalid or unused handle with the value `-1` (decimal) or `0xFFFF` (hexadecimal). This value can be used to indicate that a handle is not initialized, an operation has failed, or a resource is unavailable.
2. `GLOBAL`: Represents a pseudo-handle with the value `32767` (decimal) or `0x7FFF` (hexadecimal). This value is used to address a global destination (broadcast) within the ISOBUS network, rather than a specific individual device.

These constants are typically used in the data connections or internal logic of other functional blocks (e.g., for ISOBUS communication) to improve code readability and maintainability, rather than using magic numbers directly in the code.

## Technical Details

- **Packet Assignment:** The constants are assigned to the `isobus::pgn` package, which clearly defines their use in ISOBUS PGN communication.
- **Typing:** Both constants are of type `INT` (Integer).
- **Initialization:** The values are assigned directly upon declaration (`InitialValue`).
- **Visibility:** As global constants (`GLOBALCONSTANTS`), they are visible and usable within the defined package (`isobus::pgn`) for all function blocks contained within it.

## State Overview

Since this is a static constant definition, there is no state machine or mutable state.

## Application Scenarios

- **Initializing Handles:** When a system starts, communication handles can be initialized with the value `UNVALID` to indicate their "empty" state.
- **Error Handling:** Function blocks that return handles (e.g., after opening a connection) can return `UNVALID` to indicate an error.
- **Broadcast Communication:** A sender block can use the `GLOBAL` handle to address a message to all participants in the ISOBUS network instead of a specific receiver.
- **Comparisons:** The readability of conditions such as `IF currentHandle = UNVALID THEN ...` or `IF targetHandle = GLOBAL THEN ...` is significantly improved.

## ⚖️ Comparison with Similar Blocks

- **`CONSTANT` Function Block:** A generic `CONSTANT` block can output a fixed value but is an instance within a function block network. The `HANDLE` global constant is a central, package-wide definition that does not need to be instantiated and is referenced directly by its name.
- **Direct Value Input:** Instead of using `UNVALID` or `GLOBAL`, the numeric values (`-1`, `32767`) could be entered directly into the blocks. However, using the constants is significantly better practice, as it makes the code more self-explanatory and resistant to changes (changes only need to be made in one place).

## Conclusion

The `HANDLE` global constant is a simple yet essential tool for developing ISOBUS-compliant applications in 4diac. It improves code quality by assigning meaningful names to two frequently used, special handle values. Using this promotes readable, maintainable, and fault-tolerant code in function blocks that use ISOBUS PGN addressing.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
