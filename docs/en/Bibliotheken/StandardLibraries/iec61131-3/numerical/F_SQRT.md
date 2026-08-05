# F_SQRT
![F_SQRT](https://user-images.githubusercontent.com/116869307/214145163-97573336-a23e-420b-88ab-99876f5083e5.png)

* * * * * * * * * *
## Introduction
The F_SQRT function block is a standard function block according to IEC 61131-3 that calculates the square root of a numeric input. It belongs to the category of numeric functions and is used for the mathematical calculation of the square root of any real input value.
![F_SQRT](F_SQRT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service Request - triggers the square root calculation

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**
- **IN** (ANY_REAL): Input value from which the square root is to be calculated

### **Data Outputs**
- **OUT** (ANY_REAL): Result of the square root calculation

### **Adapters**
No adapter interfaces are available.

## Functionality
The F_SQRT function block calculates the square root of the input value IN. The calculation is performed when activated by the REQ event. After the calculation is complete, the CNF event is triggered, and the result is output via the OUT variable.

## Technical Features
- Uses the ANY_REAL data type for maximum flexibility with various real number types
- Complies with the IEC 61131-3 standard specification
- Simple and direct functionality without additional parameters

## State Transitions
1. **Wait State**: Block waits for a REQ event

2. **Calculate State**: Upon a REQ event, the square root is calculated
3. **Output State**: After calculation, a CNF event is triggered and the result is output

## Application Scenarios
- Mathematical calculations in control systems
- Signal processing and filtering
- Scientific and technical applications
- Control engineering and process control

## ⚖️ Comparison with Similar Blocks
Compared to other mathematical function blocks, F_SQRT offers a specialized function for calculating square roots. Other blocks such as F_ADD or F_MUL offer basic arithmetic operations, while F_SQRT provides a specific mathematical function.

## Conclusion

The F_SQRT function block is an essential tool for numerical calculations in IEC 61131-3 based control systems. Its simple interface and reliable functionality make it a valuable component for mathematical operations in industrial automation solutions.
