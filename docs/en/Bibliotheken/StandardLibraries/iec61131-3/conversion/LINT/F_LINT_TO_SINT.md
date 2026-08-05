# F_LINT_TO_SINT
<img width="1438" height="214" alt="F_LINT_TO_SINT" src="https://github.com/user-attachments/assets/a76f6188-5a80-4252-a7d7-56944d50fde0" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_SINT` converts a 64-bit integer value (`LINT`) into an 8-bit integer value (`SINT`). This conversion is useful when data needs to be exchanged or processed between systems with different word lengths.
![F_LINT_TO_SINT](F_LINT_TO_SINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is connected to data output `OUT`.

### **Data Inputs**
- **IN** (`LINT`): The 64-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`SINT`): The resulting 8-bit integer value after conversion.

### **Adapters**
No adapters are available.

### ## Functionality
When the event `REQ` is triggered, the algorithm is executed, converting the value of `IN` (of type `LINT`) to a `SINT` value and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features
- Data loss can occur if the original `LINT` value is outside the representable range of `SINT` (-128 to 127).
- The function block is simple and deterministic, without internal states or complex logic.

## State Overview

This function block has no internal states. Execution occurs solely in response to the `REQ` event.

## Application Scenarios
- Data reduction during transmission between systems with different word widths.
- Processing of sensor data where only the lower 8 bits are relevant.
- Compatibility with older systems that can only process 8-bit data.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_LINT_TO_SINT` is specialized and optimized for converting `LINT` to `SINT`.
- Other conversion blocks might offer additional features such as overflow handling or scaling, which is not the case here.

## Conclusion

The `F_LINT_TO_SINT` function block is a simple and efficient tool for converting 64-bit to 8-bit integers. Its simplicity makes it robust and easy to understand, although it lacks advanced features such as overflow control. It is ideal for applications requiring direct and fast conversion.