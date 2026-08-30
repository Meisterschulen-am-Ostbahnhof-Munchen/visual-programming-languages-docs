# F_ULINT_AS_WSTRING

<img width="1490" height="214" alt="F_ULINT_AS_WSTRING" src="https://github.com/user-attachments/assets/b7e7929e-cc1c-4998-8090-b8ceb12f4d39" />
* * * * * * * * * *
## Introduction

The function block `F_ULINT_AS_WSTRING` converts an unsigned 64-bit integer value (`ULINT`) into a Unicode string (`WSTRING`). This functionality is particularly useful in scenarios where numeric values are needed for display or further processing as text.
![F_ULINT_AS_WSTRING](F_ULINT_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The unsigned 64-bit integer value (`ULINT`) to be converted to a Unicode string.

### **Data Outputs**

- **OUT**: The resulting Unicode string (`WSTRING`) after the conversion.

### **Adapters**

- No adapters are present.

## Functionality

The function block performs the conversion when the event `REQ` is triggered. The value at input `IN` is converted into a Unicode string using the function `ULINT_AS_WSTRING` and output at `OUT`. The event `CNF` signals the successful completion of the conversion.

## Technical Features

- Uses the function `ULINT_AS_WSTRING` for the conversion.
- Supports the full value range of `ULINT` (0 to 18,446,744,073,709,551,615).

## State Overview

- **Idle**: Waits for the `REQ` event.
- **Converting**: Performs the conversion and outputs the result via `CNF`.

## Application Scenarios

- Displaying large numeric values in user interfaces.
- Logging numeric data in text format.
- Preparing data for communication with systems that expect string data.

## ⚖️ Comparison with Similar Function Blocks

- Compared to `F_INT_AS_WSTRING` or `F_DINT_AS_WSTRING`, this function block supports the larger value range of `ULINT`.
- Similar to `F_ULINT_TO_WSTRING`, but with direct conversion without additional formatting options.

## Conclusion

The `F_ULINT_AS_WSTRING` function block offers a simple and efficient way to convert large unsigned integer values into Unicode strings. Its clear interface and reliable functionality make it a valuable component in the 4diac IDE.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
