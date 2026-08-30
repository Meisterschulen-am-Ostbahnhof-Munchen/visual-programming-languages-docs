# ILOCK_FB_SR_AX

![ILOCK_FB_SR_AX](./ILOCK_FB_SR_AX.svg)

* * * * * * * * * *

## Introduction

The function block **ILOCK_FB_SR_AX** implements a set-dominant (set-priority) bistable flip-flop (RS latch) with interlock functionality. It is designed for use in safety and interlocking chains where a set signal can be propagated and fed back through multiple stages. The interface consists of two unidirectional AX adapters (SET1, RESET) and one AX2 bidirectional adapter pair (ILOCK_IN / ILOCK_OUT), as well as an output adapter Q1. The block operates in an event-driven manner and recalculates the output values with each incoming event.

## Interface Structure

### **Event Inputs**

| Event | Data Source | Description |
| ---------- | --------------- | -------------- |
| `SET1.E1` | Socket SET1 | Sets output Q1 (set-dominant) |
| `RESET.E1` | Socket RESET | Resets output Q1 (only effective if SET1 = 0) |
| `ILOCK_IN.EO1` | Socket ILOCK_IN | Receives the propagation event from the parent interlock stage |
| `ILOCK_OUT.EI1` | Plug ILOCK_OUT | Receives an event from the child interlock stage (e.g., acknowledgment) |

### **Event Outputs**

| Event | Data Source | Description |
| ---------- | --------------- | -------------- |
| `Q1.E1` | Plug Q1 | Output event after each Q1 update |
| `ILOCK_IN.EI1` | Socket ILOCK_IN | Sends propagation event to the parent stage |
| `ILOCK_OUT.EO1` | Plug ILOCK_OUT | Sends propagation event to the child stage |

### **Data Inputs**

| Data | Type | Description |
| ------- | ----- | --------------- |
| `SET1.D1` | BOOL | Set input (dominant) |
| `RESET.D1` | BOOL | Reset input (active when SET1=0) |
| ILOCK_IN.DO1` | BOOL | Data from the parent interlock stage (propagation signal) |
| ILOCK_OUT.DI1` | BOOL | Data from the child interlock stage (feedback) |

### **Data Outputs**

| Data | Type | Description |
| ------- | ----- | -------------- |
| Q1.D1` | BOOL | Latch output (set by Set or Interlock) |
| ILOCK_IN.DI1` | BOOL | Propagated Set signal to the parent stage |
| `ILOCK_OUT.DO1` | BOOL | Propagated Set signal to the subordinate stage |

### **Adapter**

| Adapter | Type | Direction | Description |
| --------- | ----- | ---------- | -------------- |
| `Q1` | AX (unidirectional) | Plug | Latch output |
| `ILOCK_OUT` | AX2 (bidirectional) | Plug | Interlock interface to the subordinate stage |
| `SET1` | AX (unidirectional) | Socket | Set input |
| ax (unidirectional) | Socket | Reset input |
| `ILOCK_IN` | AX2 (bidirectional) | Socket | Interlock interface to the higher-level interface |

## Functionality

The function block implements an algorithm that performs the following calculations on each incoming event:

1. **Q1.D1 (Latch Output):**

Q1.D1 := SET1.D1 OR ILOCK_IN.DO1 OR ILOCK_OUT.DI1 OR ((NOT RESET.D1) AND Q1.D1)`

- The output is set if **SET1.D1**, **ILOCK_IN.DO1** (from above), or **ILOCK_OUT.DI1** (from below) has the value `TRUE`.
- If no set signal is active and **RESET.D1 = FALSE**, the current value of Q1 is retained (memory behavior).
- Set is dominant: An active set overrides a reset.
1. **ILOCK_IN.DI1 (Propagation Upwards):**

ILOCK_IN.DI1 := SET1.D1 OR ILOCK_OUT.DI1`

- The set signal is propagated upwards when either its own set input or the signal of the lower stage is active.
1. **ILOCK_OUT.DO1 (Propagation Downwards):**

ILOCK_OUT.DO1 := SET1.D1 OR ILOCK_IN.DO1`

- The set signal is propagated downwards when either its own set input or the signal of the upper stage is active.

After each calculation, the event outputs `Q1.E1`, `ILOCK_IN.EI1`, and `ILOCK_OUT.EO1` are activated.

## Technical Features

- **Interlock Cascade:** The function block can be used in a chain of multiple identical blocks. The AX2 adapter (ILOCK) propagates a set signal both upwards and downwards. This enables mutual interlocking across multiple stages.
- **Bidirectional Communication:** The AX2 adapter allows both sending and receiving events and data in both directions, enabling feedback from subordinate stages.
- **Set Dominance:** An active set input immediately sets the output and blocks a reset. This function block is therefore an **SR flip-flop with set signal priority**.
- **Pure Event Control:** The function block has no cyclical execution; every change is triggered only by a corresponding event.

## State Overview

The function block has a single internal state, **REQ**, in which it always resides. The algorithm is executed upon each incoming event (SET1.E1, RESET.E1, ILOCK_IN.EO1, ILOCK_OUT.EI1), and then the system returns to the REQ state. There are no other states; the function block (FB) is essentially stateless (combinatorically with memory via feedback from Q1.D1).

## Application Scenarios

- **Safety Interlock in Agricultural Engineering:** Cascading multiple ILOCK_FB_SR_AX functions to create a continuous interlock chain (e.g., for machine axes). A set signal from any point blocks all subsequent stages.
- **Production Systems with Release Chains:** Setting and resetting release signals in a hierarchical control system, where higher stages override lower ones.
- **Redundant Control Systems:** Utilizing the interlock function for mutual monitoring and interlocking of multiple control channels.

## Comparison with Similar Function Blocks

- **Standard RS Flip-Flop (SR):** A simple SR function block has no interlock mechanism and no bidirectional data propagation. It can only be set or reset locally.
- **ILOCK_FB_SR_AX** extends the classic RS flip-flop with cascading capability via the AX2 interfaces. The dominance of the set signal and the bidirectional propagation make it particularly suitable for safety chains.
- **Monostable Function Blocks:** Unlike monostable functions, this function block retains its state until the next reset or set (bistable).

## Conclusion

The ILOCK_FB_SR_AX is a specialized function block for building interlock chains with a set-dominant latch function. By combining unidirectional set/reset inputs and bidirectional interlock adapters, it is ideally suited for safety-related applications requiring cascading and mutual interlocking of multiple stages. Its simple, event-driven logic enables efficient and deterministic processing in automation technology.
