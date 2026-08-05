# F_TIME_AS_STRING
<img width="1464" height="212" alt="F_TIME_AS_STRING" src="https://github.com/user-attachments/assets/e9156094-840f-4d48-bc5d-8fd718a9e157" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_AS_STRING` is used to convert a `TIME` value into a `STRING` value. It is particularly useful when time values are needed for display or logging in textual form.
![F_TIME_AS_STRING](F_TIME_AS_STRING.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Triggers the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the successful execution of the function block. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`TIME`): The time value to be converted to a string.

### **Data Outputs**
- **OUT** (`STRING`): The resulting string representing the converted time value.

### **Adapters**
No adapters are defined for this function block.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The input value `TIME` is converted to a value `STRING` and output `OUT`. The conversion is performed using the function `TIME_AS_STRING`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features
- This function block is a simple function block (SimpleFB) and does not perform any complex state transitions.
- The conversion is performed directly without additional parameters.

## State Overview
Since this is a simple function block, there are no state transitions. This block performs the conversion on every `REQ` event and signals completion with `CNF`.

## Application Scenarios
- Displaying timestamps in user interfaces.
- Logging timestamps in textual log files.
- Integration into systems that process timestamps as strings.

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks like `F_INT_AS_STRING` or `F_REAL_AS_STRING`, this block is specifically optimized for converting `TIME` values.
- Similar functionality could also be achieved with a custom algorithm, but this block offers a standardized and reusable solution.

## Conclusion

The `F_TIME_AS_STRING` function block offers a simple and efficient way to convert time values into strings. Its clear interface and direct functionality make it a useful building block for various applications where time values are required in textual form.