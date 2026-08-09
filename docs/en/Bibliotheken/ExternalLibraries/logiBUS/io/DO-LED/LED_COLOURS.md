# LED_COLOURS

![LED_COLOURS](./LED_COLOURS.svg)

* * * * * * * * * *
## Introduction

LED_COLOURS is a global constant definition that provides standardized color values for LED displays. These constants are used in logiBUS systems for the uniform control of colored LED outputs.
## Interface Structure

### **Event Inputs**

*No event inputs available*

### **Event Outputs**

*No event outputs available*

### **Data Inputs**

*No data inputs available*

#### **Data Outputs**

*No data outputs available*

#### **Adapters**

*No adapters available*

## Functionality

LED_COLOURS defines a collection of global constants of type UINT (16-bit unsigned integer) that represent different LED colors. Each color is assigned a fixed numerical value:

- LED_RED: 1
- LED_YELLOW: 2
- LED_ORANGE: 3
- LED_GREEN: 4
- LED_BLUE: 5
- LED_WHITE: 6
- LED_MAGENTA: 7
- LED_CYAN: 8

## Technical Specifications

- All constants are of type UINT (16-bit unsigned integer)
- Value range: 1-8 for the defined colors
- Constants are set at compile time and are immutable
- Part of the logiBUS::io::DO_LED package

## State Overview

*Since these are static constants, no state model exists*

## Application Scenarios

- Color coding in machine controllers
- Status indicators with colored LEDs
- Standardization of color control in distributed systems
- Visualization of operating states in industrial plants

## ⚖️ Comparison with similar Building Blocks

Unlike function blocks with dynamic behavior, these are purely static constant definitions. Similar constructs would be:

- ENUM data types for color definitions
- #define preprocessor instructions in C/C++
- Constant blocks in other IEC 61131 languages

## Conclusion

LED_COLOURS offers a standardized and maintainable solution for controlling the color of LED displays in logiBUS systems. Centralized definition avoids inconsistencies and increases code reusability.
