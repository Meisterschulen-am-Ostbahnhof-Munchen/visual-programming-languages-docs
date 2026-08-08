# F_BOOL_TO_DINT
<img width="1235" height="182" alt="F_BOOL_TO_DINT" src="https://github.com/user-attachments/assets/a1422f1d-6480-464e-9ae1-5251c70d054e" />
* * * * * * * * * *
The function block `F_BOOL_TO_DINT` converts a Boolean value (`BOOL`) into a 32-bit integer value (`DINT`). This conversion is useful when Boolean signals need to be integrated into numerical calculations or control systems.
![F_BOOL_TO_DINT](F_BOOL_TO_DINT.svg)
- **REQ**: Starts the conversion. When this event is triggered, the Boolean input value (`IN`) is converted into a `DINT` value.

- **CNF**: Signals the completion of the conversion. This event is output along with the converted output value (`OUT`).

- **IN**: The Boolean input value (`BOOL`) to be converted to a `DINT` value.

- **OUT**: The converted 32-bit integer value (`DINT`). The value is `1` if `IN` is `TRUE`, otherwise `0`.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
This function block does not use any adapters.

## Functionality
The function block performs the conversion from `BOOL` to `DINT` by converting the Boolean value `TRUE` to `1` and `FALSE` to `0`. The conversion is triggered by the event `REQ`, and the result is confirmed by the event `CNF`.

- The conversion is performed using the function `BOOL_TO_DINT`, which is implemented in the function block's algorithm.


The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

- Integration of Boolean signals into numerical controllers.
- Conversion of switching states (`TRUE`/`FALSE`) into numerical values for further calculations.
- Interfaces between Boolean and numerical system components.

- **F_BOOL_TO_INT**: Converts `BOOL` to a 16-bit integer (`INT`). In contrast, `F_BOOL_TO_DINT` returns a 32-bit integer.
- **F_BOOL_TO_REAL**: Converts `BOOL` to a floating-point value (`REAL`). `F_BOOL_TO_DINT`, on the other hand, returns an integer value.

The function block `F_BOOL_TO_DINT` is a simple and efficient tool for converting Boolean values to 32-bit integers. It is particularly suitable for applications where Boolean signals need to be integrated into numerical controllers. Its deterministic operation and clear interface structure make it a reliable component in IEC 61499-based automation.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion