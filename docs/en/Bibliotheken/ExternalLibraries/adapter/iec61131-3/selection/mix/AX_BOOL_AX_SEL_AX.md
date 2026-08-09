# AX_BOOL_AX_SEL_AX

![AX_BOOL_AX_SEL_AX](./AX_BOOL_AX_SEL_AX.svg)

*No image available*

* * * * * * * * * *
## Introduction

The function block `AX_BOOL_AX_SEL_AX` is used for binary selection between two Boolean signal sources. The special feature of this block is the seamless combination of classic IEC 61499 events/data and specialized unidirectional adapters of type `AX`. It allows a signal to be selected from either an adapter input (`IN0`) or a local data input (`IN1`) and forwarded to an adapter output (`OUT`). The control over which signal is passed through is handled by a selector adapter (`G`).

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acquisition and processing of the value at data input `IN1`.

### **Event Outputs**

* *No direct event outputs are available.* (Event output is coupled via the adapter output `OUT`).

### **Data Inputs**

* **IN1** (BOOL): Selectable input variable linked to event `EI1`.

### **Data Outputs**

* *No direct data outputs available.* (Data output is coupled via the adapter output `OUT`).

### **Adapters**

* **Sockets (Input Adapters)**:
* **IN0** (Type: `adapter::types::unidirectional::AX`): Adapter-based signal input that provides the first selectable value.
* **G** (Type: `adapter::types::unidirectional::AX`): The selector adapter. The state of this adapter determines which input is routed to the output.
* **Plugs (Output Adapters)**:
* **OUT** (Type: `adapter::types::unidirectional::AX`): The selected output to which the selected signal is routed.

---

## Functionality

The module is internally based on a network that utilizes the IEC 61131-3 standard selection module `F_SEL` and various flip-flops (`E_D_FF`, `E_D_FF_ANY`) for event and state synchronization.

The logic is as follows:

1. **State Detection**: As soon as a new event (`E1`) is received by the adapters `G` or `IN0`, the corresponding data value (`D1`) is temporarily stored via an internal flip-flop.
2. **Manual Triggering**: When a signal arrives at event input `EI1`, the current value of data input `IN1` is captured.
3. **Selection Logic (F_SEL)**:
* If the state of selector `G` is equal to **`FALSE`**, the signal from adapter **`IN0`** is passed to the output.
* If the state of selector `G` is equal to **`TRUE`**, the signal from input **`IN1`** is passed to the output.
* If the state of selector `G` is equal to **`TRUE`**, the signal from input **`IN1`** is passed to the output. 4. **Output**: Any change to the inputs triggers an update at the output adapter `OUT`. This triggers the event `OUT.E1` and passes the selected state to `OUT.D1`.

---

## Technical Features

* **Hybrid Approach**: This module bridges the gap between classic event- and data-based IEC 61499 programming (via `EI1`/`IN1`) and modern, adapter-based signal wiring.
* **Signal Stability**: The use of internal event D flip-flops (`E_D_FF` / `E_D_FF_ANY`) ensures that signal changes are only applied when corresponding events occur. This prevents uncontrolled signal states ("glitches") during asynchronous data changes.

---

## State Overview

The following truth table describes the behavior of the selection logic:

| State Selector (G) | Signal Source IN0 | Signal Source IN1 | Output (OUT) |
| :--- | :--- | :--- | :--- |
**FALSE** | Value A | Value B | **Value A** (from IN0) |
**TRUE** | Value A | Value B | **Value B** (from IN1) |

---

## Application Scenarios

* **Automatic/Manual Operation Switching**: A control signal is obtained automatically by default via the `IN0` adapter. When needed (e.g., for maintenance or manual intervention), the selector `G` switches, allowing a manual value to be specified via `IN1` (triggered by an HMI at `EI1`).
* **Dynamic Signal Source Selection**: In complex, modularized systems, sensor signals or enable conditions can be flexibly switched between a bus system (adapter) and a hardwired emergency level (direct input), depending on the operating mode.

---

## Comparison with Similar Components

* **`F_SEL` (Standard Selection Component)**: Operates purely data-flow-oriented according to IEC 61131-3. It does not offer direct event control and does not support adapter connections.
* **Classic Multiplexer**: Usually requires a large number of individual event and data lines. `AX_BOOL_AX_SEL_AX` significantly reduces this wiring effort in the 4diac system through the use of adapters.

---

## Conclusion

The `AX_BOOL_AX_SEL_AX` function block is an efficient tool for event-driven signal switching. By natively integrating unidirectional `AX` adapters, it significantly simplifies system design in the 4diac IDE network, while the internal synchronization mechanisms guarantee high reliability and data consistency.