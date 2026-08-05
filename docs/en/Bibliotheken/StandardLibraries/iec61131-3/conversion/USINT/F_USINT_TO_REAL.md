# F_USINT_TO_REAL
<img width="1451" height="214" alt="F_USINT_TO_REAL" src="https://github.com/user-attachments/assets/f1f498f3-f7f6-48bb-9136-b03a341a2ec4" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_TO_REAL` converts an unsigned 8-bit integer value (USINT) into a 32-bit floating-point value (REAL). This conversion is particularly necessary in scenarios where numeric values of different data types need to be processed or used further.
![F_USINT_TO_REAL](F_USINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: An unsigned 8-bit integer value (USINT) to be converted to a REAL value.

### **Data Outputs**
- **OUT**: The resulting 32-bit floating-point value (REAL) after the conversion.

#### **Adapters**
This function block does not use any adapters.

## Operation
The function block performs the conversion by directly converting the USINT value from `IN` to the REAL data type and outputting it to `OUT`. The conversion occurs synchronously upon receiving the `REQ` event and is confirmed by the `CNF` event.

## Technical Features
- The conversion is performed without additional scaling or rounding.
- The block is optimized for simple conversions and does not provide error handling for invalid values.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Completed**: Sends the `CNF` event and outputs the converted value.

## Application Scenarios
- Conversion of sensor values (e.g., raw ADC data) into floating-point values for further calculations.

## Application Scenarios - Integration into control systems that need to process different data types.

## ⚖️ Comparison with similar function blocks
- Compared to generic conversion blocks, `F_USINT_TO_REAL` is specialized and therefore more efficient for this specific conversion.
- Other blocks, such as `F_INT_TO_REAL` or `F_DINT_TO_REAL`, are designed for other integer data types.

## Conclusion
The `F_USINT_TO_REAL` function block is a simple and efficient function block for converting unsigned 8-bit integers to floating-point values. Its simplicity and direct operation make it ideal for applications requiring fast and reliable type conversion.