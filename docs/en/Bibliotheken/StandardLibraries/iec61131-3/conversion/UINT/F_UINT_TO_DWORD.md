# F_UINT_TO_DWORD

<img width="1452" height="216" alt="F_UINT_TO_DWORD" src="https://github.com/user-attachments/assets/c6603f80-b56e-4aa5-92ad-42ed328a3833" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_DWORD` converts a UINT value (16-bit unsigned integer) to a DWORD value (32-bit unsigned integer). This conversion is particularly necessary in scenarios where data with different bit widths needs to be processed or transmitted.
![F_UINT_TO_DWORD](F_UINT_TO_DWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: UINT value (16-bit) to be converted to a DWORD value.

### **Data Outputs**

- **OUT**: DWORD value (32-bit) containing the result of the conversion.

#### **Adapters**

- No adapters are present.

## Functionality

The function block performs the conversion as soon as an event arrives at input `REQ`. The algorithm `REQ` converts the UINT value at input `IN` to a DWORD value and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features

- The conversion is performed without data loss, as the value range of UINT (0 to 65535) can be fully mapped to DWORD (0 to 4294967295).
- The function block is part of the `iec61131::conversion` package.

## State Overview

The function block has no internal state. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Data conversion in control systems when different bit widths need to be harmonized.
- Integration into larger function block networks that process both UINT and DWORD data.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion blocks (e.g., `F_INT_TO_DINT`), `F_UINT_TO_DWORD` specializes in converting 16-bit to 32-bit unsigned integers.
- Similar blocks might offer additional features such as scaling or limit checks, which is not the case here.

## Conclusion

The `F_UINT_TO_DWORD` function block provides a simple and efficient way to convert UINT values to DWORD values. Its clear interface and deterministic operation make it ideal for use in control and automation solutions.
