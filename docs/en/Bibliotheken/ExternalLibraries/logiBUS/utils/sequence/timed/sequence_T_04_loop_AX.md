# sequence_T_04_loop_AX

![sequence_T_04_loop_AX_ecc](./sequence_T_04_loop_AX_ecc.svg)

* * * * * * * * * *
## Introduction
`sequence_T_04_loop_AX` is a variant of `sequence_T_04_loop` that additionally uses adapters (`AX`) for the outputs. It controls a purely time-controlled, cyclic sequence with 4 output states.

![sequence_T_04_loop_AX](sequence_T_04_loop_AX.svg)

## Interface Structure

### **Event Inputs**
* **START_S1**: Starts the sequence at State_01.

* **RESET**: Resets the sequence.

### **Event Outputs**

* **CNF**: Confirmation of execution.


### **Data Inputs**
* **DT_S1_S2**: Transition time State_01 -> State_02.

* **DT_S2_S3**: Transition time State_02 -> State_03.

* **DT_S3_S4**: Transition time State_03 -> State_04.

* **DT_S4_S1**: Transition time State_04 -> State_01.

### **Data Outputs**
* **STATE_NR** (SINT): Current state number.

### **Adapters**
* **DO_S1** (adapter::types::unidirectional::AX): Output adapter for State_01.

* **DO_S2** (adapter::types::unidirectional::AX): Output adapter for State_02.

* **DO_S3** (adapter::types::unidirectional::AX): Output adapter for State_03.

* **DO_S4** (adapter::types::unidirectional::AX): Output adapter for State_04.

* **timeOut** (iec61499::events::ATimeOut): Timer adapter.

## Functionality
Corresponds to `sequence_T_04_loop`, but uses adapters for the outputs.

## Technical Features
* Uses `adapter::types::unidirectional::AX`.

## State Overview
See `sequence_T_04_loop`.

## Application Scenarios
For time-controlled, cyclic 4-step sequences with adapter connection.

## ⚖️ Comparison with Similar Blocks
* **sequence_T_04_loop**: Standard version without adapter.

## Conclusion
Adapter version of the 4-step loop time sequencer.