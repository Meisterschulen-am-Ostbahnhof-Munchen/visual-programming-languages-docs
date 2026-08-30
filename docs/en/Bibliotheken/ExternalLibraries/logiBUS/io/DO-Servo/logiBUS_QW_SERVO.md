# logiBUS_QW_SERVO

<img width="1341" height="240" alt="image" src="https://github.com/user-attachments/assets/a0a3a085-d2e5-4393-893f-f377b4a3f346" />
* * * * * * * * * *
## Introduction

The logiBUS_QW_SERVO is an output service interface function block for word output data, specifically designed for controlling logiBUS servo outputs. This block enables the initialization and control of digital outputs via a standardized interface.
![logiBUS_QW_SERVO](logiBUS_QW_SERVO.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization event with associated data QI, PARAMS, and Output
- **REQ**: Service request event with associated data QI and OUT

### **Event Outputs**

- **INITO**: Initialization acknowledgment with associated data QO and STATUS
- **CNF**: Acknowledgement of the requested service operation with associated data QO and STATUS

### **Data Inputs**

- **QI** (BOOL): Event input qualifier
- **PARAMS** (STRING): Service parameters for configuration
- **OUT** (WORD): Output data for the resource
- **Output** (logiBUS::io::DQ::logiBUS_DO_S): Identifies the output Output_Q1..Q8, initially with a value "Invalid"

### **Data Outputs**

- **QO** (BOOL): Event output qualifier
- **STATUS** (STRING): Service status information

### **Adapters**

No adapter interfaces available.

## Functionality

This function block enables the initialization and control of logiBUS servo outputs. During INIT initialization, the service parameters are configured and the specific output is identified. Output data in WORD format can be sent to the resource via the REQ event. The block confirms both operations with corresponding output events (INITO and CNF) containing status information.

## Technical Features

- Uses WORD data type for output data (16-bit)
- Supports specific logiBUS output identification via the output parameter
- Initialization with an "Invalid" value for the output parameter
- String-based parameter and status transmission

## State Overview

The function block has two main operating states:

1. **Not Initialized**: Before INIT initialization
2. **Initialized and Ready**: After successful INIT initialization, ready for REQ requests

## Application Scenarios

- Control of digital outputs in logiBUS systems
- Servo controllers with word data output
- Industrial automation applications with precise output control
- Embedded systems with a logiBUS interface

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital output blocks, logiBUS_QW_SERVO offers extended functionality through:

- Word-based data output (16-bit instead of individual bits)
- Specific servo control functions
- Detailed status feedback
- Configurable initialization

## Conclusion

The logiBUS_QW_SERVO is a specialized function block for demanding output applications in logiBUS systems. Its word-based data processing and comprehensive status feedback make it particularly suitable for precise control tasks in industrial automation solutions.
