# ButtonActivationCode
![ButtonActivationCode](./ButtonActivationCode.svg)
* * * * * * * * * *
## Introduction
ButtonActivationCode is a collection of global constants for processing button activations in ISOBUS-compatible systems. These constants define various states and events that can occur when buttons are pressed and are primarily used in agricultural applications.
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
The ButtonActivationCode constants define various button activation states as structured data types of type `ButtonActivationCode_S`. Each constant represents a specific key state and contains a numeric code as well as optional additional parameters.

## Technical Features
- **Transmission Repetition Rate**: On key press/release and every 200 ms while the key is held
- **Lockable Keys**: Do not repeat while the key is held
- **ISOBUS Compatibility**: Specifically designed for ISOBUS Virtual Terminal (VT) systems
- **Structured Constants**: Uses a structured data type with code values and additional flags

## State Overview

| Constant | Code | Description |

|-----------|------|--------------|

| BT_RELEASED_UNLATCHED | 0 | Key has been unlocked or released (state change) |

| BT_PRESSED_LATCHED | 1 | Button was "pressed" or locked (state change) |

| BT_STILL_HELD | 2 | Button is still being held (lockable buttons do not repeat) |

| BT_STILL_HELD_START | 2 | Button is still being held (with bCyclic := FALSE) |

| BT_ABORTED | 3 | Button press aborted (applies to VT version 4 and higher) |

| Invalid | 255 | Invalid state |

## Application Scenarios
- Controlling agricultural machinery via ISOBUS Virtual Terminal
- Implementing button logic in operator panels
- Processing button inputs in vehicle control systems
- Developing user interfaces for agricultural applications

## ⚖️ Comparison with similar function blocks
Compared to simple digital inputs, ButtonActivationCode offers a finely granular state representation for buttons, specifically tailored to the requirements of ISOBUS systems. The constants support advanced button functions such as locking mechanisms and cancel functions.

## Conclusion
ButtonActivationCode provides a standardized method for handling button activations in ISOBUS environments. The defined constants enable consistent and reliable processing of button inputs across different systems, which is particularly important in safety-critical agricultural applications.