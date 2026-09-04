# AE_AX_T_FF

![AE_AX_T_FF](AE_AX_T_FF.svg)

* * * * * * * * * *

## Introduction

The AE_AX_T_FF is an event-driven toggle flip-flop with a single bidirectional `AE_AX` socket: the clock event arrives on the same adapter that also reports the new state back – unlike [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md), which uses a separate CLK event input and its own AX plug for the state.

## Interface Structure

### **Event Inputs**

*No direct event inputs available – the clock event arrives via the adapter socket `CLK`*

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

*No data inputs available*

### **Data Outputs**

*No data outputs available*

### **Adapters**

- **CLK**: Bidirectional adapter socket of type `adapter::types::bidirectional::AE_AX` – clock (input), state (output) via the same adapter

## Operation

The AE_AX_T_FF has two operating states:

- **START**: Initial state
- **SET**: State after toggling

Every event arriving at `CLK.E1` moves the function block from START to SET, firing the algorithm `TOGGLE`, which executes `CLK.DI1 := NOT CLK.DI1` and thereby reports the inverted state back over the same adapter via `CLK.EI1`. From the SET state the block unconditionally (condition `1`) returns immediately to START, so that every further `CLK.E1` event triggers the same TOGGLE transition again.

## Technical Features

- Bidirectional communication over a single adapter socket instead of a separate event input plus AX plug
- The ECC state SET is only a pass-through state for firing the output event; the actual toggle semantics live in the algorithm assignment `CLK.DI1 := NOT CLK.DI1`
- A drop-in replacement for [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md) in fully adapter-based (AE_AX) applications

## State Overview

```
START (initial state)
    │
    └── CLK.E1 ─→ SET (CLK.DI1 := NOT CLK.DI1, reports state via CLK.EI1)
                       │
                       └── (unconditional) ─→ START
```

## Application Scenarios

- Toggling a state (e.g. on/off) over a single bidirectional adapter connection, without wiring a separate state output
- Replacement for [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md) in networks that consistently use AE_AX adapters

## ⚖️ Comparison with similar components

Compared to [AX_T_FF](../unidirectional/BOOL/AX_T_FF.md), which uses a separate `CLK` event input and its own AX plug for the state, AE_AX_T_FF bundles both directions into a single AE_AX socket.

## Conclusion

AE_AX_T_FF carries the proven toggle flip-flop pattern over into the bidirectional adapter world: clock input and state feedback share the same AE_AX socket, simplifying wiring in adapter-based networks.
