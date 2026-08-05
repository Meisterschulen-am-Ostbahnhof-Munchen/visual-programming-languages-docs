# Touch-sensitive
<img width="662" height="233" alt="image" src="https://github.com/user-attachments/assets/26789397-647c-4c13-b28d-5752fd19880c" />
* * * * * * * * * *
## Introduction
This exercise deals with creating and using a sub-application type in the 4diac IDE. The "touch-sensitive" function block serves as a sub-application and implements a unidirectional adapter connection between input and output adapters.
## Function Blocks (FBs) Used

### Sub-block: touch-sensitive
- **Type**: SubAppType
- **Internal FBs Used**: No internal FBs present
- **Functionality**: The "touch-sensitive" sub-block establishes an adapter connection between an input adapter (IN) and an output adapter (OUT). Both adapters use the type "adapter::types::unidirectional::AX" and enable unidirectional data transmission.

## Program Flow and Connections

The "tactile" sub-module has the following interfaces:

- **Input Adapter**: IN (Type: adapter::types::unidirectional::AX)
- **Output Adapter**: OUT (Type: adapter::types::unidirectional::AX)

The connection is made directly from the input adapter IN to the output adapter OUT. This configuration allows for easy forwarding of signals or data through the sub-module.

**Difficulty Level**: Easy

**Required Prior Knowledge**: Basic knowledge of 4diac-IDE, understanding of adapter connections and sub-applications

**Starting the Exercise**: The sub-module can be integrated into larger applications and controlled via the defined adapter interfaces.

## Summary
The "tactile" exercise demonstrates the creation of a simple sub-application type with adapter connections. It shows the basic structure of sub-modules in 4diac-IDE and their integration into larger control applications using standardized adapter interfaces.

## 🛠️ Related exercises
* [Uebung_103](../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c.md)
* [Uebung_103c2](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c2.md)

---

### 🌐 Matching topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
