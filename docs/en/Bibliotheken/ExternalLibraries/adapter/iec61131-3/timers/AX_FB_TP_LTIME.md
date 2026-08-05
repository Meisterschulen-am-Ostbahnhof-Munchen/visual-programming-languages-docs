# AX_FB_TP_LTIME
![AX_FB_TP_LTIME](./AX_FB_TP_LTIME.svg)

* * * * * * * * * *
## Introduction
The **AX_FB_TP_LTIME** is a standardized pulse timer function block (timer pulse) according to IEC 61131-3, extended by a unidirectional **AX adapter**. It is used in the 4diac IDE to generate time-limited pulses and pass the output signals to the application via an adapter. Its behavior is similar to a **TP** timer, which sets the output to TRUE for a predefined time on a rising edge at the input.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Normal execution request (non-triggering) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Execution Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| PT | LTIME | Pulse Time (Pulse Duration) |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| ET | LTIME | Elapsed Time |

### **Adapters**
- **Plugs:**
- **Q**: Output adapter type `adapter::types::unidirectional::AX`.

This adapter passes the Boolean output signal `Q.D1` and the event `Q.E1` to the application.

- **Sockets:**
- **IN**: Input adapter type `adapter::types::unidirectional::AX`.

The function block receives the start event (via `IN.E1`) and, if necessary, a Boolean signal (via `IN.D1`) via this adapter. This signal is used internally as an enable or additional condition (not directly connected to the timer logic, but routed to an internal standard timer).

## Functionality
The function block consists of two internal components:

1. **FB_TP_LTIME** – a pure pulse timer (IEC 61131-3 TP) with a time base of LTIME.

2. **E_D_FF** – an edge-triggered D flip-flop (E-D-FF according to IEC 61499) that buffers the Q output of the timer.

**Procedure:**

- An event via the adapter input `IN.E1` or the standard event input `REQ` starts the timer `FB_TP_LTIME` (the events are internally combined – both trigger the same start).
- The timer increments the elapsed time `ET` and sets its internal Boolean output `Q` to TRUE as soon as `PT` is reached. After the pulse duration elapses, `Q` returns to FALSE and a `CNF` event is output.
- The `CNF` event clocks the D flip-flop `E_D_FF`, which takes over the current state of `Q` (i.e., TRUE during the pulse duration, FALSE afterward) and makes it available at the output `Q.D1` of the adapter.
- Simultaneously, the `CNF` event is also directly forwarded to the output `CNF` of the overall module, thus informing the application about the end of the pulse.

`` - The output `ET` indicates the current elapsed time and is directly connected to the output of the internal timer.

## Technical Features
- **Adapter Interface:** The function block encapsulates the timer logic in an adapter interface, allowing for easy integration into modular, adapter-based architectures.
- **D Flip-Flop for Signal Hold:** The timer's Q output is synchronized with the `CNF` event via a flip-flop to prevent glitches or asynchronous changes.
- **Dual Event Path:** The timer can be started via the adapter (`IN.E1`) or via the standard event input `REQ` – both are internally connected, enabling flexible control.
- **LTIME Support:** The pulse time is processed as `LTIME` (Long Time, 64-bit nanoseconds), enabling extremely high time resolution and large time ranges.

## State Overview
Since the functional block consists of two parts, the following state behavior results for the complete module:

| State | Description |
|---------|--------------|
| **IDLE** | No pulse active. The adapter output `Q.D1` is FALSE. |
| **TIMING** | A pulse is running – the internal timer is counting up. `ET` is increasing, `Q.D1` is TRUE (as soon as the flip-flop was clocked at startup or after the first CNF). |
| **DONE** | The pulse is complete. `CNF` was output, `ET` is equal to `PT`, `Q.D1` will be set to FALSE with the next `CNF`. The cycle starts again with a new `REQ` or `IN.E1`. |

## Application Scenarios
- **Pulse Output with Defined Length:** Controlling actuators (e.g., valves, lamps) that are to be switched on for a specific time.
- **Adapter-Based Subsystems:** Integrating the timer into a modular automation solution where inputs and outputs communicate via adapters (AX protocol).
- **High-Resolution Time Measurement:** Utilizing `LTIME` for precise timing in the micro- or nanosecond range.

## Comparison with Similar Function Blocks

| Function Block | Type | Feature |
|----------|-----|--------------|
| **FB_TP_LTIME** (Standard) | TP Timer | No adapter, only standard events and signals. |
| **AX_FB_TP_LTIME** (this FB) | TP Timer with AX Adapter | Enables integration into adapter-based architectures, includes a D flip-flop for signal stabilization. |
| **FB_TON_LTIME** | Turn-On Delay | Delays the activation of an output. |
| **FB_TOF_LTIME** | Turn-Off Delay | Delays the switching off of an output. |

This module combines the timer function of a twisted pair (TP) with the flexibility of an adapter.

## Conclusion
The **AX_FB_TP_LTIME** is a robust and precise pulse timer for the 4diac IDE. Thanks to its adapter interface and the use of `LTIME`, it is particularly well-suited for high-resolution, modular automation solutions. The internal flip-flop structure ensures clean signal transitions, and the dual event circuitry offers flexibility in control.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
