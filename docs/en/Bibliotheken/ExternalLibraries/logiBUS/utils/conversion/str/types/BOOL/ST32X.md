# ST32X
*(No image available, as this is a data type and not a function block.)*
* * * * * * * * * *
## Introduction
The data type `ST32X` is a user-defined structure data type consisting of 32 individual BOOL variables. It serves to bundle a collection of Boolean states or flags into a single, coherent data structure, which can simplify the handling and passing of status information. The name `ST32X` is derived from "Structure (ST) with 32 X/B (Boolean) bits".
## Interface Structure
Since `ST32X` is a data type and not a function block, it does not have event- or data-related inputs and outputs in the sense of a function block. Its "structure" merely defines its internal elements.

### **Event Inputs**
Not applicable, as `ST32X` is a user-defined data type and not a function block.

### **Event Outputs**
Not applicable, as `ST32X` is a user-defined data type and not a function block.

### **Data Inputs**

The structure consists of the following 32 BOOL elements, which can be considered "inputs" internally, as they receive the values from which the structure is formed:

* `X_00` (Type: BOOL, Comment: BIT 00)
* `X_01` (Type: BOOL, Comment: BIT 01)
* `X_02` (Type: BOOL, Comment: BIT 02)
* `X_03` (Type: BOOL, Comment: BIT 03)
* `X_04` (Type: BOOL, Comment: BIT 04)
* `X_05` (Type: BOOL, Comment: BIT 05)
* `X_06` (Type: BOOL, Comment: BIT 06)
* `X_07` (Type: BOOL, Comment: BIT 07)
* `X_08` (Type: BOOL, Comment: BIT 08)
* `X_09` (Type: BOOL, Comment: BIT 09)
* `B_10` (Type: BOOL, Comment: BIT 10)
* `B_11` (Type: BOOL, Comment: BIT 11)
* `B_12` (Type: BOOL, Comment: BIT 12)
* `B_13` (Type: BOOL, Comment: BIT 13)
* `B_14` (Type: BOOL, Comment: BIT 14)
* `B_15` (Type: BOOL, Comment: BIT 15)
* `B_16` (Type: BOOL, Comment: BIT 16)
* `B_17` (Type: BOOL, Comment: BIT 17)
* `B_18` (Type: BOOL, Comment: BIT 18)
* `B_19` (Type: BOOL, Comment: BIT 19)
* `B_20` (Type: BOOL, Comment: BIT 20)
*   `B_21` (Type: BOOL, Comment: BIT 21)
* `B_22` (Type: BOOL, Comment: BIT 22)
* `B_23` (Type: BOOL, Comment: BIT 23)
* `B_24` (Type: BOOL, Comment: BIT 24)
* `B_25` (Type: BOOL, Comment: BIT 25)
* `B_26` (Type: BOOL, Comment: BIT 26)
* `B_27` (Type: BOOL, Comment: BIT 27)
* `B_28` (Type: BOOL, Comment: BIT 28)
* `B_29` (Type: BOOL, Comment: BIT 29)
* `B_30` (Type: BOOL, Comment: BIT 30)
* `B_31` (Type: BOOL, Comment: BIT 31)

### **Data Outputs**
Not applicable. The structure `ST32X` itself is the "output" because it represents the bundled Boolean values. Individual elements can be accessed using the dot operator (`.`) (e.g., `myST32X.X_00`).

### **Adapters**
Not applicable because `ST32X` is a user-defined data type and not a function block.

### ## Functionality
`ST32X` has no active "function" in the sense of logic or algorithms. It merely serves as a passive data container. Its function is to organize a group of 32 individual BOOL values into a single variable, which simplifies program structuring and the transfer of data between function blocks or program sections. The individual bits of the structure can be accessed, and their values can be set or read.

## Technical Specifications
* **Number of Bits:** The structure comprises 32 independent BOOL variables.
* **Naming:** The elements are named `X_00` to `X_09` and then `B_10` to `B_31`. The comments indicate the bit number in each case. This could indicate an original intention to represent the bits in a word (e.g., DINT), even though they are declared here as separate BOOLs.
* **Memory Efficiency:** The exact memory allocation depends on the compiler implementation. Typically, such a structure would occupy at least 32 bytes (one byte per BOOL) or possibly more, depending on padding and alignment.

## State Overview
As a passive data type, `ST32X` does not have its own state machine. Its "state" is defined solely by the values of the 32 contained BOOL variables. Each bit can be either `TRUE` or `FALSE`.

## Application Scenarios
* **Status Flag Bundling:** When a system needs to manage a large amount of binary status information (e.g., error codes, component operating states, sensor flags), `ST32X` can be used to pass or store it in a single variable.
* **Interface Optimization:** Instead of passing 32 separate BOOL signals to a function block, an instance of `ST32X` can be transmitted over a single data connection.
* **Bit Mapping:** Although the elements are defined as `BOOL`, this structure could be used in conjunction with conversion function blocks (e.g., to convert to `DINT`) to access or manipulate the bits of a 32-bit word.
* * **PLC-like I/O mappings:** In environments similar to PLC programming, such a structure can be used to map digital inputs or outputs.

## ⚖️ Comparison with similar function blocks
* **Standard data types (e.g., `DINT`):** A `DINT` (Double Integer) is also 32 bits wide, but stores the bits as a single numeric value. `ST32X`, on the other hand, treats each bit as a separate Boolean variable, allowing direct access by name without bit masking or bitwise operations.
* **Other structured data types:** Other user-defined structures may exist that bundle a smaller or larger number of BOOLs or mix different data types. ``ST32X`` is specifically designed to hold 32 Boolean values.
* **Array of Boolean Values:** A ``ARRAY[0..31] OF BOOL`` would also store 32 Boolean values. The difference to ``ST32X`` lies in the access method: ``ST32X`` accesses named elements (e.g., ``myST32X.X_00``), while an array accesses its index (e.g., ``myArray[0]``). Named elements are often more readable and more robust against changes in order.

## Conclusion
The ``ST32X`` data typeIt offers a practical method for combining 32 individual Boolean variables into a coherent whole. It promotes code organization and simplifies the passing of extensive status information or flags. Although it does not implement any active logic itself, it is a useful tool in the architecture of complex control programs based on the 4diac IDE.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]