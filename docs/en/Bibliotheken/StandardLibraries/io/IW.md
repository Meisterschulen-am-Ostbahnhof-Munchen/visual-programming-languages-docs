# IW

## 🎧 Podcast

- [Miniware TS101: The Mobile Soldering All-Rounder – Strengths, Weaknesses, and the USB-C Revolution](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Miniware-TS101-Das-mobile-Lt-Multitalent--Strken--Schwchen-und-die-USB-C-Revolution-e368lka)
## Introduction

The IW (Input Word) function block is a service interface function block for processing word input data in 4diac systems. It serves as an interface between the control logic and external input devices or resources that provide word data (16-bit).
![IW](IW.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block and configures the hardware parameters
- **REQ**: Service Request - Requests a current input from the connected device

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms completion of initialization
- **CNF**: Requested Service Acknowledgement - Acknowledges a successful REQ request
- **IND**: Resource Indication - Signals incoming data without a prior request

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL) - Enables/disables processing
- **PARAMS**: Service Parameters (STRING) - Configuration parameters for the hardware interface

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL) - Processing status
- **STATUS**: Service status (STRING) - Error messages or status information
- **IN**: Input data from the resource (WORD) - The read 16-bit data

## Functionality

The IW block operates as a bidirectional interface for Word input data. During initialization (INIT), the hardware parameters are configured. The block can respond to explicit requests (REQ) as well as process asynchronous data indications (IND) from the connected resource. The read Word data is output to the IN output.

## Technical Features

- Processes 16-bit WORD data types
- Supports both request-based (REQ/CNF) and event-based (IND) communication
- String-based parameter configuration for flexible hardware connectivity
- Comprehensive status feedback via STATUS output

## State Overview

The block goes through the following main states:

- **Not Initialized**: Block waits for an INIT event
- **Initialized**: Block is ready and can process data
- **Data Request**: Processing a REQ request
- **Data Reception**: Processing incoming IND data

## Application Scenarios

- Connecting 16-bit input devices (sensors, encoders, switch groups)
- Reading digital input words from process peripherals
- Interface to I/O modules with word-based inputs
- Monitoring status words from distributed systems

## ⚖️ Comparison with Similar Blocks

Compared to IB (Input Byte) IW processes 16-bit data instead of 8-bit data. Compared to ID (Input Double Word), IW offers a narrower data width. The block's structure is similar to other I/O interface blocks, but it is specifically optimized for WORD data types.

## Conclusion

The IW function block provides a robust and flexible interface for processing 16-bit input data in 4diac systems. Its clear event structure and comprehensive status feedback make it a reliable solution for connecting word-based input devices in industrial automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
