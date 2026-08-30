# ST04X

* * * * * * * * * *
## Introduction

ST04X is a structured data type that groups four Boolean values. It serves to organize and manage a collection of four individual bits in a single structure.
## Interface Structure

Since ST04X is a data type and not a function block, it does not have event or data inputs/outputs in the sense of a function block or adapter. Instead, it defines an internal structure of data fields.
### **Event Inputs**

Not applicable to a data type.

### **Event Outputs**

Not applicable to a data type.

### **Data Inputs**

Not applicable to a data type.

### **Data Outputs**

Not applicable to a data type.

### **Adapters**

Not applicable to a data type.

**Structure Elements:**

The ST04X structure consists of the following four Boolean fields:

- **X_00** (Type: BOOL, Comment: BIT 00)
- **X_01** (Type: BOOL, Comment: BIT 01)
- **X_02** (Type: BOOL, Comment: BIT 02)
- **X_03** (Type: BOOL, Comment: BIT 03)

## Functionality

As a data type, ST04X does not have an active "function" in the sense of a function block. Its function is passive: It merely defines how four Boolean variables can be logically grouped and referenced as a single unit. This allows for better organization and readability of the code by grouping related bits in a structure.

## Technical Features

- **Compactness**: Groups four individual BOOL values, which can enable more efficient data storage or transmission in some systems.
- **Structuring**: Improves code structure and readability by grouping related bits under a common name.
- **Use in Function Blocks**: This data type can be used as an input or output parameter for function blocks or as an internal variable within a function block to manage groupings of four bits.

## State Overview

Not applicable to a data type. A data type represents a data structure, not a state machine.

## Application Scenarios

- **Status Register**: Mapping of a small status register or group of flags where each bit indicates a specific state or property.
- **Binary Inputs/Outputs**: Grouping of four digital inputs or outputs of a hardware interface.
- **Bit Fields**: When a compact representation of four independent binary pieces of information is required, for example, when processing serial data protocols or device configurations.

## ⚖️ Comparison with Similar Components

ST04X is a data type and therefore cannot be directly compared to function blocks (components).

A comparison would be more feasible with other data types, for example:

- **BOOL**: A single Boolean value. ST04X groups four of them.
- **BYTE**: An 8-bit integer. ST04X provides a structured view of 4 bits, while a BYTE is typically treated as an unstructured 8-bit number. The individual bits of a BYTE would have to be accessed via bitmasks or bitwise operations, whereas with ST04X, each bit is directly accessible by its name (e.g., `myST04X.X_00`).
- **BYTE**: An 8-bit integer. * **Array of BOOL**: An array of BOOLs (`ARRAY[0..3] OF BOOL`) also provides grouping, but access is via indices (`myArray[0]`), whereas ST04X allows access via named fields (`myST04X.X_00`), which can improve readability.

## Conclusion

ST04X is a useful structured data type in 4diac that simplifies the management and organization of four Boolean values. Although it does not offer any active functionality itself, it is an important tool for improving code structure and readability in more complex control programs by logically grouping related bits and enabling direct, named access to each bit.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
