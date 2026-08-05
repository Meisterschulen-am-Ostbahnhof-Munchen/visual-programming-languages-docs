# F_UDINT_TO_SINT
<img width="1450" height="216" alt="F_UDINT_TO_SINT" src="https://github.com/user-attachments/assets/f2a89cd0-6440-43ae-88db-8360c9ffa1b8" />
* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_SINT` converts a 32-bit unsigned integer value (UDINT) to an 8-bit signed integer value (SINT). This conversion is useful when data needs to be exchanged between systems or components that use different data types.
![F_UDINT_TO_SINT](F_UDINT_TO_SINT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**
- **IN** (UDINT): The unsigned 32-bit integer value to be converted.

### **Data Outputs**
- **OUT** (SINT): The resulting signed 8-bit integer value after conversion.

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion when the event `REQ` is triggered. The algorithm converts the value of `IN` (UDINT) to a SINT value and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Features
- The function block is simple and deterministic, as it only performs a direct type conversion.
- There is no additional logic or error handling for values that are outside the representable range of SINT.

## State Overview

The function block has no internal state. The conversion occurs immediately upon triggering `REQ`.

## Application Scenarios
- Data conversion in control systems where different data types are used.
- Interfaces between systems that require different integer formats.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks like `F_DINT_TO_SINT` or `F_INT_TO_SINT` perform similar conversions, but with different output or input data types.
- `F_UDINT_TO_SINT` is specifically for converting UDINT to SINT.

## Conclusion
The `F_UDINT_TO_SINT` function block is a simple and efficient tool for converting unsigned 32-bit integers to signed 8-bit integers. It is particularly useful in scenarios where such type conversions are needed regularly.