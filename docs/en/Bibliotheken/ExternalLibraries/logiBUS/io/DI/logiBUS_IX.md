# logiBUS_IX

<img width="1789" height="343" alt="image" src="https://github.com/user-attachments/assets/8c558337-facf-438d-87ba-69a1b8e110a9" />
* * * * * * * * * *
## Introduction

The logiBUS_IX function block is an input service interface for Boolean input data, specifically designed for communication with logiBUS input modules. It serves as an interface between the control logic and physical input signals, enabling the querying of digital input values.
![logiBUS_IX](logiBUS_IX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Request
- **IND**: Display from Resource Interface

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL)
- **PARAMS**: Service Parameters (STRING)
- **Input**: Identifies Input I1..I8 (logiBUS_DI_S) - Initial Value: Invalid

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL)
- **STATUS**: Service Status (STRING)
- **IN**: Input Data from Resource (BOOL)

### **Adapter**

No adapter interfaces are available.

## Functionality

The function block initializes itself via the INIT event and can then request input data via the REQ event. Upon successful initialization, it returns the INITO event. The actual input values are provided via the IN output, while the STATUS output provides information about the current operating state.

## Technical Features

- Supports up to 8 digital inputs (I1..I8)
- Uses special logiBUS data types for input identification
- Provides comprehensive status feedback via the STATUS output
- Initializes with an invalid input value (Invalid)

## State Overview

The function block typically goes through the following states:

1. **Not Initialized**: Before the INIT request
2. **Initialized**: After successful INIT processing
3. **Ready**: Can process REQ requests
4. **Active**: Currently processing a service request

## Application Scenarios

- Querying digital input signals in automation systems
- Integrating logiBUS input modules into 4diac-based controllers
- Monitoring switch states and sensor signals
- Industrial I/O control with status monitoring

## ⚖️ Comparison with Similar Blocks

Compared to simple digital input blocks, this offers logiBUS_IX:

- Advanced status information
- Parameterizable service parameters
- Specific logiBUS hardware integration
- More comprehensive initialization and confirmation mechanisms

## 🛠️ Related exercises

* [Uebung_001](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_001.md)
* [Uebung_001c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_001c.md)
* [Uebung_002](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002.md)
* [Uebung_002a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a.md)
* [Uebung_002a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a2.md)
* [Uebung_002a3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a3.md)
* [Uebung_002a4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a4.md)
* [Uebung_002a5b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a5b.md)
* [Uebung_002b2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)
* [Uebung_002b3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b3.md)
* [Uebung_003](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003.md)
* [Uebung_003a0](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003a0.md)
* [Uebung_003a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003a_sub.md)
* [Uebung_003b_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003b_sub.md)
* [Uebung_003c_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003c_sub.md)
* [Uebung_003d](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003d.md)
* [Uebung_005](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_005.md)
* [Uebung_006e1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006e1.md)
* [Uebung_006e2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006e2.md)
* [Uebung_019c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
* [Uebung_020a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020a.md)
* [Uebung_020b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020b.md)
* [Uebung_020c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c.md)
* [Uebung_020c2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2.md)
* [Uebung_020c3](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
* [Uebung_020d](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020d.md)
* [Uebung_020e](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020e.md)
* [Uebung_020e2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020e2.md)
* [Uebung_020f](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020f.md)
* [Uebung_020f2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
* [Uebung_020g](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020g.md)
* [Uebung_020i](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
* [Uebung_028](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_028.md)
* [Uebung_029](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_029.md)
* [Uebung_030](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_030.md)
* [Uebung_032](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_032.md)
* [Uebung_033_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_033_sub.md)
* [Uebung_049](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_049.md)
* [Uebung_051](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_051.md)
* [Uebung_052](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)
* [Uebung_053](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_053.md)
* [Uebung_054](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_054.md)
* [Uebung_055](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_055.md)
* [Uebung_056](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)
* [Uebung_085](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_085.md)
* [Uebung_086](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_086.md)
* [Uebung_087](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
* [Uebung_087a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
* [Uebung_087a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087a2.md)
* [Uebung_088](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)
* [Uebung_089](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)
* [Uebung_090a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a1.md)
* [Uebung_090a1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a1_AX.md)
* [Uebung_090a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a2.md)
* [Uebung_090a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a2_AX.md)
* [Exercise_094](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
* [Exercise_094a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
* [Exercise_095](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
* [Exercise_160](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_160.md)
* [Exercise_160b2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)
* [Exercise_177](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_177.md)
* [Exercise_178](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)

## Conclusion

The logiBUS_IX function block represents a robust and flexible solution for integrating logiBUS input modules into 4diac-based control systems. Its comprehensive status feedback and configurable interface make it particularly suitable for industrial applications where reliable I/O communication is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]