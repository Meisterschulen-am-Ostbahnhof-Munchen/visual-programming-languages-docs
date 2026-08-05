# ST08B_TO_ARR08B

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/2ae15254-1c8f-40ed-9f4b-d611666ba335" />

![ST08B_TO_ARR08B](./ST08B_TO_ARR08B.svg)

* * * * * * * * * *
## Introduction
The function block `ST08B_TO_ARR08B` converts an 8-byte structured data type (`ST08B`) into an 8-byte array. This conversion allows for the easy adaptation of structured data to interfaces or protocols that require a sequential arrangement of bytes.

## Interface Structure
### **Event Inputs**
* **REQ**: An event input that triggers the execution of the conversion. This event is linked to the data input `IN` to ensure that the conversion is performed using the current input data.


### **Event Outputs**

* **CNF**: An event output that signals that the conversion was successful and the output `OUT` has been updated. This event is linked to the data output `OUT`.

### **Data Inputs**

* **IN**: A data input of type `logiBUS::utils::conversion::types::ST08B`. This input expects a structure consisting of 8 bytes (e.g., `B_00` to `B_07`).

### **Data Outputs**

* **OUT**: A data output of type `BYTE` as an array with size `0..7`. This array contains the 8 bytes that were converted from the input structure.

### **Adapters**
This function block does not use any adapters.

## How it Works
The operation of `ST08B_TO_ARR08B` is direct and straightforward. Upon receiving a `REQ` event, the individual byte elements of the input structure `IN` are directly assigned to the corresponding elements of the output array `OUT`. Each element `B_xx` of the structure `IN` is assigned to the element `OUT[xx]` of the array.

Specifically, the assignment is as follows:

* `OUT[0]` is assigned to `IN.B_00`.

* `OUT[1]` is assigned to `IN.B_01`.

* ...
* `OUT[7]` is assigned to `IN.B_07`.

After these assignments are complete, the `CNF` event is triggered to signal the completion of the operation.

## Technical Features
* **Data Types:** The function block works with a specific user-defined structure type, `ST08B`, and a standard `BYTE` array.

* **Direct Mapping:** No complex logic, transformation, or calculation takes place; instead, the bytes are directly mapped one-to-one.


* **Transparency:** The implementation in ST (Structured Text) is clear and easy to understand, ensuring high transparency of the function.

## State Overview
The function block `ST08B_TO_ARR08B` is a pure data conversion block without internal state in the sense of a state machine. It executes its operation deterministically on each `REQ` event and returns a result based on the current input data.

## Application Scenarios
* **Data Preparation for Communication:** To prepare structured data for serial communication protocols (e.g., Modbus RTU, SPI, I2C), Ethernet frames, or other byte-oriented interfaces.

* **Connecting External Devices:** If external devices or libraries expect data as a pure byte array, this block can convert internal structured data accordingly.

* **Type Conversion and Interoperability:** Improves compatibility between different parts of an application or between different systems that use different data representations.

* **Archiving and Logging:** Stores structured data in a generic byte format for archiving or logging purposes.

## ⚖️ Comparison with Similar Blocks
Compared to other conversion blocks, `ST08B_TO_ARR08B` stands out due to its specialization in converting an 8-byte structure to an 8-byte array. General type conversion functions might be more complex and offer more configuration options, while this block performs a highly optimized and specific task. Blocks for array-to-structure conversion (e.g., `ARR08B_TO_ST08B`) would be the inverse function of this block.


## Conclusion

The ``ST08B_TO_ARR08B`` function block is a simple yet effective way to convert an 8-byte structure into an 8-byte array. It provides a reliable solution for scenarios requiring direct and transparent adaptation of structured data to byte-oriented interfaces or formats. Its clear functionality and implementation make it a valuable tool in the 4diac development environment.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```