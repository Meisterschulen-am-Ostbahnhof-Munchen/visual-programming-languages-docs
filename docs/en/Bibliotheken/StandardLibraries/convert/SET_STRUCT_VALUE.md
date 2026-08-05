# SET_STRUCT_VALUE
<img width="1393" height="152" alt="image" src="https://github.com/user-attachments/assets/06ce9694-a203-4982-895d-68c27425acd1" />
* * * * * * * * * *
## Introduction
The function block `SET_STRUCT_VALUE` is a service interface function block used to set a specific value within a data structure. It enables the dynamic manipulation of structure elements by assigning a new value to a named member of the structure.
![SET_STRUCT_VALUE](SET_STRUCT_VALUE.svg)
## Interface Structure
The function block has event and data interfaces to enable its functionality.

### **Event Inputs**
* **REQ**: This event requests the function block to set the value in the specified structure. It is associated with the data variables `member`, `in_struct`, and `element_value`.

### **Event Outputs**
* **CNF**: This event is triggered when the `REQ` request is completed. It is associated with the data variable `out_struct`.

### **Data Inputs**
* **in_struct** (Type: ANY): The input structure in which a value is to be changed. The type `ANY` allows the processing of any structure type.
* **member** (Type: STRING): The name of the structure member whose value is to be set. Inner members can be addressed using the dot operator (`.`) (e.g., "config.port").
* **element_value** (Type: ANY): The new value to be assigned to the specified structure member.

### **Data Outputs**
* **out_struct** (Type: ANY): The modified structure after the element is set. The comment in the XML states "TRUE if no errors occurred, FALSE otherwise," which is a remnant of a `STATUS` output, but here it refers to the output, modified structure.

### **Adapters**
No adapters are present.

## Functionality
Upon receiving a `REQ` event, the function block accesses the data structure provided via `in_struct`. Based on the string passed as `member`, the corresponding element within the structure is identified. The function block then assigns the value provided via `element_value` to this element. The function block then outputs the modified structure via `out_struct` and signals the completion of the operation with the `CNF` event.

## Technical Features
* **Generic Types (ANY)**: By using the data type `ANY` for `in_struct`, `element_value`, and `out_struct`, this function block offers high flexibility. It can work with any user-defined or predefined structure types and values without requiring specific types to be known at compile time.
* **Access to Nested Members**: The `member` variable supports access to deeper levels of a nested structure using dot notation (e.g., "outer.inner.value"). This simplifies the handling of complex data models.

## State Overview
The function block primarily operates in a request-based (`REQ`) and confirmation-based (`CNF`) schema. It processes a request, modifies the data, and signals completion. There are no complex internal states beyond this simple request/confirm cycle.

## Application Scenarios
* **Runtime Configuration Management**: Dynamically modify configuration parameters stored in structures without recompiling the function block.
* **Data Manipulation in SCADA/HMI Systems**: Updating specific values in complex data objects received from or sent to higher-level systems.
* **Interfaces to External Systems**: Adapting data structures used for communication with external APIs or databases.
* **Process Control**: Modifying process parameters organized in structures based on dynamic conditions or user input.

## ⚖️ Comparison with Similar Function Blocks
Compared to function blocks that support hard-coded structures or only read values, `SET_STRUCT_VALUE` offers unique flexibility through:

* **Write Access**: Allows setting values, not just reading.
* **Generic Access**: Works with any `ANY` type, making it more universal than function blocks bound to specific structure types.
* **Dynamic Member Selection**: The member name is passed as a string at runtime, allowing for more dynamic field selection than with fixed inputs/outputs.

It often complements function blocks that read values from structures (`GET_STRUCT_VALUE`) to provide complete read/write functionality for generic structures.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2023 Primetals Technologies Austria GmbH |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2023-03-06, Alois Zoitl) |
| 4diac Package | eclipse4diac::convert |

## Conclusion

The `SET_STRUCT_VALUE` function block is a powerful tool for dynamically manipulating data structures within a 4diac application. Its generic nature and support for accessing nested members make it extremely versatile for applications that require flexible configuration or runtime data processing.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
