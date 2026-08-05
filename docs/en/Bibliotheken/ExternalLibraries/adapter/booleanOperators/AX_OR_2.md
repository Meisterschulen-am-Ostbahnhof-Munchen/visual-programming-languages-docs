# AX_OR_2

<img width="963" height="265" alt="image" src="https://github.com/user-attachments/assets/3c1d3b81-2420-46cc-b7cf-fc6828db919c" />

* * * * * * * * * *
## Introduction
The AX_OR_2 function block is a generic function block for calculating Boolean OR operations. It processes two input signals and outputs the logical OR result. This function block is specifically designed for use in automation systems.


![AX_OR_2](AX_OR_2.svg)

## Interface Structure
### **Event Inputs**
No event inputs available

### **Event Outputs**
No event outputs available

### **Data Inputs**
No direct data inputs available

### **Data Outputs**
No direct data outputs available

### **Adapters**
**Input Adapter:**
- **IN1** - OR Input 1 (Adapter Type: adapter::types::unidirectional::AX)
- **IN2** - OR Input 2 (Adapter Type: adapter::types::unidirectional::AX)

**Output Adapter:**
- **OUT** - OR Result (Adapter Type: adapter::types::unidirectional::AX)

## Functionality
The AX_OR_2 function block performs a logical OR operation between the two input signals IN1 and IN2. The result is output via the output adapter OUT. Processing occurs continuously as soon as input signals are available.

## Technical Features
- Generic function block with the class 'GEN_AX_OR'
- Uses unidirectional adapters for signal transmission
- Implemented as part of the "adapter::booleanOperators" package
- Supports the Eclipse 4diac standard specification 61499-2

## State Overview
Since it is a combinational logic block, AX_OR_2 has no internal state. The output is determined solely by the current input values.


## Application Scenarios

- Safety circuits with redundant sensors
- Parallel control commands
- Monitoring systems with multiple input signals
- Logical operations in control algorithms

## ⚖️ Comparison with similar components

Compared to other OR components, AX_OR_2 is distinguished by its adapter-based interface, which enables flexible integration into various system architectures. The unidirectional adapters ensure a clear signal flow direction.


Comparison with [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md)

## 🛠️ Related exercises

* [Uebung_002a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_035a2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_160_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Uebung_160b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Conclusion
The AX_OR_2 function block offers a reliable A simple solution for Boolean OR operations in automation systems. Its adapter-based architecture allows for flexible use in various control contexts.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]