# F_MID

<img width="1158" height="232" alt="F_MID" src="https://github.com/user-attachments/assets/0f4a4667-023e-4ada-8ea0-2df3b494c7db" />
* * * * * * * * * *
The function block `F_MID` is used to extract a substring from a given string. A specific number of characters are extracted starting from a defined position. This function block is part of the standard character and string functions according to IEC 61131-3.
![F_MID](F_MID.svg)
- **REQ**: Service request to execute the extraction. This is linked to the data inputs `IN`, `L`, and `P`.
- **CNF**: Confirmation of successful request execution. Linked to the data output `OUT`.
- **IN**: The input string from which the substring is to be extracted (Type: `ANY_STRING`).
- **L**: The length of the substring to be extracted (Type: `ANY_INT`).
- **P**: The starting position from which the extraction should begin (Type: `ANY_INT`).
- **OUT**: The extracted substring (Type: `ANY_STRING`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- No adapters available.

The function block `F_MID` extracts a substring from the input string `IN`. The extraction begins at position `P` and includes `L` characters. The result is output via output `OUT` as soon as the event output `CNF` is triggered.

- The function block supports any string type (`ANY_STRING`) and integer type (`ANY_INT`).
- The function block supports arbitrary string types (`ANY_STRING`) and integer types (`ANY_INT`).

- The start position `P` and the length `L` must be valid values within the length of the input string to ensure correct results.

1. **Initialization**: The function block waits for a request via `REQ`.
2. **Processing**: Upon receiving `REQ`, the input data is processed and the substring is extracted.
3. **Output**: The extracted substring is output via `OUT`, and `CNF` is triggered.
- Extraction of substrings from longer texts or data strings.
- Use in string processing routines, e.g., for parsing data formats.
- Similar function blocks like `F_LEFT` or `F_RIGHT` extract substrings from the beginning or end of a string, while `F_MID` allows for flexible extraction from any position.

The `F_MID` function block offers a simple and efficient way to extract substrings from a given string. Its flexibility and compatibility with various string and integer types make it a useful tool in string manipulation.

## Functionality

## Application Scenarios

## State Overview

## Technical Features

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion