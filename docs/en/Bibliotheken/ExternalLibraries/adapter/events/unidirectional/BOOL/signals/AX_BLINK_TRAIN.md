# AX_BLINK_TRAIN
* * * * * * * * * *
## Introduction
The AX_BLINK_TRAIN is a function block that outputs a train flashing signal (alternating two lights) via an AX adapter.
![AX_BLINK_TRAIN](AX_BLINK_TRAIN.svg)
## Interface Structure
### **Data Inputs**
- **DT** (TIME): Flashing period.

### **Adapters**
**Plugs (Outputs):**
- **OUT1** (adapter::types::unidirectional::AX)
- **OUT2** (adapter::types::unidirectional::AX)

## Functionality
The function block switches outputs OUT1 and OUT2 on and off alternately with the period DT.

## Technical Features
- Uses unidirectional adapters.

## State Overview
State-based.

## Application Scenarios
Railway crossings, warning signals.

## ⚖️ Comparison with similar modules
- No direct standard equivalent.

## 🛠️ Related Exercises
* [Exercise_035a3_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)

## Conclusion
Adapter-based train flashing module.