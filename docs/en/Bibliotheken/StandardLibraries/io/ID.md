# ID
## 🎧 Podcast
* [4diac IDE: Your "Hello World" of Automation – The Blinking Tutorial Local](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)
* [4diac IDE: Your Open-Source Toolkit for Distributed Industrial Automation according to IEC 61499](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Open-Source-Werkzeugkasten-fr-verteilte-Industrieautomatisierung-nach-IEC-61499-e36821e)
* [4diac IDE: How the IEC 61499 Standard is Revolutionizing Industrial Automation](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Wie-der-IEC-61499-Standard-die-Industrieautomatisierung-revolutioniert-e36756a)
* [From Pyramid to Plug-and-Play: The Rise of Self-Configurable Industrial Automation](https://podcasters.spotify.com/pod/show/eclipse-4diac-en/episodes/From-Pyramid-to-Plug-and-Play-The-Rise-of-Self-Configurable-Industrial-Automation-e368lvk)
* [Building Tomorrow's Factories: Bridging OT and IT with IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Building-Tomorrows-Factories-Bridging-OT-and-IT-with-IEC-61499-e376pia)

## 📺 Video
* [Ideal Diodes](https://www.youtube.com/watch?v=cPYHaOczu6s)

## Introduction

The ID function block is an input service interface module for double-word (DWORD) input data. It serves as an interface between the control logic and external input devices or resources and enables the querying of 32-bit input data.

![ID](ID.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization - Initializes the function block and configures the parameters
- **REQ**: Service Request - Triggers a query of the input data

### **Event Outputs**
- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Confirmation of Requested Service - Confirms a successful service request
- **IND**: Indication from Resource - Signals incoming data from the resource

### **Data Inputs**
- **QI**: Event Input Qualifier (BOOL) - Enables/disables the service
- **PARAMS**: Service Parameters (STRING) - Configuration parameters for the service

### **Data Outputs**
- **QO**: Event Output Qualifier (BOOL) - Status of the Service Output
- **STATUS**: Service status (STRING) - Status information about the service
- **IN**: Input data from the resource (DWORD) - The read 32-bit input data

### **Adapter**
No adapter interfaces available.

## Functionality
The ID block functions as a service interface for double-word input. During initialization (INIT), the service parameters are configured. Subsequently, input data can be selectively queried from the connected resource via REQ events. The block returns the read data via the IN outputs along with status information.

# ## Technical Features
- Processes 32-bit data (DWORD)
- Supports both requested (REQ/CNF) and spontaneous (IND) data transmissions
- Flexible parameter configuration via STRING parameters
- Qualifier-based control (QI/QO) for service activation

## State Overview
The function block goes through the following main states:

1. **Not Initialized**: Before INIT processing
2. **Initialized**: After successful INIT processing, ready for data queries
3. **Data Query**: During the processing of REQ events
4. **Data Reception**: During spontaneously received data (IND)

## Application Scenarios
- Querying 32-bit sensor data
- Reading digital input signals in groups
- Communication with peripheral devices that provide double-word data
- Integration of external measurement systems into 4diac controllers

## ⚖️ Comparison with Similar Function Blocks
Compared to ID offers simpler input blocks:

- Extended status feedback
- Configurable service parameters
- Support for both operating modes (demand-driven and ad hoc)
- 32-bit data width instead of simple BOOL or BYTE values

## 🛠️ Related Exercises
* [Exercise_011](../../../Uebungen/test_B/Uebungen_doc/Uebung_011.md)
* [Exercise_011a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_011a2.md)
* [Exercise_012](../../../Uebungen/test_B/Uebungen_doc/Uebung_012.md)
* [Exercise_012a_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_012a_sub.md)
* [Exercise_012b](../../../Uebungen/test_B/Uebungen_doc/Uebung_012b.md)
* [Exercise_012c](../../../Uebungen/test_B/Uebungen_doc/Uebung_012c.md)
* [Uebung_020c2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2_sub.md)
* [Uebung_028](../../../Uebungen/test_B/Uebungen_doc/Uebung_028.md)
* [Uebung_034](../../../Uebungen/test_B/Uebungen_doc/Uebung_034.md)
* [Uebung_034a1_Q1](../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q1.md)
* [Uebung_034a1_Q2](../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q2.md)
* [Uebung_034a1_Q4](../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q4.md)
* [Uebung_060](../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)
* [Uebung_103](../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_150](../../../Uebungen/test_B/Uebungen_doc/Uebung_150.md)
* [Exercise_150_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_150_AX.md)
* [Exercise_151](../../../Uebungen/test_B/Uebungen_doc/Uebung_151.md)
* [Exercise_151_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)
* [Exercise_152](../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Exercise_153](../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion
The ID function block provides a powerful and flexible interface for double-word input data. Its comprehensive status feedback and configurable parameters make it particularly suitable for demanding applications requiring reliable and informative input data processing.

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 Diode & Semiconductor Basics on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektronik-i/diode/diode/)
* [🌐 Smart Switch vs. Relay on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektronik-ii/smart-switch/relais-vs-smart-switch/)

