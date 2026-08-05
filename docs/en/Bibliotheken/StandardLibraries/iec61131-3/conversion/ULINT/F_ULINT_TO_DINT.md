# F_ULINT_TO_DINT

<img width="1453" height="214" alt="F_ULINT_TO_DINT" src="https://github.com/user-attachments/assets/0a9c4fad-0e7e-45ea-a121-a14bf7015759" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_DINT` converts a `ULINT` value (64-bit unsigned integer) to a `DINT` value (32-bit signed integer). This conversion is particularly relevant in scenarios where data needs to be exchanged between systems with different data types.

![F_ULINT_TO_DINT](F_ULINT_TO_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN** (`ULINT`): The unsigned 64-bit value to be converted.

### **Data Outputs**

- **OUT** (`DINT`): The result of the conversion as a signed 32-bit value.

### **Adapters**
No adapters are present.


### ## Functionality
When the `REQ` event is triggered, the algorithm is executed, converting the `ULINT` value at input `IN` to a `DINT` value and outputting the result at output `OUT`. Subsequently, the `CNF` event is triggered to signal the completion of the conversion.

## Technical Details
- Data loss can occur if the original `ULINT` value is outside the representable range of `DINT` (i.e., greater than 2³¹-1).

- The function block is part of the `iec61131::conversion` package.

## State Overview
The function block has no internal states. The conversion occurs immediately upon receipt of the `REQ` event.

## Application Scenarios

- Data conversion in control systems that use different data types.

- Integration of systems that use different bit widths for integers.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_ULINT_TO_DINT` specializes in converting `ULINT` to `DINT`.

- Other conversion blocks may support different data types or conversion directions.


## Conclusion

The `F_ULINT_TO_DINT` function block offers a simple and efficient way to convert unsigned 64-bit values to signed 32-bit values. Its use is beneficial in scenarios with varying data type requirements; however, potential data loss during the conversion should be considered.