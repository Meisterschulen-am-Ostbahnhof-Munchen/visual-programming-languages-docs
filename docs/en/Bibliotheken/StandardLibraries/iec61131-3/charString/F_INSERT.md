# F_INSERT
<img width="1330" height="232" alt="F_INSERT" src="https://github.com/user-attachments/assets/a4d23188-0238-4c4c-a6b8-f51a6a493b1c" />
* * * * * * * * * *
## Introduction
The function block `F_INSERT` is used to manipulate character strings. It inserts one character string (`IN2`) into another character string (`IN1`) at a specific position (`P`). The block is part of the standard character and string functions according to IEC 61131-3.
![F_INSERT](F_INSERT.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Service request. Triggers the execution of the function block. Linked to the data inputs `IN1`, `IN2`, and `P`.

### **Event Outputs**
- `CNF`: Confirmation of the requested service. Linked to the data output `OUT`.

### **Data Inputs**
- `IN1` (`ANY_STRING`): The first input string into which `IN2` is inserted.

### - `IN2` (`ANY_STRING`): The second input string to be inserted into `IN1`.
- `P` (`ANY_INT`): The position in `IN1` where `IN2` is to be inserted.

### **Data Outputs**
- `OUT` (`ANY_STRING`): The resulting string after the insertion operation.

### **Adapters**
No adapters available.

#
## ## Functionality

When the event `REQ` is triggered, the string `IN2` is inserted into the string `IN1` at the position defined by `P`. The result of this operation is output via the data output `OUT`, and the event `CNF` is triggered to indicate successful processing.

## Technical Features
- Supports all string types (`ANY_STRING`), allowing for flexible use.
- The position `P` can be any integer value (`ANY_INT`), but must be within the length of `IN1` to ensure defined behavior.

## State Overview
The function block has no internal state. The operation is re-executed with each `REQ` event.

## Application Scenarios
- Text processing in automation applications.
- Dynamic creation of log messages or notifications.
- Manipulation of data strings before further processing or output.

## ⚖️ Comparison with Similar Blocks
- Similar to `F_CONCAT`, which, however, simply concatenates two strings without considering a specific insertion position.

Unlike ``F_MID``, which extracts parts of a string, ``F_INSERT`` inserts one string into another.

## Conclusion
``F_INSERT`` is a useful function block for applications that require precise string manipulation. Its simple yet effective functionality makes it a valuable tool in automation engineering.
