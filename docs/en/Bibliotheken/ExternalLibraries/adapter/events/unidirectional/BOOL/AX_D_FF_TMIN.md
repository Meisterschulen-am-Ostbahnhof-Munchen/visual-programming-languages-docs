# AX_D_FF_TMIN

![AX_D_FF_TMIN](./AX_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction

The function block **AX_D_FF_TMIN** implements a data-latch D flip-flop that additionally enforces a minimum time between successive event outputs (e.g., EO). It serves as a modular wrapper around the IEC 61499 standard function block `E_D_FF_TMIN` and uses a unidirectional adapter (`adapter::types::unidirectional::AX`) for event-driven data transfer. This function block is particularly suitable for applications requiring reliable data transfer with an adjustable minimum interval between output pulses.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-----|--------------|

| `INIT` | EInit | Initialization request; sets the minimum delay time (parameter `Tmin`). |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|--------------|

| `INITO` | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Name | Type | Description |

|------|-----|--------------|

| `Tmin` | TIME | Minimum inter-disposal time between two consecutive events at output `EO`. The value is only adopted upon a `INIT` event. |

### **Data Outputs**

This function block has no direct data outputs; the latching data value is provided via the adapter `Q`.

### **Adapters**

| Role | Name | Type | Description |

|-------|------|-----|--------------|

| Socket | `I` | adapter::types::unidirectional::AX | Input adapter; Provides the data word to be latched (`D1`) and the clock event (`E1`). |

| Plug | `Q` | adapter::types::unidirectional::AX | Output adapter; provides the latching data word (`D1`) and the output event (`E1`). |

The adapters `AX` are unidirectional: They transmit exactly one event and one associated data value.


## Functionality

The function block encapsulates the internal function block `E_D_FF_TMIN`, which operates as follows:

1. **Initialization**: When a `INIT` event is received, the current time `Tmin` is stored as the minimum lock time for the output `EO`. The function block acknowledges this with `INITO`.

2. **Clocking (D Flip-Flop)**:

- An event at socket `I.E1` is forwarded as a clock signal (CLK) to the internal flip-flop.

- Simultaneously, the data value `I.D1` is adopted as the new input value `D`.

- On each rising edge of the clock (here: each `E1` event), the current data value `D` is acquired and made available at output `Q`.

- After acquisition, an output event `EO` is generated at plug `Q.E1` – but only after the minimum lock time since the last `EO` has elapsed. This ensures that output pulses do not follow each other faster than specified by `Tmin`.

3. **Output**: The latching data value appears at plug `Q.D1`, and the corresponding event at plug `Q.E1`.


## Technical Features

- **Minimum Interval Time**: The function block enforces an adjustable minimum time (`Tmin`) between two output events. If the clock signal frequency exceeds this time, individual clock events are suppressed so that the output does not exceed a maximum permissible event sequence.

- **Adapter Interface**: By using the unidirectional adapter `AX`, loose coupling between transmitter and receiver is achieved. The adapter transports both the event and the data value in a single logical unit.

- **Initialization Dependency**: The minimum time `Tmin` is set only once at `INIT` and remains constant until the next `INIT`. Changes during operation are not permitted.

## State Overview

The function block does not have an explicit state machine. The internal logic of the embedded `E_D_FF_TMIN` can assume the following states:

- **Idle**: Waiting for a `INIT` or a clock event.

- **Initialized**: `Tmin` has been acquired; the function block is ready for operation.

- **Lockout Time Active**: After an output event, the delay defined by `Tmin` is applied; incoming clock events are ignored.

- **Ready**: After the lockout time has expired, the next clock event can trigger a new output event.

## Application Scenarios

- **Buffered Sensor Values**: A sensor delivers data at an irregular rate. The `AX_D_FF_TMIN` acquires the last valid value and passes it on to a subsequent controller with a maximum permissible output frequency.

- **Signal Debouncing**: Mechanical pushbuttons or switches generate bounce pulses. The minimal delay suppresses excessively rapid state changes.

- **Data Forwarding with Bandwidth Limiting**: In communication networks, this component can be used to limit the output rate of a data channel without requiring adaptation of the sender.

## Comparison with Similar Components

| Component | Difference |

|----------|-------------|

| `E_D_FF` (Standard D Flip-Flop) | No time limit on output pulses; events are forwarded immediately. |

| `AX_D_FF_TMIN` (present) | Inserts the minimum interval `Tmin` between output events, implemented via the built-in `E_D_FF_TMIN`. |

| `E_CTD` / `E_CTU` (counter) | Count events; do not offer data transfer or latching functionality. |

The `AX_D_FF_TMIN` combines the latching data transfer of a flip-flop with the time-based filtering of a monostable multivibrator, but is implemented as a pure event-to-data adapter.

## Conclusion

The **AX_D_FF_TMIN** is a specialized function block for applications that require clocked data transfer with a guaranteed minimum time between output events. The encapsulation of the standard function block `E_D_FF_TMIN` and the adapter interface facilitate integration into modular 4diac projects. The function block offers a clean separation of initialization and dynamic operation and is particularly suitable for time-critical, event-driven systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter function block on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```