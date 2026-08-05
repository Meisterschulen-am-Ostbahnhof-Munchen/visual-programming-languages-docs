# F_UINT_TO_UDINT
<img width="1448" height="216" alt="F_UINT_TO_UDINT" src="https://github.com/user-attachments/assets/25a7fa31-e6ae-414e-9283-52eb7ff84478" />
* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_UDINT` converts a 16-bit unsigned integer value (`UINT`) to a 32-bit unsigned integer value (`UDINT`). This block is part of the `iec61131::conversion` package and is suitable for applications requiring an extension of the bit width of numeric values.
![F_UINT_TO_UDINT](F_UINT_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The 16-bit unsigned integer value to be converted (`UINT`).

### **Data Outputs**
- **OUT**: The converted 32-bit unsigned integer value (`UDINT`).

### **Adapters**
This function block does not use any adapters.

#
## ## Functionality
When the event input `REQ` is triggered, the value of the data input `IN` is read and directly assigned to the data output `OUT`. Since `UDINT` has a larger bit width than `UINT`, the conversion occurs without data loss. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Features
- The conversion is lossless because `UDINT` completely covers the value range of `UINT`.
- The block is deterministic and has no internal states.

## State Overview
The function block has no internal states. The operation is re-executed with each `REQ` event.

## Application Scenarios
- Extending the bit width of sensor data for further processing.
- Ensuring compatibility between systems that use different integer formats.
- Preprocessing data for algorithms that require `UDINT`.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_UINT_TO_UDINT` is specialized and optimized for the specific conversion of `UINT` to `UDINT`.
- Other blocks, such as `F_INT_TO_DINT`, handle signed integers, while this block processes unsigned values.

## 🛠️ Related Exercises
* [Exercise_015](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_015.md)]
* [Exercise_015a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_015a.md)]

## Conclusion
The `F_UINT_TO_UDINT` function block is an efficient and reliable tool for converting 16-bit to 32-bit unsigned integer values. Its simplicity and determinism make it ideal for real-time applications where performance and precision are critical.
