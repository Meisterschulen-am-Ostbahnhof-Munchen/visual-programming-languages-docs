# F_ULINT_TO_WORD

<img width="1448" height="214" alt="F_ULINT_TO_WORD" src="https://github.com/user-attachments/assets/8be2ddee-0d88-4c60-98ec-e97dc61f329c" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_WORD` converts a 64-bit unsigned integer value (ULINT) to a 16-bit unsigned integer value (WORD). This block is part of the `iec61131::conversion` package and implements a simple type conversion.

![F_ULINT_TO_WORD](F_ULINT_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion process. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: ULINT (64-bit unsigned integer) - The input value to be converted.

### **Data Outputs**

- **OUT**: WORD (16-bit unsigned integer) - The result of the conversion.

#### **Adapters**
No adapters are available.

## Functionality
This function block performs the conversion from ULINT to WORD when the `REQ` event occurs. The conversion is carried out using the built-in function `ULINT_TO_WORD`. After successful conversion, the `CNF` event is triggered.


### **Adapters**

# ## Technical Features
- The block does not support overflow error handling (since ULINT has a larger value range than WORD).

- The conversion is instantaneous and without any additional delay.

## State Overview

The block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Type conversion in control applications where ULINT values need to be converted to WORD values.

- Data reduction when only the lower 16 bits of a ULINT value are relevant.

## ⚖️ Comparison with Similar Blocks
- Similar blocks such as `F_DINT_TO_WORD` or `F_LINT_TO_WORD` offer conversions from other integer types to WORD, but with different value ranges and precision.


## Conclusion

The `F_ULINT_TO_WORD` function block is a simple and efficient tool for converting ULINT to WORD values. It is particularly useful in scenarios where data width reduction is required. However, be aware of the potential data loss when converting from larger to smaller data types.