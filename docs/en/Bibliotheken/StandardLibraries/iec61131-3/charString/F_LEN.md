# F_LEN
<img width="1366" height="211" alt="F_LEN" src="https://github.com/user-attachments/assets/ca04179e-54ed-4419-aee6-51c03a2829a8" />
* * * * * * * * * *
## Introduction
The function block `F_LEN` is used to determine the length of an input string. It is part of the standard library for character and string functions according to IEC 61131-3.
![F_LEN](F_LEN.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Service request. When this event is triggered, the string length calculation begins.

### **Event Outputs**
- `CNF`: Acknowledgement of the service request. Triggered as soon as the calculation is complete.

### ### **Data Inputs**
- `IN` (ANY_STRING): The input string whose length is to be determined.

### **Data Outputs**
- `OUT` (ANY_INT): The length of the input string.

#### **Adapters**
No adapters available.

## Functionality
The function block `F_LEN` calculates the length of the passed string (`IN`) and outputs the result as an integer (`OUT`). The calculation is started by the event `REQ` and confirmed by `CNF`.

## Technical Features
- Supports all string types (`ANY_STRING`).
- Returns the length as an integer type (`ANY_INT`).

## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Calculation State**: Calculates the string length.

3. **Acknowledgement State**: Sends the `CNF` event with the calculated length.

## Application Scenarios
- Checking the length of user input.
- Validating string data before further processing.
- Logging and debugging string operations.

## ⚖️ Comparison with Similar Function Blocks
- Similar to `LEN` in other programming languages, but a standardized function block in IEC 61131-3.
- Unlike `F_MID` or `F_LEFT`, which extract parts of a string, `F_LEN` only returns the length.

## Conclusion
The `F_LEN` function block is a simple yet essential tool for string processing in IEC 61131-3 environments. Its clear interface and straightforward functionality make it a reliable building block for diverse applications.