# ST16B

* * * * * * * * * *
## Introduction

The data type `ST16B` is a structured data component defined in the 4diac framework. Unlike a function block (FB), `ST16B` has no inherent logic or executable functions. Instead, it serves as a fixed container for 16 individual byte values. Its primary purpose is to provide a clearly defined structure for handling fixed-size raw data packets, which is particularly important in communication protocols or when interacting with low-level hardware interfaces.
## Interface Structure

Since `ST16B` is a data type and not a function block, it does not have event or data interfaces in the conventional sense. Its "structure" refers to the definition of its internal components, i.e., the individual bytes that comprise it.
### **Event Inputs**

Not applicable, as `ST16B` is a data type and not a function block, and therefore does not process events.

### **Event Outputs**

Not applicable, as `ST16B` is a data type and not a function block, and therefore does not generate events.

### **Data Inputs**

Not applicable, as `ST16B` is a data type and not a function block, and therefore does not have direct data inputs in the context of function block connections.

### **Data Outputs**

Not applicable, as `ST16B` is a data type and not a function block, and therefore does not have direct data outputs in the context of function block connections.

### **Adapter**

Not applicable, as `ST16B` is a data type and not a function block, and therefore does not implement any adapter interfaces.

### Component Data Structure

ST16B` consists of 16 individual variables of type `BYTE`, arranged sequentially:

| Name | Type | Description |
| :--- | :----- | :----------- |
| B_00 | BYTE | BYTE 00 |
| B_01 | BYTE | BYTE 01 |
| B_02 | BYTE | BYTE 02 |
| B_03 | BYTE | BYTE 03 |
| B_04 | BYTE | BYTE 04 |
| B_05 | BYTE | BYTE 05 |
| B_06 | BYTE | BYTE 06 |
B_07 | BYTE | BYTE 07 |
B_08 | BYTE | BYTE 08 |
B_09 | BYTE | BYTE 09 |
B_10 | BYTE | BYTE 10 |
B_11 | BYTE | BYTE 11 |
B_12 | BYTE | BYTE 12 |
B_13 | BYTE | BYTE 13 |
B_14 | BYTE | BYTE 14 |
B_15 | BYTE | BYTE 15 |

## Functionality

ST16B` itself has no active functionality. It is a passive data container. Its function is to provide a defined memory template for 16 bytes. Each byte (`B_00` to `B_15`) can be read and written individually. This structured access to individual bytes enables granular data manipulation and easy assignment to communication fields or memory areas.

## Technical Features

* **Fixed Size:** The data type `ST16B` has a fixed size of exactly 16 bytes. This is advantageous for predictable memory usage and compatibility with protocols that expect fixed lengths.
* **Direct Byte Access:** Each of the 16 bytes is directly accessible via its specific name (e.g., `MyVariable.B_00`).
* **Raw Data Container:** Ideal for storing and transporting raw data whose content will be interpreted later.
* **Architecture Independence:** As a collection of bytes, the basic structure is relatively platform-independent, although the interpretation of the bytes can vary across different systems (e.g., endianness for larger values spread across multiple bytes).

## State Overview

Not applicable, as `ST16B` is a data type and does not have internal states in the sense of a function block (e.g., initialization, execution, error). The "states" of `ST16B` are simply the current values stored in its 16-byte components.

## Application Scenarios

* **Communication Protocols:** Ideal for packaging or unpacking messages for protocols such as Modbus, CAN bus, or proprietary serial protocols where data packets have a fixed size of 16 bytes.
* **Hardware Interfaces:** Mapping of registers or data blocks in low-level interfaces that operate in fixed byte patterns.
* **Binary Data Buffer:** Used as a buffer for binary data read from or sent to external sources.
* **Hashe or ID Caching:** For applications that need to store 128-bit hashes (e.g., MD5) or long IDs that are exactly 16 bytes long.

## ⚖️ Comparison with Similar Building Blocks

* **`ARRAY[0..15] OF BYTE`:** `ST16B` is similar to a 16-byte array. The main difference lies in the access method: `ST16B` uses named components (`B_00`, `B_01`, etc.), while an array allows access via indices (`MyArray[0]`, `MyArray[1]`). Named components can improve readability if each byte has a specific semantic meaning within the 16 bytes.
* **Other structured data types:** Compared to user-defined structures that mix different data types (INT, REAL, BOOL), `ST16B` specializes in pure byte collections. It offers a flat, uniform structure.

## Conclusion

The data type `ST16B` is a simple yet effective structure for handling fixed-size 16-byte data blocks. It provides a clear and readable way to access individual bytes within such a block. Although it is not a function block and does not implement its own logic, it is a valuable tool in 4diac for applications that require precise control at the byte level, especially in communication and hardware interaction.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
