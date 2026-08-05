# F_ATAN
![F_ATAN](https://user-images.githubusercontent.com/116869307/214144971-bb9f4445-caa8-466d-a1dc-026d8e0a982b.png)

* * * * * * * * * *
## Introduction
The F_ATAN function block calculates the arctangent of a real number. It is a standard function for a numeric variable according to IEC 61131-3. The function block converts a tangent value into the corresponding angle in radians.
![F_ATAN](F_ATAN.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service Request - triggers the calculation of the arctangent

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**
- **IN**: Input value of type ANY_REAL - the tangent value for which the arctangent is to be calculated

### **Data Outputs**
- **OUT**: Output value of type ANY_REAL - the calculated arctangent value in radians

### **Adapters**
No adapter interfaces are available.

## Functionality
Upon receiving a REQ event, the F_ATAN function block calculates the arctangent of the value passed to IN. The result is output to OUT, and a CNF event is simultaneously generated to signal the completion of the calculation.

The function calculates the principal value of the arctangent, which lies in the range of -π/2 to π/2.

## Technical Features
- Supports the ANY_REAL data type, enabling various real data types (REAL, LREAL)
- Compliant with the IEC 61131-3 standard
- Deterministic computational behavior
- Suitable for real-time applications

## State Transitions
1. **Initial State**: Waits for a REQ event
2. **Computation State**: ATAN(IN) is calculated upon a REQ event
3. **Output State**: The result is sent to OUT and a CNF event is triggered
4. Returns to the initial state

## Application Scenarios
- Angle measurement and calculation in control systems
- Coordinate transformations in robotics applications
- Control engineering for position controllers
- Signal processing in mathematical calculations
- Navigation and orientation systems

## ⚖️ Comparison with Similar Function Blocks
- **F_ATAN2**: Calculates the arctangent of two coordinates (x,y) and returns an angle in the range from -π to π
- **F_SIN/F_COS**: Basic trigonometric functions for sine and cosine
- **F_TAN**: Calculates the tangent of an angle (inverse function of F_ATAN)

## Conclusion
The F_ATAN function block offers a reliable and standards-compliant implementation of the arctangent function for automation applications. Its simple interface and deterministic operation make it ideal for real-time applications in industrial automation where trigonometric calculations are required.
