# E_SPLIT_3

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
The `E_SPLIT_3` is a basic function block according to IEC 61499 that splits a single input event (`EI`) into a sequence of three output events (`EO1`, `EO2`, `EO3`).
![E_SPLIT_3](E_SPLIT_3.svg)

- **EI**: The input event that triggers the sequence.
- **EO1**: The first output event of the sequence.
- **EO3**: The third output event of the sequence.

### Event Outputs

### **Ereignis-Eingang**

## Interface Structure

## Introduction

## Functionality

When an event arrives at input `EI`, the function block immediately triggers the three output events in succession. The order is guaranteed:

1. First, `EO1` is triggered.
2. Immediately afterward, `EO2` is triggered.
3. Immediately afterward, `EO3` is triggered.
- **1-to-3 Sequence**: Splits an event into a guaranteed sequence of three events.
- **Stateless**: The function block has no internal memory beyond a single transaction.
- **Generic Building Block**: The functionality is provided by the generic class `GEN_E_SPLIT`.
- **Initialization Sequence**: A `INIT` event can be used to initialize three different system components sequentially (`EO1`, `EO2`, `EO3`).
- **Sequence Control**: Triggering three consecutive actions with a single trigger event (e.g., "Close gripper," "Raise arm," "Rotate arm").
* [Exercise_004a9](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a9.md)
* [Exercise_004a9_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a9_AX.md)

The `E_SPLIT_3` block is a useful tool for generating a fixed, short event sequence of three steps from a single trigger. Its simplicity and guaranteed execution order make it a robust component for sequence control in IEC 61499 applications.
## Technical Features

## Application Scenarios

## 🛠️ Zugehörige Übungen

## Conclusion