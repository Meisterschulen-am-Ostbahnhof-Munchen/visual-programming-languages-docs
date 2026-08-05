# F_LWORD_TO_DWORD

<img width="1461" height="211" alt="F_LWORD_TO_DWORD" src="https://github.com/user-attachments/assets/bf518310-0981-4a9a-b327-5d9ada8d10f1" />

* * * * * * * * * *
## Introduction
The function block `F_LWORD_TO_DWORD` is used to convert an LWORD data type to a DWORD data type. This conversion is useful when data needs to be exchanged between systems or components that use different data types.

![F_LWORD_TO_DWORD](F_LWORD_TO_DWORD.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.


### **Data Inputs**
- **IN**: Input for the LWORD value to be converted.

### **Data Outputs**
- **OUT**: Output for the converted DWORD value.

#### **Adapters**
- No adapters available.

## Functionality
The function block performs the conversion from LWORD to DWORD when the event `REQ` is triggered. The algorithm within the function block uses the function `LWORD_TO_DWORD` to perform the conversion. After successful conversion, the event `CNF` is triggered to signal the completion of the operation.

## Technical Features
- The function block is a simple function block (SimpleFB) and performs a direct conversion.

- There are no additional states or complex logic, as the conversion occurs in a single step.


## State Overview
Since this is a simple function block, there are no state transitions or state machines. The function block reacts directly to the `REQ` event and outputs the result via `CNF`.

## Application Scenarios

- **Data Compatibility**: When one system creates LWORD data, but another system can only process DWORD data.

- **Protocol Conversion**: For communication between different protocols or interfaces that use different data types.

## ⚖️ Comparison with Similar Function Blocks

- **F_DWORD_TO_LWORD**: Performs the reverse conversion (DWORD to LWORD).

- **F_WORD_TO_DWORD**: Converts WORD to DWORD, but has a smaller input size compared to LWORD.


## Conclusion

The `F_LWORD_TO_DWORD` function block is a simple and efficient tool for converting LWORD to DWORD data. Its simplicity and direct functionality make it a reliable solution for data conversion tasks in 4diac IDE-based systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```