# IL

## 📺 Video

* [The silent failure]

## 🎧 Podcast

* [4diac IDE: Your open-source toolkit for distributed industrial automation according to IEC 61499]

* [Eclipse 4diac 3.0: ST interpreter, FBE, and 7200 commits – The turbocharger for distributed automation]

* [Eclipse 4diac: Your bicycle for Industry 4.0 – Mastering software complexity and controlling distributed systems]

* [IEC 61499: The future of industrial automation and distributed systems]

* [Step 2 - 4diac applications] Distribute](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Schritt-2---4diac-Anwendungen-verteilen-e36974b)

----

![](https://user-images.githubusercontent.com/69573151/210780439-a6842673-058d-48f2-8cb7-135c6a960116.png)

* * * * * * * * * *

## Introduction
The IL (Input Long Word) function block is a Service Interface Function Block for processing long word input data. It serves as an interface between the control logic and external input devices or resources that provide 64-bit data values.


![IL](IL.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Operation
- **IND**: Indication from Resource

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier - Controls the execution of the service
- **PARAMS** (STRING): Service Parameters for Configuration

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier - Displays the status of the operation

- **STATUS** (STRING): Service Status Information

- **IN** (LWORD): Input Data from the Resource (64-bit value)

### **Adapters**
No adapter interfaces are available.


## Functionality

The IL block functions as an input service interface for long word data. Upon receiving the INIT event, the service is initialized and the configuration parameters are passed via PARAMS. The REQ event triggers a read operation, in which data is read from the connected resource. The block supports both requested reads (CNF) and spontaneous data updates (IND) from the resource.


``` ## Technical Features
- Processes 64-bit Long Word (LWORD) data types
- Supports both poll-based and event-based data queries
- Flexible parameter configuration via STRING parameters
- Status feedback via STATUS output

## State Overview
The block goes through the following states:

1. **Not Initialized**: Before the INIT operation

2. **Initialized**: After successful INIT operation, ready for data queries
3. **Active**: During data querying or when receiving indications

## Application Scenarios
- Reading 64-bit sensor data
- Communication with external devices that provide Long Word data
- High-precision data acquisition systems
- Control systems that need to process large numerical values

## ⚖️ Comparison with Similar Blocks
Compared to other input blocks such as IB (Byte), IW (Word), or ID (Double Word), IL processes the largest data size (64 bits). It thus offers the highest precision for numerical input values in the 4diac I/O library.

## Conclusion
The IL function block provides a robust and flexible interface for processing 64-bit input data in IEC 61499 control systems. Its support for various operating modes (polling and event-driven) makes it versatile for use in a wide range of industrial applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]