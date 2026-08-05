# F_TIME_AS_WSTRING
<img width="1479" height="212" alt="F_TIME_AS_WSTRING" src="https://github.com/user-attachments/assets/ed6f36e7-4f40-4837-a19d-4f35b3fbce62" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_AS_WSTRING` converts a TIME value to a WSTRING value. This is particularly useful when time values are needed for display or logging in a human-readable format.
![F_TIME_AS_WSTRING](F_TIME_AS_WSTRING.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Normal execution call. When this input is triggered, the function block performs the conversion.

### **Event Outputs**
- **CNF**: Confirmation of execution. Triggered after successful conversion.

### **Data Inputs**
- **IN**: Input for the TIME value to be converted.

#
## ### **Data Outputs**
- **OUT**: Output for the converted WSTRING value.

#### **Adapters**
This function block has no adapters.

## Functionality
The function block converts the incoming TIME value (`IN`) into a WSTRING value (`OUT`) as soon as the event `REQ` is triggered. The conversion is performed using the function `TIME_AS_WSTRING`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion is performed directly and without additional parameters.

## State Overview
The function block has no complex states. It responds to the `REQ` event by executing the algorithm and confirms the execution with the `CNF` event.

## Application Scenarios
- Displaying time values in user interfaces.
- Logging timestamps in a readable format.
- Integration into systems that require time values as strings.

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks, `F_TIME_AS_WSTRING` specializes in converting TIME to WSTRING.
- Other blocks might offer additional formatting options, but this block is simple and efficient.

## Conclusion
The `F_TIME_AS_WSTRING` function block is a simple and effective tool for converting TIME values to WSTRING. It is particularly suitable for applications where time values need to be displayed or processed in a readable form.
