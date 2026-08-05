# AX_SWITCH
<img width="1215" height="181" alt="image" src="https://github.com/user-attachments/assets/e3a4235c-ef25-4396-b440-3929cea8731a" />
* * * * * * * * * *
## Introduction
The AX_SWITCH function block serves as a switching module (demultiplexer) for events based on a Boolean input value. It forwards incoming events to one of two possible outputs, depending on the state of the control signal.
![AX_SWITCH](AX_SWITCH.svg)

## Interface Structure

### **Event Inputs**
- No direct event inputs - event input is handled via adapters

### **Event Outputs**
- **EO0**: Output event that is activated when an event occurs at G=0
- **EO1**: Output event that is activated when an event occurs at G=1

### **Data Inputs**
- No direct data inputs - data is provided via adapters

### **Data Outputs**
- No data outputs available

### **Adapters**
- **G**: Adapter of type `adapter::types::unidirectional::AX`
- Switches incoming events from EI to EO0 when G=0
- Switches incoming events from EI to EO1 when G=1

## Functionality
The AX_SWITCH block receives events and control data via adapter G. Based on the Boolean value of the The control signal G forwards each incoming event either to output EO0 (when G=0) or to output EO1 (when G=1). Internally, the block uses an E_SWITCH function block to implement the switching function.

## Technical Features
- Implemented as a wrapper around the standard E_SWITCH function block
- Uses unidirectional adapters for event and data communication
- No direct interfaces; all communication occurs via adapters

## State Overview
The block has no internal states in the traditional sense. It operates purely event-driven and immediately forwards each incoming event to the corresponding output based on the current value of G.

## Application Scenarios
- Control of alternative process paths
- Switching between operating modes
- Distribution functions in event-based controllers
- Demultiplexing of event streams

## ⚖️ Comparison with Similar Function Blocks
Compared to the standard E_SWITCH block, AX_SWITCH offers an adapter-based interface, enabling better integration into adapter-based architectures. While E_SWITCH has direct inputs and outputs, AX_SWITCH communicates exclusively via adapters.

Comparison with [E_SWITCH](../../../../../StandardLibraries/events/E_SWITCH.md)

## 🛠️ Related exercises
* [Uebung_004b_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX.md)
* [Uebung_004b_AX_ASR](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR.md)
* [Uebung_004b_AX_ASR_X](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR_X.md)
* [Uebung_005_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_005_AX.md)
* [Uebung_006a3_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_sub_AX.md)
* [Uebung_007a3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_008_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_008_AX.md)
* [Uebung_009_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_009_AX.md)
* [Uebung_020a_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020a_AX.md)
* [Uebung_020b_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020b_AX.md)
* [Uebung_020c3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020d_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020d_AX.md)
* [Uebung_020e2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020f2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_020i_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020i_AX.md)

## Conclusion
AX_SWITCH is a specialized switching device for event-based systems thanks to its adapter-based architecture It enables flexible integration into more complex control systems. The clear separation of event and data flow via adapters ensures a clear system structure.