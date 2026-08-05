# logiBUS_IXA
<img width="1838" height="367" alt="image" src="https://github.com/user-attachments/assets/fcf18e0e-a542-4642-a00f-1438f4caf5fb" />
* * * * * * * * * *
## Introduction
The logiBUS_IXA is a composite function block for processing Boolean input data. It serves as an interface for digital inputs and enables the initialization and querying of input signals via standardized service interfaces.
![logiBUS_IXA](logiBUS_IXA.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service initialization event with the associated data QI, PARAMS, and Input
- **REQ**: Service request event with the associated data value QI

### **Event Outputs**
- **INITO**: Initialization confirmation with the associated data values QO and STATUS

### **Data Inputs**
- **QI**: Boolean event input qualifier
- **PARAMS**: Service parameters as a string
- **Input**: Identifies inputs Q1 to Q8 with type logiBUS_DI_S and initial value "Invalid"

### **Data Outputs**
- **QO**: Boolean event output qualifier
- **STATUS**: Service status as a string

### **Adapters**
- **IN**: Unidirectional AX-type adapter for input data processing

## Functionality
The logiBUS_IXA composite function block encapsulates the logiBUS_IX base function block and extends its functionality with additional adapter interfaces. Upon INIT events, parameters are forwarded to the internal IX block, which performs the initialization. IND events from the IX block are passed to the IN input adapter, while the data connections ensure the corresponding signal processing.

## Technical Features
- Uses the specific data type logiBUS_DI_S for input identification
- Implements standardized service interfaces according to DIN 61499-2
- Supports parameter passing via the STRING data type
- Provides status feedback via the STATUS output

## State Overview
The function block has two main states:

1. **Not initialized**: Before the INIT event

2. **Initialized and ready for operation**: After successful INIT confirmation

## Application Scenarios
- Connecting digital inputs in automation systems
- Integration into logiBUS-based control architectures
- Use in PLC systems with Boolean signal processing requirements

## ⚖️ Comparison with Similar Blocks
Compared to simple digital input blocks, logiBUS_IXA offers extended service functionalities with parameterization options and status feedback. The composite structure enables better reusability and enhanced diagnostic capabilities.

## 🛠️ Related exercises
* [Uebung_001_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_001_AX.md)
* [Uebung_001_AX_b](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_001_AX_b.md)
* [Uebung_001c_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_001c_AX.md)
* [Uebung_002_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002_AX.md)
* [Uebung_002a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a2_AX.md)
* [Uebung_002a3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002a5_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5_AX.md)
* [Uebung_002a5b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5b_AX.md)
* [Uebung_002a6_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a6_AX.md)
* [Uebung_002a7_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a7_AX.md)
* [Uebung_002a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a_AX.md)
* [Uebung_002b3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_003_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003_AX.md)
* [Uebung_003a0_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003a0_AX.md)
* [Uebung_003a_AX_sub](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003a_AX_sub.md)
* [Uebung_003c_sub_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003c_sub_AX.md)
* [Uebung_003d_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003d_AX.md)
* [Uebung_005_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_005_AX.md)
* [Uebung_006e1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006e1_AX.md)
* [Uebung_006e2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006e2_AX.md)
* [Uebung_020a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020a_AX.md)
* [Uebung_020b_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020b_AX.md)
* [Uebung_020c3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020c_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c_AX.md)
* [Uebung_020d_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020d_AX.md)
* [Uebung_020e2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020e_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e_AX.md)
* [Uebung_020f2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_020f_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f_AX.md)
* [Uebung_020g_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020g_AX.md)
* [Uebung_020i_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020i_AX.md)
* [Uebung_020j2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020j2_AX.md)
* [Uebung_020j_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020j_AX.md)
* [Uebung_090a1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a1_AX.md)
* [Uebung_090a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a2_AX.md)
* [Uebung_094a_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Uebung_095_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_095_AX.md)
* [Uebung_103](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c.md)
* [Uebung_103c2](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c2.md)
* [Uebung_160_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Exercise_177_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_177_AX.md)
* [Exercise_178_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_178_AX.md)

## Conclusion
The logiBUS_IXA function block represents a robust and flexible solution for processing digital input signals in 4diac-based automation systems. Thanks to its standardized interfaces and extended service functions, it is particularly suitable for complex applications with high demands on diagnostics and parameterization.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
