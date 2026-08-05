# F_LREAL_TO_USINT

<img width="1463" height="214" alt="F_LREAL_TO_USINT" src="https://github.com/user-attachments/assets/65089d2d-a285-4427-8a17-fbb9a66adf8b" />

* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_USINT` converts an LREAL value (64-bit floating-point number) to a USINT value (8-bit unsigned integer). This conversion is particularly useful when floating-point numbers need to be converted to unsigned integers, for example, for controlling hardware registers or communicating with systems that can only process integers.

![F_LREAL_TO_USINT](F_LREAL_TO_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: LREAL (64-bit floating-point number) – The input value to be converted.

### **Data Outputs**

- **OUT**: USINT (8-bit unsigned integer) – The result of the conversion.

### **Adapters**

- No adapters are present.

## Functionality
The function block performs the conversion by executing the algorithm `REQ` as soon as the event `REQ` occurs. The algorithm converts the LREAL value `IN` to a USINT value using the function `LREAL_TO_USINT` and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Details
- The conversion truncates the floating-point value to an 8-bit unsigned integer. Note that values outside the range of 0 to 255 can lead to unexpected results (overflow/underflow).

- The block is implemented as a simple function block (SimpleFB) and uses an ST algorithm for the conversion.

## State Overview
The function block has no internal state. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of sensor values (e.g., temperature, voltage) into unsigned integers for controlling hardware.

- Communication with systems that can only process integers (e.g., older controllers or protocols).

- Data reduction when high precision is not required.

## ⚖️ Comparison with Similar Blocks

- Compared to `F_REAL_TO_USINT` (conversion of 32-bit floating-point numbers), this block offers higher input precision through the use of 64-bit floating-point numbers.

- Similar blocks such as `F_LREAL_TO_INT` or `F_LREAL_TO_UINT` offer conversions to other integer types with different value ranges.


## 🛠️ Related Exercises

* [Exercise_126b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)

## Conclusion
The `F_LREAL_TO_USINT` function block is a simple yet effective tool for converting 64-bit floating-point numbers to 8-bit unsigned integers. It is particularly suitable for applications requiring a limited output size; however, the input signal's range should be considered to avoid overflows.