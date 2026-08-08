# F_WSTRING_AS_DWORD
<img width="1490" height="214" alt="F_WSTRING_AS_DWORD" src="https://github.com/user-attachments/assets/0a7a9611-fec8-4a92-8bfd-ea8b545785de" />
* * * * * * * * * *
The function block `F_WSTRING_AS_DWORD` is used to convert a WSTRING value to a DWORD value. This functionality is particularly useful when strings need to be converted into numeric values, for example, for further processing in control algorithms.
![F_WSTRING_AS_DWORD](F_WSTRING_AS_DWORD.svg)
- **REQ**: Normal execution request. Triggers the conversion.

- **CNF**: Execution confirmation. Triggered after successful conversion.

- **IN**: Input of type WSTRING. The string to be converted to a DWORD value.

- **OUT**: Output of type DWORD. The converted numeric value.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
#### **Adapters**
No adapters available.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The conversion is carried out using the function `WSTRING_AS_DWORD`, which converts the WSTRING input value into a DWORD value. After successful conversion, the event `CNF` is triggered, and the converted value is available at output `OUT`.

- The function block is a simple function block (SimpleFB) and has a single algorithm that is executed when `REQ` is triggered.


The function block has no internal state. The conversion is performed anew with each `REQ` event.

- Conversion of user input (e.g., via HMI) into numeric values for control.
- Processing of strings containing numeric information in control algorithms.

- Compared to other conversion blocks such as `F_STRING_AS_DWORD`, this one is specifically designed for WSTRING input.
- Similar function blocks might offer additional parameters or error handling, but this function block is limited to basic conversion.


The `F_WSTRING_AS_DWORD` function block offers a simple and efficient way to convert WSTRING values to DWORD values. Its simplicity makes it particularly suitable for applications where direct conversion without additional complexity is required.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion