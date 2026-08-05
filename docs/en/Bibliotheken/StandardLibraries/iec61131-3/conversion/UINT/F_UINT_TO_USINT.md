# F_UINT_TO_USINT

<img width="1454" height="216" alt="F_UINT_TO_USINT" src="https://github.com/user-attachments/assets/a0991cf7-1e8b-4cee-971c-5bf9334f137f" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_USINT` converts an unsigned 16-bit integer value (UINT) to an unsigned 8-bit integer value (USINT). This block is part of the `iec61131::conversion` library and implements a simple type conversion.

![F_UINT_TO_USINT](F_UINT_TO_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion process. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (UINT): The unsigned 16-bit integer value to be converted.

### **Data Outputs**

- **OUT** (USINT): The resulting unsigned 8-bit integer value after conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
When the `REQ` event is triggered, the algorithm that converts the `IN` value from UINT to USINT is executed and outputs the result to `OUT`. The ``CNF`` event is then triggered to signal the successful completion of the operation. The conversion is performed by truncating the higher-order bits if the input value exceeds the USINT range.

## Technical Features
- **Value Range Handling**: Since USINT can only represent values from 0 to 255, higher-order bits are discarded for input values outside this range. This can lead to data loss.

- **Deterministic Behavior**: The conversion is performed in a single execution step without state management.

## State Overview

The function block is stateless and re-executes the conversion with each ``REQ`` event.

## Application Scenarios

- **Data Reduction**: Use in systems where storage space is limited and data size reduction is required.


## Data Reduction - **Protocol Adaptation**: Adapts data formats for communication protocols that only support 8-bit data.

## ⚖️ Comparison with Similar Function Blocks

- **F_UINT_TO_SINT**: Converts UINT to a signed 8-bit integer (SINT), handling the value range differently.

- **F_UINT_TO_INT**: Retains the 16-bit size but converts to a signed type.

## Conclusion
`F_UINT_TO_USINT` is a simple and efficient function block for converting 16-bit to unsigned 8-bit data. Its use is ideal in scenarios where a space-saving representation is required; however, the possibility of data loss with large input values should be considered.