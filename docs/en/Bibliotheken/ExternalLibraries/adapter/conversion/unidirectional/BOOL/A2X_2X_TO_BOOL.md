# A2X_2X_TO_BOOL

<img width="1133" height="205" alt="image" src="https://github.com/user-attachments/assets/04474ccc-a4d3-46b8-b00e-a15ae93d09e9" />
* * * * * * * * * *
## Introduction

The A2X_2X_TO_BOOL function block is a composite function block used to convert A2X signals into two separate BOOL signals. It enables the conversion of bidirectional control signals into simple logic outputs for various applications.
![A2X_2X_TO_BOOL](A2X_2X_TO_BOOL.svg)

## Interface Structure

### **Event Inputs**

No direct event inputs available

### **Event Outputs**

- **E_UP**: Activated when an upward/forward movement is detected
- **E_DOWN**: Activated when a downward/backward movement is detected

### **Data Inputs**

No direct data inputs available

### **Data Outputs**

- **UP**: BOOL - TRUE for forward, upward, right, or clockwise
- **DOWN**: BOOL - TRUE for backward, downward, left, or counterclockwise

### **Adapter**

- **A2X_IN**: A2X adapter input for unidirectional communication

## Functionality

The function block receives signals via the A2X adapter and forwards them directly to the corresponding outputs. The events and data values are passed directly from the adapter to the output interfaces without any additional processing or delay.

## Technical Features

- Composite function block without internal logic
- Direct pass-through of adapter signals
- No state retention or storage
- Real-time signal forwarding

## State Overview

The function block has no internal states. It behaves purely combinatorially and immediately forwards incoming signals to the outputs.

## Application Scenarios

- Control of motion directions in actuators
- Conversion of complex control signals into simple direction commands
- Connection of A2X-compatible components to BOOL-based controllers
- Direction detection in drive systems

## ⚖️ Comparison with Similar Blocks

Compared to other conversion blocks, A2X_2X_TO_BOOL offers a specific solution for converting A2X signals into Boolean direction signals. Other function blocks could offer additional features such as filtering, delay, or more complex signal processing.

## Conclusion

The A2X_2X_TO_BOOL function block provides a simple and efficient solution for converting A2X control signals into Boolean directional outputs. Its clear interface definition and direct signal routing make it particularly suitable for applications requiring unadulterated transmission of control information.