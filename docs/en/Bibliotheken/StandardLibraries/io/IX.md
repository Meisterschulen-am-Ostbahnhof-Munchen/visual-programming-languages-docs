# IX

## 🎧 Podcast

- [Infineon MOTIX BTM9020/9021EP: Datasheet Analysis for Automotive – Robust Motor Driver with Intelligent Diagnostics (HW vs. SPI) ](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Infineon-MOTIX-BTM90209021EP-Datenblatt-Analyse-fr-Automotive--Robuster-Motortreiber-mit-intelligenter-Diagnose-HW-vs--SPI-e39av51)
- [Integrated Full Bridge ICs MOTIX™ BTM9020EP ](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/integrierten-Vollbrcken-ICs-MOTIX-BTM9020EP-e368kse)

## Introduction

The IX function block is a service interface function block for Boolean input data. It serves as an interface for communication with input devices and enables the querying and processing of digital input signals in 4diac systems.

![IX](IX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block and configures the hardware parameters
- **REQ**: Service Request - Requests a query of the current input value

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Confirmation of Requested Service - Confirms a successful query
- **IND**: Indication from Resource - Signals a change in the input signal's state

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL) - Controls the activation of the service functionality
- **PARAMS**: Service Parameters (STRING) - Contains configuration parameters for the hardware interface

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL) - Displays the service execution status
- **STATUS**: Service status (STRING) - Provides status information about the service execution
- **IN**: Input data from the resource (BOOL) - Contains the current value of the digital input

### **Adapter**

No adapter interfaces are available.

## Functionality

The IX function block acts as an intermediary between the control logic and physical input devices. During initialization (INIT), the hardware parameters are configured. Subsequently, the current state of the input can be queried via REQ events. The block can process both poll-based queries (REQ/CNF) and event-based notifications (IND) upon state changes.

## Technical Features

- Supports both request-based and event-driven operating modes
- Boolean data type for simple digital inputs
- Flexible parameter configuration via STRING parameters
- Comprehensive status feedback for fault diagnosis

## State Overview

The function block goes through the following main states:

1. **Not Initialized**: Block is inactive
2. **Initialized**: Block is ready for operation after successful INIT processing
3. **Query Active**: Processing a REQ request
4. **Indication Ready**: Ready for event-driven notifications

## Application Scenarios

- Querying digital sensors (limit switches, proximity switches)
- Monitoring push-button inputs
- Reading switch positions
- Digital signal processing in automation systems

## ⚖️ Comparison with Similar Blocks

Compared to other input blocks, IX offers an enhanced service interface with both poll-based and event-driven operating modes. While simpler input blocks often only provide direct values, IX offers additional status information and error handling.

## 🛠️ Related exercises

