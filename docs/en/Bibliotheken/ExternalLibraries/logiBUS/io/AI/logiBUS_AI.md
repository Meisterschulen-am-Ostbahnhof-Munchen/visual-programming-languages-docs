# logiBUS_AI

![logiBUS_AI](./logiBUS_AI.svg)

* * * * * * * * * *

## Introduction

The logiBUS_AI GlobalConstants define a collection of constants for configuring analog inputs in the logiBUS system. These constants are used for simple and consistent referencing of the analog input channels.

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

The logiBUS_AI GlobalConstants provide predefined constants of type `logiBUS_AI_S`, each representing a specific analog input channel. Each constant contains a pin number that identifies the physical input channel.

## Technical Specifications

- **Constant Type**: All constants are of the structured data type `logiBUS_AI_S`
- **Pin Assignment**: The constants `AnalogInput_I1` to `AnalogInput_I9` correspond to analog inputs 1 to 9
- **Invalid Reference**: The constant `Invalid` with pin value 255 serves as a marker for invalid or non-existent inputs
- **Initialization**: All constants are initialized with their corresponding pin values upon declaration

## State Overview

Since these are constants, they do not undergo state changes. Their values remain unchanged throughout runtime.

## Application Scenarios

- Configuration of analog inputs in logiBUS systems
- Parameterization of function blocks that require analog inputs
- Type-safe referencing of analog channels in programming
- Error handling through the use of the Invalid constant

## ⚖️ Comparison with similar function blocks

Unlike function blocks with dynamic behavior, GlobalConstants offer:

- No runtime calculations
- No event handling
- Constants instead of variable values
- Direct initialization during declaration

## Conclusion

The logiBUS_AI GlobalConstants provide an efficient and type-safe method for referencing analog inputs in the logiBUS system. The predefined constants simplify programming and reduce the potential for errors during channel configuration.
