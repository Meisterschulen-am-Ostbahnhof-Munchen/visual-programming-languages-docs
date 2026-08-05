# ILOCK_FB_SR
![ILOCK_FB_SR](./ILOCK_FB_SR.svg)

* * * * * * * * * *
## Introduction
The ILOCK_FB_SR function block implements a bistable set-dominant SR latch, specifically designed for use in interlock circuits. It extends a simple SR latch with bidirectional adapters for coupling with other function blocks, enabling the implementation of complex interconnections and priority logic.
## Interface Structure

### **Event Inputs**

| Event | Description | Accompanying Data |
|----------|---------------|-------------------|
| `REQ` | Execution Request for Processing the Set and Reset Signals | `S1`, `R` |

### **Event Outputs**

| Event | Description | Carrying Data |
|----------|--------------|-------------------|
| `CNF` | Execution Confirmation, outputs the current output value | `Q1` |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
| `S1` | `BOOL` | Set Input |
| `R` | `BOOL` | Reset Input |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|--------------|
| `Q1` | `BOOL` | Latch Output (set-dominant) |

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|-----------|--------------|
| `ILOCK_IN` | `adapter::types::bidirectional::AX2` | Socket | Receives data and events from an upstream interlock block |
| `ILOCK_OUT` | `adapter::types::bidirectional::AX2` | Plug | Sends data and events to a downstream interlock block |

The adapters enable bidirectional chaining of interlock blocks by allowing both the reception of enable/lock signals and the transmission of states.

## Functionality

The core of the block is an internal SR latch (`FB_SR`) that operates in a **set-dominant** manner: If both Set (`S1`) and Reset (`R`) are active simultaneously, the block sets the output `Q1` to `TRUE`.

The logic is supplemented by three OR gates:

- **OR_3_BOOL** combines the signals from the Set input (`S1`) with the feedback signals from the adjacent Interlock devices (`ILOCK_IN.DO1` and `ILOCK_OUT.DI1`). The result is fed to the Set input of the internal SR latch.
- **OR_2_BOOL_IN** combines the Set signal (`S1`) and the signal from the downstream Interlock device (`ILOCK_OUT.DI1`). The result is sent to the upstream device via the adapter `ILOCK_IN.DI1`.
- **OR_2_BOOL_IN** combines the Set signal (`S1`) and the signal from the downstream Interlock device (`ILOCK_OUT.DI1`). - **OR_2_BOOL_OUT** combines the set signal (`S1`) and the signal of the upstream interlock block (`ILOCK_IN.DO1`). The result is sent to the downstream block via the adapter `ILOCK_OUT.DO1`.

This structure allows multiple interlock blocks to be cascaded: A set signal can be blocked or forwarded by an upstream block. Simultaneously, the release of its own latch is reported to the adjacent blocks.

## Technical Features
- **Set-Dominant Behavior**: In case of conflict (S1=TRUE, R=TRUE), the set signal takes precedence.
- **Adapter-Based Coupling**: The bidirectional adapters `ILOCK_IN` and `ILOCK_OUT` allow for modular interconnection without the need to manually establish direct data or event connections between the components.
- **Feedback**: The internal logic processes both external set and reset signals as well as the states of adjacent components, creating a dynamic interlocking chain.

## State Overview

The internal SR latch has four states based on the (combined) inputs:

| S1 (after logic) | R | Q1 (previous) | Q1 (new) |
|-----------------|---|-----------------|------------|
| 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 0 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 |

The effective values for S1 (Set) result from the OR operation of `S1`, `ILOCK_IN.DO1`, and `ILOCK_OUT.DI1`.

## Application Scenarios
- **Safety Interlocks**: In systems where multiple conditions must be met simultaneously before a process is enabled (e.g., safety gates, emergency stop).
- **Cascaded Controls**: Superior and subordinate interlock units that interact via adapters (e.g., in production lines).
- **Priority-Based Sets**: Used in systems where a set signal must take precedence over a reset signal to enforce safety-critical states.

## Comparison with Similar Devices
- **IEC 61131 SR (reset-dominant)**: Standard SR latch where the reset signal takes precedence in case of a conflict. The ILOCK_FB_SR reverses this priority.
- **IEC 61131 RS (set-dominant)**: Similar behavior at its core, but without the adapter-based interconnection and the logic for chaining multiple devices.
- **D Flip-Flop**: Clocked memory cell that only takes over on a rising edge – this is an asynchronous, clock-independent latch.

The ILOCK_FB_SR is specifically optimized for interlock chains, while simple SR latches operate in isolation.

## Conclusion

The ILOCK_FB_SR offers a flexible and robust solution for set-dominant interlock circuits. By combining an SR latch with bidirectional adapters and OR logic, arbitrarily complex interconnections can be built without the need for extensive wiring of signals between the components. The set-dominant behavior is particularly advantageous in safety-critical applications where a set signal must take precedence.
