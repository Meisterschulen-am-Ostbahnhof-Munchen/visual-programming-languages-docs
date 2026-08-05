# F_TAN
![F_TAN](https://user-images.githubusercontent.com/116869307/214145191-77e281a6-b6e0-4ead-bc17-9638dc4fdf03.png)
* * * * * * * * * *
## Introduction
The F_TAN function block calculates the tangent of an input value in radians. It is a standard function for numerical calculations according to IEC 61131-3.
![F_TAN](F_TAN.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Service request - triggers the tangent calculation

### **Event Outputs**
- **CNF**: Confirmation of requested service - signals the completion of the calculation

### **Data Inputs**
- **IN**: Input value in radians (ANY_REAL data type)

### **Data Outputs**
- **OUT**: Calculated tangent value (ANY_REAL data type)

### **Adapters**
No adapter interfaces are available.

## Functionality
Upon receiving a REQ event, the F_TAN block calculates the tangent of the angle passed to IN in radians. The result is output to OUT, and simultaneously, a CNF event is generated to signal the completion of the calculation.

``` ## Technical Features
- Supports the ANY_REAL data type for maximum flexibility with numeric inputs
- Calculations are performed in radians (not degrees)
- Implemented according to the IEC 61131-3 standard for numeric functions
- Mathematical peculiarity: Very large values or overflows can occur for angles close to π/2 + kπ (k ∈ ℤ)

## State Transitions
1. **Wait State**: Block waits for a REQ event
2. **Calculate State**: Upon a REQ event, the tangent is calculated
3. **Output State**: Result is sent to OUT and a CNF event is generated
4. Return to Wait State

## Application Scenarios
- Trigonometric calculations in control systems
- Signal processing and filtering
- Robotics and motion control
- Mathematical modeling and simulation
- Control engineering and position determination

## ⚖️ Comparison with similar function blocks
- **F_SIN**: Calculates sine instead of tangent
- **F_COS**: Calculates cosine instead of tangent
- **F_ATAN**: Inverse function (arcutangent)
- **F_TAN** specifically provides the tangent function for trigonometric applications

## Conclusion
The F_TAN function block is an essential element for trigonometric calculations in IEC 61131-3 based control systems. Its simple and standards-compliant interface enables reliable integration into more complex control algorithms, especially in applications requiring trigonometric functions.