- [Uebung_001](../../../Uebungen/test_B/Uebungen_doc/Uebung_001.md)
- [Uebung_001c](../../../Uebungen/test_B/Uebungen_doc/Uebung_001c.md)
- [Uebung_002](../../../Uebungen/test_B/Uebungen_doc/Uebung_002.md)
- [Uebung_002a](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a.md)
- [Uebung_002a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a2.md)
- [Uebung_002a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a3.md)
- [Uebung_002a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a4.md)
- [Uebung_002a5b](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a5b.md)
- [Uebung_002b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)
- [Uebung_002b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_002b3.md)
- [Uebung_003](../../../Uebungen/test_B/Uebungen_doc/Uebung_003.md)
- [Uebung_003a0](../../../Uebungen/test_B/Uebungen_doc/Uebung_003a0.md)
- [Uebung_003a_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003a_sub.md)
- [Uebung_003b2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003b2_sub.md)
- [Uebung_003b_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003b_sub.md)
- [Uebung_003c_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003c_sub.md)
- [Uebung_003d](../../../Uebungen/test_B/Uebungen_doc/Uebung_003d.md)
- [Uebung_005](../../../Uebungen/test_B/Uebungen_doc/Uebung_005.md)
- [Uebung_006e1](../../../Uebungen/test_B/Uebungen_doc/Uebung_006e1.md)
- [Uebung_006e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_006e2.md)
- [Uebung_010](../../../Uebungen/test_B/Uebungen_doc/Uebung_010.md)
- [Uebung_010a](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a.md)
- [Uebung_010a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a2.md)
- [Uebung_010a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a3.md)
- [Uebung_010a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a4.md)
- [Uebung_010b1](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b1.md)
- [Uebung_010b4_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b4_sub.md)
- [Uebung_010b5_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b5_sub.md)
- [Uebung_010c](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c.md)
- [Uebung_010c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c2.md)
- [Uebung_010c3_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c3_sub.md)
- [Uebung_010c4_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c4_sub.md)
- [Uebung_019c](../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
- [Uebung_020a](../../../Uebungen/test_B/Uebungen_doc/Uebung_020a.md)
- [Uebung_020b](../../../Uebungen/test_B/Uebungen_doc/Uebung_020b.md)
- [Uebung_020c](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c.md)
- [Uebung_020c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2.md)
- [Uebung_020c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
- [Uebung_020d](../../../Uebungen/test_B/Uebungen_doc/Uebung_020d.md)
- [Uebung_020e](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e.md)
- [Uebung_020e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e2.md)
- [Uebung_020f](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f.md)
- [Uebung_020f2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
- [Uebung_020g](../../../Uebungen/test_B/Uebungen_doc/Uebung_020g.md)
- [Uebung_020i](../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
- [Uebung_028](../../../Uebungen/test_B/Uebungen_doc/Uebung_028.md)
- [Uebung_029](../../../Uebungen/test_B/Uebungen_doc/Uebung_029.md)
- [Uebung_030](../../../Uebungen/test_B/Uebungen_doc/Uebung_030.md)
- [Uebung_032](../../../Uebungen/test_B/Uebungen_doc/Uebung_032.md)
- [Uebung_033_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_033_sub.md)
- [Uebung_039_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
- [Uebung_039b](../../../Uebungen/test_B/Uebungen_doc/Uebung_039b.md)
- [Uebung_049](../../../Uebungen/test_B/Uebungen_doc/Uebung_049.md)
- [Uebung_051](../../../Uebungen/test_B/Uebungen_doc/Uebung_051.md)
- [Uebung_052](../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)
- [Uebung_053](../../../Uebungen/test_B/Uebungen_doc/Uebung_053.md)
- [Uebung_054](../../../Uebungen/test_B/Uebungen_doc/Uebung_054.md)
- [Uebung_055](../../../Uebungen/test_B/Uebungen_doc/Uebung_055.md)
- [Uebung_056](../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)
- [Uebung_085](../../../Uebungen/test_B/Uebungen_doc/Uebung_085.md)
- [Uebung_086](../../../Uebungen/test_B/Uebungen_doc/Uebung_086.md)
- [Uebung_087](../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
- [Uebung_087a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
- [Uebung_087a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a2.md)
- [Uebung_088](../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)
- [Uebung_089](../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)
- [Uebung_090a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_090a1.md)
- [Uebung_090a1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a1_AX.md)
- [Uebung_090a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_090a2.md)
- [Uebung_090a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a2_AX.md)
- [Uebung_094](../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
- [Uebung_094a](../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
- [Uebung_095](../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
- [Uebung_160](../../../Uebungen/test_B/Uebungen_doc/Uebung_160.md)
- [Uebung_160b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)
- [Uebung_177](../../../Uebungen/test_B/Uebungen_doc/Uebung_177.md)
- [Exercise_178](../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)

## Conclusion

The IX function block provides a robust and flexible solution for integrating Boolean input data into 4diac systems. Its comprehensive error handling and flexible operating modes make it particularly suitable for reliable automation applications with digital input signals.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
