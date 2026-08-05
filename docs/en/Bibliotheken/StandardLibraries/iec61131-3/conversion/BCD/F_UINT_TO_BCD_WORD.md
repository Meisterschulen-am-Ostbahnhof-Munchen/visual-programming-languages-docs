# F_UINT_TO_BCD_WORD

<img width="1281" height="185" alt="F_UINT_TO_BCD_WORD" src="https://github.com/user-attachments/assets/8e1d0c92-d549-4131-a8b9-a7bbc0add010" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_BCD_WORD` converts an unsigned integer value (UINT) into a BCD-encoded word (WORD). BCD (Binary Coded Decimal) is a method for representing decimal numbers where each digit is encoded by 4 bits. This function block is particularly useful in applications where numerical values need to be output in a human-readable format, such as in display systems or printers.

![F_UINT_TO_BCD_WORD](F_UINT_TO_BCD_WORD.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The unsigned integer value (UINT) to be converted.

### **Data Outputs**

- **OUT**: The result of the conversion as a BCD-encoded word (WORD).

### **Adapters**
This function block does not use adapters.

## Operation
When the event input `REQ` is triggered, the algorithm is executed that converts the value of `IN` into a BCD-encoded `WORD` and outputs the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features
- The function block implements direct UINT to WORD conversion using BCD encoding.

- The conversion is performed in a single algorithm step, ensuring high efficiency.

## State Overview
The function block has no internal states other than the initial readiness to process the `REQ` event.

## Application Scenarios
- Display controllers that require numeric values in BCD format.

- Printers and other output devices that process BCD-encoded data.

- Systems that require compatibility with legacy BCD-based components.


## ⚖️ Comparison with Similar Building Blocks

Compared to generic conversion building blocks, `F_UINT_TO_BCD_WORD` offers a specialized solution for BCD encoding that can be more efficient and easier to use than general-purpose conversion methods.

## Conclusion
The `F_UINT_TO_BCD_WORD` function block is a specialized tool for the efficient conversion of unsigned integer values to the BCD format. Its simple interface and straightforward operation make it ideal for applications requiring fast and reliable BCD encoding.