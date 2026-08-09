# SPLIT_DWORD_INTO_WORDS

![SPLIT_DWORD_INTO_WORDS](https://github.com/user-attachments/assets/393aad99-3222-4c5f-981b-4795868b5052)

* * * * * * * * * *
## Introduction

The function block `SPLIT_DWORD_INTO_WORDS` is used to split a 32-bit DWORD into two 16-bit WORDs. This functionality is particularly useful when working with data that is stored as a DWORD but needs to be further processed in separate WORD parts.
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the successful execution of the function block. Linked to the data outputs `WORD_00` and `WORD_01`.

### **Data Inputs**

- **IN**: DWORD (32-bit) to be split into two WORDs.

### **Data Outputs**

- **WORD_00**: First WORD (16-bit) of the DWORD.
- **WORD_01**: Second WORD (16-bit) of the DWORD.

### **Adapters**

This function block does not use adapters.

## Functionality

The function block takes a DWORD as input and splits it into two WORDs:

- `WORD_00` contains the lower 16 bits of the DWORD (`IN.%W0`).
- `WORD_01` contains the upper 16 bits of the DWORD (`IN.%X1`).

The split occurs with each `REQ` event, and the result is confirmed with the `CNF` event.

## Technical Details

- The implementation is in Structured Text (ST).
- The function block is part of the `eclipse4diac::utils::splitting` package.

## State Overview

The function block has no internal state. Processing occurs immediately with each `REQ` event.

## Application Scenarios

- Processing DWORD data originating from hardware registers or communication protocols.
- Splitting 32-bit values for further processing in 16-bit systems.

## ⚖️ Comparison with similar blocks

- Unlike generic bit manipulation blocks, `SPLIT_DWORD_INTO_WORDS` specializes in splitting DWORDs into WORDs.
- Similar blocks might offer additional flexibility, such as selecting which bits to extract, but are often more complex to use.

## Conclusion

The `SPLIT_DWORD_INTO_WORDS` function block provides a simple and efficient way to split DWORD data into its WORD components. Its specialized functionality makes it particularly useful for applications that regularly perform such data conversions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
