# AX_FB_TOF_LTIME

![AX_FB_TOF_LTIME](./AX_FB_TOF_LTIME.svg)

* * * * * * * * * *
## Introduction

The function block **AX_FB_TOF_LTIME** implements a standard timer for the off-delay according to IEC 61131-3. It is specifically designed for use with an AX adapter and uses an internal timer module and a D flip-flop to precisely represent the timing behavior. The time base uses the data type `LTIME`, resulting in high temporal resolution.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| `REQ` | Normal execution command (non-triggering) – starts or updates the timer calculation. The corresponding data input is `PT`. |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| `CNF` | Execution confirmation – signals the completion of a timer update. The corresponding data output is `ET`. |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `PT` | `LTIME` | Process Time – The desired shutdown delay duration. |

### **Data Outputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `ET` | `LTIME` | Elapsed Time – The time elapsed since the delay started. |

### **Adapter**

| Direction | Adapter Type | Comment |
|----------|------------|-----------|
| **Socket** `IN` | `adapter::types::unidirectional::AX` | Input adapter – receives the binary control signal (e.g., via event `E1` and data `D1`). |
**Plug** `Q` | `adapter::types::unidirectional::AX` | Output adapter – forwards the time-delayed output signal (via event `E1` and data `D1`). |

## Functionality

The module behaves like a classic time-of-flight (TOF) delay circuit:

- As long as the input `IN` (via the adapter) is **TRUE**, the output `Q` is also **TRUE**, and the elapsed time `ET` is set to zero.
- As soon as `IN` changes from **TRUE** to **FALSE**, the timing starts. The output `Q` remains **TRUE** for the duration of the specified time `PT` and only then falls to **FALSE**.
- As soon as `IN` changes from **TRUE** to **FALSE**, the timing measurement starts. The output `Q` remains **TRUE** for the duration of the specified time `PT` and only then falls to **FALSE**.
- As long as the input `Q` (via the adapter) is **TRUE**, the output `PT` remains **TRUE**. If `IN` becomes **TRUE** again before the delay time expires, the timer is reset and `Q` remains **TRUE**.

Event-driven processing occurs as follows:

1. The event `REQ` (either directly or from the adapter input `IN.E1`) triggers the internal timer `FB_TOF_LTIME`.
2. The timer calculates the elapsed time and outputs the event `CNF` upon completion.
3. This `CNF` clocks the D flip-flop `E_D_FF`, which stores the current timer output (`Q` of the timer) and passes it through to the output adapter `Q.D1`.
4. Simultaneously, the `CNF` event is forwarded to the output adapter `Q.E1`, so that the downstream adapter is informed of the change.

The variable `ET` is taken directly from the timer and displays the currently elapsed delay time at all times.

## Technical Features

- **High time resolution** through the use of `LTIME` (Long Time) according to IEC 61131-3.
- **Adapter-based I/O** via the unidirectional `AX` adapter enables loose coupling between different resources (e.g., between the application and the I/O driver).
- **Standard compliance** according to IEC 61131-3 – the behavior corresponds exactly to that of a TOF timer.
- **Internal structure**: The component combines a pure timer (`FB_TOF_LTIME`) with an edge-triggered D flip-flop to implement the turn-off delay behavior.

## State overview

| State | Input `IN` | Output `Q` | Elapsed time `ET` |
|---------|--------------|--------------|------------------------|
| Inactive / Ready | TRUE | TRUE | 0 (Zero) |
| Delay in progress | FALSE → Return to TRUE possible | TRUE | 0 … PT |
| Delay expired | FALSE | FALSE | PT (constant) |

A change from `IN` to **TRUE** resets the timer and immediately returns it to the "Inactive / Ready" state. A change to **FALSE** restarts the delay.

## Application Scenarios

- **Run-on control** of fans, pumps, or conveyor belts after a signal is switched off.
- **Debouncing** of signals: a brief level change is filtered out by the delay.
- **Protection times** when switching inductive loads: the switch-off is delayed by a defined time.
- **Time-controlled logic** in production plants, where an output should remain active for a specific duration after the input event.

## Comparison with similar function blocks

- **TON (Switch-on delay)**: The output only becomes active after a delay following the switch-on. – TOF delays the switch-off.
- **TP (Pulse)**: The output provides a pulse of a predefined length, independent of the duration of the input signal. – TOF only reacts to the falling edge.
- **RTRIG / FTRIG (Edge detection)**: Detect signal changes without a time component. – TOF combines edge detection with time control.

## Conclusion

The `AX_FB_TOF_LTIME` is a powerful, standardized function block for time-critical switch-off delays in automation technology. The AX adapter allows for flexible integration into distributed systems, while the internal combination of timer and flip-flop ensures precise and reproducible timing. It is particularly suitable for applications requiring an accurate time base and a modular interface.
