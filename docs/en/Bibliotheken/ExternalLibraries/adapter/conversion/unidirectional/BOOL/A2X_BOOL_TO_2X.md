# A2X_BOOL_TO_2X

<img width="1145" height="205" alt="image" src="https://github.com/user-attachments/assets/8248af7a-7ffe-41f8-af30-bd33f4e69bed" />
* * * * * * * * * *
## Introduction

The A2X_BOOL_TO_2X is a compound function block that converts two BOOL values into an A2X output format. This block serves as a bridge between simple Boolean control signals and the standardized A2X adapter interface.
![A2X_BOOL_TO_2X](A2X_BOOL_TO_2X.svg)

## Interface Structure

### **Event Inputs**

- **E_UP**: Event input for up/forward movement
- **E_DOWN**: Event input for down/backward movement

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

- **UP**: BOOL input for up/forward direction (TRUE = forward, up, right, clockwise)
- **DOWN**: BOOL input for down/backward direction (TRUE = backward, down, left, counterclockwise)

### **Data Outputs**

*No direct data outputs available*

### **Adapters**

- **A2X_OUT**: Unidirectional A2X output adapter for forwarding the converted signals

## Functionality

The function block receives two independent Boolean input signals (UP and DOWN) along with their corresponding event inputs are passed directly to the A2X output adapter, with event and data connections processed in parallel.

## Technical Features

- Completely unidirectional signal processing
- Direct pass-through without additional logic processing
- Uses the standardized A2X adapter interface
- No internal states or delays

## State Overview

The function block has no internal states and operates stateless. Every incoming event is immediately passed to the corresponding adapter output.

## Application Scenarios

- Control of bidirectional actuators (e.g., motors, cylinders)
- Interface between simple switching logic and more complex control systems
- Conversion of push-button/switch signals into standardized motion signals
- Drive controls with forward/reverse functionality

## ⚖️ Comparison with similar components

Compared to simple conversion components, A2X_BOOL_TO_2X offers the specific combination of two Boolean inputs with a standardized A2X interface. Other components might perform individual BOOL-to-A2X conversions, but this component combines both directions in a single component.

## Conclusion

The A2X_BOOL_TO_2X is a specialized interface component that provides a simple and efficient interface between basic Boolean control signals and the standardized A2X protocol. Its clear structure and direct pass-through make it a reliable solution for bidirectional control applications.
