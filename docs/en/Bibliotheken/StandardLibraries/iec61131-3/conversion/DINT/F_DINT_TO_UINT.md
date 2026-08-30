# F_DINT_TO_UINT

<img width="1442" height="217" alt="F_DINT_TO_UINT" src="https://github.com/user-attachments/assets/19436375-bd4c-4e93-ad90-b387e008a9c2" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_UINT` converts a 32-bit integer value (DINT) to an unsigned 32-bit integer value (UINT). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_DINT_TO_UINT](F_DINT_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `DINT` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `UINT`, representing the result of the conversion.

### **Adapters**

No adapters are defined for this function block.

## Functionality

This function block performs the conversion from `DINT` to `UINT` when the event `REQ` is received. The conversion is performed using the built-in function `DINT_TO_UINT`. After successful conversion, the event `CNF` is triggered, and the converted value is output via the output `OUT`.

## Technical Features

- The conversion is performed directly without any additional delay.
- The block does not support error handling for invalid input values.

## State Overview

1. **Idle**: Waits for the event `REQ`.
2. **Conversion**: Performs the conversion and outputs the result via `OUT`, followed by an event `CNF`.

## Application Scenarios

- Type conversion in control applications where signed values need to be converted to unsigned values.
- Data processing in industrial automation systems.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_DINT_TO_UINT` specializes in converting between `DINT` and `UINT`, thus offering a simpler and more direct solution for this specific use case.

## Conclusion

The `F_DINT_TO_UINT` function block is an efficient tool for the specific conversion between `DINT` and `UINT` data types. Its simplicity and direct functionality make it ideal for applications requiring fast and reliable type conversion.
