# AX_BLINK
* * * * * * * * * *
## Introduction
The AX_BLINK is a function block that outputs a flashing signal via an AX adapter.
![AX_BLINK](AX_BLINK.svg)
## Interface Structure
### **Data Inputs**
- **DT** (TIME): Flashing period.

### **Adapters**
**Plugs (Outputs):**

- **OUT** (adapter::types::unidirectional::AX)

## Functionality
The function block switches the output OUT on and off alternately with the period DT.

## Technical Features
- Uses unidirectional adapters.

## State Overview
State-based (flashing).

## Application Scenarios
Flashing displays.

## ⚖️ Comparison with Similar Function Blocks
- **E_BLINK**: Standard flashing function block.

## 🛠️ Related Exercises
* [Exercise_020f3_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f3_AX.md)

## Conclusion
Adapter-based blink module.