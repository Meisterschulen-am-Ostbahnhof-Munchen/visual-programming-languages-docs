# ARR08X_TO_ST08X
<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/f6ca4174-d362-4551-a80d-487df811f414" />
![ARR08X_TO_ST08X](./ARR08X_TO_ST08X.svg)
* * * * * * * * * *
## Introduction
This function block (FB) is used to convert an array of 8 BOOL values (ARR08X) into a corresponding structure of 8 BOOL values (ST08X). It enables easy conversion between these two data formats.
## Interface Structure
### **Event Inputs**
* **REQ**: An event that triggers the conversion. When REQ is received, the value of input `IN` is processed, and the result is provided at output `OUT`.

### **Event Outputs**
* **CNF**: An acknowledgment event that is triggered once the conversion is complete and the output `OUT` has been updated.

### **Data Inputs**
* **IN**: An array of 8 BOOL values (BOOL[0..7]) representing the source data for the conversion.

### **Data Outputs**
* **OUT**: A structure of type `logiBUS::utils::conversion::types::ST08X` containing the converted 8 BOOL values.

### **Adapters**
This function block has no adapters.

### ## Functionality
The function block `ARR08X_TO_ST08X` performs a direct, element-by-element assignment of values from the input array `IN` to the corresponding fields of the output structure `OUT`. On each `REQ` event, the value of the `IN` array is read, and the individual elements of the array `IN[0]` to `IN[7]` are assigned to the fields `X_00` to `X_07` of the `ST08X` structure. After the assignment, the `CNF` event is triggered.

The assignments are made as follows:

* `OUT.X_00 := IN[0];`
* `OUT.X_01 := IN[1];`
* `OUT.X_02 := IN[2];`
* `OUT.X_03 := IN[3];`
* `OUT.X_04 := IN[4];`
* `OUT.X_05 := IN[5];`
* `OUT.X_06 := IN[6];`
* `OUT.X_07 := IN[7];`

## Technical Features
* **Data Type Conversion**: This function block specializes in converting a generic BOOL array into a specific BOOL structure of type `ST08X`. This structure type must be known to the system (via `IMPORT logiBUS::utils::conversion::types::ST08X;`).

## Technical Features
* **Data Type Conversion**: This function block specializes in converting a generic BOOL array into a specific BOOL structure of type `ST08X`. * **Fixed Size**: This function block is designed for arrays and structures with exactly 8 BOOL elements. It is not variable for other array sizes.
* **Determinism**: The conversion is direct and deterministic. Execution occurs immediately upon receiving the `REQ` event.

## State Overview
The `ARR08X_TO_ST08X` function block is a stateless function block. It does not store any internal states between calls. Each execution of the function block is independent of previous executions and is based solely on the current input values.

## Application Scenarios
* **Interface Adaptation**: Ideal for adapting data formats between different system components, especially when one component prefers or expects an array and another a structure.
* **Standardized Data Access**: Enables access to individual Boolean values via named fields (`X_00`, `X_01`, etc.) instead of array indices, which can improve code readability.
* **Visualization**: Simplifies integration with visualization systems that may prefer a structured representation of Boolean signals over an array.
* **Legacy Systems**: Can serve as a bridge between older systems that may use Boolean arrays and newer components that work with structures.

## ⚖️ Comparison with Similar Blocks
* **Manual Assignment**: The functionality could also be implemented through direct assignments in the control program's code (e.g., in a `ST` block). The `ARR08X_TO_ST08X` function block encapsulates this logic in a reusable function block, increasing modularity and clarity.
* **Generic Converters**: Unlike a generic converter that could handle arbitrary array sizes or types, this block is specifically designed for 8-element BOOL arrays and the `ST08X` structure. This simplifies implementation but makes it less flexible for other sizes.

## Conclusion
The `ARR08X_TO_ST08X` function block is a useful, specialized block for efficiently and clearly converting 8-element BOOL arrays into an 8-element BOOL structure. It contributes to improved code readability and modular architecture in 4diac applications, especially in scenarios requiring data format adaptation.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]