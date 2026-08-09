# AX_T_FF

<img width="1181" height="187" alt="image" src="https://github.com/user-attachments/assets/fe3f05c1-c201-42ef-a5d8-874b826680de" />
![AX_T_FF_ecc](./AX_T_FF_ecc.svg)

* * * * * * * * * *
## Introduction

The AX_T_FF (Toggle Flip-Flop) is a fundamental memory component in 4diac that functions as a toggle flip-flop. With each clock event, the output value toggles between its two possible states. The component implements a simple switching behavior where the output value is toggled on each clock pulse.

![AX_T_FF](AX_T_FF.svg)

## Interface Structure

### **Event Inputs**

- **CLK**: Clock input that triggers an output toggle

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- No data inputs available

### **Data Outputs**

- No direct data outputs available

### **Adapters**

- **Q**: Unidirectional adapter of type AX that provides the current flip-flop value

## Functionality

The AX_T_FF operates as a simple toggle flip-flop. Upon each incoming CLK event, the TOGGLE algorithm is executed, which inverts the current value of adapter Q.D1. The device starts in the START state and transitions to the SET state upon each CLK event, where the toggle is performed.

## Technical Features

- Uses a unidirectional adapter for output
- Implemented as a Basic Function Block (BFB)
- Features a simple two-state machine
- The TOGGLE algorithm performs a logical negation of the output value

## State Overview

The block has two states:

1. **START**: Initial state, waits for a CLK event
2. **SET**: Active state in which the TOGGLE algorithm is executed

State Transitions:

- START → SET: On a CLK event
- SET → START: Always (Condition "1" = true)

## Application Scenarios

- Frequency division of clock signals
- Generation of square waves with half the input frequency
- Counter and divider circuits
- State control with alternating behavior

## ⚖️ Comparison with Similar Blocks

Compared to other flip-flop types such as RS or D flip-flops, the A toggle flip-flop is a specialized functionality for simple switching operations. It has a simpler structure than more general-purpose flip-flop types and requires no additional data inputs.

Comparison with [E_T_FF](../../../../../StandardLibraries/events/E_T_FF.md)

## 🛠️ Related exercises

* [Uebung_004a2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a2_AX.md)
* [Uebung_004a3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a3_AX.md)
* [Uebung_004a4_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a4_AX.md)
* [Uebung_004a5_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a5_AX.md)
* [Uebung_004a6_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a6_AX.md)
* [Uebung_004a8_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a8_AX.md)
* [Uebung_004a9_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a9_AX.md)
* [Uebung_004a_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a_AX.md)
* [Uebung_004c1_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c1_AX.md)
* [Uebung_004c2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c2_AX.md)
* [Uebung_004c3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c3_AX.md)
* [Uebung_004c4_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c4_AX.md)
* [Uebung_004c5_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c5_AX.md)
* [Uebung_004c6_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c6_AX.md)
* [Uebung_004c7_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c7_AX.md)
* [Uebung_005_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_005_AX.md)
* [Uebung_006a3_sub_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_sub_AX.md)
* [Uebung_007_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007_AX.md)
* [Uebung_007a1_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a1_AX.md)
* [Uebung_007a2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a2_AX.md)
* [Uebung_010b2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b2_AX.md)
* [Uebung_010b3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b3_AX.md)
* [Uebung_010b6_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b6_AX.md)
* [Uebung_010b7_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b7_AX.md)
* [Uebung_010b8_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b8_AX.md)
* [Uebung_010b9_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b9_AX.md)
* [Uebung_010bA2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA2_AX.md)
* [Uebung_010bA3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA3_AX.md)
* [Uebung_010bA4_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA4_AX.md)
* [Uebung_010bA_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA_AX.md)
* [Uebung_035a2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Exercise_094a_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Exercise_095_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_095_AX.md)
* [Exercise_150_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_150_AX.md)
* [Exercise_151_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)

## Conclusion

The AX_T_FF is a specialized and efficient component for applications requiring pure toggle behavior. Its simple structure and clear functionality make it a reliable component for frequency division and state switching in control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
