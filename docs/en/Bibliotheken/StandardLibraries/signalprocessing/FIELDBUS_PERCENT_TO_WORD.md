# FIELDBUS_PERCENT_TO_WORD

<img width="919" height="181" alt="FIELDBUS_PERCENT_TO_WORD" src="https://github.com/user-attachments/assets/559a5a2e-44fd-433f-b22a-d685fe90c062" />
* * * * * * * * * *
## Introduction

The function block `FIELDBUS_PERCENT_TO_WORD` converts a REAL value in the range of 0.0 to 100.0 into a WORD value in the range of 0 to FAFF (hexadecimal). This function block is particularly suitable for signal processing in fieldbus systems according to the SAE J1939 and ISO 11783 standards.
## Interface Structure

### **Event Inputs**

- `REQ`: Trigger event for the conversion. Linked to the input value `RI`.

### **Event Outputs**

- `CNF`: Confirmation event triggered after successful conversion.

### **Data Inputs**

- `RI` (REAL): Input value in the range 0.0 to 100.0 to be converted.

### **Data Outputs**

- (WORD): The converted output value in the range 0 to FAFF (hexadecimal).

### **Adapters**

No adapters available.

## Functionality

The function block performs the following steps:

1. Multiplication of the input REAL value (`RI`) by the converted maximum valid signal value (`FIELDBUS_SIGNAL::VALID_SIGNAL_W`).
2. Conversion of the result to a UDINT value.
3. Converting the UDINT value to the final WORD output value.

The conversion is performed using the following formula:

FIELDBUS_PERCENT_TO_WORD = UDINT_TO_WORD(REAL_TO_UDINT(RI * UDINT_TO_REAL(WORD_TO_UDINT(FIELDBUS_SIGNAL::VALID_SIGNAL_W))))

## Technical Features

- Uses special type conversion functions (REAL_TO_UDINT, UDINT_TO_WORD, etc.)
- Works with the constant value `FIELDBUS_SIGNAL::VALID_SIGNAL_W` as the maximum limit
- Embedded in the package `eclipse4diac::signalprocessing`

## State Overview

1. Wait state: Waits for the `REQ` event
2. Process state: Conversion is performed upon `REQ` input
3. Output state: `CNF` is triggered after successful conversion

## Application Scenarios

- Signal processing in agricultural machinery
- Vehicle control systems
- Industrial automation with fieldbus communication
- Process data conversion between different systems

## ⚖️ Comparison with similar modules

- Specialized to the specific requirements of SAE J1939 and ISO 11783
- Offers more precise control over the value range than generic conversion blocks
- Optimized for use in signal processing

## Conclusion

The `FIELDBUS_PERCENT_TO_WORD` function block is a specialized tool for the precise conversion of percentage values into fieldbus-specific WORD values. Its clear interface and efficient implementation make it particularly suitable for applications in mobile machine control and industrial automation.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
