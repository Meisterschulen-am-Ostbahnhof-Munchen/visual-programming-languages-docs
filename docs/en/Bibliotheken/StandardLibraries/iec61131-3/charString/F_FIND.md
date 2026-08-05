# F_FIND
<img width="1408" height="240" alt="F_FIND" src="https://github.com/user-attachments/assets/04ca16d1-99bf-4317-8cc7-adf2d6f70af7" />
* * * * * * * * * *
## Introduction
The function block `F_FIND` determines the position of the first occurrence of a string (IN2) within another string (IN1). If the searched string is not found, the block returns the value 0.
![F_FIND](F_FIND.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the search for the string. Inputs IN1 and IN2 are linked to this event.

### **Event Outputs**
- **CNF**: Confirms the completion of the search operation. Output OUT is linked to this event.

### **Data Inputs**
- **IN1** (ANY_STRING): The string to be searched.
- **IN2** (ANY_STRING): The string to search for.

### **Data Outputs**
- **OUT** (ANY_INT): The position of the first occurrence of IN2 in IN1. If not found, 0 is returned.

#### **Adapters**
No adapters are present.

## Functionality
The function block `F_FIND` searches the string IN1 for the first occurrence of the string IN2. The position of the first character of the found string is returned as the result. If IN2 is not contained in IN1, 0 is returned.

## Technical Features
- Supports any string type (ANY_STRING).
- Returns any integer type (ANY_INT).
- The search is case-sensitive.

## State Overview
1. **Idle**: Waiting for the REQ event.

2. **Processing**: Searches IN1 for IN2.

3. **Completed**: Sends the CNF event with the result.

## Application Scenarios
- Searching for substrings in text.
- Validating input data.
- Processing strings in automation processes.

## ⚖️ Comparison with Similar Blocks
- Compared to `F_FIND_STRING`, `F_FIND` offers similar functionality but is specifically for searching for the first position of a substring.
- Other blocks, such as `F_MID` or `F_LEFT`, offer additional string manipulation capabilities but lack a search function.

## Conclusion

The `F_FIND` function block is a useful tool for searching for substrings in automation applications. Its simple and efficient implementation makes it ideal for integration into more complex control logic.