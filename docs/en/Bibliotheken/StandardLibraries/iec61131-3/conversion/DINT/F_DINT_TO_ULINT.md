# F_DINT_TO_ULINT
<img width="1451" height="217" alt="F_DINT_TO_ULINT" src="https://github.com/user-attachments/assets/00d56131-c3f4-44e3-b204-7fb2373bc4e8" />
* * * * * * * * * *
## Introduction
The function block `F_DINT_TO_ULINT` converts a 32-bit signed integer value (`DINT`) into a 64-bit unsigned integer value (`ULINT`). This block is particularly useful when data needs to be exchanged between systems with different data types.
![F_DINT_TO_ULINT](F_DINT_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this event is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event, along with the converted value, is output at data output `OUT`.

### **Data Inputs**
- **IN** (`DINT`): The signed 32-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`ULINT`): The unsigned 64-bit integer value containing the result of the conversion.

### **Adapters**
- No adapters are available.

### ## Functionality

The function block performs the conversion of `DINT` to `ULINT` as soon as the event `REQ` is received. The algorithm `REQ` is executed, converting the value of `IN` using the function `DINT_TO_ULINT` and outputting it to `OUT`. Finally, the event `CNF` is triggered to signal the successful completion of the operation.

## Technical Features
- The function block supports direct conversion without additional parameters.
- The conversion is performed without data loss because the `ULINT` type covers a larger value range than `DINT`.

## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Conversion State**: Performs the conversion and sets the output `OUT`.

3. **Acknowledgement State**: Triggers the `CNF` event and returns to the idle state.

## Application Scenarios
- Data conversion in control systems that use different data types.
- Integration of components that require unsigned 64-bit values.
- Increased compatibility between different systems.

## ⚖️ Comparison with similar function blocks
- **F_INT_TO_ULINT**: Converts a smaller signed integer (`INT`) to `ULINT`.
- **F_LINT_TO_ULINT**: Converts a 64-bit signed integer (`LINT`) to `ULINT`.
- **F_DINT_TO_LINT**: Converts `DINT` to a signed 64-bit integer (`LINT`).

## Conclusion

The `F_DINT_TO_ULINT` function block provides a simple and efficient way to convert signed 32-bit integer values to unsigned 64-bit integer values. Its clear interface and reliable operation make it ideal for applications requiring safe and lossless data type conversion.