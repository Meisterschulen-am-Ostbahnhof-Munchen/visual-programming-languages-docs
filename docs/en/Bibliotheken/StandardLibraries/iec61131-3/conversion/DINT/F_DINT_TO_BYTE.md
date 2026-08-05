# F_DINT_TO_BYTE

<img width="1437" height="212" alt="F_DINT_TO_BYTE" src="https://github.com/user-attachments/assets/ed116d5d-f0ed-4f4d-9ddc-489b45dec70f" />

* * * * * * * * * *
## Introduction
The function block `F_DINT_TO_BYTE` converts a 32-bit integer value (DINT) to an 8-bit integer value (BYTE). This conversion is particularly useful when data needs to be exchanged or processed between systems with different word lengths.

![F_DINT_TO_BYTE](F_DINT_TO_BYTE.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the successful completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `DINT` (32-bit integer) to be converted.

### **Data Outputs**

- **OUT**: The output value of type `BYTE` (8-bit integer) containing the result of the conversion.

### **Adapters**
This function block does not have any adapter interfaces.


### ## Functionality
When the event input `REQ` is triggered, the algorithm is executed, converting the value at input `IN` (of type `DINT`) into a value of `BYTE`. The result is output at `OUT`, and the event `CNF` signals the completion of the operation.

The algorithm used is:

```ST
OUT := DINT_TO_BYTE(IN);
```
## Technical Features

- Converting `DINT` to `BYTE` can result in data loss if the original value is outside the representable range of `BYTE` (0 to 255).

- The function block is simple and deterministic, without internal states or complex logic.

## State Overview

The function block has no internal state. Execution occurs exclusively upon triggering the `REQ` event.

## Application Scenarios

- Reducing data width for communication with peripheral devices that can only process BYTE data.

- Preprocessing data for systems with limited storage capacity.

- Integration into larger control systems where different data types need to be converted.


## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_DINT_TO_BYTE` is specialized and optimized for the specific conversion of `DINT` to `BYTE`.

- Similar blocks like `F_INT_TO_BYTE` or `F_WORD_TO_BYTE` offer conversions between other data types, but with similar functionality.

## Conclusion
The `F_DINT_TO_BYTE` function block is a simple and efficient tool for converting 32-bit integers to 8-bit values. Its simplicity and determinism make it reliable, but users should consider potential data loss with large input values. Ideal for applications where space-saving data representation is required.