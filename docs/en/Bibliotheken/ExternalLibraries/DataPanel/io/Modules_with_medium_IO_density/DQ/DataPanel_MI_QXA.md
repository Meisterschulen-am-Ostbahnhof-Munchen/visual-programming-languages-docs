# DataPanel_MI_QXA
<img width="1373" height="208" alt="image" src="https://github.com/user-attachments/assets/734858f5-fe59-47ff-9c4f-6ba7b19e3c85" />
* * * * * * * * * *
## Introduction
The DataPanel_MI_QXA is a composite function block for controlling Boolean output data in automation systems. This block serves as an interface for digital outputs and enables the configuration and control of output channels via standardized service parameters.
``` ![DataPanel_MI_QXA](DataPanel_MI_QXA.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service initialization event with associated data QI, PARAMS, u8SAMember, and Output

### **Event Outputs**
- **INITO**: Initialization acknowledgment with QO and STATUS
- **CNF**: Acknowledgement of the requested service with QO and STATUS

### **Data Inputs**
- **QI** (BOOL): Event input qualifier
- **PARAMS** (STRING): Service parameter
- **u8SAMember** (USINT): Node SA address in the range 224-239, initialized with MI::MI_00
- **Output** (DataPanel_MI_DO_S): Output identification (DigitalOutput_1A..8B and Input_Power_Port_5..8), initialized with Invalid

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapters**
- **OUT**: Unidirectional AX-type adapter for output control

## Functionality
The DataPanel_MI_QXA composite function block encapsulates the functionality of the DataPanel_MI_QX block and extends it with an adapter interface. Upon initialization, the configuration parameters are passed to the internal QX block. The OUT adapter enables external control of the output functions via standardized interfaces.

## Technical Features
- Supports SA addresses in the range 224-239
- Uses specific output identification for digital outputs and power ports
- Integrated error handling through invalid initialization
- Unidirectional adapter architecture for clean interface separation

## State Overview
The function block goes through the following states:

1. **Initialization Phase**: The INIT event processes configuration parameters

2. **Ready State**: Waits for control requests via adapter OUT
3. **Active Operation**: Processes output commands and generates CNF acknowledgments

## Application Scenarios
- Control of digital outputs in industrial automation
- Connection of power port controllers
- Integration into modular control systems with SA addressing
- Use in distributed automation systems

## ⚖️ Comparison with Similar Function Blocks
Compared to simple digital output function blocks, DataPanel_MI_QXA offers:

- Extended parameterization options via STRING Parameters
- SA Addressing Support for Network Integration
- Composite Architecture with Adapter Interface
- Comprehensive Status Feedback

## 🛠️ Related Exercises
* [Exercise_003b2_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003b2_sub_AX.md)
* [Exercise_003b3_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003b3_sub_AX.md)
* [Exercise_010a4_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010a4_AX.md)

## Conclusion
The DataPanel_MI_QXA is a powerful composite function block for controlling Boolean output data in complex automation environments. Its modular architecture and standardized interfaces make it ideal for use in distributed control systems with high demands on flexibility and maintainability.