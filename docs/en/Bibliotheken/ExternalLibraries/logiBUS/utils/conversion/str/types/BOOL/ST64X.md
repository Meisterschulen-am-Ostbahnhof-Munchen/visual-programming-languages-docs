# ST64X

*(No image available because this is a data type and not a function block.)*

* * * * * * * * * *
## Introduction

The provided XML definition describes a **DataType** named `ST64X`, not a function block (FB). This structured data type serves as a container for a collection of 64 individual binary values (BOOL variables). It allows 64 independent switches, flags, or status bits to be grouped under a single name and addressed individually via named fields. Although the internal XML comment states "A Structure with 16 BOOLs," the actual definition contains 64 BOOL variables.
## Interface Structure

Since `ST64X` is a data type and not a function block, it does not have direct event or data inputs and outputs in the sense of an FB. Instead, it defines an internal structure of components that can be used as a unified variable within a function block (e.g., as an input or output parameter).

### **Event Inputs**

Not applicable for a data type.

### **Event Outputs**

Not applicable for a data type.

### **Data Inputs**

Not applicable for a data type. The elements listed here are the **internal components** of the `ST64X` structure that hold data. When `ST64X` is used as a data input for a function block, these are the available fields:

| Name | Type | Comment |
| :--- | :--- | :-------- |
| `X_00` | `BOOL` | `BIT 00` |
| `X_01` | `BOOL` | `BIT 01` |
| `X_02` | `BOOL` | `BIT 02` |
| `X_03` | `BOOL` | `BIT 03` |
| `X_04` | `BOOL` | `BIT 04` |
| `X_05` | `BOOL` | `BIT 05` |
| `X_06` | `BOOL` | `BIT 06` |
| `X_07` | `BOOL` | `BIT 07` |
| `X_08` | `BOOL` | `BIT 08` |
| `X_09` | `BOOL` | `BIT 09` |
| `B_10` | `BOOL` | `BIT 10` |
| `B_11` | `BOOL` | `BIT 11` |
| `B_12` | `BOOL` | `BIT 12` |
| `B_13` | `BOOL` | `BIT 13` |
| `B_14` | `BOOL` | `BIT 14` |
| `B_15` | `BOOL` | `BIT 15` |
| `B_16` | `BOOL` | `BIT 16` |
| `B_17` | `BOOL` | `BIT 17` |
| `B_18` | `BOOL` | `BIT 18` |
| `B_19` | `BOOL` | `BIT 19` |
| `B_20` | `BOOL` | `BIT 20` |
| `B_21` | `BOOL` | `BIT 21` |
| `B_22` | `BOOL` | `BIT 22` |
| `B_23` | `BOOL` | `BIT 23` |
| `B_24` | `BOOL` | `BIT 24` |
| `B_25` | `BOOL` | `BIT 25` |
| `B_26` | `BOOL` | `BIT 26` |
| `B_27` | `BOOL` | `BIT 27` |
| `B_28` | `BOOL` | `BIT 28` |
| `B_29` | `BOOL` | `BIT 29` |
| `B_30` | `BOOL` | `BIT 30` |
| `B_31` | `BOOL` | `BIT 31` |
| `B_32` | `BOOL` | `BIT 32` |
| `B_33` | `BOOL` | `BIT 33` |
| `B_34` | `BOOL` | `BIT 34` |
| `B_35` | `BOOL` | `BIT 35` |
| `B_36` | `BOOL` | `BIT 36` |
| `B_37` | `BOOL` | `BIT 37` |
| `B_38` | `BOOL` | `BIT 38` |
| `B_39` | `BOOL` | `BIT 39` |
| `B_40` | `BOOL` | `BIT 40` |
| `B_41` | `BOOL` | `BIT 41` |
| `B_42` | `BOOL` | `BIT 42` |
| `B_43` | `BOOL` | `BIT 43` |
| `B_44` | `BOOL` | `BIT 44` |
| `B_45` | `BOOL` | `BIT 45` |
| `B_46` | `BOOL` | `BIT 46` |
| `B_47` | `BOOL` | `BIT 47` |
| `B_48` | `BOOL` | `BIT 48` |
| `B_49` | `BOOL` | `BIT 49` |
| `B_50` | `BOOL` | `BIT 50` |
| `B_51` | `BOOL` | `BIT 51` |
| `B_52` | `BOOL` | `BIT 52` |
| `B_53` | `BOOL` | `BIT 53` |
| `B_54` | `BOOL` | `BIT 54` |
| `B_55` | `BOOL` | `BIT 55` |
| `B_56` | `BOOL` | `BIT 56` |
| `B_57` | `BOOL` | `BIT 57` |
| `B_58` | `BOOL` | `BIT 58` |
| `B_59` | `BOOL` | `BIT 59` |
| `B_60` | `BOOL` | `BIT 60` |
| `B_61` | `BOOL` | `BIT 61` |
| `B_62` | `BOOL` | `BIT 62` |
| `B_63` | `BOOL` | `BIT 63` |

