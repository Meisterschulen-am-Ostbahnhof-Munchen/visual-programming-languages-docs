# FIELDBUS_WORD_TO_PERCENT

<img width="888" height="143" alt="FIELDBUS_WORD_TO_PERCENT" src="https://github.com/user-attachments/assets/e6b552d3-4641-408d-b965-e2eb5c8cdef0" />

* * * * * * * * * *
## Introduction
The function block `FIELDBUS_WORD_TO_PERCENT` converts a REAL value in the range of 0.0 to 100.0 into a WORD value in the range of 0 to FAFF (hexadecimal). This is particularly useful for signal processing in fieldbus systems that operate according to the SAE J1939 and ISO 11783 standards.

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. Linked to the data input `WI`.

#### **Event Outputs**

- **CNF**: Confirms the completion of the conversion. Outputs the converted value via the data output `WO`.

### **Data Inputs**

- **WI** (WORD): The input value to be converted.

### **Data Outputs**

- **WO** (WORD): A mirror image of the input value `WI`, if the signal is valid.

- **(REAL)**: The converted REAL value in the range of 0.0 to 100.0.

## Functionality
The function block first checks whether the input value `WI` is less than or equal to the defined `VALID_SIGNAL_W`. If so, the value is mirrored (`WO := WI`) and then converted into a REAL value between 0.0 and 100.0. The conversion is performed by dividing the converted WORD value by the maximum valid signal value (`VALID_SIGNAL_W`).

## Technical Features

- The block supports the SAE J1939 and ISO 11783 standards.

- Conversion only occurs if the input signal is valid (`WI <= VALID_SIGNAL_W`).

- The output `WO` is used to validate the input signal.

## State Overview

1. **Initialization**: The block waits for a `REQ` event.

2. **Processing**: Upon `REQ`, `WI` is checked and converted if necessary.

3. **Output**: Upon successful conversion, `CNF` is triggered and the results are output.

## Application Scenarios

- Signal processing in agricultural machinery (ISO 11783).

- Control systems in commercial vehicles (SAE J1939).

- General fieldbus communication where WORD-to-REAL conversions are required.

## ⚖️ Comparison with Similar Blocks
- Unlike generic conversion blocks, `FIELDBUS_WORD_TO_PERCENT` is specifically optimized for the requirements of SAE J1939 and ISO 11783.

- Other blocks may not offer direct mirroring of the input signal for validation.

## Conclusion
The `FIELDBUS_WORD_TO_PERCENT` block is a specialized converter for signal processing in fieldbus systems. Its simple interface and robust functionality make it ideal for applications that require reliable conversion from WORD to REAL values.