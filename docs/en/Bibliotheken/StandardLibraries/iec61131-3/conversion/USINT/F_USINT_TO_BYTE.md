# F_USINT_TO_BYTE
<img width="1454" height="214" alt="F_USINT_TO_BYTE" src="https://github.com/user-attachments/assets/c086c1af-bc1b-492e-87cb-d7c3a52dd7a0" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_TO_BYTE` converts an unsigned 8-bit integer value (USINT) into a byte value (BYTE). This conversion is particularly necessary in scenarios where data needs to be exchanged between different formats or systems.
![F_USINT_TO_BYTE](F_USINT_TO_BYTE.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `USINT` (unsigned 8-bit integer) to be converted to a `BYTE` value.

### **Data Outputs**
- **OUT**: The output value of type `BYTE`, representing the result of the conversion.

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The input value `IN`, of type `USINT`, is converted to a value of `BYTE` and output `OUT`. The event `CNF` signals the successful completion of the conversion.

## Technical Features
- The conversion is performed directly without any additional processing steps.
- The block is suitable for use in real-time systems because it does not perform any time-critical operations.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Conversion**: Performs the conversion and outputs the result via `OUT`.

3. **Confirmation**: Sends the `CNF` event to confirm successful conversion.

## Application Scenarios
- Data conversion in control systems.
- Communication between systems with different data types.
- Preprocessing of sensor data.

## ⚖️ Comparison with similar function blocks
- **F_BYTE_TO_USINT**: Performs the reverse conversion (BYTE to USINT).
- **F_INT_TO_STRING**: Converts an integer value to a string, but is more complex to handle.

## 🛠️ Related Exercises
* [Exercise_126b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b_sub.md)

## Conclusion
The `F_USINT_TO_BYTE` function block is a simple and efficient tool for converting `USINT` values to `BYTE` values. Its clear interface structure and direct functionality make it ideal for use in various industrial applications.