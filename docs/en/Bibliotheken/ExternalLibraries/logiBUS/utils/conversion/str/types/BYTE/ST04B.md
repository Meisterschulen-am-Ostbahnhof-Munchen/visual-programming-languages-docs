# ST04B

* * * * * * * * * *
## Introduction
`ST04B` is a user-defined, structured data type within the 4diac IDE. Unlike a function block (FB), which implements specific functionality, a data type defines a data structure that can be used by function blocks or other data types. This data type groups four individual bytes into a logical unit to simplify their interaction.

## Structure Definition
Since `ST04B` is a data type and not a function block, it does not have interfaces in the sense of event inputs/outputs, data inputs/outputs, or adapters. The following sections adapt the original requirement of an interface structure to represent the internal components of the data type.


### **Components of the Structure**
The structure `ST04B` consists of the following four byte variables:

* **B_00** (Type: `BYTE`): The first byte of the structure (BYTE 00).

* **B_01** (Type: `BYTE`): The second byte of the structure (BYTE 01).

* **B_02** (Type: `BYTE`): The third byte of the structure (BYTE 02).

* **B_03** (Type: `BYTE`): The fourth byte of the structure (BYTE 03).


## Functionality
As a passive data type, `ST04B` has no inherent "function" in the sense of logic or algorithm. Its function is to provide a defined template for data. Instances of this data type can be declared and used in function blocks to store, organize, and exchange data as a coherent unit between different function blocks. The internal components (B_00 to B_03) are directly addressable.

## Technical Details
`ST04B` is defined as `StructuredType` and consists of four consecutive `BYTE` variables. The total size of an instance of this data type is therefore 4 bytes. In the context of the 4diac runtime environment, this data type is stored in memory according to its definition. The internal structure allows direct access to each individual byte via its name (e.g., `myST04B.B_00`).

The 4diac compiler assigns this data type to the package `logiBUS::utils::conversion::types`.

## State Overview
As a passive data type that merely defines a data structure, `ST04B` has no internal logic or state machine in the sense of a function block. Its "state" is determined solely by the values of its four component bytes. Therefore, a state overview in the sense of behavioral states is not applicable.

## Application Scenarios
* **Data Transmission**: Bundling of 4 bytes that are received or sent via a communication interface (e.g., serial, Modbus, CAN) and are to be treated as a unit.

* **Register Mapping**: Representation of a 4-byte register or group of registers in a programmable logic controller (PLC) or other control system.

* **Small Data Packets**: Simplified handling of small, predefined data packets in industrial automation.

* **Type Conversion Utility**: Internally used in conversion function blocks to process specific byte sequences and convert them to other data types.

## ⚖️ Comparison with Similar Building Blocks

* **Array of Bytes (ARRAY OF BYTE [4])**: An array of 4 bytes serves the same purpose for storage. However, ``ST04B`` offers the advantage that individual bytes can be addressed via named fields (`B_00`, `B_01`, etc.) instead of indices (e.g., ``myArray[0]``, ``myArray[1]``), which can improve code readability and self-description.

* **Other structured types**: If the bytes had a specific meaning (e.g., status flag, counter value), more complex structured types with more descriptive variable names or even bit fields might be more appropriate. ``ST04B`` is intentionally generic to allow for flexible byte grouping.

* * **`WORD`, `DWORD`**: These standard data types also represent a specific number of bytes (2 and 4, respectively). However, `ST04B` is more flexible when individual bytes need to be manipulated independently or when byte order (endianness) is important and needs to be explicitly controlled.

## Conclusion
`ST04B` is a basic yet useful structured data type in 4diac that simplifies the management of four bytes as a coherent unit. It improves code readability and modularity, especially in applications that require the exchange or processing of byte-sequenced data. Its simple definition makes it a flexible building block for a wide range of data management tasks in automation technology.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```