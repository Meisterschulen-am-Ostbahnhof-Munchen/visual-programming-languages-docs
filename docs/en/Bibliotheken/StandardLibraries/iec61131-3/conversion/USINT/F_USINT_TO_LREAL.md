# F_USINT_TO_LREAL

<img width="1466" height="214" alt="F_USINT_TO_LREAL" src="https://github.com/user-attachments/assets/2d3923ad-e527-4fda-be3b-8e21c0beb013" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_LREAL` converts an unsigned 8-bit integer value (USINT) to a 64-bit floating-point value (LREAL). This conversion is particularly useful when data needs to be exchanged or processed between systems with different data types.
![F_USINT_TO_LREAL](F_USINT_TO_LREAL.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (USINT): The input value to be converted.

### **Data Outputs**

- `OUT` (LREAL): The converted output value.

### **Adapters**

- No adapters are available.

## Functionality

The function block performs a direct type conversion. Upon the arrival of a `REQ` event, the value of `IN` is converted to the LREAL data type and output to `OUT`. The `CNF` event is then triggered to signal the completion of the conversion.

## Technical Features

- The conversion is performed without any additional scaling or adaptation.
- The block is optimized for simple type conversions and has no complex logic or state management.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Conversion of sensor data in USINT format for calculations requiring LREAL.
- Interfaces between systems with different data type requirements.
- Simple type conversions in automation applications.

## ⚖️ Comparison with similar blocks

- Compared to generic conversion blocks, `F_USINT_TO_LREAL` is specialized and therefore more efficient for this specific conversion.
- Other blocks might offer additional features such as scaling or range checks, which are not required here.

## Conclusion

The `F_USINT_TO_LREAL` function block is a simple and efficient building block for the direct conversion of USINT to LREAL. Its strength lies in its simplicity and specialization, making it ideal for specific use cases where no additional logic is needed.
