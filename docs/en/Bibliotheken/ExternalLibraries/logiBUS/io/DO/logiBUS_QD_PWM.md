# logiBUS_QD_PWM

<img width="1848" height="333" alt="image" src="https://github.com/user-attachments/assets/ea4b0496-56de-4eb9-a419-6cd8c9b095bb" />

* * * * * * * * * *

## Introduction
The function block `logiBUS_QD_PWM` is an output service interface function block for double-word output data. It serves as an interface for controlling PWM (pulse-width modulation) outputs via the logiBUS system and enables the control of outputs Q1 to Q8.


![logiBUS_QD_PWM](logiBUS_QD_PWM.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization

- Linked to: QI, PARAMS, Output

- **REQ**: Service Request

- Linked to: QI, OUT

### **Event Outputs**

- **INITO**: Initialization Acknowledgement

- Linked to: QO, STATUS

- **CNF**: Acknowledgement of Requested Service Operation

- Linked to: QO, STATUS

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters

- **OUT** (DWORD): Output Data for the Resource

- **Output** (logiBUS_DO_S): Identifies the output Output_Q1..Q8

- Initial Value: `logiBUS_DO::Invalid`

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapters**
No adapter interfaces available.

## Functionality
This function block enables PWM control of outputs via the logiBUS system. During initialization (INIT), the service parameters are configured and the specific output is identified. PWM data (DWORD) can be sent to the configured output via a REQ request. The block acknowledges both initialization and service requests via the corresponding output events.


## Technical Features
- Uses DWORD data type for PWM output data
- Supports up to 8 outputs (Q1-Q8) via output configuration
- String-based parameter configuration for flexible service settings
- Status feedback via STRING variable for detailed error information

## State Overview
The function block has two main states:

1. **Not Initialized**: Block waits for an INIT event
2. **Initialized and Ready**: Block can process REQ requests and output PWM data

## Application Scenarios
- Control of PWM-controlled actuators (motors, heating elements)
- Control of LED lighting with brightness control
- Control of valves with proportional control
- Industrial automation applications with logiBUS hardware

## ⚖️ Comparison with Similar Blocks
Compared to simple digital output blocks, `logiBUS_QD_PWM` offers extended PWM functionality with 32-bit resolution (DWORD). Compared to analog output blocks, it enables direct PWM control without additional conversion.


``` ## 🛠️ Related exercises

* [Uebung_034](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034.md)
* [Uebung_034a1_Q1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q1.md)
* [Uebung_034a1_Q2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q2.md)
* [Uebung_034a1_Q4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q4.md)
* [Uebung_034b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034b.md)
* [Uebung_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion
The `logiBUS_QD_PWM` function block provides a powerful interface for PWM outputs in the logiBUS system. Thanks to its flexible configuration and support for 32-bit PWM data, it is ideally suited for precise control applications in industrial automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 The PWM signal & infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)

]