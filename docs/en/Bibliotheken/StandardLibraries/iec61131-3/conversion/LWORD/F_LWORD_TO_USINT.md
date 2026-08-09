# F_LWORD_TO_USINT

<img width="1462" height="214" alt="F_LWORD_TO_USINT" src="https://github.com/user-attachments/assets/3e074b62-8455-47a2-93d5-a1b212894115" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_USINT` converts a 64-bit value (LWORD) to an 8-bit unsigned integer (USINT). This conversion is particularly useful when data from a larger range of values needs to be transformed into a smaller, more specific range.
![F_LWORD_TO_USINT](F_LWORD_TO_USINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion and outputs the result via the data output `OUT`.

### **Data Inputs**

- **IN (LWORD)**: The 64-bit value to be converted to a USINT value.

### **Data Outputs**

- **OUT (USINT)**: The resulting 8-bit unsigned integer value after the conversion.

### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The algorithm converts the 64-bit input value `IN` into an 8-bit unsigned integer value and stores the result in `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Details

- The conversion is performed by the built-in function `LWORD_TO_USINT`.
- Note that when converting from a larger to a smaller data type, data loss may occur if the original value is outside the representable range of the target type.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion. 3. **Acknowledge State**: Sends the `CNF` event and returns to the idle state.

## Application Scenarios

- Processing 64-bit data that needs to be reduced to 8 bits.
- Communication between systems with different data widths.
- Memory optimization in embedded systems.

## ⚖️ Comparison with Similar Components

- **F_LWORD_TO_BYTE**: Also converts LWORD to an 8-bit value, but without a sign (BYTE).
- **F_LWORD_TO_INT**: Converts to a 16-bit signed integer, offering a larger value range, but with a sign.

## Conclusion

The `F_LWORD_TO_USINT` function block is a simple and efficient tool for converting 64-bit data to 8-bit unsigned integer values. It is particularly useful in scenarios where storage space or data bandwidth is limited. However, it should be ensured that the original data is within the representable range of the target type to avoid data loss.