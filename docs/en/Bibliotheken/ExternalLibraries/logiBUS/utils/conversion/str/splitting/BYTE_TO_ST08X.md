# BYTE_TO_ST08X
<img width="1225" height="244" alt="image" src="https://github.com/user-attachments/assets/aaadee66-4701-4548-a8a5-c07d4936e97d" />
![BYTE_TO_ST08X](./BYTE_TO_ST08X.svg)

* * * * * * * * * *
## Introduction
This function block (FB) is used to break down a single byte value into a structure of eight individual BOOL values. Each bit of the input byte is assigned to a separate BOOL field in the output structure, which simplifies the handling of bitwise information.
## Interface Structure
### **Event Inputs**
* **REQ**: An event input that triggers the execution of the function block. It is associated with the data input `IN`.

### **Event Outputs**
* **CNF**: An event output that signals that the conversion is complete. It is associated with the data output `OUT`.

### **Data Inputs**
* **IN**: Type `BYTE`. This is the byte value whose eight bits are to be split into individual Boolean values.

### **Data Outputs**
* **OUT**: Type `logiBUS::utils::conversion::types::ST08X`. This is a structure containing eight BOOL values (named X_00 to X_07). Each of these fields represents one bit of the input byte.

### **Adapters**
This function block does not use adapters.

## Functionality
The `BYTE_TO_ST08X` function block converts a single 8-bit byte into a predefined structure `ST08X`, which contains eight separate BOOL variables.

On a `REQ` event, the value of the `IN` byte is read. Then, each bit of the `IN` byte is assigned to the corresponding BOOL field in the `OUT` structure:

* `OUT.X_00` is assigned bit 0 of `IN`.
* `OUT.X_01` is assigned bit 1 of `IN`.
* ...
* `OUT.X_07` is assigned bit 7 of `IN`.
* `OUT.X_07` is assigned bit 7 of `IN`.
* After the assignment, a `CNF` event is triggered to signal the completion of the operation.

## Technical Features
* **Direct Bit Extraction:** The conversion is performed by directly assigning the individual bits of the byte (e.g., `IN.0`) to the BOOL fields of the target structure (e.g., `OUT.X_00`).
* **Use of `ST08X`:** The function block uses the specific data type structure `logiBUS::utils::conversion::types::ST08X`, which is explicitly designed to hold eight Boolean values. This structure must be known to the system.
* **Event-driven:** The operation is triggered by an input event `REQ` and signals its completion with an output event `CNF`. This ensures controlled data flow in the 4diac system.

## State Overview

This function block is a pure data converter without internal states. Its function is deterministic and depends solely on the input values and the triggering event.

## Application Scenarios
* **Hardware Interfacing:** If a byte representing the state of eight discrete digital inputs or outputs is received from external devices (e.g., via fieldbuses such as Modbus or CANopen), this function block can be used to isolate the individual states for further processing in the control program.
* **Protocol Parsing:** Decomposition of status bytes in communication protocols, where each bit indicates a specific flag or state.
* **Logical Operations:** Preparing data for logical operations that require individual Boolean values.
* **Visualization:** Displaying individual bits of a byte value on a user interface.

## ⚖️ Comparison with Similar Blocks
Standard function blocks in 4diac often provide general type conversions (e.g., `BYTE_TO_INT`). However, this block specializes in decomposing a byte into a structured group of Boolean values (`ST08X`), which distinguishes it from generic converters. There is no direct equivalent in the standard library for this specific structure conversion. Other approaches could involve using bitmasks and logical operations (AND, SHIFT) with multiple individual conversion blocks, but this would result in a more complex and less user-friendly implementation. This block provides a direct and elegant solution to the task at hand.

## Conclusion

The `BYTE_TO_ST08X` function block is a useful tool for efficiently and clearly decomposing a byte value into eight individual Boolean states, organized in a `ST08X` structure. It simplifies the handling of bitwise information, especially in I/O processing and protocol analysis, by providing a clear and event-driven interface.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
