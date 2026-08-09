# ST32B

* * * * * * * * * *
The data type `ST32B` is a structured data type within the 4diac IDE, designed for the aggregation of 32 individual bytes. It serves as a template for data structures that require a fixed length of 32 bytes and allow direct access to individual bytes. This type is registered in the 4diac IDE under the package `logiBUS::utils::conversion::types`.
Since `ST32B` is a structured data type and not a function block, it does not have external event or data interfaces in the conventional sense. Instead, it defines an internal structure of elements that can be accessed in a program.
Not applicable to structured data types. `ST32B` has no event inputs.

Not applicable to structured data types. `ST32B` has no event outputs.

Not applicable to structured data types. `ST32B` has no data inputs; its elements are directly accessible via the type name.

Not applicable to structured data types. `ST32B` has no data outputs; its elements are directly accessible via the type name.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

Not applicable to structured data types. `ST32B` has no adapters.

## Functionality

ST32B` is a passive data type and does not implement any active functionality or logic. It serves merely as a blueprint (schema) for organizing and storing 32-byte values under a single logical name. Instances of this data type can be declared and used in other function blocks or data types to store or transfer data in a structured manner.

The individual bytes are named as follows and can be accessed directly:

- `B_00`: Byte 00
- `B_01`: Byte 01
- ...
- `B_30`: Byte 30
- `B_31`: Byte 31
* **Fixed Size:** The data type `ST32B` is fixed to an exact size of 32 bytes.
* **Direct Byte Access:** Each of the 32 bytes can be addressed individually by its name (`B_00` to `B_31`).
* **Basic Type:** It consists exclusively of the primitive data type `BYTE`, making it ideal for low-level data operations or the representation of raw data.
* **Simplicity:** The structure is deliberately kept simple to ensure efficient use and clear data organization.

As a passive data type, `ST32B` has no internal states in the sense of a state machine. The "state" of an instance of this type is defined solely by the current values of the 32 bytes it contains.

* **Raw Data Transport:** Ideal for transmitting fixed-length raw data packets, for example, from sensors or via communication interfaces such as SPI, I2C, UART, or Ethernet, when the payload has a fixed length of 32 bytes.
* **Message Structures:** Can serve as the basis for simple message formats where a portion of the message frame occupies a defined length of 32 bytes.
* **Memory Image:** For mapping a small, fixed memory area or register set in a controller.
* **Configuration Data:** Storage of 32-byte configuration parameters.

A comparable approach would be the use of an array of type `ARRAY[0..31] OF BYTE`.

The main difference lies in the access method and semantics:

* **`ST32B` (structure):** Allows access to bytes via symbolic names (`B_00`, `B_01`, ...), which can improve code readability and maintainability, especially when individual bytes have a specific meaning.
* **`ARRAY[0..31] OF BYTE` (array):** Allows access via a numeric index (`[0]`, `[1]`, ...), which is advantageous for loops and generic operations.
* While an array can offer more flexibility in sizing, ``ST32B`` provides a clearly defined, named structure that makes the purpose behind each byte more explicit, even though the names are generic.

The ``ST32B`` data type is a fundamental structured data type in 4diac that offers a simple and efficient way to treat 32 bytes as a single unit. Its strength lies in providing a fixed, well-defined structure for raw data, making it a useful tool in applications that require precise control over byte sequences. Although it has no active functionality itself, it is an important foundation for data-driven architectures within 4diac applications.

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de