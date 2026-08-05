# F_SINT_TO_USINT
<img width="1450" height="213" alt="F_SINT_TO_USINT" src="https://github.com/user-attachments/assets/e1008d5b-c1c4-4a42-8bfd-7d328b59eced" />
* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_USINT` converts a signed 8-bit integer value (SINT) to an unsigned 8-bit integer value (USINT). This conversion is useful when exchanging data between systems that use different representations for numeric values.
![F_SINT_TO_USINT](F_SINT_TO_USINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (SINT): The signed 8-bit integer value to be converted.

### **Data Outputs**
- **OUT** (USINT): The resulting unsigned 8-bit integer value after the conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
When the event `REQ` is triggered, the algorithm that converts the value of `IN` from SINT to USINT is executed and outputs the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features
- The function block performs a direct type conversion, converting the signed value to an unsigned value.
- There is no additional logic for handling overflow conditions or invalid inputs.

## State Overview
The function block has a simple state machine:

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion and triggers `CNF`.

3. No other states, as it is a simple, stateless block.

## Application Scenarios
- Conversion of sensor values that are delivered as signed values but are to be processed as unsigned values.
- Data preparation for communication protocols that require unsigned values.

## ⚖️ Comparison with Similar Function Blocks
- **F_INT_TO_UINT**: Converts signed 16-bit integer values to unsigned 16-bit integer values.
- **F_DINT_TO_UDINT**: Converts signed 32-bit integer values to unsigned 32-bit integer values.
- **F_SINT_TO_USINT** is specific to 8-bit values and is therefore more efficient for this data size.

## Conclusion
The `F_SINT_TO_USINT` function block is a simple yet effective tool for converting signed to unsigned 8-bit integer values. Its simplicity and efficiency make it ideal for applications where such conversions need to be performed regularly.