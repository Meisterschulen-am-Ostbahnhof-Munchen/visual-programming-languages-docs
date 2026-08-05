# ST08B
* * * * * * * * * *
## Introduction
The data type `ST08B` is a structured data structure that sequentially groups exactly eight bytes (BYTE). It primarily serves as a container for the efficient grouping and transport of eight individual byte values within an IEC 61499-based control system. This data type is particularly useful for handling raw data, protocol frames, or for the structured transfer of parameterized data blocks between function blocks.
## Interface Structure
`ST08B` is a data type and, as such, does not have event-driven inputs or outputs in the sense of a function block. Its structure is defined exclusively by its data members.
## **Data Inputs**
Not applicable. This section is intended for function blocks.

## **Data Outputs**
Not applicable. This section is intended for function blocks.

## ### **Event Inputs**
Not applicable. This section is for function blocks.

### **Event Outputs**
Not applicable. This section is for function blocks.

### **Adapters**
Not applicable. This section is for function blocks.

## How it Works
As a structured data type (STRUCT), `ST08B` acts as a composite container. It groups eight independent variables of type `BYTE` under a common name. Each byte within the structure is directly addressable via its unique member name (`B_00` to `B_07`). Function blocks can declare variables of type `ST08B` to pass, store, or process all eight bytes as a single unit. Individual bytes are accessed using dot notation (e.g., `MyST08BInstance.B_04`).

## Technical Features
* **Fixed Size:** The structure has a fixed and predictable size of exactly 8 bytes, which is advantageous for memory allocation and communication protocols.
* **Sequential Arrangement:** The bytes are arranged in the order `B_00` to `B_07`. This order is crucial for interpreting the data, for example, when converting it to larger data types such as `WORD`, `DWORD`, or `LWORD`.
* **TypeHash Attribute:** The data type contains the attribute `eclipse4diac::core::TypeHash` with an empty value (`''`). This indicates that type-safe validation via hash value has not (yet) been configured for this user-defined type.

## State Overview
Since this is a passive data type and not an active function block, there is no state machine. The "state" of an instance of `ST08B` is simply the current value of each of its eight byte members.

## Application Scenarios

1. **Data Packaging:** Grouping eight configurable parameters or status values together to be sent from one function block to another.

2. **Protocol Handling:** Representing a fixed data frame header or segment in serial or network communication.

3. **Raw Data Buffer:** Temporary storage of an 8-byte block from a sensor or communication interface before further processing or interpretation.

4. **Conversion Base:** Used as a source or target for conversion function blocks that convert `ST08B` to or generate other data types, such as `LWORD` (64-bit).

## ⚖️ Comparison with Similar Building Blocks
* **Simple Byte Array:** An array of 8 `BYTE` (`ARRAY[0..7] OF BYTE`) could perform a similar function. However, `ST08B` offers the advantage of named access paths (`B_01`), which, unlike index-based access (`Array[1]`), improve code readability and maintainability.
* **LWORD:** The data type `LWORD` also represents 8 bytes (64 bits), but as a single, undivided numeric value. `ST08B` allows targeted access to each individual byte within these 64 bits.
* **Other STRUCT Types:** Similar structured types such as `ST04B` (4 bytes) or `ST16B` (16 bytes) serve the same purpose, but for different amounts of data. `ST08B` fills the gap for 8-byte structured data.

## Conclusion
The `ST08B` is a simple yet extremely useful structured data type for IEC 61499 programming. It provides a clear and structured method for grouping eight bytes of data, thereby promoting readability, maintainability, and type safety in applications that work with fixed data blocks or parameterized datasets. Its fixed size and sequential arrangement make it a reliable building block for data communication and conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]