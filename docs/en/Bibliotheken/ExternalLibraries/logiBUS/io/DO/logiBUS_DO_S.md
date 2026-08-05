# logiBUS_DO_S
* * * * * * * * * *
## Introduction
The function block `logiBUS_DO_S` is a structured data type (struct) used to configure a digital output (DO) within the logiBUS system. It defines the necessary parameters to uniquely address and control a physical output pin of a logiBUS I/O module. This data type is typically used as input for function blocks that provide the actual output functionality.
## Interface Structure
As a structured data type, `logiBUS_DO_S` does not have event or adapter interfaces in the conventional sense of a function block. Instead, it defines a data structure that is passed as a whole to other blocks.
## **Data Inputs**
The structure itself contains the following data field, which is populated when the type is instantiated:

| Name | Data Type | Initial Value | Description |
| :--- | :--- | :--- | :--- |
| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Defines the number of the physical output pin to be controlled. The value 255 represents an invalid/undefined state and serves as the default initialization. |

### **Event Inputs**
*Not present.* This type is a data structure only.

### **Event Outputs**
*Not present.* This type is a data structure only.

### **Data Outputs**
*Not present.* This type is a data structure only.

### **Adapters**
*Not present.* This type is a data structure only.

## Functionality

The `logiBUS_DO_S` struct acts as a configuration container. Its main task is to transport the information about the desired pin number (`Pin`) in a bundled and typed manner. A higher-level function block (e.g., a `logiBUS_DO` block) receives an instance of this struct, reads the `Pin` value, and uses this information to switch the corresponding physical output of the logiBUS hardware module.

The initial value of 255 for `Pin` indicates that the pin is not yet configured. Valid pin numbers are within the range supported by the respective logiBUS I/O module (e.g., 0-7 for an 8-channel module).

## Technical Features
* **Typing:** Using a structured data type instead of a simple `USINT` increases type safety and application readability. It is clear that the value represents a logiBUS output pin.
* **Initial Value:** The initial value of 255 serves as a "Safe State" indicator. Before the structure is correctly configured, this value indicates an inactive or faulty state.
* **Package Assignment:** The struct is part of the `logiBUS::io::DQ` package, indicating its membership in the digital input/output (Digital I/O) of the logiBUS framework.

## State Overview
Since it is a passive data type, `logiBUS_DO_S` does not have an internal state machine. The "state" is determined solely by the stored value of the ``Pin`` variable.

## Application Scenarios

1. **Output Configuration:** This struct is primarily used to parameterize function blocks that control lamps, valves, relays, or other binary actuators via logiBUS modules.

2. **Structured Parameter Passing:** In more complex applications, multiple ``logiBUS_DO_S`` instances can be organized in arrays or other structures to centrally manage the configuration of all outputs in a station.

3. **Initialization:** The default initial value allows variables of this type to be declared without having to populate them immediately. The actual configuration (assigning a valid pin number) can be performed later in the program flow.

## ⚖️ Comparison with Similar Building Blocks
* **Simple `USINT`:** Directly using a `USINT` value for the pin number is possible, but offers less semantic clarity and type safety. The `logiBUS_DO_S` makes the purpose of the data element explicit.
* **`logiBUS_DI_S`:** This is the structural counterpart for digital inputs (DIs). It has an identical structure (a `USINT` field `Pin`), but conceptually belongs to the input side. Separating DO and DI structs improves code readability and maintainability.
*
## 🛠️ Related exercises
* [Uebung_003a_AX_sub](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003a_AX_sub.md)
* [Uebung_003a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003a_sub.md)
* [Uebung_003b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003b_sub.md)
* [Uebung_010b4_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010b4_sub.md)
* [Uebung_010b4_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b4_sub_AX.md)
* [Uebung_010b5_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010b5_sub.md)
* [Uebung_010b5_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b5_sub_AX.md)
* [Uebung_010c2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c2.md)
* [Uebung_010c2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c2_AX.md)
* [Uebung_010c3_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c3_sub.md)
* [Uebung_010c3_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c3_sub_AX.md)
* [Uebung_010c4_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c4_sub.md)
* [Uebung_010c4_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c4_sub_AX.md)
* [Uebung_026_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_026_sub.md)
* [Uebung_039_sub_Outputs](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
* [Uebung_039a_sub_Outputs](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)

## Conclusion
The The `logiBUS_DO_S` struct is a simple yet essential helper element in the logiBUS ecosystem of the 4diac IDE. It standardizes and formalizes the addressing of digital output pins, promotes type-safe programming, and, thanks to its defined initial value, serves as the basis for robust initialization logic. Its use is recommended when configuring logiBUS library function blocks for digital outputs.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
