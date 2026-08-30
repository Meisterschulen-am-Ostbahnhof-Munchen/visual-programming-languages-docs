# Wago459

<img width="1338" height="318" alt="image" src="https://github.com/user-attachments/assets/a327cecb-2330-4f40-9961-8c1c1b151097" />
* * * * * * * * * *
## Introduction

The Wago459 is a Service Interface Function Block for connecting Wago-750-459 analog input modules in 4diac systems. This function block enables the configuration and monitoring of up to four analog input channels and establishes communication with the Wago bus system.
![Wago459](Wago459.svg)

## Interface Structure

### **Event Inputs**

- **MAP**: Initiates the pin assignment for the analog inputs. Linked to the data variables AnalogInput_1 to AnalogInput_4 and QI.

### **Event Outputs**

- **MAPO**: Confirms successful pin assignment. Linked to QO.
- **IND**: Provides status information from the resource manager. Linked to QO and STATUS.

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Controls the activation of the function block
- **AnalogInput_1** (STRING): Configuration for analog input 1
- **AnalogInput_2** (STRING): Configuration for analog input 2
- **AnalogInput_3** (STRING): Configuration for analog input 3
- **AnalogInput_4** (STRING): Configuration for analog input 4

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - Indicates the operating status
- **STATUS** (WSTRING): Detailed status information of the service

### **Adapters**

- **BusAdapterOut** (Plug): Outgoing bus adapter connection of type WagoBusAdapter
- **BusAdapterIn** (Socket): Incoming bus adapter connection of type WagoBusAdapter

## Functionality

The Wago459 function block serves as Interface between the 4diac controller and the Wago 750-459 analog input module. Upon receiving the MAP event, the configured pin assignments (AnalogInput_1 to AnalogInput_4) are transmitted to the bus system. The block confirms successful assignments via MAPO and continuously provides status information via IND events.

## Technical Features

- Supports up to four analog input channels
- Uses STRING data types for flexible pin configuration
- Provides comprehensive status feedback via WSTRING
- Implements a bidirectional adapter system for bus communication
- Includes qualifier variables (QI/QO) for reliable state management

## State Overview

The function block has the following operating states:

- Inactive: Waits for a MAP event with QI enabled
- Configuration: Processes pin assignments after a MAP event
- Operational: Continuously monitors the module status and sends IND events
- Error: In case of problems, STATUS is populated with error information

## Application Scenarios

- Connecting Wago 750-459 analog input modules in automation systems
- Acquiring data from analog sensors (0-10V, 0-20mA, 4-20mA)
- Process monitoring in industrial control systems
- Integration into distributed systems Peripheral Systems with Wago Bus Architecture

## ⚖️ Comparison with Similar Modules

Compared to generic I/O function blocks, Wago459 offers:

- Specific optimization for Wago-750-459 hardware
- Pre-configured adapters for Wago bus systems
- Direct support for all four channels of the module
- Integrated status monitoring and error handling

## Conclusion

The Wago459 function block represents a reliable and specialized solution for integrating Wago-750-459 analog input modules into 4diac-based control systems. Its clear interface definition and comprehensive status feedback enable efficient implementation of analog measurement processing in industrial automation projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
