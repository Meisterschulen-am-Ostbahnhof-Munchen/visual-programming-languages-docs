# F_BOOL_TO_DINT
<img width="1235" height="182" alt="F_BOOL_TO_DINT" src="https://github.com/user-attachments/assets/a1422f1d-6480-464e-9ae1-5251c70d054e" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_DINT` converts a Boolean value (`BOOL`) into a 32-bit integer value (`DINT`). This conversion is useful when Boolean signals need to be integrated into numerical calculations or control systems.
![F_BOOL_TO_DINT](F_BOOL_TO_DINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this event is triggered, the Boolean input value (`IN`) is converted into a `DINT` value.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event is output along with the converted output value (`OUT`).

### **Data Inputs**
- **IN**: The Boolean input value (`BOOL`) to be converted to a `DINT` value.

### **Data Outputs**
- **OUT**: The converted 32-bit integer value (`DINT`). The value is `1` if `IN` is `TRUE`, otherwise `0`.

### **Adapters**
This function block does not use any adapters.

## Functionality
The function block performs the conversion from `BOOL` to `DINT` by converting the Boolean value `TRUE` to `1` and `FALSE` to `0`. The conversion is triggered by the event `REQ`, and the result is confirmed by the event `CNF`.

## Technical Details
- The conversion is performed using the function `BOOL_TO_DINT`, which is implemented in the function block's algorithm.

# - The function block is simple and deterministic, as it contains no internal states or complex calculations.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Integration of Boolean signals into numerical controllers.
- Conversion of switching states (`TRUE`/`FALSE`) into numerical values for further calculations.
- Interfaces between Boolean and numerical system components.

## ⚖️ Comparison with Similar Function Blocks
- **F_BOOL_TO_INT**: Converts `BOOL` to a 16-bit integer (`INT`). In contrast, `F_BOOL_TO_DINT` returns a 32-bit integer.
- **F_BOOL_TO_REAL**: Converts `BOOL` to a floating-point value (`REAL`). `F_BOOL_TO_DINT`, on the other hand, returns an integer value.

## Conclusion
The function block `F_BOOL_TO_DINT` is a simple and efficient tool for converting Boolean values to 32-bit integers. It is particularly suitable for applications where Boolean signals need to be integrated into numerical controllers. Its deterministic operation and clear interface structure make it a reliable component in IEC 61499-based automation.