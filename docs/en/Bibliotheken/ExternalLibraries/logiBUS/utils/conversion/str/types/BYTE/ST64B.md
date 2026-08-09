# ST64B

* * * * * * * * * *
## Introduction

The `ST64B` data type is a structured data type used to encapsulate 64 individual byte values. It was developed to provide a fixed 64-byte data structure that can be used for various use cases where a precisely defined size and direct access to individual bytes are required. The original XML definition contained a comment that incorrectly stated 16 bytes; the correct value is 64 bytes.
## Structure Definition

The `ST64B` data type is a composite structure consisting exclusively of individual byte variables. It has no event- or adapter-based interfaces, as it is a pure data structure.
### **Event Inputs**

Not applicable, as `ST64B` is a data type and not a function block.

### **Event Outputs**

Not applicable, as `ST64B` is a data type and not a function block.

### **Data Components**

The structure `ST64B` consists of the following 64 byte variables:

| Name | Type | Description |
| :--- | :--- | :--- |
| B\_00 | BYTE | BYTE 00 |
| B\_01 | BYTE | BYTE 01 |
| B\_02 | BYTE | BYTE 02 |
| B\_03 | BYTE | BYTE 03 |
| B\_04 | BYTE | BYTE 04 |
B\_05 | BYTE | BYTE 05 |
| B\_06 | BYTE | BYTE 06 |
| B\_07 | BYTE | BYTE 07 |
| B\_08 | BYTE | BYTE 08 |
| B\_09 | BYTE | BYTE 09 |
| B\_10 | BYTE | BYTE 10 |
| B\_11 | BYTE | BYTE 11 |
| B\_12 | BYTE | BYTE 12 |
| B\_13 | BYTE | BYTE 13 |
| B\_14 | BYTE | BYTE 14 |
| B\_15 | BYTE | BYTE 15 |
| B\_16 | BYTE | BYTE 16 |
| B\_17 | BYTE | BYTE 17 |
| B\_18 | BYTE | BYTE 18 |
| B\_19 | BYTE | BYTE 19 |
| B\_20 | BYTE | BYTE 20 |
| B\_21 | BYTE | BYTE 21 |
| B\_22 | BYTE | BYTE 22 |
| B\_23 | BYTE | BYTE 23 |
| B\_24 | BYTE | BYTE 24 |
| B\_25 | BYTE | BYTE 25 |
| B\_26 | BYTE | BYTE 26 |
| B\_27 | BYTE | BYTE 27 |
| B\_28 | BYTE | BYTE 28 |
| B\_29 | BYTE | BYTE 29 |
| B\_30 | BYTE | BYTE 30 |
| B\_31 | BYTE | BYTE 31 |
| B\_32 | BYTE | BYTE 32 |
| B\_33 | BYTE | BYTE 33 |
| B\_34 | BYTE | BYTE 34 |
| B\_35 | BYTE | BYTE 35 |
| B\_36 | BYTE | BYTE 36 |
| B\_37 | BYTE | BYTE 37 |
| B\_38 | BYTE | BYTE 38 |
| B\_39 | BYTE | BYTE 39 |
| B\_40 | BYTE | BYTE 40 |
| B\_41 | BYTE | BYTE 41 |
| B\_42 | BYTE | BYTE 42 |
| B\_43 | BYTE | BYTE 43 |
| B\_44 | BYTE | BYTE 44 |
| B\_45 | BYTE | BYTE 45 |
| B\_46 | BYTE | BYTE 46 |
| B\_47 | BYTE | BYTE 47 |
| B\_48 | BYTE | BYTE 48 |
| B\_49 | BYTE | BYTE 49 |
| B\_50 | BYTE | BYTE 50 |
| B\_51 | BYTE | BYTE 51 |
| B\_52 | BYTE | BYTE 52 |
| B\_53 | BYTE | BYTE 53 |
| B\_54 | BYTE | BYTE 54 |
| B\_55 | BYTE | BYTE 55 |
| B\_56 | BYTE | BYTE 56 |
| B\_57 | BYTE | BYTE 57 |
| B\_58 | BYTE | BYTE 58 |
| B\_59 | BYTE | BYTE 59 |
| B\_60 | BYTE | BYTE 60 |
| B\_61 | BYTE | BYTE 61 |
| B\_62 | BYTE | BYTE 62 |
| B\_63 | BYTE | BYTE 63 |

### **Data Outputs**

Not applicable, as `ST64B` is a data type and its components do not function as "outputs" in the sense of a function block.

### **Adapters**

Not applicable, as `ST64B` is a data type and not a function block.

## Functionality

As a structured data type, `ST64B` does not have its own "function" in the sense of active behavior or logic. Its primary function is to define a memory area of 64 bytes and make it accessible in an organized form. This allows addressing individual bytes within the structure via their named variables (e.g., `ST64B.B_00`, `ST64B.B_15`). It serves as a passive data container.

## Technical Features

The main feature of `ST64B` is its fixed size of exactly 64 bytes. Each byte is individually addressable via a unique variable name. This makes it ideal for situations requiring a strict data size and byte-by-byte manipulation of the content, such as when processing communication protocols or hardware registers. The sequential naming of the variables simplifies their allocation to a continuous memory area.

## State Overview

As a pure data type, `ST64B` has no states in the sense of a state machine or a function block. The "state" of a `ST64B` instance is defined solely by the current values of the 64 contained byte variables. Each combination of these values represents a valid data state of the structure.

## Application Scenarios

ST64B` is ideally suited for the following application scenarios:

* **Communication Buffer:** As a standard buffer for messages or packets with a fixed size of 64 bytes, e.g., in CAN bus messages (when multiple frames are needed), serial communication, or other protocols.
* **Hardware Register Map:** Mapping of a 64-byte range of hardware registers, where each byte variable corresponds to a specific register.
* **Data Serialization:** Storing raw data before serialization or after deserialization, especially when data is transmitted without explicit type information.
* **Generic Data Blocks:** Handling generic, fixed-size data blocks that can be interpreted flexibly, e.g., as part of larger protocols or data structures.

## ⚖️ Comparison with Similar Building Blocks

ST64B` is a basic data type and cannot be directly compared to function blocks. Within the data types, it is comparable to:

* **Other structured data types:** `ST64B` is a specific instance of `StructuredType`. There are similar structures with different numbers or types of elements (e.g., structures with 8, 16, or 32 bytes, or those containing integers, booleans, etc.). `ST64B` is characterized by its purely byte-wise division.
* **Arrays of BYTE:** An array of type `ARRAY[0..63] OF BYTE` would also store 64 bytes. The difference lies in the access method: `ST64B` uses named members (e.g., `myST64B.B_10`), while an array uses an index (e.g., `myArray[10]`). Named members can be advantageous in certain contexts for improved code readability or for directly addressing specific byte positions.

## Conclusion

ST64B` is a simple yet powerful structured data type that provides a fixed data set of 64 bytes. Its strength lies in the clear definition and direct accessibility of each individual byte, making it an excellent choice for applications requiring precise control and interpretation of raw data blocks, particularly in communication and hardware interaction.
