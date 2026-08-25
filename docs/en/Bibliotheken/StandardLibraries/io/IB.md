# IB

## 🎧 Podcast

* [Eclipse 4diac: Innovation Engine Research vs. User Needs – What Really Drives Development? ](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Eclipse-4diac-Innovationsmotor-Forschung-vs--Nutzerbedrfnisse--Was-treibt-die-Entwicklung-wirklich-voran-e38cke4)
* [DIN EN 61499-1: The Digital Lego Kit for Flexible Automation and a Smart Future ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/DIN-EN-61499-1-Der-digitale-Lego-Baukasten-fr-flexible-Automatisierung-und-smarte-Zukunft-e3681pb)
* [DIN EN 61499-1: The Lego Bricks for Flexible and Event-Driven Industrial Controls ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/DIN-EN-61499-1-Die-Lego-Steine-fr-flexible-und-ereignisgesteuerte-Industriesteuerungen-e3681o1)
* [IEC 61499: The DNA of Flexible Automation – Powering Industry 4.0 from Factories to the High Seas ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/IEC-61499-The-DNA-of-Flexible-Automation--Powering-Industry-4-0-from-Factories-to-the-High-Seas-e376pi8)
* [IEC 61499 vs. 61131: Unpacking the Architectural Revolution of Distributed Control and Industry 4.0 ](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/IEC-61499-vs--61131-Unpacking-the-Architectural-Revolution-of-Distributed-Control-and-Industry-4-0-e3ahbv5)

## 📺 Video

* [LogiBUS Project Update](https://www.youtube.com/watch?v=kVNTJ9ZejFM)

## Introduction

The IB (Input Byte) function block is a service interface function block for processing byte input data. It serves as an interface between an IEC 61499 control system and external input devices or resources that supply byte data.

![IB](IB.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block and configures the interface parameters
- **REQ**: Service Request - Requests current data input

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Service Acknowledgement - Confirms the requested service operations
- **IND**: Indication from Resource - Signals incoming data from the external resource

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL) - Controls the execution of events
- **PARAMS**: Service Parameters (STRING) - Configuration parameters for the interface

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL) - Status indicator for the output events
- **STATUS**: Service Status (STRING) - Status information about the current operation
- **IN**: Input data from the resource (BYTE) - The received byte data

### **Adapter**

No adapter interfaces are available.

## Functionality

The IB function block operates as a bidirectional interface for byte input data. During initialization (INIT), the interface parameters are configured. Data can be explicitly requested via REQ events, while IND events signal asynchronous data inputs. The received byte data is provided via the IN output.

## Technical Features

- Supports both request-based (REQ/CNF) and event-based (IND) data acquisition
- BYTE data type for compact 8-bit data processing
- String-based parameter configuration for flexible customization
- Status feedback via SERVICE status output

## State Overview

The function block goes through the following main states:

1. **Not Initialized**: Waiting for an INIT event
2. **Initialized**: Ready for data acquisition
3. **Data Request**: Processing REQ events
4. **Data Receive**: Processing incoming IND events

## Application Scenarios

- Reading 8-bit sensor data
- Interface to simple digital input devices
- Communication with peripheral devices that provide byte data
- Protocol implementations with byte-oriented data formats

## ⚖️ Comparison with Similar Function Blocks

Compared to other input blocks:

- IB specialized for the BYTE data type (8-bit)
- Offers both polling (REQ) and interrupt-type (IND) operating modes
- Simpler than more complex protocol blocks, but more specific for byte data

## 🛠️ Related Exercises

* [Exercise_006c](../../../Uebungen/test_B/Uebungen_doc/Uebung_006c.md)
* [Exercise_011a](../../../Uebungen/test_B/Uebungen_doc/Uebung_011a.md)

## Conclusion

The IB function block offers an efficient and flexible solution for integrating byte-based input data into IEC 61499 control systems. Its dual operating mode (request-based and event-driven) makes it versatile for various applications in industrial automation.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
