# F_UDINT_TO_BCD_DWORD

<img width="1304" height="185" alt="F_UDINT_TO_BCD_DWORD" src="https://github.com/user-attachments/assets/9028a6e3-4da9-4881-90d3-71ad99cbbef7" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_BCD_DWORD` converts an unsigned 32-bit integer value (UDINT) into a BCD-encoded DWORD. This conversion is particularly useful in applications where numeric values need to be represented or processed in a human-readable format.
![F_UDINT_TO_BCD_DWORD](F_UDINT_TO_BCD_DWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: An unsigned 32-bit integer value (UDINT) to be converted into a BCD-encoded DWORD.

### **Data Outputs**

- **OUT**: The result of the conversion as a BCD-encoded DWORD.

#### **Adapters**

No adapters are available.

## Functionality

The function block performs the conversion as soon as the event `REQ` is received. The algorithm converts the value at input `IN` from UDINT to a BCD-encoded DWORD and outputs the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Details

- The conversion is performed using the function `UDINT_TO_BCD_DWORD`, which is implemented in the function block's algorithm.
- The function block is part of the package `iec61131::conversion`.

## State Overview

1. **Wait State**: The function block waits for the event `REQ`.
2. **Active State**: Upon receiving `REQ`, the conversion is performed and the result is output to `OUT`.
3. **Confirmation State**: After successful conversion, `CNF` is triggered, and the function block returns to the wait state.

## Application Scenarios

- **Display Control**: Converting numeric values for display on seven-segment displays or LCDs.
- **Data Communication**: Preparing data for transmission in BCD-encoded protocols.
- **Printer Control**: Converting numeric values for printing in a readable format.

## ⚖️ Comparison with Similar Function Blocks

- **F_UDINT_TO_STRING**: Converts a UDINT to a string, but is less efficient for BCD-specific applications.
- **F_UDINT_TO_DWORD**: Performs a direct type conversion without BCD encoding.

## Conclusion

The function block `F_UDINT_TO_BCD_DWORD` provides an efficient and specialized solution for converting unsigned 32-bit integers to BCD-encoded DWORDs. Its simple interface and reliable operation make it ideal for applications that require BCD encoding.