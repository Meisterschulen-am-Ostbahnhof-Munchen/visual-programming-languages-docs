# F_UINT_TO_WORD

<img width="1436" height="216" alt="F_UINT_TO_WORD" src="https://github.com/user-attachments/assets/6e3b2752-57b0-41a0-b681-16c58d50879f" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_WORD` converts an unsigned 16-bit integer value (UINT) into a 16-bit word (WORD). This conversion is particularly necessary in scenarios where data needs to be exchanged between different representation formats or systems.

![F_UINT_TO_WORD](F_UINT_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The UINT value to be converted.

### **Data Outputs**
- **OUT**: The converted WORD value.

#### **Adapters**
- No adapters available.

## Functionality
The function block performs the conversion by converting the UINT value of `IN` into a WORD using the function `UINT_TO_WORD` and outputting the result to `OUT`. The conversion is triggered by the event `REQ` and confirmed by `CNF`.

## Technical Features
- The conversion is performed directly without any additional processing.

- The function block is deterministic and has no internal states.

## State Overview
The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Data conversion in control systems.

- Communication between systems that use different data types.

- Integration of legacy systems that require WORD data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks such as `F_INT_TO_WORD` or `F_BYTE_TO_WORD`, `F_UINT_TO_WORD` is specifically designed for converting unsigned 16-bit integers.

- The function block has a simpler structure than generic conversion blocks that support multiple data types.


## Conclusion

The `F_UINT_TO_WORD` function block offers an efficient and direct solution for converting UINT to WORD values. Its simplicity and determinism make it a reliable choice for control and communication applications.