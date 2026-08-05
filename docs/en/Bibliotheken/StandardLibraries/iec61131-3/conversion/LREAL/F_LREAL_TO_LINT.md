# F_LREAL_TO_LINT

<img width="1447" height="214" alt="F_LREAL_TO_LINT" src="https://github.com/user-attachments/assets/e03961d0-f79d-4f0f-b085-02a7f2c18bc2" />

* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_LINT` is used to convert an LREAL value (64-bit floating-point number) to a LINT value (64-bit integer). This conversion is particularly necessary in scenarios where floating-point numbers need to be converted to integers, for example, when processing sensor values or controlling actuators.

![F_LREAL_TO_LINT](F_LREAL_TO_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This input triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. This output signals the completion of the conversion.


### **Data Inputs**

- **IN**: LREAL (64-bit floating-point number). The input value to be converted.

### **Data Outputs**

- **OUT**: LINT (64-bit integer). The converted output value.

#### **Adapters**
No adapters available.

## Functionality
This function block performs the conversion from LREAL to LINT as soon as the event `REQ` is received. The conversion is carried out using the function `LREAL_TO_LINT`, which converts the input value `IN` to the output value `OUT`. After the conversion is complete, the event `CNF` is triggered.


## Technical Features
- The conversion truncates the decimal part of the floating-point number.

- The value is not rounded.

- Values outside the representable range of LINT may result in overflow problems.

## State Overview
The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Conversion of sensor values (e.g., temperature measurements) into integers for further processing.

- Control of actuators that expect integer values.

- Data preprocessing in control systems.

## ⚖️ Comparison with Similar Function Blocks

- `F_REAL_TO_INT`: Converts REAL (32-bit floating-point number) to INT (16-bit integer).

- `F_LREAL_TO_DINT`: Converts LREAL (64-bit floating-point number) to DINT (32-bit integer).

- `F_LREAL_TO_LINT` offers higher accuracy through the use of 64-bit integers.

## Conclusion
The function block `F_LREAL_TO_LINT` is a simple and efficient building block for converting 64-bit floating-point numbers to 64-bit integers. It is particularly suitable for applications requiring high accuracy and a large value range. Its simple interface and direct operation make it easy to integrate into existing control systems.