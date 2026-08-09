# ST02B

* * * * * * * * * *
## Introduction

ST02B` is a user-defined, structured data type within the 4diac IDE. It defines a data structure that combines two individual bytes into a logical unit. This simplifies the handling of byte pairs.
## Structure Definition

Since `ST02B` is a data type and not a function block, it has no interfaces in the sense of event inputs/outputs, data inputs/outputs, or adapters. Instead, the internal components of the data type are described here.
## **Components of the Structure**

The structure `ST02B` consists of the following two byte variables:

* **B_00** (Type: `BYTE`): The first byte of the structure (BYTE 00).
* **B_01** (Type: `BYTE`): The second byte of the structure (BYTE 01).

## Functionality

As a passive data type, `ST02B` has no inherent "function." Its function is to provide a defined template for data. Instances of this data type can be used to store, organize, and exchange data as a unit between different functional blocks.

## Technical Details

ST02B` is defined as `StructuredType` and consists of two consecutive `BYTE` variables. Therefore, the total size of an instance of this data type is 2 bytes.

## Application Scenarios

* **Data Transfer**: Bundling 2 bytes that should be treated as a single unit.
* **Register Mapping**: Representation of a 2-byte register (similar to a WORD, but with explicit byte access).
* **Small Data Packets**: Simplified handling of small, predefined data packets.

## ⚖️ Comparison with Similar Building Blocks

* **Array of Bytes (ARRAY OF BYTE [2])**: An array of 2 bytes serves the same purpose. However, `ST02B` offers the advantage of named fields (B_00, B_01).
* **`WORD`**: Also represents 2 bytes. `ST02B` is more flexible if the individual bytes need to be manipulated independently.

## Conclusion

ST02B` is a simple, useful structured data type for managing two bytes as a coherent unit.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
