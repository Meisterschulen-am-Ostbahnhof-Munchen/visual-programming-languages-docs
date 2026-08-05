# BOOLS_TO_ST08X
<img width="1032" height="423" alt="image" src="https://github.com/user-attachments/assets/6ba52e2e-b4e7-4f80-ac9f-c05e7c05956f" />
![BOOLS_TO_ST08X](./BOOLS_TO_ST08X.svg)

* * * * * * * * * *
## Introduction
This function block (FB) is used to combine eight individual BOOL values into a structure of type `ST08X`. It enables the clear grouping and transfer of eight binary pieces of information as a single structured variable.
## Interface Structure
### **Event Inputs**
* **REQ** (Event): This event triggers the conversion and assignment of the input values to the output. All data inputs are connected to this event and are read upon its arrival.

### **Event Outputs**
* **CNF** (Event): This confirmation event is triggered after the conversion is successfully completed and the output `OUT` has been updated. The data output `OUT` is associated with this event.

### **Data Inputs**
* **IN_00** (BOOL): The value for bit 0 of the output structure.
* **IN_01** (BOOL): The value for bit 1 of the output structure.
* **IN_02** (BOOL): The value for bit 2 of the output structure.
* **IN_03** (BOOL): The value for bit 3 of the output structure.
* **IN_04** (BOOL): The value for bit 4 of the output structure.
* **IN_05** (BOOL): The value for bit 5 of the output structure.
* **IN_06** (BOOL): The value for bit 6 of the output structure.
* **IN_07** (BOOL): The value for bit 7 of the output structure.

### **Data Outputs**
* **OUT** (logiBUS::utils::conversion::types::ST08X): The resulting structure containing the values of the eight binary inputs in their respective fields (`X_00` to `X_07`).

### **Adapters**
This function block has no adapters.

## Functionality
The function block `BOOLS_TO_ST08X` is activated by an incoming `REQ` event. With each activation, the current values of the eight data inputs (`IN_00` to `IN_07`) are directly assigned to the corresponding fields (`X_00` to `X_07`) of the output structure `OUT`. After successful assignment, the `CNF` event is triggered at the output to signal the completion of the operation and make the updated `OUT` value available. The assignment is one-to-one, where `IN_00` corresponds to the field `X_00`, `IN_01` to the field `X_01`, and so on, until `IN_07` is assigned to the field `X_07`.

## Technical Features
* **Direct Assignment:** The logic consists of a direct one-to-one assignment of the Boolean inputs to the fields of the `ST08X` structure.
* **Typing:** The `ST08X` type is a user-defined structure specifically designed for aggregating eight Boolean values and can be used in a type-safe manner.

## Technical Features
* **Direct Assignment:** * **Efficiency:** Due to its simple implementation, this function block is very efficient and resource-saving.
* **Stateless:** The function block does not store any internal states and processes each request independently of previous calls.

## State Overview
The function block `BOOLS_TO_ST08X` is a stateless function block. This means that it does not store any information about previous executions that could influence its current behavior. Each activation by the `REQ` event results in a recalculation of the output `OUT` based on the values of the data inputs valid at that time.

## Application Scenarios
* **Sensor Data Acquisition:** Combining eight individual digital sensor states (e.g., limit switches, light barriers) into a single structure for more compact data processing or visualization.

## * **Status Register:** Create a status byte or register from individual BOOL flags that indicate various operating states or errors.
* **Interface Communication:** Prepare binary data for transmission via serial interfaces or communication protocols that expect data in structured formats.
* **Programming Logic:** Simplify the logic in more complex function blocks by combining eight separate signals into a single, more manageable variable.

## ⚖️ Comparison with Similar Blocks

This function block specializes in converting eight BOOL values to the user-defined `ST08X` type. Compare to:

* **`BOOLS_TO_BYTE` or `BOOL_TO_WORD`:** These blocks convert individual BOOL values to a primitive integer type (byte, word), where individual bits must be accessed via bitwise operations. In contrast, ``BOOLS_TO_ST08X`` offers a structured variable whose fields are directly accessible via names (``OUT.X_00``, ``OUT.X_01``, etc.), which improves code readability.
* **Logical Operators (AND, OR, XOR):** These operators combine Boolean values, but not into a structure; instead, they combine them into a single Boolean result. ``BOOLS_TO_ST08X`` is used for aggregation, not logical combination.

The main advantage of ``BOOLS_TO_ST08X`` lies in its use of a specific structure type, which offers higher type safety and better code organization compared to generic integer types.

* **Logical Operators (AND, OR, XOR):** These operators combine Boolean values, but not into a structure; rather, they combine them into a single Boolean result.
## Conclusion

The `BOOLS_TO_ST08X` function block is a simple yet extremely useful building block for converting eight individual BOOL signals into a standardized `ST08X` structure. It enhances the modularity and readability of 4diac applications by providing a clean and type-safe method for grouping bit information. This simplifies data handling and transmission in complex control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
