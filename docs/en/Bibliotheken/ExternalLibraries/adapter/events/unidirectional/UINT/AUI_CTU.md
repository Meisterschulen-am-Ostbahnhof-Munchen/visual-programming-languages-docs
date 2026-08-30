# AUI_CTU

![AUI_CTU](./AUI_CTU.svg)
*Image of function block not available*

* * * * * * * * * *
## Introduction

The AUI_CTU is an event-driven up counter with an adapter interface. It increments the counter on every positive edge event at input `CU` and outputs the count via adapter `CV`. The output `Q` indicates whether the counter value (`CV`) has reached or exceeded the set limit (`PV`). The special feature of this implementation is the "On-Change" triggering: The event on the adapter `Q.E1` is only triggered if the logical state of `Q` actually changes. This reduces unnecessary events in subsequent processing.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CU` | Event | Count Up |
| `R` | Event | Reset |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CUO` | Event | Output after successful increment |
| `RO` | Event | Output after successful reset |

### **Data Inputs**

Direct data inputs are not available. The limit value (`PV`) is provided via an adapter socket.

### **Data Outputs**

Direct data outputs are not available. The current counter value (`CV`) and the comparison status (`Q`) are output via adapter plugs.

### **Adapters**

| Type | Direction | Name | Description |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AX` | Plug (Output) | `Q` | Outputs `TRUE` if `CV >= PV`, otherwise `FALSE`. The event `Q.E1` is only sent on state changes. |
| `adapter::types::unidirectional::AUI` | Plug (Output) | `CV` | Returns the current counter value (unsigned integer). The event `CV.E1` is triggered after each increment or reset. |
| `adapter::types::unidirectional::AUI` | Socket (Input) | `PV` | Receives the threshold value of type `UINT`. Changing this value automatically recalculates `Q`. |

## Functionality

This function block implements a finite state machine (ECC) with the following algorithms:

- **`CU`**: Increments the internal counter `CV` by `1` and then calculates `Q := (CV >= PV)`.
- **`R`**: Sets `CV` to `0` and recalculates `Q`.
- **`UPDATE`**: Calculates `Q` from the current `CV` and the (modified) `PV`, without changing the counter.
- **`SAVE_Q`**: Stores the current value of `Q` in the internal variable `Q_OLD` for the next state change detection.

Process:

1. **Event `CU`** (and `CV < 65535`): Transition to state `CU`. The counter is incremented, `Q` is recalculated, and `CV.E1` and the event `CUO` are output.
- If `Q` has changed compared to the last stored value (`Q_OLD`), the state changes to `EMIT_Q`.
- Otherwise, the function block returns to state `START`.
2. **Event `R`**: Transition to state `R`. The counter is reset, `Q` is recalculated, and `CV.E1` and `RO` are output. Then, analogous to `CU`, a decision is made whether to reach `EMIT_Q` or return to `START`.
3. **Adapter event `PV.E1`** (limit change): Transition to state `UPDATE_PV`. The algorithm `UPDATE` recalculates `Q`. Here too, the state `EMIT_Q` is only traversed when `Q` changes.
4. **State `EMIT_Q`**: Executes the algorithm `SAVE_Q` (stores the new `Q` value in `Q_OLD`) and sends the event `Q.E1`. Afterward, the function block always returns to `START`.
4. **State `EMIT_Q`**: Executes the algorithm `SAVE_Q` (stores the new `Q` value in `Q_OLD`) and sends the event `Q.E1`.

The function block then always returns to `START`.
## Technical Features

- **On-Change Triggering for Adapter `Q`**: The event `Q.E1` is only triggered when the logical value of `Q` (true/false) changes. This is achieved through the internal status variable `Q_OLD`. This prevents unnecessary event flooding in the application.
- **Automatic Response to Threshold Change**: If the threshold value supplied via socket `PV` changes, `Q` is immediately recalculated and output upon change. The counter itself remains unaffected.
- **Overflow Protection**: The counter is only incremented if `CV` is less than 65535 (maximum value of `UINT`). Further incrementing beyond this value is not possible.
- **Adapter-Based**: Instead of classic direct inputs/outputs, all values are exchanged via standardized adapters. This allows for easy integration into existing 4diac adapter concepts.

## State Overview

| State | Description | Actions | Outgoing Transitions |
|---------|--------------|----------|-------------------------|
| `START` | Idle state, waiting for events | – | `CU` → `CU`, `R` → `R`, `PV.E1` → `UPDATE_PV` |
| `CU` | Count up | `CU` algorithm, send `CV.E1` and `CUO` | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `R` | Reset | `R` algorithm, send `CV.E1` and `RO` | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `UPDATE_PV` | Recalculation after PV change | `UPDATE` algorithm | `[Q != Q_OLD]` → `EMIT_Q`, `[Q == Q_OLD]` → `START` |
| `EMIT_Q` | Emission of the Q event | `SAVE_Q` algorithm, send `Q.E1` | 1 → `START` |

The transitions are triggered by conditions:

- `CU[CV.D1 < 65535]`: CU event if the counter is not at its maximum.
- `R`: R event, always possible.
- `PV.E1`: Event from the PV adapter.
- `[Q.D1 <> Q_OLD]` / `[Q.D1 = Q_OLD]`Comparison of the current Q with the stored previous value.

## Application Scenarios

- **Event Counter with Threshold Monitoring**: Counting pulses (e.g., workpieces on a conveyor belt) and triggering an action as soon as a specific threshold is reached.
- **Level Monitoring**: Used as a limit switch that transmits a status when a setpoint is exceeded.
- **State-Dependent Controls**: E.g., in batch processing where a process step should be triggered after a certain number of steps.
- **Systems with Dynamic Threshold**: The threshold can be changed during operation via the adapter `PV`; the function block reacts automatically.

## Comparison with Similar Function Blocks

| Feature | `AUI_CTU` | Standard `CTU` (IEC 61131-3) | `CTUD` (Up/Down Counter) |
---------|-----------|------------------------------|------------------------------|
| Interface | Adapter-based | Direct Inputs/Outputs | Direct Inputs/Outputs |
| Event on Q Change | Yes (On-Change) | No (Always on Counting Event) | No |
| Response to PV Change | Automatic | Not Provided | Not Provided |
| Overflow Protection | Yes (max. 65535) | Yes, via configuration | Yes |
| Down Count | No | No | Yes |

The `AUI_CTU` is specifically optimized for event-driven systems with an adapter concept. On-change triggering and automatic PV recalculation are key differences compared to traditional meters.

## Conclusion

The `AUI_CTU` is a modern, adapter-based up-meter that stands out for its efficient event handling. Thanks to on-change triggering for the status `Q`, unnecessary messages in the system are avoided. Support for dynamic limits via the `PV` adapter increases flexibility in control applications. The module is robust against overflows and offers a clear, state-driven flow structure. It is particularly well-suited for distributed automation systems where loose coupling and event-driven communication are paramount.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
