# logiBUS_LED_PWM_QX

<img width="1905" height="366" alt="image" src="https://github.com/user-attachments/assets/ff509262-3aeb-48fd-88e2-74c2323ab225" />
* * * * * * * * * *
## Introduction

The logiBUS_LED_PWM_QX is an output service interface function block for Boolean output data with PWM functionality for LED control. This block enables the control of LED outputs with configurable frequencies and provides a standardized interface for communication with logiBUS I/O resources.
![logiBUS_LED_PWM_QX](logiBUS_LED_PWM_QX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization with parameters QI, PARAMS, Output, and FREQ
- **REQ**: Service request with parameters QI and OUT

### **Event Outputs**

- **INITO**: Initialization acknowledgment with parameters QO and STATUS
- **CNF**: Acknowledgement of the requested service operation with parameters QO and STATUS

### **Data Inputs**

- **QI**: BOOL - Event input qualifier
- **PARAMS**: STRING - Service parameter
- **OUT**: BOOL - Output data for the resource
- **Output**: logiBUS_DO_S - Identifies the output (Output_Q1..Q8), initial value: Invalid
- **FREQ**: UINT - Defines the LED frequency and priority Initial value: LED_FREQ::LED_OFF

### **Data Outputs**

- **QO**: BOOL - Event output qualifier
- **STATUS**: STRING - Service status

### **Adapters**

No adapter interfaces available.

## Functionality

This function block manages the PWM control of LED outputs via the logiBUS system. During initialization (INIT event), the output configuration, frequency settings, and service parameters are passed. Output data (OUT) can be sent via the REQ event, which is then applied to the specified output at the configured PWM frequency.

## Technical Features

- Supports various LED frequencies via the FREQ parameter
- Integrated error handling via STATUS output
- Typed output identification via logiBUS_DO_S data type
- Initialization with an invalid state for unconfigured outputs
- Frequency priority control for LED control

## State Overview

The function block has the following operating states:

- **Not Initialized**: Before the INIT event, outputs are inactive
- **Initialized**: After successful INIT processing, ready for REQ operations
- **Active**: During PWM signal generation
- **Error**: In case of invalid parameters or configuration errors

## Application Scenarios

- Control of status LEDs in industrial control systems
- PWM-controlled lighting systems
- Visual signaling with variable brightness control
- Priority-controlled LED displays in logiBUS-based applications

## ⚖️ Comparison with similar devices Modules

Compared to simple digital output modules, logiBUS_LED_PWM_QX offers advanced PWM functionality with frequency control and priority-based control. Integration into the logiBUS ecosystem enables standardized communication with I/O resources.

## 🛠️ Related Exercises

* [Exercise_030](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_030.md)]

## Conclusion

The logiBUS_LED_PWM_QX is a specialized function block for demanding LED control applications in industrial automation systems. With its PWM functionality, configurable frequencies, and integration into the logiBUS system, it provides a powerful solution for visual output scenarios with high demands on flexibility and reliability.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 The PWM signal & infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)
