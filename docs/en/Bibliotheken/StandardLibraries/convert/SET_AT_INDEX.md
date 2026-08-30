# SET_AT_INDEX

<img width="1449" height="238" alt="image" src="https://github.com/user-attachments/assets/b43c3e3b-03a9-421b-a9ba-bcd4c4f00f28" />
* * * * * * * * * *
## Introduction

The function block `SET_AT_INDEX` is used to set the value of an element in an array at a specific index. It must be ensured that the data types of the value to be set match the data type of the array. The resulting output array will also have the same data type as the input array. This function block is useful for dynamically manipulating array data within a control program.
![SET_AT_INDEX](SET_AT_INDEX.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Event): A request input that initiates the execution of the function block. This event processes the data inputs `IN_ARRAY`, `INDEX`, and `VALUE`.

### **Event Outputs**

- **CNF** (Event): An acknowledgment output triggered after successful service execution. This event updates the data outputs `QO` and `OUT_ARRAY`.

### **Data Inputs**

- **IN_ARRAY** (ANY): The input array whose value is to be modified at a specific index. The data type `ANY` allows its use with various array types.
- **INDEX** (UINT): The zero-based index of the element in the array whose value is to be set.
- **IN_ARRAY** (ANY): The input array whose value is to be modified at a specific index. * **VALUE** (ANY): The value to be set at the specified position in the array. The data type must match the data type of `IN_ARRAY`.

### **Data Outputs**

- **QO** (BOOL): An event output qualifier that indicates the success of the operation. `TRUE` on success, `FALSE` on error (e.g., invalid index).
- **OUT_ARRAY** (ANY): The resulting array after the value has been set at the specified index.

### **Adapter**

Not present.

## Functionality

The `SET_AT_INDEX` function block waits for a `REQ` event. As soon as this event occurs, the function block checks the passed arrays `IN_ARRAY`, `INDEX`, and `VALUE`. It attempts to store `VALUE` at the address of `INDEX` within `IN_ARRAY`. If the operation is successful, a new array is created and output to `OUT_ARRAY`, setting `QO` to `TRUE`. If the specified `INDEX` is outside the valid range of `IN_ARRAY`, or if the data types of `VALUE` and the array elements do not match, the operation may fail, and `QO` could display `FALSE`.

## Technical Features

- **Data Type Flexibility:** By using `ANY` for the array and value parameters, the function block is flexible with respect to the data types it can process. However, it is crucial that the data type of `VALUE` exactly matches the element data type of `IN_ARRAY` to avoid runtime errors.
- **Index Type:** The `INDEX` block is of type `UINT` (Unsigned Integer), meaning that only positive indices are allowed.
- **Zero-Based Indexing:** The index starts at 0 for the first element of the array.
- **Error Handling:** The `QO` output serves as a simple indicator of the operation's success. More advanced error handling (e.g., for index out-of-bounds errors) may need to be implemented at the application level or supplemented with additional checks.

## State Overview

The `SET_AT_INDEX` block is essentially an event-driven block without complex internal state. It waits for a `REQ` event, executes the action, and outputs a `CNF` event. Its function is direct and reactive.

## Application Scenarios

- **Dynamic Configuration:** Modifying configuration parameters stored in arrays at runtime.
- **Data Processing:** Updating sensor or actuator data collected in arrays.
- **Algorithmic Adjustment:** Modifying lookup tables or controller parameters in real time.
- **User Interaction:** Setting array values based on user input.

## ⚖️ Comparison with Similar Blocks

This block is complementary to the `GET_AT_INDEX` block, which would read values from an array at a specific index. It is a fundamental operation for array manipulation and forms the basis for more complex data structure algorithms. Unlike building blocks that copy or move entire arrays, `SET_AT_INDEX` focuses on the precise manipulation of a single element.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2014 Profactor GmbH |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-08-05, Matthias Plasch) |
| 4diac Package | eclipse4diac::convert |

## Conclusion

The `SET_AT_INDEX` function block is a fundamental yet powerful tool for manipulating array data in 4diac applications. Its flexibility, thanks to the `ANY` data types and its clear event-driven interface, makes it a valuable component for many applications requiring dynamic data structures. Correct handling of data types and indices is crucial for its error-free use.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
