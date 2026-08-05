# sequence_E_08_loop_AX
![sequence_E_08_loop_AX_ecc](./sequence_E_08_loop_AX_ecc.svg)

* * * * * * * * * *
## Introduction
sequence_E_08_loop_AX` is a variant of `sequence_E_08_loop` that additionally uses adapters (`AX`) for the outputs. It controls a purely event-driven, cyclic sequence with 8 output states.
![sequence_E_08_loop_AX](sequence_E_08_loop_AX.svg)
## Interface Structure

### **Event Inputs**
* **START_S1**: Starts the sequence at State_01.
* **S1_S2** ... **S7_S8**: Manual transitions between states.
* **S8_S1**: Transition State_08 -> State_01 (Loop).
* **RESET**: Resets the sequence.

### **Event Outputs**
* **CNF**: Confirmation of execution.

### **Data Inputs**
* None.

### **Data Outputs**
* **STATE_NR** (SINT): Current state number.

### **Adapters**
* **DO_S1** ... **DO_S8** (adapter::types::unidirectional::AX): Output adapters for State_01 to State_08.

## Functionality
Corresponds to `sequence_E_08_loop`, but uses adapters for the outputs.

## Technical Features
* Uses `adapter::types::unidirectional::AX`.

## State Overview
See `sequence_E_08_loop`.

## Application Scenarios
For cyclic, event-driven 8-step sequences with adapter connectivity.

## ⚖️ Comparison with similar modules
* **sequence_E_08_loop**: Standard version without adapter.

## 🛠️ Related Exercises
* [Exercise_040_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_040_AX.md)]

## Conclusion
Adapter version of the 8-step loop event sequencer.
