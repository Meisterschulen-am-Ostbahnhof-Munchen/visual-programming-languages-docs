# ASRT_AX_T_FF_SR_2

![ASRT_AX_T_FF_SR_2](ASRT_AX_T_FF_SR_2.svg)

* * * * * * * * * *

## Introduction

The ASRT_AX_T_FF_SR_2 is an event-driven bistable flip-flop with toggle functionality and a single bidirectional `ASRT_AX` socket: Set/Reset/Toggle arrive on the same adapter that also reports the new state back. It is thus the bidirectional counterpart of [ASRT_AX_T_FF_SR](../unidirectional/BOOL/ASRT_AX_T_FF_SR.md) (unidirectional ASRT socket + separate AX plug) and the Toggle-extended variant of [ASR_AX_SR_2](ASR_AX_SR_2.md).

## Interface Structure

### **Event Inputs**

*No direct event inputs available – Set/Reset/Toggle arrive via the adapter socket `S_R_T`*

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

*No data inputs available*

### **Data Outputs**

*No data outputs available*

### **Adapters**

- **S_R_T**: Bidirectional adapter socket of type `adapter::types::bidirectional::ASRT_AX` – Set/Reset/Toggle (input), state (output) via the same adapter

## Operation

The ASRT_AX_T_FF_SR_2 has three operating states:

- **START**: Initial state
- **SET**: State TRUE
- **RESET**: State FALSE

The state transitions are controlled by the adapter events arriving at socket `S_R_T`:

- `S_R_T.SET` transitions from any state to the SET state
- `S_R_T.RESET` transitions from any state to the RESET state
- `S_R_T.TOGGLE` toggles the current state (SET → RESET or RESET → SET, and from START to SET)

With each state change, the corresponding algorithm is executed, setting `S_R_T.DI1` (`TRUE` in the SET state, `FALSE` in the RESET state) and thereby reporting the state back over the same adapter via `S_R_T.EI1`.

## Technical Features

- Bidirectional communication over a single adapter socket instead of a separate ASRT socket plus AX plug
- Identical ECC structure to [ASRT_AX_T_FF_SR](../unidirectional/BOOL/ASRT_AX_T_FF_SR.md); the only difference is the adapter direction (bidirectional instead of unidirectional plus separate plug)
- A drop-in replacement for [ASRT_AX_T_FF_SR](../unidirectional/BOOL/ASRT_AX_T_FF_SR.md) in fully adapter-based (ASRT_AX) applications

## State Overview

```
START (initial state)
    │
    ├── S_R_T.SET ────→ SET (S_R_T.DI1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (S_R_T.DI1 = TRUE)

SET (S_R_T.DI1 = TRUE)
    │
    ├── S_R_T.RESET ──→ RESET (S_R_T.DI1 = FALSE)
    │
    └── S_R_T.TOGGLE ─→ RESET (S_R_T.DI1 = FALSE)

RESET (S_R_T.DI1 = FALSE)
    │
    ├── S_R_T.SET ────→ SET (S_R_T.DI1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (S_R_T.DI1 = TRUE)
```

## Application Scenarios

- State storage with Set/Reset/Toggle over a single bidirectional adapter connection, without wiring a separate state output
- Replacement for [ASRT_AX_T_FF_SR](../unidirectional/BOOL/ASRT_AX_T_FF_SR.md) in networks that consistently use ASRT_AX adapters

## ⚖️ Comparison with similar components

Compared to [ASRT_AX_T_FF_SR](../unidirectional/BOOL/ASRT_AX_T_FF_SR.md), which uses a unidirectional ASRT socket and a separate AX plug for the state, ASRT_AX_T_FF_SR_2 bundles both directions into a single ASRT_AX socket. [ASR_AX_SR_2](ASR_AX_SR_2.md) is the same family without the toggle input.

## Conclusion

ASRT_AX_T_FF_SR_2 carries the proven Set/Reset/Toggle flip-flop pattern over into the bidirectional adapter world: control input and state feedback share the same ASRT_AX socket, simplifying wiring in adapter-based networks.
