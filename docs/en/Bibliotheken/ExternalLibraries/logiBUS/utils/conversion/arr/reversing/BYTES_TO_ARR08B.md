# BYTES_TO_ARR08B
<img width="1102" height="362" alt="image" src="https://github.com/user-attachments/assets/a1d78d97-bc58-4056-8fa5-6127a949d1fc" />
![BYTES_TO_ARR08B](./BYTES_TO_ARR08B.svg)
* * * * * * * * * *
## Introduction
The function block `BYTES_TO_ARR08B` converts eight individual `BYTE` values into an array of type `BYTE` with eight elements. It is part of a collection of helper functions for data conversion and array operations.
## Interface Structure
### **Event Inputs**
* **REQ**: This event triggers the processing of the function block. Upon its arrival, the values at the data inputs are read and written to the output array.

### **Event Outputs**
* **CNF**: This event is generated after successful processing and assignment of the values to the output array. It indicates the availability of the result.
...
### **Data Inputs**
* **IN_00** (`BYTE`): Value for the array element at index 0.
* **IN_01** (`BYTE`): Value for the array element at index 1.
* **IN_02** (`BYTE`): Value for the array element at index 2.
* **IN_03** (`BYTE`): Value for the array element at index 3.
* **IN_04** (`BYTE`): Value for the array element at index 4.
* **IN_05** (`BYTE`): Value for the array element at index 5.
* **IN_06** (`BYTE`): Value for the Array element at index 6.
* **IN_07** (`BYTE`): Value for the array element at index 7.

### **Data Outputs**
* **OUT** (`ARRAY[0..7] OF BYTE`): The resulting byte array. Indices 0 through 7 contain the values from `IN_00` to `IN_07`, sequentially.

### **Adapters**
This function block does not use any adapters.

## Operation
When triggered by the `REQ` event, the block copies the values of the eight `BYTE` inputs directly into the corresponding positions of the output array `OUT`. The assignment is sequential: `IN_00` → `OUT[0]`, `IN_01` → `OUT[1]`, and so on, up to `IN_07` → `OUT[7]`. Immediately after this assignment, the `CNF` event is triggered.

The internal implementation is in Structured Text (ST) and consists of a simple series of assignments.

## Technical Features
* **Deterministic Runtime:** The operation has a constant and very short execution time because it consists only of direct assignments.
* **No Buffering:** There is no intermediate storage of the input values. Processing occurs exclusively upon the arrival of a `REQ` event.
* **Fixed Size:** The block is specifically designed for a combination of exactly eight bytes.

## State Overview
The function block is stateless. Each `REQ` call is independent of previous calls and processes only the currently available input values.

## Application Scenarios
* **Data Aggregation:** Combining individual byte values (e.g., from various sources or sensors) into a compact array for further processing or transmission.
* **Protocol and Interface Adaptation:** Preparing data structures for communication protocols or function blocks that expect a byte array instead of individual bytes.
* **Data Restructuring:** Converting between different data representations within a control application.

## ⚖️ Comparison with Similar Blocks
* **`CONCAT` Blocks:** General-purpose blocks for concatenating strings are not directly comparable, as they are designed for the `STRING` data type.
* **Manual Assignment in ST:** The functionality could be implemented directly in an ST program using assignments. However, the function block encapsulates this logic for improved reusability, readability, and maintainability within FBD/LD diagrams.
* **Custom Array Blocks:** Unlike general-purpose array blocks that have index inputs, `BYTES_TO_ARR08B` is optimized for a specific, fixed task and is therefore easier and faster to use.
*
## 🛠️ Related Exercises
* [Exercise_126b_sub](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)]
* [Exercise_12x_sub](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_12x_sub.md)]

## Conclusion
The `BYTES_TO_ARR08B` is a specialized and efficient utility module for a common data manipulation task. It offers a clear, event-driven interface and saves the user from repeatedly implementing array mapping manually. Its strength lies in its simplicity and unambiguity for the specific use case of combining eight bytes.
