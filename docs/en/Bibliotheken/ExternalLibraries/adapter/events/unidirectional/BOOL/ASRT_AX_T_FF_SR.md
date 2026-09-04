# ASRT_AX_T_FF_SR

![ASRT_AX_T_FF_SR](ASRT_AX_T_FF_SR.svg)

* * * * * * * * * *

## Introduction

The ASRT_AX_T_FF_SR is an event-driven bistable function block with toggle functionality – the direct counterpart of [AX_T_FF_SR](AX_T_FF_SR.md), where the three event inputs S/R/CLK are combined into a single unidirectional **ASRT socket** (Set/Reset/Toggle) instead of being routed as three separate event inputs.

## Interface Structure

### **Event Inputs**

- No direct event inputs available – Set/Reset/Toggle arrive bundled via the adapter socket `S_R_T`

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- No data inputs available

### **Data Outputs**

- No direct data outputs available

### **Adapters**

- **S_R_T**: Unidirectional adapter socket of type `adapter::types::unidirectional::ASRT` (Set/Reset/Toggle)
- **Q**: Unidirectional adapter plug of type `adapter::types::unidirectional::AX` that provides the flip-flop value

## Operation

The ASRT_AX_T_FF_SR has three operating states:

- **START**: Initial state
- **SET**: Output Q is TRUE
- **RESET**: Output Q is FALSE

The state transitions are controlled by the adapter events arriving at socket `S_R_T`:

- `S_R_T.SET` transitions from any state to the SET state
- `S_R_T.RESET` transitions from any state to the RESET state
- `S_R_T.TOGGLE` toggles the current state (SET → RESET or RESET → SET, and from START to SET)

With each state change, the corresponding algorithm is executed, setting the adapter value `Q.D1` accordingly (`TRUE` in the SET state, `FALSE` in the RESET state).

## Technical Features

- Combines SR flip-flop and T flip-flop functionality like [AX_T_FF_SR](AX_T_FF_SR.md), but with a bundled adapter interface instead of three separate event inputs
- Uses the unidirectional ASRT adapter interface for Set/Reset/Toggle and the AX adapter interface for data output
- Initial state is START, from which a transition to SET can occur directly or via TOGGLE

## State Overview

```
START (initial state)
    │
    ├── S_R_T.SET ────→ SET (Q.D1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (Q.D1 = TRUE)

SET (Q.D1 = TRUE)
    │
    ├── S_R_T.RESET ──→ RESET (Q.D1 = FALSE)
    │
    └── S_R_T.TOGGLE ─→ RESET (Q.D1 = FALSE)

RESET (Q.D1 = FALSE)
    │
    ├── S_R_T.SET ────→ SET (Q.D1 = TRUE)
    │
    └── S_R_T.TOGGLE ─→ SET (Q.D1 = TRUE)
```

## Application Scenarios

- State storage in control applications where Set/Reset/Toggle are already bundled via an ASRT adapter (e.g. from [ASRT_CLIENT_0](../../../net/ASRT_CLIENT_0.md) or [ASRT_3EVENTS_TO_SRT](../../../conversion/unidirectional/EVENT/ASRT_3EVENTS_TO_SRT.md))
- Clock and frequency division
- State machines with memory function in fully adapter-based applications

## ⚖️ Comparison with similar components

Compared to [AX_T_FF_SR](AX_T_FF_SR.md), the ASRT_AX_T_FF_SR offers the same functionality, but with a single ASRT adapter socket instead of three separate event inputs (S/R/CLK) – allowing it to be connected directly to an ASRT-providing block without wiring the events individually.

## Conclusion

The ASRT_AX_T_FF_SR is the adapter-based variant of the proven SR/T flip-flop pattern from [AX_T_FF_SR](AX_T_FF_SR.md). By bundling Set/Reset/Toggle into a single ASRT socket, it is particularly suited to fully adapter-based control architectures.
