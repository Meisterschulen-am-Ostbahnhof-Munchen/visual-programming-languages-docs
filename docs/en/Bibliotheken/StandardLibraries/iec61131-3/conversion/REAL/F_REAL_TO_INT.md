# F_REAL_TO_INT
<img width="1423" height="216" alt="F_REAL_TO_INT" src="https://github.com/user-attachments/assets/35987aee-ae88-4b7f-9f53-776f056c104e" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_INT` converts a REAL value (floating-point number) to an INT value (integer). This conversion is particularly useful when data needs to be exchanged between systems that use different data types.
![F_REAL_TO_INT](F_REAL_TO_INT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: The input for the REAL value to be converted.

### **Data Outputs**
- **OUT**: The output for the converted INT value.

#### **Adapters**
- No adapters are available.

## Functionality
The function block performs the conversion by converting the REAL value at input `IN` into an INT value and outputting the result at output `OUT`. The conversion is triggered by the event `REQ` and confirmed by the event `CNF`.

## Technical Details
- The conversion is performed using the function `REAL_TO_INT`, which converts the REAL value into an INT value.
- The function block is simple and efficient because it does not use complex algorithms or state machines.

## State Overview
The function block has no internal states. The conversion occurs immediately after the `REQ` event is triggered.

## Application Scenarios
- **Data Conversion**: Converting sensor values (floating-point numbers) to integers for further processing.
- **Interface Compatibility**: Adapting data between systems that expect different data types.

## ⚖️ Comparison with Similar Blocks
- **F_TRUNC**: Converts REAL to INT by truncating the decimal places, while `F_REAL_TO_INT` performs standard rounding.
- **F_ROUND**: Rounds REAL to INT, similar to `F_REAL_TO_INT`, but with specific rounding rules.

## Conclusion

The `F_REAL_TO_INT` function block is a simple and effective tool for converting floating-point numbers to integers. Its simplicity and direct functionality make it ideal for applications requiring fast and straightforward data type conversion.