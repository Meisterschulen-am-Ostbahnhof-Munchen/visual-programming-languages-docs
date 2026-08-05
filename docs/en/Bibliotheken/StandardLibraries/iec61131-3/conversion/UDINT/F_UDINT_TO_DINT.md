# F_UDINT_TO_DINT
<img width="1454" height="212" alt="F_UDINT_TO_DINT" src="https://github.com/user-attachments/assets/c47b354a-12d3-401a-b4b6-b6e8f6493ba0" />
* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_DINT` converts an unsigned 32-bit integer value (UDINT) to a signed 32-bit integer value (DINT). This conversion is useful in scenarios where data is exchanged between systems that use different data types.
![F_UDINT_TO_DINT](F_UDINT_TO_DINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (UDINT): The unsigned 32-bit integer value to be converted.

### **Data Outputs**
- **OUT** (DINT): The resulting signed 32-bit integer value after conversion.

#### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion by transforming the value of input `IN` from type `UDINT` to type `DINT`. The conversion occurs synchronously when the event `REQ` is triggered. After the conversion is complete, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The conversion is performed directly without additional processing.
- The function block is suitable for use in real-time systems.
- The implementation is in Structured Text (ST).

## State Overview
1. **Idle State**: Waits for the event `REQ`.

2. **Conversion State**: Performs the conversion when `REQ` is triggered.

3. **Acknowledgement State**: Triggers `CNF` as soon as the conversion is complete.

## Application Scenarios
- Data conversion in control systems.
- Interfaces between systems that use different data types.
- Real-time data processing requiring type conversions.

## ⚖️ Comparison with similar function blocks
- Compared to generic conversion function blocks, `F_UDINT_TO_DINT` specializes in converting between `UDINT` and `DINT`.
- Other function blocks might offer additional features such as range checks or error handling, which is not the case here.

## Conclusion
The function block `F_UDINT_TO_DINT` is a simple and efficient function block for converting between unsigned and signed 32-bit integers. It is particularly useful in scenarios where fast and direct type conversion is required.