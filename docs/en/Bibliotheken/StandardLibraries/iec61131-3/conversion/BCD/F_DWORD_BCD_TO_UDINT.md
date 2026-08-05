# F_DWORD_BCD_TO_UDINT

<img width="1089" height="154" alt="F_DWORD_BCD_TO_UDINT" src="https://github.com/user-attachments/assets/4f68ef0e-2d87-4362-94ac-25386376948e" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_BCD_TO_UDINT` converts a BCD-encoded DWORD value to a UDINT value. BCD (Binary Coded Decimal) is an encoding method where each digit of a decimal number is represented by four bits. This function block is particularly useful in applications that need to process BCD-encoded data.

![F_DWORD_BCD_TO_UDINT](F_DWORD_BCD_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This event input is linked to the data input `IN`.


### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (DWORD): The BCD-encoded input value to be converted to a UDINT value.

### **Data Outputs**

- `OUT` (UDINT): The converted UDINT value.

### **Adapters**
This function block has no adapters.

## Operation
The function block performs the conversion when the `REQ` event is triggered. The conversion is performed using the function ``DWORD_BCD_TO_UDINT``, which converts the BCD-encoded value ``IN`` into a UDINT value. After the conversion is complete, the event ``CNF`` is triggered, and the converted value is available at the output ``OUT``.

## Technical Features
- The function block has a simple structure and contains only one algorithm for the conversion.

- The conversion is performed directly without additional state management.

## State Overview

The function block has no internal state. The conversion is performed anew with each ``REQ`` event.

## Application Scenarios

- Processing of BCD-encoded data from external devices or sensors.

- Conversion of BCD-encoded values to UDINT format for further calculations.

## ⚖️ Comparison with similar function blocks

- Compared to generic conversion function blocks, `F_DWORD_BCD_TO_UDINT` specializes in converting BCD-encoded DWORD values to UDINT values.

- Other conversion function blocks might offer additional features or flexibility, but may be less efficient for this specific use case.

## Conclusion
The `F_DWORD_BCD_TO_UDINT` function block is an efficient tool for the specific task of BCD-to-UDINT conversion. Its simplicity and straightforward operation make it a reliable solution for applications requiring this type of conversion.