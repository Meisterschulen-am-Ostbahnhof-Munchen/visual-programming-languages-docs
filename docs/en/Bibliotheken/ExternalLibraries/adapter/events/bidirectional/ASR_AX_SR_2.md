# ASR_AX_SR_2

![ASR_AX_SR_2](ASR_AX_SR_2.svg)

* * * * * * * * * *

## Introduction

The ASR_AX_SR_2 is an event-driven bistable flip-flop (Set/Reset) with a single bidirectional `ASR_AX` socket: the Set and Reset events arrive on the same adapter that also reports the new state back – unlike [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md), which uses a unidirectional ASR socket and a separate AX plug for the state.

## Interface Structure

### **Event Inputs**

*No direct event inputs available – Set/Reset arrive via the adapter socket `S_R`*

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

*No data inputs available*

### **Data Outputs**

*No data outputs available*

### **Adapters**

- **S_R**: Bidirectional adapter socket of type `adapter::types::bidirectional::ASR_AX` – Set/Reset (input), state (output) via the same adapter

## Operation

The ASR_AX_SR_2 has three operating states:

- **START**: Initial state
- **SET**: State TRUE
- **RESET**: State FALSE

The state transitions are controlled by the adapter events arriving at socket `S_R`:

- `S_R.SET` transitions from START or RESET to the SET state
- `S_R.RESET` transitions from the SET state to the RESET state

With each state change, the corresponding algorithm is executed, setting `S_R.DI1` (`TRUE` in the SET state, `FALSE` in the RESET state) and thereby reporting the state back over the same adapter via `S_R.EI1`.

## Technical Features

- Bidirectional communication over a single adapter socket instead of a separate ASR socket plus AX plug
- No toggle input – a pure Set/Reset flip-flop (unlike [ASRT_AX_T_FF_SR_2](ASRT_AX_T_FF_SR_2.md))
- A drop-in replacement for [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md) in fully adapter-based (ASR_AX) applications

## State Overview

```
START (initial state)
    │
    └── S_R.SET ───→ SET (S_R.DI1 = TRUE)

SET (S_R.DI1 = TRUE)
    │
    └── S_R.RESET ─→ RESET (S_R.DI1 = FALSE)

RESET (S_R.DI1 = FALSE)
    │
    └── S_R.SET ───→ SET (S_R.DI1 = TRUE)
```

## Application Scenarios

- State storage (Set/Reset) over a single bidirectional adapter connection, without wiring a separate state output
- Replacement for [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md) in networks that consistently use ASR_AX adapters

## ⚖️ Comparison with similar components

Compared to [ASR_AX_SR](../unidirectional/BOOL/ASR_AX_SR.md), which uses a unidirectional ASR socket and a separate AX plug for the state, ASR_AX_SR_2 bundles both directions into a single ASR_AX socket. [ASRT_AX_T_FF_SR_2](ASRT_AX_T_FF_SR_2.md) extends the same pattern with an additional toggle input.

## Conclusion

ASR_AX_SR_2 carries the proven Set/Reset flip-flop pattern over into the bidirectional adapter world: Set/Reset input and state feedback share the same ASR_AX socket, simplifying wiring in adapter-based networks.
