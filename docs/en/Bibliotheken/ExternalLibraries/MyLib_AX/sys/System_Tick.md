# System_Tick

![System_Tick_network](./System_Tick_network.svg)

* * * * * * * * * *

## Introduction

`System_Tick` generates a continuous, cyclically incrementing DINT counter (200 ms tick, value range 0..99, wrapping via modulo) and exposes it through an `ADI` adapter (DINT) for other blocks to consume — a simple heartbeat counter.

## Function Blocks Used

### Sub-blocks: System_Tick

- **Type**: SubAppType
- **Internal FBs used**:
    - **INIT**: `iec61131::booleanOperators::INIT` — fires once at startup (`INITO` fed back to `REQ`) and starts the cycle timer.
    - **E_CYCLE**: `iec61499::events::E_CYCLE` — cyclic event, `DT=T#200ms`, started via `INIT.CNF`.
    - **ADD_2**: `iec61131::arithmetic::ADD_2` — adds `IN1=DINT#1` to the current counter value (`IN2`, fed back from `F_MOVE.OUT`).
    - **F_MOVE**: `iec61131::selection::F_MOVE` (`DataType=DINT`) — holds/passes the current counter value, acting as the feedback loop's intermediate storage.
    - **F_MOD**: `iec61131::arithmetic::F_MOD` — modulo operation with `IN2=DINT#100`, limiting the value range to 0..99.
    - **ADI_DINT_TO_DI**: `adapter::conversion::unidirectional::ADI_DINT_TO_DI` — converts the DINT value onto the `ADI_OUT` adapter for external use.
- **Operation**: `INIT` starts the `E_CYCLE` timer; each cycle increments the counter via `ADD_2`/`F_MOVE` by 1, `F_MOD` keeps it within 0..99, and `ADI_DINT_TO_DI` places the result onto the output adapter.

## Program Flow and Connections

1. `INIT.INITO` → `INIT.REQ` (self-trigger at startup); `INIT.CNF` → `E_CYCLE.START`.
2. `E_CYCLE.EO` → `ADD_2.REQ` (every 200 ms).
3. `F_MOVE.OUT` → `ADD_2.IN2` (feedback of the current value); `ADD_2.OUT` → `F_MOVE.IN`.
4. `ADD_2.CNF` → `F_MOVE.REQ` → `F_MOD.REQ` (event chain); `F_MOVE.OUT` → `F_MOD.IN1`.
5. `F_MOD.CNF` → `ADI_DINT_TO_DI.REQ`; `F_MOD.OUT` → `ADI_DINT_TO_DI.OUT`.
6. `ADI_DINT_TO_DI.ADI_OUT` (adapter) → `ADI_OUT` (SubApp interface).

## Technical Details

- The counter runs purely internally within the block (no external data inputs) — it is an autonomous clock that triggers itself via `INIT`.
- The modulo bound `DINT#100` yields a value range of 0..99, not 1..100 as one might assume at first glance — the value implicitly starts at 0 after `INIT`, and `ADD_2` counts up by 1 each cycle from there.

## Application Scenarios

- Heartbeat/liveness signal for diagnostic purposes, e.g. to show on the VT or via OPC-UA that the controller is actively cycling.
- Simple substitute for a one-second tick (5 cycles of 200 ms ≈ 1 s) for test purposes, without configuring a dedicated timer block.

## Summary

Autonomous, self-triggering 200 ms counter with modulo limiting, exposed via a DINT adapter — a simple heartbeat block.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
