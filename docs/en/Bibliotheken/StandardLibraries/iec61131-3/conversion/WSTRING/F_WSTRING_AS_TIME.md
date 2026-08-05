# F_WSTRING_AS_TIME

<img width="1481" height="214" alt="F_WSTRING_AS_TIME" src="https://github.com/user-attachments/assets/508ad921-2d01-48fe-b8ef-0c57d37b7f10" />

* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_TIME` is used to convert a string in WSTRING format into a TIME value. This block is particularly useful when time values are in string format and need to be converted to TIME format for use in further calculations or control logic.

![F_WSTRING_AS_TIME](F_WSTRING_AS_TIME.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. When this event input is triggered, the WSTRING value contained in the data input `IN` is converted into a TIME value.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. This event, along with the converted TIME value, is output at data output `OUT`.

### **Data Inputs**

- **IN** (WSTRING): The string to be converted into a TIME value.

### **Data Outputs**

- **OUT** (TIME): The converted TIME value.

#### **Adapters**
This function block has no adapters.

## Functionality
When event input `REQ` is triggered, the WSTRING value contained in data input `IN` is converted into a TIME value using the function `WSTRING_AS_TIME`. The result is output at the data output `OUT`, and the event `CNF` signals the successful completion of the conversion.

## Technical Features
- The function block has a simple structure and contains only one algorithm that performs the conversion.

- There are no additional states or complex logic, as the conversion is performed directly without intermediate steps.

## State Overview
Since it is a simple function block, there are no explicit states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- **Data Conversion**: When time values are available as strings (e.g., from user input or an external data source) and need to be converted into the TIME format.

- **Interface Communication**: When communicating with systems that transmit time values as strings.


## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_AS_TIME**: Similar function block, but it uses STRING instead of WSTRING. `F_WSTRING_AS_TIME` is suitable for Unicode strings.

- **F_TIME_AS_WSTRING**: Performs the reverse conversion (TIME to WSTRING).

## Conclusion
The function block `F_WSTRING_AS_TIME` is a simple and effective tool for converting WSTRING strings to TIME values. Its clear interface and direct functionality make it a reliable solution for relevant use cases.