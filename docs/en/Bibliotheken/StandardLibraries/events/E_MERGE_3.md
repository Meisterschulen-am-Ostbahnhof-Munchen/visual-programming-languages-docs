# E_MERGE_3

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## Introduction
The `E_MERGE_3` is a fundamental function block of the IEC 61499 standard that combines three event streams (`EI1`, `EI2`, `EI3`) into a single output (`EO`). This logical OR operation of events is essential for control logic in industrial automation systems.


![E_MERGE_3](E_MERGE_3.svg)

## Interface Structure

### **Event Inputs:**

- `EI1` (Event Input 1): First event input
- `EI2` (Event Input 2): Second event input
- `EI3` (Event Input 3): Third event input

### **Event Outputs:**

- `EO` (Event Output): Combined event output

## Functionality
The function is simple and direct:

- An event at input `EI1`, `EI2`, or `EI3` immediately triggers an event at output `EO` without prioritization.

The inputs are logically ORed and forwarded without delay.

## Technical Features
- **3-to-1 Linking**: Combines three event streams into one.

- **Stateless**: The function block has no internal memory.

- **Generic Function Block**: The functionality is provided by the generic class `GEN_E_MERGE`, enabling optimized execution by the 4diac runtime environment.

## Application Scenarios

- **Operating Concepts**: Combining control signals from three buttons into a common function (e.g., "Manual," "Automatic," and "Service" start the same process).

- **Sensors**: Combining the trigger events from three different sensors into a single event.

- **Fault Management**: Creating a collective fault message from three potential fault sources.


## 🛠️ Related Exercises

* [Exercise_004a2_3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_3.md)

## Conclusion
The `E_MERGE_3` is a simple yet useful building block for linking up to three event sources. Its clear functionality and efficient implementation as a generic building block make it a reliable component for basic control logic.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```