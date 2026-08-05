# F_BYTE_TO_DWORD

<img width="1243" height="183" alt="F_BYTE_TO_DWORD" src="https://github.com/user-attachments/assets/12ed4687-4afb-4a1c-8e33-7b03054d593d" />

* * * * * * * * * *
## Introduction
The function block `F_BYTE_TO_DWORD` converts a `BYTE` value to a `DWORD` value. This block is particularly useful in scenarios where an extension of the data width is required, for example, when processing sensor data or communicating between systems with different data formats.

![F_BYTE_TO_DWORD](F_BYTE_TO_DWORD.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. This input is coupled to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is coupled to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `BYTE` to be converted to a `DWORD` value.

### **Data Outputs**

- **OUT**: The output value of type `DWORD`, containing the result of the conversion.

### **Adapters**
This function block does not use any adapters.


### ## Functionality
When the event input `REQ` is triggered, the algorithm is executed. This algorithm converts the `BYTE` value at input `IN` into a `DWORD` value and outputs the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features
- The function block is simple and efficient because it directly utilizes the built-in function `BYTE_TO_DWORD`.

- No additional states or complex logic are required.

## State Overview
Because it is a simple function block, there are no state transitions or internal states. The operation is performed atomically upon triggering `REQ`.

## Application Scenarios

- Extending data widths in communication protocols.

- Processing sensor data that is in `BYTE` but needs to be further processed in `DWORD`.

- Compatibility adjustments between different system components.

## ⚖️ Comparison with similar function blocks

- **F_WORD_TO_DWORD**: Converts `WORD` to `DWORD`, similar in functionality, but with a different input data size.

- **F_BYTE_TO_WORD**: Converts `BYTE` to `WORD`, offering a smaller output data size compared to `F_BYTE_TO_DWORD`.

## Conclusion
The `F_BYTE_TO_DWORD` function block is a simple and efficient tool for converting `BYTE` to `DWORD` values. Its clear interface and direct functionality make it ideal for applications requiring data width expansion.