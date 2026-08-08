# F_BOOL_TO_BYTE
<img width="1231" height="182" alt="F_BOOL_TO_BYTE" src="https://github.com/user-attachments/assets/726d9bee-c530-487f-ab01-086582dfd936" />
* * * * * * * * * *
The function block `F_BOOL_TO_BYTE` converts a Boolean value (`BOOL`) into a byte value (`BYTE`). This conversion is useful when Boolean signals need to be processed in systems that require byte data.
![F_BOOL_TO_BYTE](F_BOOL_TO_BYTE.svg)

- **REQ**: This event input triggers the execution of the function block. It is linked to the data input `IN`.

- **CNF**: This event output signals the successful execution of the function block. It is linked to the data output `OUT`.

- **IN** (`BOOL`): The Boolean input value to be converted into a byte.

- **OUT** (`BYTE`): The resulting byte value after conversion.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
This function block does not use any adapters.

## Functionality
The function block performs the conversion from `BOOL` to `BYTE` as soon as the event `REQ` is triggered. The Boolean value `IN` is converted to a byte value, with `FALSE` becoming `0` and `TRUE` becoming `1`. The result is output via `OUT`, and the event `CNF` signals successful execution.

- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm (`ST`) for the conversion.


The function block has no internal states. Execution occurs immediately upon triggering the ``REQ`` event.

- **Signal Processing**: Conversion of Boolean control signals into byte values for communication with devices that expect byte data.
- **Data Logging**: Conversion of Boolean status information into byte format for storage or transmission.

- **F_BOOL_TO_INT**: Converts a Boolean value to an integer value, while ``F_BOOL_TO_BYTE`` is specifically optimized for byte output.
- **F_BOOL_TO_WORD**: Similar to `F_BOOL_TO_BYTE`, but designed for larger data formats (Word).

The function block `F_BOOL_TO_BYTE` is a simple and efficient tool for converting Boolean values to byte data. It is particularly suitable for applications that require a compact representation of Boolean signals in byte format. Its simple interface and direct functionality make it easy to integrate into existing systems.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion