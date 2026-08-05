# ATM_AX_PULSE
![ATM_AX_PULSE](./ATM_AX_PULSE.svg)
*Image not available*

* * * * * * * * * *
## Introduction
The function block **ATM_AX_PULSE** is a standardized timer module for generating a non-retriggerable pulse. It is configured and read via the adapter interfaces **PT** (ATM) and **Q** (AX). The module complies with the IEC 61499-2 standard and is part of the library **adapter::events::unidirectional::timers**.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-----|---------------|

| **REQ** | Event | Service request – starts the pulse. |

| **R** | Event | Reset – terminates the pulse prematurely. |

### **Event Outputs**
No direct event outputs. Output is provided via the **Q** adapter (see below).

### **Data Inputs**
No direct data inputs. The pulse duration is provided via the **PT** adapter.

### **Data Outputs**
No direct data outputs. The pulse status is queried via the **Q** adapter.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| **PT** | Socket | `adapter::types::unidirectional::ATM` | Returns the pulse duration as a time value. |

| **Q** | Plug | `adapter::types::unidirectional::AX` | Outputs the pulse status: **D1** = current value (TRUE during the pulse); **E1** = event at the end or change of the pulse. |

## Functionality
This function block implements the behavior of a non-retriggerable pulse generator (E_PULSE). Upon arrival of the **REQ** event, a pulse is initiated, the duration of which is determined by the value applied to the **PT** adapter. During the pulse, the output **Q.D1** = *TRUE*. After the pulse duration has elapsed, **Q.D1** becomes *FALSE* and the **Q.E1** event is triggered. A subsequent **REQ** during an ongoing pulse is ignored (non-retriggerable). The pulse can be prematurely terminated at any time via the **R** reset input; **Q.E1** is also triggered in this case.

## Technical Features
- **Adapter-based communication:** Instead of direct data/event ports, typed adapters (ATM for time, AX for output) are used. This simplifies reuse in modular systems.
- **Non-retriggerable:** A second start pulse during an ongoing pulse has no effect.
- **Validated versions:** The function block has been revised several times (versions 1.0 to 3.0, most recently in 2025) and includes a reset function.
- **Licensed under EPL 2.0** (Eclipse Public License 2.0).

## State overview

1. **Idle** – No pulse active. **Q.D1** = FALSE.

2. **PulseActive** – Pulse running. **Q.D1** = TRUE. Entered by **REQ** and exited either by timeout or **R**.

- At time elapse: Transition to Idle, triggering **Q.E1**.
- At **R**: Transition to Idle, triggering **Q.E1**.

3. During **PulseActive**, **REQ** is ignored.

## Application Scenarios
- Control of actuators (e.g., valves, lamps) with a defined on-time.
- Timers in production machines that require one-time pulses.
- Signal conditioning in sensor-actuator networks (AX/ATM-compatible peripherals).

## Comparison with Similar Function Blocks
- **E_PULSE (iec61499::events::timers):** Standard implementation without an adapter interface. ATM_AX_PULSE encapsulates this function block and adds the adapter connection.
- **ATM_AX_PULSE_R (retriggerable):** Retriggerable variant; a subsequent **REQ** extends the pulse. The present block is not retriggerable.
- **E_DELAY, E_CYCLE:** Different timing behavior (delay, periodic) – not comparable.

## Conclusion
The **ATM_AX_PULSE** is a robust, non-retriggerable pulse block that, thanks to its adapter interface, can be particularly well integrated into modular automation solutions using the AX/ATM protocol. It offers clear, reliable functionality for generating time-defined pulses and meets the requirements of IEC 61499-2.
