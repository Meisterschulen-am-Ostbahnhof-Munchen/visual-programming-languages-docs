# GET_STRUCT_VALUE

<img width="1391" height="128" alt="image" src="https://github.com/user-attachments/assets/0abda300-6bff-4217-b40b-4f2cccc9fc49" />
* * * * * * * * * *
## Introduction

The function block (FB) `GET_STRUCT_VALUE` is a service interface module designed to dynamically read specific values from a given data structure. It provides a flexible way to access structure members whose names or paths are determined at runtime.
![GET_STRUCT_VALUE](GET_STRUCT_VALUE.svg)
## Interface Structure

### **Event Inputs**

| Name | Type | Description | Data with |
| :--- | :---- | :------------------------------- | :-------- |
| `REQ`| `Event`| Requests the retrieval of a value from the structure. | `member`, `in_struct` |

### **Event Outputs**

| Name | Type | Description | Data with |
| :--- | :---- | :------------------------------- | :-------- |
| `CNF`| `Event`| Confirms the completion of the `REQ` event. | `QO`, `output` |

### **Data Inputs**

| Name | Type | Description |
| :-------- | :------- | :------------------------------------------------------------------------------------------------------- |
| `in_struct`| `ANY` | The data structure from which a value is to be read. |
| `member` | `STRING` | The name of the member of the structure to be retrieved. Inner members are accessed using the dot operator (`.`). |

### **Data Outputs**

| Name | Type | Description |
| :----- | :---- | :---------------------------------------------------- |
| `QO` | `BOOL` | `TRUE` if no errors occurred, otherwise `FALSE`. |
| `output` | `ANY` | The value of the selected member if `QO = TRUE`. Otherwise, this value remains unchanged. |

### **Adapters**

No adapters available.

## Functionality

The `GET_STRUCT_VALUE` function block is activated by a `REQ` event. Upon activation, the function block attempts to extract the value of a structure member specified in `member` from the data structure present at input `in_struct`. The path to the member can also specify nested members (e.g., "config.port") using the dot operator (`.`). After reading, a `CNF` event is triggered, which provides the status (`QO`) and the extracted value (`output`). If an error occurs (e.g., member not found or invalid path), `QO` is set to `FALSE`.

## Technical Features

* **Dynamic Member Access:** This function block allows access to structure members via a `STRING` input, offering high flexibility in data processing.
* **Nested Structures:** Members in nested structures can also be efficiently addressed using the dot operator (`.`) in the string `member`.
* **Type Independence:** The inputs and outputs `in_struct` and `output` are of type `ANY`, meaning that the function block can handle any data structure and member data type.

## State Overview

The `GET_STRUCT_VALUE` is a stateless service function block that implements simple request acknowledgment logic (REQ/CNF). It processes each request individually and does not maintain any complex internal states.

## Application Scenarios

* **Dynamic Configuration:** Reading configuration parameters from a central structure, where the required parameters are determined at runtime.
* **Generic Data Processing:** Developing generic algorithms or logic that need to access different parts of a data structure based on external inputs or rules.
* **Logging and Diagnostics:** Extracting specific status information or measured values from a complex system state structure for monitoring or diagnostic purposes.
* **Interfaces to External Systems:** Adapting to data formats of external systems where field names are passed dynamically.

## ⚖️ Comparison with Similar Building Blocks

There are no directly comparable function blocks in the 4diac standard library that allow dynamic access to structure members via a `STRING` path. This building block fills a niche for use cases requiring flexible, runtime-configurable structure manipulation that goes beyond the static access of conventional function blocks.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2018 fortiss GmbH |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2018-10-16, Jose Cabral) |
| 4diac Package | eclipse4diac::convert |

## 🛠️ Related Exercises

* [Exercise_052](../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)

## Conclusion

The `GET_STRUCT_VALUE` function block is a valuable tool for developers who need a flexible and dynamic method for reading values from data structures in 4diac. Its ability to access members via string paths, including nested structures, makes it particularly useful in scenarios where the structure of the required data is not fully known or is variable at compile time.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
