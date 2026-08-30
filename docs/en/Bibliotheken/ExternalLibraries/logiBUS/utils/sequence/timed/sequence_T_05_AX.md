# sequence_T_05_AX

![sequence_T_05_AX_ecc](./sequence_T_05_AX_ecc.svg)

* * * * * * * * * *
## Introduction

sequence_T_05_AX` is a variant of `sequence_T_05` that additionally uses adapters (`AX`) for the outputs. It controls a purely time-based sequence with 5 output states.
![sequence_T_05_AX](sequence_T_05_AX.svg)
## Interface Structure

### **Event Inputs**

- **START_S1**: Starts the sequence at State_01.
- **RESET**: Resets the sequence.

### **Event Outputs**

- **CNF**: Confirms execution.

### **Data Inputs**

- **DT_S1_S2**: Transition time for State_01 -> State_02.
- **DT_S2_S3**: Transition time for State_02 -> State_03.
- **DT_S3_S4**: Transition time for State_03 -> State_04.
- **DT_S4_S5**: Transition time for State_04 -> State_05.
- **DT_S5_START**: Transition time for State_05 -> START.

### **Data Outputs**

- **STATE_NR** (SINT): Current state number.

### **Adapters**

- **DO_S1** (adapter::types::unidirectional::AX): Output adapter for State_01.
- **DO_S2** (adapter::types::unidirectional::AX): Output adapter for State_02.
- **DO_S3** (adapter::types::unidirectional::AX): Output adapter for State_03.
- **DO_S4** (adapter::types::unidirectional::AX): Output adapter for State_04.
- **DO_S5** (adapter::types::unidirectional::AX): Output adapter for State_05.
- **timeOut** (iec61499::events::ATimeOut): Timer adapter.

## Functionality

Corresponds to `sequence_T_05`, but uses adapters for the outputs.

## Technical Features

- Uses `adapter::types::unidirectional::AX`.

## State Overview

See `sequence_T_05`.

## Application Scenarios

For time-controlled 5-step sequences with adapter connection.

## ⚖️ Comparison with similar components

- **sequence_T_05**: Standard version without adapter.

## Conclusion

Adapter version of the 5-step time sequencer.
