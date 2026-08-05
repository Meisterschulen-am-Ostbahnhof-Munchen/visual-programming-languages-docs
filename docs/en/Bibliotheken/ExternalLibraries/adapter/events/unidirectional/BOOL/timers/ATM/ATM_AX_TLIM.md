# ATM_AX_TLIM
![ATM_AX_TLIM](./ATM_AX_TLIM.svg)

* * * * * * * * * *
## Introduction
The function block **ATM_AX_TLIM** is a standardized time monitoring module (timer) with a special adapter interface. It implements time limiting (timeout) for Boolean input signals. The module communicates via adapters instead of individual event and data ports, enabling flexible and encapsulated integration into industrial control systems.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|-------|--------|----------------------------------------|

| EIPT | Event | Set Preset Time (non-triggering) |

### **Event Outputs**
The module does not have separate event outputs. Event forwarding occurs exclusively via the adapter output **Q**, which triggers an event on its `E1` port after a change in the output signal.

### **Data Inputs**
There are no direct data inputs. The required data (input signal IN and time limit PT) is provided via the corresponding adapter ports.

### **Data Outputs**
Similarly, there are no direct data outputs. The result (Boolean value Q) is output via the adapter output **Q** (port `D1`).

### **Adapters**

| Name | Type | Direction | Comment |

|-------------|--------|-----------|--------------------------------------|

| IN | AX | Input | Boolean Input (Adapter) |

| PT | ATM | Input | Time Limit (Adapter) |

| Q | AX | Output | Boolean Output (Adapter) |

## Functionality
The function block internally uses the standard function block **E_TLIM** and wraps it in an adapter. The logic is as follows:

1. **Activation**: An event at the adapter input **IN** (port `E1`) triggers processing. Simultaneously, the Boolean value from **IN.D1** is taken.

2. **Time Measurement**: When the input signal `IN` becomes **TRUE**, the function block sets the output `Q` to **TRUE** and starts a timer with a duration of **PT** (from adapter **PT**, port `D1`).

3. **Timeout**: If `IN` remains active longer than `PT`, `Q` is reset to **FALSE** (timeout).

4. **Premature Termination**: If `IN` becomes **FALSE** before the time expires, the function block `Q` is immediately reset (also to **FALSE**).

5. **Setting the Time Limit**: The event input **EIPT** allows you to specify the value of **PT** without triggering a new event. This is used to configure the time limit before the actual use.

4. **Premature Termination**: The output adapter **Q** outputs an event on its `E1` port as soon as `Q` changes (rising or falling edge).

## Technical Features
- **Adapter-Based Communication**: Instead of individual event and data ports, AX/ATM adapters are used. These enable modular and reusable coupling with other components.
- **Internal Standard Component**: The implementation uses the established **E_TLIM** (IEC 61499), ensuring reliable and tested timing logic.
- **Non-Triggering Time Setting**: The **EIPT** input only changes the time limit without starting or resetting the timer. This is useful for dynamically adjusting parameters.
- **Typical Time Measurement**: Suitable for monitoring applications where a signal must not be active for a specific duration.

## State Overview
The function block (FB) implicitly cycles through the following states:

| State | Description |

|------------|--------------------------------------------------------------|

| **Idle** | IN = FALSE, Q = FALSE, Timer is not running. |

| **Timing** | IN = TRUE, Q = TRUE, Timer is running. |

| **Timeout** | IN = TRUE, Timer expires, Q = FALSE (remains until IN = FALSE). |

A switch back to **Idle** occurs as soon as IN becomes FALSE. The **Timeout** state is only reached when the timeout has occurred.

## Application Scenarios
- **Monitoring of signals** in automation technology (e.g., maximum on-time of an actuator).
- **Safety functions** where an output must be deactivated if a signal persists for too long.
- **Timed resets** in communication protocols (watchdog functionality).
- **Simple time limiting** in complex control systems based on adapter interfaces.

## Comparison with similar function blocks
- **E_TLIM (Standard)**: Offers the same core logic, but with classic input/output ports. **ATM_AX_TLIM** encapsulates this logic in an adapter interface and is therefore better suited for modular and reusable components.
- **E_TON / E_TOF**: These function blocks implement turn-on and turn-off delays, respectively. In contrast, **ATM_AX_TLIM** monitors the maximum duration of an active signal and responds with a timeout.
- **E_CYCLE**: A cyclic timer that periodically generates signals has a different objective than simple monitoring.

## Conclusion
The **ATM_AX_TLIM** function block offers a compact, adapter-based solution for time monitoring tasks. It combines the proven functionality of the standard timer **E_TLIM** with the flexibility of adapter interfaces and allows dynamic specification of the time limit via **EIPT**. This makes it particularly suitable for modern, modular automation projects based on IEC 61499 that require a clear separation of interfaces and logic.
