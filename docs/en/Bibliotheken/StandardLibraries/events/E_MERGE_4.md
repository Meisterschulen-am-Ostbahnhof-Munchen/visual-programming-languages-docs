# E_MERGE_4

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *

## Introduction

The `E_MERGE_4` is a fundamental function block of the IEC 61499 standard that combines four event streams (`EI1` to `EI4`) into a single output (`EO`). This logical OR operation of events is essential for control logic in industrial automation systems.
![E_MERGE_4](E_MERGE_4.svg)

## Interface Structure

### **Event Inputs:**

- `EI1` (Event Input 1): First Event Input
- `EI2` (Event Input 2): Second Event Input
- `EI3` (Event Input 3): Third Event Input
- `EI4` (Event Input 4): Fourth Event Input

### **Event Outputs:**

- `EO` (Event Output): Combined Event Output

## Functionality

The function is simple and direct:

- An event at one of the four inputs (`EI1` to `EI4`) immediately triggers an event at the output without prioritization. `EO`.

The inputs are logically ORed and forwarded without delay.

## Technical Features

- **4-to-1 Linking**: Combines four event streams into one.
- **Stateless**: The block has no internal memory.
- **Generic Block**: The functionality is provided by the generic class `GEN_E_MERGE`, enabling optimized execution by the 4diac runtime environment.

## Application Scenarios

- **Collective Fault Message**: Combines four different fault events into a single alarm message.
- **Operation**: A process step can be triggered by four different buttons or sources.
- **Sensor Array**: A single "object detected" event is triggered when one of four sensors detects an object.

## Conclusion

The `E_MERGE_4` is a simple yet useful building block for linking up to four event sources. Its clear functionality and efficient implementation as a generic building block make it a reliable component for basic control logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
