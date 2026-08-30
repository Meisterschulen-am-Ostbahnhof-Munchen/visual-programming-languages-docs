# F_REPLACE

<img width="1244" height="258" alt="F_REPLACE" src="https://github.com/user-attachments/assets/f5ad83d5-e863-468c-b5d8-5e1fcf3c2462" />
* * * * * * * * * *
## Introduction

The F_REPLACE function block is used to manipulate strings. It replaces a specific number of characters (L) in the first input string (IN1) with the second input string (IN2), starting at a specified position (P).
![F_REPLACE](F_REPLACE.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service request. Triggers the replacement operation. Linked to the data inputs IN1, IN2, L, and P.

### **Event Outputs**

- **CNF**: Confirmation of the requested service. Triggered when the replacement is complete. Linked to the data output OUT.

### **Data Inputs**

- **IN1** (ANY_STRING): The first input string in which the replacement is performed.
- **IN2** (ANY_STRING): The second input string used as a replacement.
- **L** (ANY_INT): The number of characters to be replaced.
- **P** (ANY_INT): The starting position for the replacement in IN1.

### **Data Outputs**

- **OUT** (ANY_STRING): The resulting string after the replacement.

### **Adapters**

No adapters available.

## Operation

The function block performs the following operation:

1. Upon receiving the REQ event, the input values IN1, IN2, L, and P are read.
2. In the string IN1, exactly L characters are replaced with the string IN2, starting at position P.
3. The result is stored in OUT, and the CNF event is triggered.

## Technical Features

- Supports any string type (ANY_STRING).
- The position P and length L must be valid indices within the string IN1 to ensure correct results.

## State Overview

The function block has no internal states. The operation is re-executed with each REQ event.

## Application Scenarios

- Text processing in automation applications.
- String manipulation in protocol messages.
- Dynamic adjustment of configuration strings.

## ⚖️ Comparison with Similar Function Blocks

- Similar to F_INSERT, however, F_REPLACE replaces existing characters instead of inserting new ones.
- Unlike F_DELETE, F_REPLACE replaces existing characters with new ones.

## Conclusion

F_REPLACE is a useful function block for string manipulation in IEC 61131-3-based controllers. Its simple and clear functionality makes it ideal for various applications in automation technology.
