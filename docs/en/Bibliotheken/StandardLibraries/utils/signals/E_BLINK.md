# E_BLINK

![E_BLINK Funktionsblock](https://github.com/user-attachments/assets/29d3de7c-a775-4796-9c22-096e97347a6e)

* * * * * * * * * *
## Introduction

The E_BLINK function block simulates a flashing signal that alternates between the states TRUE and FALSE. The duration of each state can be configured individually. Unlike similar implementations, this function block always returns to FALSE upon the STOP event.
![E_BLINK](E_BLINK.svg)

## Interface Structure

### **Event Inputs**

- **START**: Starts the periodic generation of events. Uses the data `TIMELOW` and `TIMEHIGH`.
- **STOP**: Stops the generation of events and sets the output to FALSE.

### **Event Outputs**

- **CNF**: Acknowledges execution and returns the current output value `OUT`.

### **Data Inputs**

- **TIMELOW**: Time in milliseconds during which the output is FALSE.
- **TIMEHIGH**: Time in milliseconds during which the output is TRUE.

### **Data Outputs**

- **OUT**: The output value that toggles between TRUE and FALSE.

### **Adapters**

No adapters available.

## Functionality

The E_BLINK function block internally uses an E_PULSE timer and an E_CYCLE generator to implement the periodic state changes. During the START event, the times for TRUE and FALSE are added and used as the cycle time for E_CYCLE. The E_PULSE timer then controls the duration of the TRUE state, while the time difference determines the FALSE state.

## Technical Features

- The function block always resets the output to FALSE upon the STOP event.
- The implementation differs from similar solutions like CODESYS BLINK, which retain the last state.

## State Overview

1. **Inactive**: Output is FALSE.
2. **Active**: Output toggles periodically between TRUE and FALSE.
3. **Stopped**: Output is set to FALSE.

## Application Scenarios

- Controlling flashing warning lights
- Generating clock signals for testing purposes
- Visualizing state changes in user interfaces

## ⚖️ Comparison with Similar Function Blocks

Compared to the CODESYS BLINK function block, E_BLINK offers simplified handling due to the automatic reset to FALSE upon stopping. The functionality is similar, but the behavior during a STOP event is more consistent.

## Conclusion

The E_BLINK function block offers a simple and reliable way to generate periodic signals with configurable on and off times. The clear definition of the STOP behavior makes it particularly suitable for safety-critical applications.
