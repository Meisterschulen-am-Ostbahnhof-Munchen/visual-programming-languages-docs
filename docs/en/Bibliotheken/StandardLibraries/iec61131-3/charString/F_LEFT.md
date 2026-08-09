# F_LEFT

<img width="1279" height="207" alt="F_LEFT" src="https://github.com/user-attachments/assets/a5684213-fe32-44e3-a3b3-69bfaefab215" />
* * * * * * * * * *
## Introduction

The function block `F_LEFT` extracts the leftmost characters `L` from the input string `IN`. It is part of the standard character and string functions according to IEC 61131-3.
![F_LEFT](F_LEFT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the string extraction. It is linked to the data inputs `IN` and `L`.

### **Event Outputs**

- **CNF**: Confirms successful extraction. Linked to data output `OUT`.

### **Data Inputs**

- **IN** (`ANY_STRING`): The input string from which the leftmost characters are to be extracted.
- **L** (`ANY_INT`): The number of characters to be extracted from the left.

### **Data Outputs**

- **OUT** (`ANY_STRING`): The extracted substring consisting of the leftmost characters of `L` from `IN`.

### **Adapters**

No adapters are available.

## **Adapters** ## Functionality

When the event `REQ` is triggered, the function block extracts the first characters `L` from the input string `IN` and outputs the result as `OUT`. The event `CNF` signals successful execution.

## Technical Features

- Supports all string types (`ANY_STRING`).
- `L` must be a valid integer value. If `L` is greater than the length of `IN`, the entire string is returned.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Processes the input and extracts the characters.
3. **Completed**: Sends `CNF` with the result.

## Application Scenarios

- Extracting prefixes from strings.
- Shortening strings for specific requirements.

## ⚖️ Comparison with Similar Function Blocks

- **F_RIGHT**: Extracts characters from the right.
- **F_MID**: Extracts characters from the middle of a string.

## Conclusion

F_LEFT` is a simple and efficient function block for extracting substrings from the beginning of a string. Its use is intuitive and it meets the requirements of IEC 61131-3.
