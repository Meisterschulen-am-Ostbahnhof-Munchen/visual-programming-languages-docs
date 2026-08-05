# F_CONCAT

<img width="1436" height="240" alt="F_CONCAT" src="https://github.com/user-attachments/assets/5f43c8b8-b683-4d0d-83c8-16dc8e4e987d" />

* * * * * * * * * *
## Introduction
The function block `F_CONCAT` is used to concatenate two strings. It is part of the standard library for character and string operations according to IEC 61131-3.

![F_CONCAT](F_CONCAT.svg)

## Interface Structure

### **Event Inputs**

- `REQ` (Service Request): Starts the concatenation operation. The block requires both input strings (`IN1` and `IN2`) to execute the operation.


### **Event Outputs**

- `CNF` (Confirmation of Requested Service): Signals the successful completion of the concatenation operation. The result is provided via the data output `OUT`.

### **Data Inputs**

- `IN1` (input string 1): First input string of type `ANY_STRING`.

- `IN2` (input string 2): Second input string of type `ANY_STRING`.


### **Data Outputs**

- `OUT` (string 1 + string 2): Result of concatenating `IN1` and `IN2` as `ANY_STRING`.

### **Adapters**
This function block has no adapters.

## Functionality
When the event `REQ` is triggered, the two input strings `IN1` and `IN2` are concatenated. The result is output via `OUT`, and the event `CNF` signals the successful completion of the operation.


## Technical Features
- Supports the data type `ANY_STRING`, enabling flexible use with various string types.

- Simple and direct implementation without additional parameters or complex state logic.

## State Overview

The function block has no internal state. The operation is re-executed with each `REQ` event.

## Application Scenarios

- Combining text segments in automated messaging systems.

- Creating dynamic strings in control logic, e.g., for logging or notifications.

## ⚖️ Comparison with Similar Blocks
- Unlike `F_STRING_TO_*` blocks, which convert strings, `F_CONCAT` does not perform type conversion.

- Simpler than blocks with additional formatting options like `F_STRING_FORMAT`.

## Conclusion
`F_CONCAT` is a basic and efficient building block for string processing in IEC 61131-3 environments. Its simplicity and direct functionality make it ideal for basic concatenation tasks.