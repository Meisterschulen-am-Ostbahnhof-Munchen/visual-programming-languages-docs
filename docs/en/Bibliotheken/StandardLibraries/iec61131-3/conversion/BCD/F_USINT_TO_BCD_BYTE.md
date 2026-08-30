# F_USINT_TO_BCD_BYTE

<img width="1293" height="181" alt="F_USINT_TO_BCD_BYTE" src="https://github.com/user-attachments/assets/80d3e282-af2a-4b59-89db-9d093b6ef103" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_BCD_BYTE` converts an unsigned 8-bit integer value (USINT) into a BCD-encoded byte (BYTE). BCD (Binary Coded Decimal) is an encoding in which each decimal digit is represented by four bits.
![F_USINT_TO_BCD_BYTE](F_USINT_TO_BCD_BYTE.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: An unsigned 8-bit integer value (USINT) to be converted to BCD.

### **Data Outputs**

- **OUT**: The result of the conversion as a BCD-encoded byte (BYTE).

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion when the event `REQ` occurs. The algorithm converts the input value `IN` from USINT to a BCD-encoded byte and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features

- The function block is deterministic and does not perform any internal state changes.
- The conversion is performed directly via the function `USINT_TO_BCD_BYTE`.

## State Overview

The function block has no internal state. The conversion is performed anew with each `REQ` event.

## Application Scenarios

- Display control for seven-segment displays.
- Communication with devices that expect BCD-encoded data.
- Data conversion in control systems that require the BCD format.

## ⚖️ Comparison with Similar Function Blocks

- Unlike generic conversion blocks, `F_USINT_TO_BCD_BYTE` is specialized for converting USINT to BCD.

Other blocks might offer additional features such as error handling or different encodings, but are often more complex.

## Conclusion

The function block `F_USINT_TO_BCD_BYTE` is an efficient tool for the specific task of converting USINT to BCD. Its simplicity and determinism make it a reliable choice in control applications that require BCD-encoded data.
