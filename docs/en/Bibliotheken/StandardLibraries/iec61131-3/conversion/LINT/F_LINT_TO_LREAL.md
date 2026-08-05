# F_LINT_TO_LREAL
<img width="1448" height="214" alt="F_LINT_TO_LREAL" src="https://github.com/user-attachments/assets/411d5efa-708f-43f3-8da5-db0f863bcd2c" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_LREAL` converts an integer value of type `LINT` (64-bit integer) to a floating-point value of type `LREAL` (64-bit floating-point). This conversion is particularly necessary when integer values are to be used in calculations with floating-point numbers.
![F_LINT_TO_LREAL](F_LINT_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `LINT` to be converted to a `LREAL` value.

### **Data Outputs**
- **OUT**: The converted output value of type `LREAL`.

### **Adapters**
This function block does not use adapters.

### ## Functionality
When the event `REQ` is triggered, the algorithm is executed, converting the value of `IN` of type `LINT` to type `LREAL` and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features
- The conversion is performed directly without additional parameters.
- The function block is suitable for use in real-time systems because it operates deterministically.

## State Overview
The function block has no internal states. The conversion occurs immediately upon the triggering of `REQ`.

## Application Scenarios
- Conversion of large integers to floating-point numbers for mathematical calculations.
- Integration into control systems that need to process mixed data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks such as `F_INT_TO_REAL` or `F_DINT_TO_REAL`, `F_LINT_TO_LREAL` handles larger number ranges (64-bit).

## Conclusion
The `F_LINT_TO_LREAL` function block provides an efficient and reliable method for converting 64-bit integers to 64-bit floating-point numbers. Its simple interface and deterministic operation make it ideal for use in industrial control systems.