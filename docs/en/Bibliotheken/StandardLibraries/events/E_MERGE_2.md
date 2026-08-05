# E_MERGE_2

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## Introduction
The `E_MERGE_2` is a fundamental function block according to the IEC 61499 standard. It combines two event streams (`EI1`, `EI2`) into a single output (`EO`). This logical OR operation of events is essential for control logic in industrial automation systems. This block is functionally identical to the `E_MERGE` block.


![E_MERGE_2](E_MERGE_2.svg)

## Interface Structure

### **Event Inputs:**

- `EI1` (Event Input 1): First event input
- `EI2` (Event Input 2): Second event input

### **Event Outputs:**

- `EO` (Event Output): Combined event output

## Functionality
The function is simple and direct:

- An event at input `EI1` immediately triggers an event at output `EO`.

- An event at input `EI2` also immediately triggers an event at output `EO`.


The inputs are logically ORed and forwarded without prioritization or delay.

## Technical Features
- **2-to-1 Linking**: Combines two event streams into one.

- **Stateless**: The function block has no internal memory.

- **Generic Function Block**: The functionality is provided by the generic class `GEN_E_MERGE`, enabling optimized execution by the 4diac runtime environment.

## Application Scenarios

- **Operating Concepts**: Combining control signals from two pushbuttons into a single function.

- **Sensors**: Combining trigger events from two different sensors.

- **Fault Management**: Creating a collective fault message from two potential fault sources.


## 🛠️ Related Exercises

* [Exercise_004a2_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_2.md)

## Conclusion
The `E_MERGE_2` is a fundamental and frequently used building block for the simplest form of event linking. Its clear functionality and efficient implementation as a generic building block make it a reliable component for basic control logic.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```