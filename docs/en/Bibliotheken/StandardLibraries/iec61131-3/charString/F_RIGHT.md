# F_RIGHT

<img width="1390" height="208" alt="F_RIGHT" src="https://github.com/user-attachments/assets/d39c7fe1-3c16-4c26-90c3-b78236b98380" />

* * * * * * * * * *
## Introduction
The function block `F_RIGHT` is a standard function block for processing character strings according to the IEC 61131-3 standard. It extracts the rightmost characters `L` from the input string `IN` and outputs them as the result `OUT`. This function block is particularly useful in applications where parts of character strings need to be processed or analyzed.

![F_RIGHT](F_RIGHT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request. Triggers the extraction of the rightmost characters `L`. Linked to the data `IN` and `L`.

### **Event Outputs**

- **CNF**: Confirmation of the requested service. Linked to the result `OUT`.

### **Data Inputs**

- **IN**: Input string from which the rightmost characters are to be extracted. The data type is `ANY_STRING`.

- **L**: Number of characters to be extracted from the right of the input string. The data type is `ANY_INT`.

### **Data Outputs**

- **OUT**: Result string containing the extracted characters. The data type is `ANY_STRING`.

### **Adapters**
This function block has no adapters.

## Functionality
When the event `REQ` is triggered, the input string `IN` is processed. The function block extracts the rightmost characters `L` from `IN` and outputs the result via the output `OUT`. The event `CNF` signals successful processing and provides the result.

## Technical Features
- Supports various string types (`ANY_STRING`), allowing for flexible use.

- The position `L` can be specified using various integer types (`ANY_INT`).

- This function block is part of the `iec61131::charString` package.

## State Overview
The function block has no internal states. Processing occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Extracting file extensions from filenames.

- Processing fixed-length string formats where relevant information is located at the end of the string.

- General string manipulation in control and automation applications.

## ⚖️ Comparison with Similar Function Blocks
- Compared to `F_LEFT`, which extracts the leftmost characters of a string, `F_RIGHT` offers the opposite functionality.

Other string function blocks, such as ``F_MID``, allow the extraction of substrings from the middle of a string, while ``F_RIGHT`` focuses specifically on the rightmost characters.

## Conclusion
The function block ``F_RIGHT`` is a simple and effective building block for extracting characters from the end of a string. Its flexibility regarding supported data types makes it a versatile tool for string manipulation.