### **Data Outputs**

Not applicable for a data type. The elements listed above are the **internal components** of the `ST64X` structure that hold data. When `ST64X` is used as a data output of a function block, these are the available fields.

### **Adapters**

Not applicable for a data type.

## Functionality

ST64X` itself has no "function" in the sense of an active component that performs calculations or changes states. Its "function" is to provide a defined structure that serves as a template for data objects. Once instantiated, a variable of type `ST64X` holds 64 individual BOOL values that can be read or written directly via their names (e.g., `MyVariable.X_00`, `MyVariable.B_63`). It is a passive data container.

## Technical Features

- **Structured Data:** Defines a fixed arrangement of 64 BOOL variables.
- **Named Fields:** Each bit has a unique name (`X_00` to `X_09` and `B_10` to `B_63`), which improves code readability compared to purely numeric indices.
- **Size:** Represents 64 bits, which typically occupies 8 bytes of memory (depending on the compiler implementation and padding).
- **Package Information:** The data type is located in the package `logiBUS::utils::conversion::types`, indicating its role in utilities or conversions.

## State Overview

Not applicable for a data type, as it has no internal logic or state machine. The "state" of a `ST64X`The variable is simply the current value of the 64 contained BOOL variables.

## Application Scenarios

- **Bit Fields and Flags:** Ideal for representing a large number of binary status flags, switch positions, or configuration options that need to be organized in a single, coherent block.
- **Hardware Interfaces:** Can be used to map registers or I/O ports where individual bits represent specific functions or states.
- **Compact Data Transmission:** When a large number of BOOL values need to be transmitted efficiently, this type can provide a compact representation.
- **Abstract States:** Represents complex states resulting from the combination of 64 binary features.
*
## ⚖️ Comparison with Similar Building Blocks

Since `ST64X` is a data type, it is not directly compared to function blocks, but rather to other ways of structuring BOOL values:

- **`ARRAY OF BOOL`:** A `ARRAY[0..63] OF BOOL` would also store 64 BOOL values. The main difference lies in the access method: `ST64X` uses named arrays (e.g., `MyVar.X_00`), which is often more readable if each bit has a specific meaning. Arrays use indices (e.g., `MyArray[0]`), which is more flexible for loops and dynamic access, but less informative if the meaning of the individual indices is not obvious.
- **`ARRAY OF BOOL`:** A `ARRAY[0..63] OF BOOL` would also store 64 BOOL values. * **Individual `BOOL` variables:** You could also declare 64 separate `BOOL` variables. However, this would result in a cluttered list of variables and obscure the relationship between the bits. `ST64X` groups them logically.
- **Integer data types (e.g., `LWORD`):** A `LWORD` (64-bit integer) could also store 64 bits. However, accessing individual bits would require bitwise operations (AND, OR, SHIFT), which can be more complex and error-prone than direct array access to a structure. `ST64X` provides direct, symbolic bit access.

## Conclusion

The data type ``ST64X`` is a useful construct in 4diac-ide for defining a structured variable containing 64 individual BOOL values. It provides a clear, named interface to each individual bit, improving code readability and maintainability, especially in applications requiring fine-grained control or status indication with many binary flags. It is a good alternative to ``ARRAY OF BOOL`` or bit manipulations on integer types when the individual meaning of each bit is paramount.

`ST64X`` or bit manipulations on integer types when the individual meaning of each bit is crucial.

`ST64X`` is a useful construct in 4diac-ide for defining a structured variable containing 64 individual BOOL values.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
