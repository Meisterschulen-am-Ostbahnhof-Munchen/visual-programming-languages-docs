# logiBUS_IE

<img width="2037" height="313" alt="image" src="https://github.com/user-attachments/assets/3cb31c53-ac68-4483-bfc4-834776122b60" />
* * * * * * * * * *
## Introduction

The logiBUS_IE function block is an input service interface module for event input data. It serves as an interface between the logiBUS system and the 4diac runtime environment for processing digital input signals with extended event detection functions.
`` ![logiBUS_IE](logiBUS_IE.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization
- Linked to: QI, PARAMS, Input, InputEvent
- **REQ**: Service Request
- Linked to: QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Services
- Linked to: QO, STATUS
- **IND**: Resource Indication
- Linked to: QO, STATUS

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameter
- **Input** (logiBUS_DI_S): Identifies the Input (I1..I8)
- Initial Value: Invalid
- **InputEvent** (logiBUS_DI_Events_S): Identifies the event (Down, Up, Single-Click, Double-Click, etc.)
- Initial value: Invalid

### **Data Outputs**

- **QO** (BOOL): Event output qualifier
- **STATUS** (STRING): Service status

### **Adapter**

No adapter interfaces available.

## Functionality

This function block enables the processing of digital input signals with advanced event detection. Specific parameters can be configured via the INIT initialization. The block recognizes various input events such as key presses, releases, single clicks, and double clicks and signals these via the corresponding output events.

## Technical Features

- Supports multiple event types (Down, Up, Single-Click, Double-Click)
- Flexible input configuration via PARAMS string
- Status feedback via STATUS output
- Initialization with invalid values for a safe start

## State Overview

The function block has an initialized state and an operating state. After successful INIT initialization, it switches to the operating state, in which event processing and service requests can be handled.

## Application Scenarios

- Operator Panel Controllers
- Keyboard Input Processing
- Mechanical Switch Monitoring
- User Interaction Systems
- Industrial Control Pushbuttons

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital input blocks, logiBUS_IE offers advanced event detection capabilities and can recognize complex input patterns such as double-clicks. The configurable design allows for flexible adaptation to various hardware interfaces.

## 🛠️ Related exercises

* [Uebung_004a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a.md)
* [Uebung_004a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2.md)
* [Uebung_004a2_2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_2.md)
* [Uebung_004a2_3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_3.md)
* [Uebung_004a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a2_AX.md)
* [Uebung_004a3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a3.md)
* [Uebung_004a3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a3_AX.md)
* [Uebung_004a4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a4.md)
* [Uebung_004a4_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a4_AX.md)
* [Uebung_004a5](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a5.md)
* [Uebung_004a5_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a5_AX.md)
* [Uebung_004a6](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a6.md)
* [Uebung_004a6_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a6_AX.md)
* [Uebung_004a7](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a7.md)
* [Uebung_004a7_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a7_AX.md)
* [Uebung_004a8](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a8.md)
* [Uebung_004a8_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a8_AX.md)
* [Uebung_004a9](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004a9.md)
* [Uebung_004a9_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a9_AX.md)
* [Uebung_004a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a_AX.md)
* [Uebung_004b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004b.md)
* [Uebung_004b2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004b2.md)
* [Uebung_004b3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004b3.md)
* [Uebung_004b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX.md)
* [Uebung_004b_AX_ASR](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR.md)
* [Uebung_004b_AX_ASR_X](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR_X.md)
* [Uebung_004c1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c1.md)
* [Uebung_004c1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c1_AX.md)
* [Uebung_004c2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c2.md)
* [Uebung_004c2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c2_AX.md)
* [Uebung_004c3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c3.md)
* [Uebung_004c3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c3_AX.md)
* [Uebung_004c4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c4.md)
* [Uebung_004c4_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c4_AX.md)
* [Uebung_004c5](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c5.md)
* [Uebung_004c5_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c5_AX.md)
* [Uebung_006](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006.md)
* [Uebung_006_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006_AX.md)
* [Uebung_006a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a.md)
* [Uebung_006a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a2.md)
* [Uebung_006a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a2_AX.md)
* [Uebung_006a3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3.md)
* [Uebung_006a3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_AX.md)
* [Uebung_006a4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a4.md)
* [Uebung_006a4_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a4_AX.md)
* [Uebung_006a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a_AX.md)
* [Uebung_006b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006b.md)
* [Uebung_006b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006b_AX.md)
* [Uebung_006d](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006d.md)
* [Uebung_006d_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006d_AX.md)
* [Uebung_007a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_007a1.md)
* [Uebung_007a1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a1_AX.md)
* [Uebung_007a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_007a2.md)
* [Uebung_007a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a2_AX.md)
* [Uebung_007a3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_007a3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_009a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)
* [Uebung_019](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019.md)
* [Uebung_019a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019a.md)
* [Uebung_019b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019b.md)
* [Uebung_019c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
* [Uebung_020f3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020f3.md)
* [Uebung_020f3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f3_AX.md)
* [Uebung_020h](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020h.md)
* [Uebung_020h_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020h_AX.md)
* [Uebung_020i](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
* [Uebung_020i_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020i_AX.md)
* [Uebung_031](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_031.md)
* [Uebung_034b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034b.md)
* [Uebung_035](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035.md)
* [Uebung_035a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a.md)
* [Uebung_035a1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1_AX.md)
* [Uebung_035a1b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1b_AX.md)
* [Uebung_035a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)
* [Uebung_035a3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_035b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035b.md)
* [Uebung_035c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_035c.md)
* [Uebung_036](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_036.md)
* [Uebung_037](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_037.md)
* [Uebung_038](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_038.md)
* [Uebung_038_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_038_AX.md)
* [Uebung_039](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_039.md)
* [Uebung_039a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_039a.md)
* [Uebung_040](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_040.md)
* [Uebung_040_2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_040_2.md)
* [Uebung_040_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_040_AX.md)
* [Uebung_041](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_041.md)
* [Uebung_042](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_042.md)
* [Uebung_043](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_043.md)
* [Uebung_080](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_080.md)
* [Uebung_080b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_080b.md)
* [Uebung_080c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_080c.md)
* [Uebung_081](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_081.md)
* [Uebung_082](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_082.md)
* [Uebung_083](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_083.md)
* [Uebung_083_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_083_AX.md)
* [Uebung_084](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_084.md)
* [Uebung_085](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_085.md)
* [Uebung_087](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
* [Uebung_087a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
* [Uebung_091](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_091.md)
* [Uebung_093](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_093.md)
* [Uebung_093b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_093b.md)
* [Uebung_094](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
* [Uebung_094a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
* [Uebung_094a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Uebung_095](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
* [Uebung_095_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_095_AX.md)
* [Uebung_110](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_110.md)
* [Uebung_111](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)
* [Uebung_124](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_124.md)
* [Uebung_127](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_127.md)
* [Uebung_128](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_128.md)
* [Uebung_128b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)
* [Uebung_132](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_132.md)
* [Uebung_150_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_150_AX.md)
* [Uebung_151_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)
* [Uebung_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)
* [Uebung_160b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b.md)
* [Uebung_160b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)
* [Uebung_171_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_171_AX.md)
* [Uebung_179](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_179.md)
* [Uebung_180](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_180.md)

## Conclusion

The logiBUS_IE function block provides a powerful interface for digital input devices Advanced event detection is available. Its flexible configurability and support for various event types make it ideal for applications requiring complex user interactions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
