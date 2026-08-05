# Softkey_IXA
## 🎧 Podcast
* [ISO 11783-6: Understanding Softkeys and the Virtual Terminal – Your Key to Agricultural Machinery Mechatronics]
## Introduction
Softkey_IXA is a composite function block for processing Boolean input data. The block serves as an interface for softkey operations and enables the initialization and querying of input states via standardized ISOBUS communication protocols.
``` ![Softkey_IXA](Softkey_IXA.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service initialization event with the associated data QI, PARAMS, and u16ObjId
- **REQ**: Service request event with the qualifier QI

### **Event Outputs**
- **INITO**: Initialization confirmation with the output data QO and STATUS

### **Data Inputs**
- **QI**: BOOL - Event Input Qualifier
- **PARAMS**: STRING - Service Parameter
- **u16ObjId**: UINT - Object ID with initial value ID_NULL

### **Data Outputs**
- **QO**: BOOL - Event Output Qualifier
- **STATUS**: STRING - Service Status

### **Adapters**
- **IN**: Adapter of type adapter::types::unidirectional::AX for unidirectional communication

## Functionality
The composite function block Softkey_IXA encapsulates the internal function block Softkey_IX and acts as an intermediary between external calls and the actual softkey functionality. During initialization (INIT), parameters are passed to the internal block, and during service requests (REQ), the corresponding queries are executed. The IN adapter enables communication with external components.

```
## Technical Features
- Uses ISOBUS-specific types and constants
- Supports object identification via u16ObjId
- Flexible parameter passing via STRING parameters
- Unidirectional adapter interface for extended communication

## State Overview
The function block has two main states:

1. **Initialization State**: Processing of INIT events with parameter passing

2. **Service State**: Processing of REQ requests and return of results

## Application Scenarios
- Agricultural operator terminals with softkey functionality
- ISOBUS-compatible control systems
- Applications with Boolean input queries
- Systems with configurable service interfaces

## ⚖️ Comparison with Similar Blocks
Compared to simple Boolean input blocks, Softkey_IXA offers extended ISOBUS compatibility, configurable service interfaces, and adapter-based extensibility. The composite structure allows for a clear separation between interface logic and core functionality.

## 🛠️ Related exercises
* [Uebung_010_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010_AX.md)
* [Uebung_010a4_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010a4_AX.md)
* [Uebung_010a_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010a_AX.md)
* [Uebung_010b4_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b4_sub_AX.md)
* [Uebung_010b5_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b5_sub_AX.md)
* [Uebung_010c2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c2_AX.md)
* [Uebung_010c3_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c3_sub_AX.md)
* [Uebung_010c4_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c4_sub_AX.md)
* [Exercise_010c_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010c_AX.md)

## Conclusion
Softkey_IXA represents a robust and extensible composite function block for softkey operations in ISOBUS environments. Its clear interface separation and adapter support make it ideally suited for complex control systems in agricultural technology.
