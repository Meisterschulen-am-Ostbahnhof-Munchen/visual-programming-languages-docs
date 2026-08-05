# F_USINT_TO_SINT
<img width="1451" height="214" alt="F_USINT_TO_SINT" src="https://github.com/user-attachments/assets/6cc23cdf-2a2a-43cf-b2fe-3158508fb208" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_TO_SINT` converts an unsigned 8-bit integer value (USINT) to a signed 8-bit integer value (SINT). This block is particularly useful when exchanging data between systems that use different data types.
![F_USINT_TO_SINT](F_USINT_TO_SINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When activated, the input value `IN` is processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output value `OUT` is then available.

### **Data Inputs**
- **IN** (USINT): The unsigned 8-bit integer value to be converted.

### **Data Outputs**
- **OUT** (SINT): The resulting signed 8-bit integer value after the conversion.

#### **Adapters**
No adapters are available.

## Functionality
The function block performs the conversion by converting the USINT value `IN` to a SINT value `OUT`. The conversion occurs directly upon activation of the `REQ` event, and the result is output via the `CNF` event.

## Technical Features
- The conversion is performed without additional parameters or configuration.
- The algorithm is implemented in Structured Text (ST) and uses the function `USINT_TO_SINT`.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Completed**: Sends the `CNF` event with the result.

## Application Scenarios
- Data conversion in control systems.
- Communication between devices with different data types.
- Preprocessing of sensor data.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_INT_TO_REAL` or `F_BOOL_TO_INT` offer conversions between other data types.
- `F_USINT_TO_SINT` specializes in conversion between 8-bit integer types.

## Conclusion
The `F_USINT_TO_SINT` function block is a simple and efficient building block for converting between unsigned and signed 8-bit integer values. Its clear interface and direct functionality make it ideal for use in various control and communication applications.