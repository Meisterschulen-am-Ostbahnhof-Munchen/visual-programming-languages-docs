# F_WORD_BCD_TO_UINT

<img width="1281" height="182" alt="F_WORD_BCD_TO_UINT" src="https://github.com/user-attachments/assets/37d8f223-a93a-45ff-8ae6-a51b72d499a3" />
* * * * * * * * * *
## Introduction

The function block `F_WORD_BCD_TO_UINT` converts a BCD-encoded WORD value into an unsigned integer (UINT). This is particularly useful in applications where data in BCD format needs to be processed or displayed.
![F_WORD_BCD_TO_UINT](F_WORD_BCD_TO_UINT.svg)
## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- `IN` (WORD): The BCD-encoded input value to be converted.

### **Data Outputs**

- `OUT` (UINT): The converted unsigned integer value.

### **Adapters**

This function block does not use adapters.

## Operation

When the `REQ` event is triggered, the BCD-encoded value at the input `IN` is converted to an unsigned integer value. The result is output at `OUT`, and the `CNF` event signals the completion of the conversion.

## Technical Features

- The function block is simple and direct, without complex state logic.
- The conversion is performed using the function `WORD_BCD_TO_UINT`.

## State Overview

Since it is a simple function block, there are no complex states. The block reacts directly to the `REQ` event with a conversion and the output of the result.

## Application Scenarios

- Conversion of BCD-encoded data from external devices or sensors.
- Use in control systems that need to process BCD data.
- Display of BCD data in a human-readable format.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_WORD_BCD_TO_UINT` specializes in BCD to UINT conversion.
- Other blocks might support additional features such as error handling or different encoding formats, but they are more complex.

## Conclusion

The `F_WORD_BCD_TO_UINT` function block is an efficient tool for the specific task of BCD to UINT conversion. Its simplicity and straightforward operation make it ideal for applications requiring fast and reliable conversions.