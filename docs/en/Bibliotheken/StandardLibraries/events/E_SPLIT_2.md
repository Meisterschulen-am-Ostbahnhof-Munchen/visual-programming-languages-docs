# E_SPLIT_2

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction

The `E_SPLIT_2` is a basic function block according to IEC 61499 that splits a single input event (`EI`) into a sequence of two output events (`EO1` and `EO2`). This block is functionally identical to `E_SPLIT`.
![E_SPLIT_2](E_SPLIT_2.svg)

## Interface Structure

### **Event Input**

- **EI**: The input event that triggers the sequence.

### **Event Outputs**

- **EO1**: The first output event of the sequence.
- **EO2**: The second output event of the sequence.

## Functionality

When an event arrives at input `EI`, the function block immediately triggers the two output events in succession. The sequence is guaranteed:

1. First, `EO1` is triggered.
2. Immediately afterward, `EO2` is triggered.

## Technical Features

- **1-to-2 Sequence**: Splits an event into a guaranteed sequence of two events.
- **Stateless**: The function block has no internal memory beyond a single transaction.
- **Generic Function Block**: The functionality is provided by the generic class `GEN_E_SPLIT`, enabling optimized execution by the 4diac runtime environment.

## Application Scenarios

- **Reset and Start**: A single `RESET` event can be used to first reset a value (`EO1`) and then restart a process (`EO2`).
- **Read and Process**: A `REQ` event can first read a sensor value (`EO1`) and then trigger a calculation using the new value (`EO2`).
- **Sequence Control**: Triggering two consecutive actions with a single trigger event.

## 🛠️ Related Exercises

* [Exercise_004a8](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a8.md)
* [Exercise_004a8_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a8_AX.md)

## Conclusion

The `E_SPLIT_2` block is a useful tool for generating a fixed, short event sequence from a single trigger. Its simplicity and guaranteed execution order make it a robust component for sequence control in IEC 61499 applications.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
