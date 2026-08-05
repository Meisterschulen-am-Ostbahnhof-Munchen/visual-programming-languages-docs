# logiBUS_2_CAN_DI

![logiBUS_2_CAN_DI](./logiBUS_2_CAN_DI.svg)

* * * * * * * * * *

## Introduction
The logiBUS_2_CAN_DI GlobalConstants define constants for configuring digital inputs (DIs) in the logiBUS system via CAN bus. These constants are used for pin assignment for digital input channels and provide a standardized interface for hardware configuration.


## Interface Structure

### **Constant Definitions**

The GlobalConstants define three main constants for the digital input configuration:

- **Input_CI1**: Configuration for digital input channel 1
- **Input_CI2**: Configuration for digital input channel 2
- **Invalid**: Indicates an invalid or unconfigured input

### **Data Types**

All constants use the structured data type `logiBUS_2_CAN_DI_S`, which contains the following component:

- **Pin**: Integer value for identifying the physical input pin

## Functionality
The constants are not modified at runtime and are used exclusively for configuring the digital inputs. They define the hardware mapping between logical channels and physical pins in the CAN-based logiBUS system.


## Technical Features

- **Pin Assignment**: Channel 1 is assigned to Pin 1, Channel 2 is assigned to Pin 2

- **Invalid Identifier**: The value 255 indicates an invalid or unavailable input

- **CAN Integration**: Specifically optimized for CAN-based logiBUS systems

- **Type Safety**: Use of structured data types for consistent configuration

## Application Scenarios

- Configuration of digital inputs in logiBUS controllers
- Hardware abstraction in CAN-based automation systems

- Pin assignment in distributed I/O systems

- Error handling for unconfigured inputs

## ⚖️ Comparison with Similar Function Blocks

Compared to simple numeric constants, these structured constants offer:

- Higher type safety through structured data types

- Improved maintainability through centralized configuration
- Extensibility for additional parameters
- Compatibility with logiBUS system architecture

## Conclusion
The logiBUS_2_CAN_DI GlobalConstants offer a robust and type-safe solution for configuring digital inputs in CAN-based logiBUS systems. Their structured approach enables clear hardware mapping and simplifies the maintenance and expansion of automation solutions.