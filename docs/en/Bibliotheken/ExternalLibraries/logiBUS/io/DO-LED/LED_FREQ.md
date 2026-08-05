# LED_FREQ
![LED_FREQ](./LED_FREQ.svg)

* * * * * * * * * *
## Introduction
LED_FREQ is a collection of global constants for controlling LED blinking patterns with priority management. The constants define various blinking frequencies and operating modes for LEDs with assigned priority values that can be used in control applications.
## Interface Structure
### **Event Inputs**
*No event inputs available*

### **Event Outputs**
*No event outputs available*

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

#### **Adapters**
*No adapters available*

## Functionality
The global constants provide numerical values for different LED operating modes. Each mode has a specific priority value, with higher numbers representing a higher priority. The constants can be used in function blocks to control LED behavior and resolve priority conflicts.

```
## Technical Features
- **Data Type**: All constants are of type UINT (unsigned integer)
- **Priority Range**: Values from 0 to 6, where 6 represents the highest priority
- **Frequency Ranges**: 5 Hz, 2 Hz, 1 Hz, 0.5 Hz blinking and breathing effect
- **Package Membership**: logiBUS::io::DO_LED

## State Overview
*No state machine present - these are static constants*

## Application Scenarios
- Control of status LEDs in industrial control systems
- Prioritized display control in machine operator panels
- Visualization of operating states with varying urgency
- Multi-channel LED control with priority management

## ⚖️ Comparison with Similar Function Blocks
Unlike function blocks with dynamic behavior control, LED_FREQ offers static, predefined operating modes with fixed priorities. This allows for simpler implementation with known, standardized display requirements.

## Conclusion
LED_FREQ offers an efficient method for defining standardized LED operating modes with integrated priority management. The constant collection is particularly suitable for applications requiring clear, predictable LED behavior patterns with defined priorities.
