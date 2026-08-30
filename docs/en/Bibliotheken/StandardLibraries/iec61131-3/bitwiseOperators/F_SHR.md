# F_SHR

<img width="1350" height="208" alt="F_SHR" src="https://github.com/user-attachments/assets/7ff0f80c-c8c6-4472-85d8-32658fa25627" />
* * * * * * * * * *
## Introduction

The function block `F_SHR` performs a bitwise right shift. It is part of the standard bit operators according to IEC 61131-3 and is used for logical and arithmetic operations in control applications.
![F_SHR](F_SHR.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the right shift. It is linked to the data `IN` and `N`.

### **Event Outputs**

- `CNF`: Confirms the completion of the right shift. Returns the result `OUT`.

### **Data Inputs**

- `IN` (`ANY_BIT`): The input value to be shifted right.
- `N` (`ANY_INT`): The number of bits to shift.

### **Data Outputs**

- `OUT` (`ANY_BIT`): The result of the right shift. The freed bits on the left are padded with zeros.

### **Adapters**

No adapters available.

## Functionality

1. Upon a `REQ` event, the value `IN` is shifted right by `N` bits.
2. The freed bits on the left side are padded with zeros (logical right shift).
3. The result is output via `OUT`, triggering the `CNF` event.

## Technical Features

- Supports all bit data types (`ANY_BIT`), e.g. B. `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD`.
- `N` can use any integer type (`ANY_INT`), e.g. B. `SINT`, `INT`, `DINT`, `LINT`, `USINT`, `UINT`, `UDINT`, `ULINT`.
- The right shift is independent of the sign (logical shift).

## Status Overview

- **Idle**: Waiting for `REQ`.
- **Processing**: Performing the right shift.
- **Completed**: Sending `CNF` with the result.

## Application Scenarios

- Bit manipulation in control algorithms.
- Data compression or extraction.
- Fast division by powers of two (for unsigned numbers).

## ⚖️ Comparison with similar function blocks

- `F_SHL`: Performs a left shift.
- `F_ROR`/`F_ROL`: Rotation operations instead of shifts.
- `F_SHR` is specific for logical right shifts (zero padding).

## Conclusion

The `F_SHR` function block is an efficient tool for bitwise operations in IEC 61131-3 environments. Its simple interface and standards compliance make it ideal for control applications involving bit manipulation.
