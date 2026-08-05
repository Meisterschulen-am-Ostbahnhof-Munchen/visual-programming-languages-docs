# ST08X_TO_ARR08X

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/d556a75a-b21c-4bf2-b1c3-909baea1e51e" />

![ST08X_TO_ARR08X](./ST08X_TO_ARR08X.svg)

* * * * * * * * * *
## Introduction
This function block (FB) is used to convert a specific structure of type `ST08X`, which contains eight individual BOOL values, into an array of eight BOOL values. It enables seamless adaptation of the data representation in automation applications.

## Interface Structure
### **Event Inputs**
* **REQ**: This event is used to initiate the conversion operation. Upon receiving this event, the data from input `IN` is processed and written to output `OUT`.


### **Event Outputs**

* **CNF**: This event is triggered after the data from the `IN` input has been successfully converted to the `OUT` array and the output has been updated.

### **Data Inputs**

* **IN** (`logiBUS::utils::conversion::types::ST08X`): This is the input for the structure of type `ST08X`. This structure contains eight named BOOL fields (X_00 to X_07) to be converted.

### **Data Outputs**

* **OUT** (`BOOL[0..7]`): This is the output for the array of BOOL values. The array has a fixed size of 8 elements containing the converted data from the input structure.

### **Adapters**
This function block does not use any adapters.

## Functionality
The function block `ST08X_TO_ARR08X` performs a direct and deterministic transformation of the input data. When the `REQ` event is received, the individual BOOL fields of the input structure `IN` are assigned to the corresponding index of the `OUT` array:

* `IN.X_00` is assigned to `OUT[0]`.

* `IN.X_01` is assigned to `OUT[1]`.

* ...
* `IN.X_07` is assigned to `OUT[7]`.


After these assignments are complete, the ``CNF`` event is thrown to indicate that the output ``OUT`` has been updated and the converted data is available.

## Technical Features
* **Specific Types**: The function block is specifically designed for converting between the user-defined type ``logiBUS::utils::conversion::types::ST08X`` and a ``BOOL[0..7]`` array.

* **Fixed Mapping**: The mapping of structure fields to array indices is static and cannot be configured at runtime.

* **Atomic Operation**: The conversion is a single, self-contained operation triggered by an input increment event.

## State Overview
The ``ST08X_TO_ARR08X`` function block is stateless. It does not store any internal state or data between executions. Each execution triggered by a `REQ` event processes the data currently assigned to `IN` completely and independently of previous operations.

## Application Scenarios

* **Interface Adaptation**: Ideal for adapting data from a component that provides 8 BOOL values as a structure (`ST08X`) to another component that expects a `BOOL` array with 8 elements (e.g., for visualizations, external devices, or generic loop processing).

* **Data Format Standardization**: If a project uses different conventions for grouping 8 BOOL values, this function block can help bring the data into a consistent format.

* **Compatibility with legacy systems**: Can be used to convert data from more modern structures into array-based formats that are easier for older or simpler systems to process.

## ⚖️ Comparison with similar function blocks
While 4diac-IDE and the IEC 61499 standard provide generic data conversion mechanisms and array manipulation functions, the `ST08X_TO_ARR08X` is a highly specialized function block. General conversion function blocks might offer more flexible handling of different data types or array sizes, but often require configuration or additional logic. This function block provides a dedicated, simple, and efficient solution for this specific conversion case without any configuration overhead.

## Conclusion
The `ST08X_TO_ARR08X` function block is a precise tool for converting an 8-BOOL structure into an 8-BOOL array. Its simplicity and specialization make it an efficient solution for interface adaptation and data formatting in 4diac-based automation applications that require such conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]