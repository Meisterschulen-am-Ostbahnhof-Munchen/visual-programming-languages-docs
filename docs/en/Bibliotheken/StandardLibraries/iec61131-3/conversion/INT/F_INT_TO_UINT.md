# F_INT_TO_UINT

<img width="1218" height="183" alt="F_INT_TO_UINT" src="https://github.com/user-attachments/assets/ab9715b9-eb59-48da-9f6d-c159088ae19c" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_UINT` converts a signed integer value (`INT`) to an unsigned integer value (`UINT`). This conversion is useful when exchanging data between systems that use different data types, or when unsigned processing is required.
![F_INT_TO_UINT](F_INT_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN** (`INT`): The signed integer value to be converted.

### **Data Outputs**

- **OUT** (`UINT`): The resulting unsigned integer value after the conversion.

### **Adapters**

No adapters are used.

## Functionality

The function block performs the conversion from `INT` to `UINT` when the event `REQ` is triggered. The conversion is performed using the function ``INT_TO_UINT(IN)``. After successful conversion, the event ``CNF`` is triggered, and the converted value is available at output ``OUT``.

## Technical Features

- The conversion is performed without additional parameters or configuration.
- The block is implemented as a simple function block (``SimpleFB``) and uses an ST algorithm for the conversion.

## State Overview

1. **Idle State**: Waits for the ``REQ`` event.
2. **Conversion State**: Performs the conversion and sets the output ``OUT``.
3. **Acknowledgement State**: Triggers the `CNF` event and returns to the idle state.

## Application Scenarios

- **Data Processing**: Converts sensor values or control data in `INT` format for systems that expect `UINT`.
- **Communication**: Prepares data for transmission between systems with different data type requirements.

## ⚖️ Comparison with Similar Blocks

- **F_UINT_TO_INT**: Performs the reverse conversion from `UINT` to `INT`.
- **Generic Conversion Blocks**: May offer more flexibility but are also more complex to use.

## Conclusion

The `F_INT_TO_UINT` function block is a simple and efficient tool for converting signed to unsigned integer values. Its clear interface and simple functionality make it ideal for applications requiring fast and reliable type conversion.
