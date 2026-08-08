# GET_AT_INDEX
<img width="1341" height="212" alt="image" src="https://github.com/user-attachments/assets/05b8aa7e-9c77-4a15-8787-2bd7d986a846" />
* * * * * * * * * *
## Introduction
This function block (FB) is used to retrieve a value from an array at a specific index position. An important prerequisite for correct operation is that the data type of the input array matches the data type of the output value. It is a fundamental building block for accessing array elements.
![GET_AT_INDEX](GET_AT_INDEX.svg)
## Interface Structure
The `GET_AT_INDEX` function block has a clearly defined interface structure with event and data inputs and outputs.

### **Event Inputs**
* **REQ** (Type: `Event`)
* Service request to execute the function block.
* Is linked to the data inputs `IN_ARRAY` and `INDEX`, which are read when the event is triggered.

### **Event Outputs**
* **CNF** (Type: `Event`)
* Acknowledgement of the requested service after successful processing.
* Is linked to the data outputs `QO` and `OUT`, which are provided after processing.

### **Data Inputs**
* **IN_ARRAY** (Type: `ANY`)
* The input array from which a value is to be retrieved. The data type is generic (`ANY`) but must match the output.

* **IN_ARRAY** (Type: `ANY`)
* The input array from which a value is to be retrieved. The data type is generic (`ANY`) but must match the output.
* **INDEX** (Type: `UINT`)
* The index (position) within `IN_ARRAY` from which the value is to be retrieved.

### **Data Outputs**
* **QO** (Type: `BOOL`)
* A qualifier for the event output, typically indicating the success or failure of the operation (e.g., `TRUE` for success, `FALSE` for failure).
* **OUT** (Type: `ANY`)
* The retrieved value from `IN_ARRAY` at the specified `INDEX` position. The data type is generic (`ANY`).

### **Adapters**
This function block does not use any adapters.

## Functionality
When a `REQ` event is received at the input of the function block, the `GET_AT_INDEX` function block reads the current values of the data inputs `IN_ARRAY` and `INDEX`. It then accesses `IN_ARRAY` and extracts the value at the position specified by `INDEX`. This retrieved value is then passed to the data output `OUT`. Simultaneously, the output `QO` is set according to the result of the operation (e.g., `TRUE` for successful access). Finally, the `CNF` event is triggered to signal the termination of the service.

## Technical Specifications
* **Data Type Match**: It is crucial that the data type of the input array (`IN_ARRAY`) is compatible with the expected data type of the retrieved value (`OUT`) to avoid type errors.
* **Index Range**: The value of `INDEX` must be within the valid limits of `IN_ARRAY` to prevent runtime errors or undefined behavior. Index range verification may need to be ensured by upstream or downstream logic.
* **ANY Type**: Using the `ANY` type for `IN_ARRAY` and `OUT` makes the function block very flexible, but requires careful typing in the application.

## State Overview
The `GET_AT_INDEX` function block is essentially stateless with respect to data storage. Its states are limited to the execution cycle:

1. **Ready**: Waits for a `REQ` event.

2. **Executing**: Reads inputs, performs array access, and sets outputs.

3. **Completed**: Triggers the `CNF` event and returns to the "Ready" state.

## Application Scenarios
* **Data Logging and Analysis**: Retrieving specific measured values from a time-series array.
* **Configuration Management**: Reading individual parameters from an array of configuration values.
* **List Processing**: Sequentially or randomly retrieving items from a list of tasks or objects.
* **Robot Control**: Accessing positions or motion parameters stored in arrays.
* **Visualization**: Retrieving data points for display on a user interface.

## ⚖️ Comparison with Similar Blocks
The `GET_AT_INDEX` block is a specialized block for array access. It differs from:

* **`SET_AT_INDEX`**: A complementary building block that sets values at a specific array position instead of retrieving them.
* **Array Iterators**: Building blocks that typically iterate through the entire array instead of retrieving a single element via a direct index.
* **General Data Manipulation Building Blocks**: These are not specifically designed for array access but perform more general operations (e.g., addition, comparison).

GET_AT_INDEX` thus fills a fundamental gap for direct, indexed read access to array data structures.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2014 Profactor GmbH |
| License | EPL-2.0 |
| Version | Version 3.0 (April 14, 2025, Patrick Aigner), Version 1.0 (July 11, 2014, Matthias Plasch) |
| 4diac package | eclipse4diac::convert |

## Conclusion

The `GET_AT_INDEX` function block is a basic and flexible building block that enables direct and indexed access to array elements. Its simplicity and support for generic data types (`ANY`) make it a versatile tool in numerous automation and control applications where data is stored in ordered lists or tables. Correct use requires only attention to data type compatibility and the valid index range.

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
