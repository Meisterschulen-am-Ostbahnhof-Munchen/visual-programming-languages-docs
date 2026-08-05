# DataPanel_MI_QX
<img width="1373" height="208" alt="image" src="https://github.com/user-attachments/assets/8a1255b9-89e3-4fc4-bcc6-e88ae8562622" />
* * * * * * * * * *
## Introduction
The DataPanel_MI_QX is a Service Interface Function Block for outputting Boolean data to a resource. This block serves as an interface between the control logic and the physical outputs of a DataPanel MI system and enables the configuration and control of digital outputs.
`` ![DataPanel_MI_QX](DataPanel_MI_QX.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Operation

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **OUT** (BOOL): Output Data for Resource
- **u8SAMember** (USINT): Node SA 224..239, Initial Value: MI::MI_00
- **Output** (DataPanel_MI_DO_S): Identifies the output (DigitalOutput_1A..8B and Input_Power_Port_5..8), Initial Value: Invalid

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapters**
No adapter interfaces are available.

## Functionality
The DataPanel_MI_QX function block manages communication with the digital outputs of a DataPanel MI system. During initialization (INIT event), the service parameters are configured and the hardware interface is set up. The REQ event triggers the output of Boolean data to the specified resource. The function block acknowledges both initialization and service operations via the corresponding output events.

## Technical Features
- Supports the configuration of SA nodes in the 224-239 range
- Enables the identification of specific digital outputs (1A to 8B) and power ports (5-8)
- Uses a special data type (DataPanel_MI_DO_S) for output identification
- Implements robust error handling through STATUS output

## State Overview
The Function Block goes through the following states:

1. **Not Initialized**: Waiting for an INIT event

2. **Initialized**: Ready for service requests
3. **Service Execution**: Processing REQ events

4. **Acknowledgement**: Sending CNF/INITO events with status information

## Application Scenarios
- Control of digital outputs in industrial automation systems
- Connection of DataPanel MI hardware components
- Implementation of secure output protocols
- Integration into larger control systems with multiple output channels

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital output blocks, DataPanel_MI_QX offers advanced functionalities such as:

- Configurable SA node configuration
- Specific hardware identification for DataPanel MI systems
- Detailed status feedback
- Flexible output configuration via the output parameter

## 🛠️ Related Exercises
* [Exercise_003b2_sub](../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003b2_sub.md)]
* [Exercise_010a4](../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010a4.md)]

## Conclusion
The DataPanel_MI_QX Function Block represents a powerful and flexible solution for controlling digital outputs in DataPanel MI systems. Its extensive parameterization and detailed status feedback make it particularly suitable for complex automation applications that require a reliable and configurable output interface.
