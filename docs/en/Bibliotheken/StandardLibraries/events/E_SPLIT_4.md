# E_SPLIT_4

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## Introduction
The `E_SPLIT_4` is a basic function block according to IEC 61499 that splits a single input event (`EI`) into a sequence of four output events (`EO1` to `EO4`).

![E_SPLIT_4](E_SPLIT_4.svg)

## Interface Structure

### **Event Input**
- **EI**: The input event that triggers the sequence.

### **Event Outputs**
- **EO1**: The first output event of the sequence.

- **EO2**: The second output event of the sequence.

- **EO3**: The third output event of the sequence.

- **EO4**: The fourth output event of the sequence.

## Functionality
When an event arrives at input `EI`, the function block immediately triggers the four output events in succession. The order is guaranteed:

1. First, `EO1` is triggered.

2. Immediately afterward, `EO2` is triggered.

3. Immediately afterward, `EO3` is triggered.

4. Immediately afterward, `EO4` is triggered.

## Technical Features

- **1-to-4 Sequence**: Splits an event into a guaranteed sequence of four events.

- **Stateless**: The function block has no internal memory beyond a single transaction.

- **Generic Block**: The functionality is provided by the generic class `GEN_E_SPLIT`.

## Application Scenarios

- **Complex Initialization**: A `INIT` event can be used to initialize four different system components sequentially.

- **Sequence Control**: Triggering four consecutive actions with a single trigger event.

## Conclusion
The `E_SPLIT_4` block is a useful tool for generating a fixed, short event sequence of four steps from a single trigger. Its simplicity and guaranteed execution order make it a robust component for sequence control in IEC 61499 applications.