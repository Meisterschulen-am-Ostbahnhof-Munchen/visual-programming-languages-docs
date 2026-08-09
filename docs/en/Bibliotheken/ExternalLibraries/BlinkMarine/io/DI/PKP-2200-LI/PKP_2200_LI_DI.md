# PKP_2200_LI_DI

![PKP_2200_LI_DI](./PKP_2200_LI_DI.svg)

* * * * * * * * * *
## Introduction

The PKP_2200_LI_DI is a global constant definition for Blink Marine PowerKey Digital Inputs. This constant defines the pin assignments for the digital inputs of a PowerKey system and provides predefined configurations for various keys as well as an invalid state.
## Interface Structure

### **Event Inputs**

*No event inputs available - this is a global constant definition*

### **Event Outputs**

*No event outputs available - this is a global constant definition*

### **Data Inputs**

*No data inputs available - this is a global constant definition*

### **Data Outputs**

*No data outputs available - this is a global constant definition*

### **Adapters**

*No adapters available - this is a global constant definition*

## Functionality

The PKP_2200_LI_DI defines global constants of type `PKP_2200_LI_DI_S`, which specify the pin numbers for digital inputs of a Blink Marine PowerKey system. Each constant represents a specific key configuration with associated hardware pins.

*No data outputs available - this is a global constant definition*

# Functionality #

- **Data Type**: All constants use the structure type `PKP_2200_LI_DI_S`
- **Pin Assignments**:
- DigitalInput_Key_1: Pin 1
- DigitalInput_Key_2: Pin 2
- DigitalInput_Key_3: Pin 3
- DigitalInput_Key_4: Pin 4
- Invalid: Pin 255 (invalid state)
- **Package Membership**: BlinkMarine::io::DI

## State Overview

*No state machine present - this is a static constant definition*

## Application Scenarios

- Configuration of digital inputs in marine control systems
- Hardware abstraction for PowerKey key assignments
- Simplification of pin mapping in IEC 61499 applications
- Error handling through defined invalid state

## ⚖️ Comparison with similar components

Unlike Function blocks with active logic are simply constant definitions that do not perform any active processing. They serve solely for the centralized management of hardware configurations.

## Conclusion

The PKP_2200_LI_DI provides a standardized and maintainable solution for the pin configuration of digital inputs in Blink Marine PowerKey systems. Centralized definition of hardware assignments ensures consistency across different applications and improves code reusability.
