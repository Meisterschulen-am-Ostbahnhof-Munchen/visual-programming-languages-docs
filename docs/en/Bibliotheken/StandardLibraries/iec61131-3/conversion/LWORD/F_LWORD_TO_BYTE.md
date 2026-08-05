# F_LWORD_TO_BYTE
<img width="1451" height="216" alt="F_LWORD_TO_BYTE" src="https://github.com/user-attachments/assets/c3044b5b-615a-4431-aacc-9746dab23af0" />
* * * * * * * * * *
## Introduction
The function block `F_LWORD_TO_BYTE` converts a 64-bit value (LWORD) to an 8-bit value (BYTE). This conversion is particularly useful when data needs to be exchanged or processed between systems with different word lengths.
![F_LWORD_TO_BYTE](F_LWORD_TO_BYTE.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**
- **IN**: The input for the 64-bit value (LWORD) to be converted.

### **Data Outputs**
- **OUT**: The output for the converted 8-bit value (BYTE).

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is triggered. The value at input `IN` is read and converted into a BYTE value using the function `LWORD_TO_BYTE`. The result is output at `OUT`, and the event `CNF` signals the completion of the operation.

## Technical Details
- The conversion can result in data loss because a 64-bit value is converted to an 8-bit value. It is important to ensure that the original value is within the representable range of a byte (0 to 255).
- The function block is implemented as a simple function block (SimpleFB) and uses an ST algorithm for the conversion.

## State Overview
1. **Idle State**: Waits for the event `REQ`.

2. **Active State**: Performs the conversion and outputs the result.

3. **Completion State**: Signals completion with `CNF` and returns to the idle state.

## Application Scenarios
- Data Reduction: When only the lower 8 bits of a 64-bit value are relevant.
- Communication with devices that can only process BYTE data.
- Memory optimization in systems with limited resources.

## ⚖️ Comparison with Similar Components
- **F_WORD_TO_BYTE**: Converts a 16-bit value (WORD) to a BYTE.
- **F_DWORD_TO_BYTE**: Converts a 32-bit value (DWORD) to a BYTE.
- **F_LWORD_TO_WORD**: Converts a 64-bit value to a 16-bit value.

## Conclusion

The function block `F_LWORD_TO_BYTE` offers a simple and efficient way to convert 64-bit data to 8-bit data. It is particularly useful in scenarios where only a portion of the data is needed or the target platform supports limited data types. However, be aware of the potential data loss during the conversion.