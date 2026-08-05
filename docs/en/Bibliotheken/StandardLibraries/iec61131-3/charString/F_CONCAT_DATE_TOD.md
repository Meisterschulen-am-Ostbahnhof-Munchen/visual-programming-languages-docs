# F_CONCAT_DATE_TOD
<img width="1388" height="208" alt="F_CONCAT_DATE_TOD" src="https://github.com/user-attachments/assets/7664ea18-4774-4f2d-b461-1b887d0a1c2a" />
* * * * * * * * * *
## Introduction
The function block `F_CONCAT_DATE_TOD` concatenates a date (`DATE`) and a time of day (`TIME_OF_DAY`) into a combined date and time stamp (`DATE_AND_TIME`). This block is particularly useful in scenarios where separate date and time information needs to be combined into a single timestamp.
![F_CONCAT_DATE_TOD](F_CONCAT_DATE_TOD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the processing of the function block. When this event is triggered, the input data `IN1` (date) and `IN2` (time of day) are processed.

### **Event Outputs**
- **CNF**: Signals successful processing and outputs the combined timestamp `OUT`.

### **Data Inputs**
- **IN1** (`DATE`): Input for the date.
- **IN2** (`TIME_OF_DAY`): Input for the time of day.

### **Data Outputs**
- **OUT** (`DATE_AND_TIME`): The combined date and time stamp generated from the inputs `IN1` and `IN2`.

### **Adapters**
This function block has no adapters.

## Functionality
When the event `REQ` is triggered, the input data `IN1` (date) and `IN2` (time of day) are read and combined into a value `DATE_AND_TIME`. The result is output via the variable `OUT`, and the event `CNF` signals successful processing.

## Technical Features
- The function block supports the standardized data types `DATE`, `TIME_OF_DAY`, and `DATE_AND_TIME` according to IEC 61131-3.
- Processing occurs synchronously with the triggering of the `REQ` event.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Processes the input data and combines it into a `DATE_AND_TIME` value.

3. **Output**: Outputs the result via `OUT` and signals `CNF`.

## Application Scenarios
- Combining separately recorded date and time information in control systems.
- Generating timestamps for logging and monitoring purposes.

## ⚖️ Comparison with Similar Function Blocks
Compared to other function blocks offering similar functionality, `F_CONCAT_DATE_TOD` stands out due to its simplicity and direct processing. There are no additional parameters or complex configuration options, making it particularly suitable for simple use cases.

## Conclusion
The `F_CONCAT_DATE_TOD` function block is an efficient tool for combining date and time information in control systems. Its ease of use and clear interface structure make it a reliable solution for basic timestamp operations.