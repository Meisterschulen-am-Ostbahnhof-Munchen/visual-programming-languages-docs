# F_DELETE
<img width="1068" height="196" alt="F_DELETE" src="https://github.com/user-attachments/assets/bf84dd90-6f79-4860-924b-8bfa70fcafcc" />
* * * * * * * * * *
## Introduction
The function block `F_DELETE` is used to manipulate strings. It removes a specific number of characters (`L`) from an input string (`IN`), starting at a defined position (`P`). The result is output as a new string (`OUT`).
![F_DELETE](F_DELETE.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the processing of the function block. The corresponding data are `IN`, `L`, and `P`.

### **Event Outputs**
- **CNF**: Signals successful processing and returns the result `OUT`.

### **Data Inputs**
- **IN**: The input string from which characters are to be removed (Type: `ANY_STRING`).
- **L**: The number of characters to be removed (Type: `ANY_INT`).
- **P**: The starting position from which characters are to be removed (Type: `ANY_INT`).

### **Data Outputs**
- **OUT**: The resulting string after character removal (Type: `ANY_STRING`).

#### **Adapters**
No adapters available.

## Functionality
1. The function block is activated by the event `REQ`.

2. Characters `L` are removed from the string `IN`, starting at position `P`.

3. The result is stored in `OUT`, and the event `CNF` is triggered.

## Technical Features
- The function block supports various string types (`ANY_STRING`), allowing for flexible use.
- The position `P` and the length `L` must be valid values within the length of `IN` to ensure correct results.

## State Overview

1. **Idle**: Waits for the event `REQ`.

2. **Processing**: Processes the input data and removes the characters.

3. **Completed**: Outputs the result and signals `CNF`.

## Application Scenarios
- Cleansing user input.
- Processing protocol or log data.
- Manipulating text data in automated processes.

## ⚖️ Comparison with Similar Building Blocks
- **F_INSERT**: Inserts characters at a specific position.
- **F_REPLACE**: Replaces characters in a string.
- **F_SUBSTRING**: Extracts a substring from a string.

## Conclusion
The `F_DELETE` function block is a useful tool for manipulating strings in the 4diac IDE. Its simple and flexible interface allows it to be used in various applications to remove characters from strings.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
