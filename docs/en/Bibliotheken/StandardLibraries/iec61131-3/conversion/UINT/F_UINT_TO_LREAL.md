# F_UINT_TO_LREAL

<img width="1452" height="216" alt="F_UINT_TO_LREAL" src="https://github.com/user-attachments/assets/a0008558-2922-435e-9642-d1886e739723" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_LREAL` converts an unsigned 16-bit integer value (UINT) to a 64-bit floating-point value (LREAL). This conversion is particularly useful in control applications where different data types need to be processed.

![F_UINT_TO_LREAL](F_UINT_TO_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. Upon this event, the value at input `IN` is read and converted.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at output `OUT`.

### **Data Inputs**

- **IN** (UINT): The unsigned 16-bit integer value to be converted to an LREAL value.

### **Data Outputs**

- **OUT** (LREAL): The resulting 64-bit floating-point value after conversion.

#### **Adapters**
No adapters are available.

## Functionality
The function block performs the conversion by directly converting the UINT value from `IN` to an LREAL value and outputting it to `OUT`. The conversion occurs when the event `REQ` is triggered, and the event `CNF` signals completion.

## Technical Features

- **Algorithm**: The algorithm is implemented in Structured Text (ST) and consists of a simple assignment (`OUT := IN`).

- **Data Types**: Supports conversion from UINT (0 to 65535) to LREAL (64-bit floating point).

## State Overview

1. **Idle**: Waits for the event `REQ`.

2. **Conversion**: Upon `REQ`, the value from `IN` is read and converted.

3. **Completion**: The event `CNF` is triggered, and the converted value is available at `OUT`.

## Application Scenarios

- **Measurement Processing**: Conversion of discrete sensor values (e.g., raw ADC data) into floating-point values for further calculations.

- **Data Communication**: Conversion of integer values for use in floating-point operations.

## ⚖️ Comparison with Similar Function Blocks

- **F_INT_TO_LREAL**: Converts a signed integer (INT) to LREAL.

- **F_DINT_TO_LREAL**: Converts a 32-bit integer (DINT) to LREAL.

- **F_ULINT_TO_LREAL**: Converts a 64-bit unsigned integer (ULINT) to LREAL.

## Conclusion
The `F_UINT_TO_LREAL` function block provides a simple and efficient way to convert unsigned 16-bit integer values to 64-bit floating-point values. Its clear interface and direct operation make it ideal for applications requiring fast and reliable type conversion.