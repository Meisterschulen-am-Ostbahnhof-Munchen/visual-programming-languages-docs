# ILOCK_FB_RS

![ILOCK_FB_RS](./ILOCK_FB_RS.svg)

* * * * * * * * * *
## Introduction

The function block `ILOCK_FB_RS` implements a bistable reset-dominant RS latch (reset-dominant flip-flop). It extends a simple RS flip-flop with a bidirectional coupling interface, enabling multiple such blocks to be chained together in an interlock chain. The output state is set by the Set input (S) and reset by the Reset input (R1) – also taking into account signals from adjacent blocks.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| `REQ` | Normal execution request (linked to data S and R1) |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| `CNF` | Execution Acknowledgement (linked to data output Q1) |

### **Data Inputs**

| Variable | Type | Comment |
|----------|--------|-----------|
| `S` | BOOL | Set (active high) |
| `R1` | BOOL | Reset (active high) – Reset-dominant |

### **Data Outputs**

| Variable | Type | Comment |
| |----------|--------|-----------|
| `Q1` | BOOL | Flip-flop output |

### **Adapter**

| Name | Direction | Type | Description |
|-------------|----------|---------------------|--------------|
| `ILOCK_IN` | Socket | bidirectional::AX2 | Receives signals from the previous component in the chain (event EO1, data DO1) |
| `ILOCK_OUT` | Plug | bidirectional::AX2 | Sends signals to the next component in the chain (event EI1, data DI1) |

The adapters of type `AX2` each provide two logic channels:

- Event channel: `EI1` (input) / `EO1` (output)
- Data channel: `DI1` (input) / `DO1` (output)

## Functionality

Internally, the component consists of an RS flip-flop (`FB_RS`, reset-dominant), two OR gates, and a 3-OR gate. The logic links the external inputs to the adapter signals:

- **Set:** The input `S` goes directly to the set input of the internal flip-flop. With `S` active and the reset input inactive, `Q1 = TRUE` is used.
- **Reset:** The reset input `R1` is connected to the data outputs of the two adapters (`ILOCK_IN.DO1` and `ILOCK_OUT.DI1`) via a 3-factor OR gate. The result controls the reset input of the internal flip-flop. As soon as **one** of these three sources becomes active, the output `Q1` is reset (reset dominance).

**Reset dominance:** - **Coupling:** The internal reset (`R1`) is additionally routed to the adapter outputs via OR gates:

- At `ILOCK_OUT.DO1`, `R1` is ORed with the received signal from `ILOCK_IN.DO1` (OR_2_BOOL_OUT), so that a reset is passed on.
- At `ILOCK_IN.DI1`, `R1` is ORed with the received signal from `ILOCK_OUT.DI1` (OR_2_BOOL_IN), so that a reset from the other side is also passed on.
- **Event Control:** All events (REQ, as well as the adapter events) are collected and forwarded to the internal flip-flop via OR logic. The acknowledgment (CNF) is output after the flip-flop has processed.

## Technical Features

- **Reset Dominance:** In case of conflict (S and R1 active simultaneously), the reset takes precedence → `Q1 = FALSE`.
- **Cascading:** Multiple `ILOCK_FB_RS` units can be cascaded using the adapters. A reset occurring at one point propagates through the chain.
- **Bidirectional Coupling:** The adapters enable both forward and reverse communication, allowing the device to receive and forward set and reset signals from both sides.
- **Compatibility:** Implemented according to IEC 61499-1 and utilizes subapplications from the `iec61131` library.

## State Overview

The internal RS flip-flop has the following state table (reset-dominant):

| S | R1_eff | Q1 (new) | Description |
|---|---|----------|--------------|
| 0 | 0 | Q1_old | Hold |
| 1 | 0 | 1 | Set |
| 0 | 1 | 0 | Reset |
| 1 | 1 | 0 | Reset dominant |

The output `R1_eff` is the result of the OR operation on `R1`, `ILOCK_IN.DO1`, and `ILOCK_OUT.DI1`. The output `Q1` is only set if none of these three reset sources are active.

## Application Scenarios

- **Interlock Chains** in safety controllers: Several components are chained together. A fault or reset at one point resets all subsequent outputs.
- **Priority Logic:** Reset-dominant latch structures where a specific event (e.g., emergency stop) takes precedence over set signals.
- **Signal Interlocking** in redundant systems where multiple conditions for setting and resetting must be combined.

## Comparison with Similar Components

| Component | Properties |
|----------|---------------|
| `FB_RS` (IEC 61131) | Simple reset-dominant RS flip-flop without adapter, no cascading |
| `ILOCK_FB_RS` | Same core function, but with bidirectional adapters for cascading and additional reset signal linking |

The `ILOCK_FB_RS` thus adds the ability to operate multiple such flip-flops in a chain, with a reset signal being passed from one link to the others.

## Conclusion

The `ILOCK_FB_RS` is a versatile component for implementing reset-dominant interlock logic. Its integrated bidirectional coupling makes it particularly suitable for modular, expandable safety and interlock circuits, eliminating the need for additional external logic.
