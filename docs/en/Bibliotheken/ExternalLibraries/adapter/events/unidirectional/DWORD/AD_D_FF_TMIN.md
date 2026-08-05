# AD_D_FF_TMIN
![AD_D_FF_TMIN](./AD_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AD_D_FF_TMIN** implements a data-retaining flip-flop (D-latch) based on adapters with a unidirectional interface. It features a configurable minimum inter-disposal time (MDR) between two consecutive events, making it suitable for time-critical signal processing.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| INIT | EInit | Initialization Request (Passing the Minimum Time) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| Tmin | TIME | Minimum time between two consecutive events on socket *I* |

### **Data Outputs**

No direct data outputs are available; output is exclusively via the adapter *Q*.

### **Adapters**

| Type | Direction | Name | Comment |
|-----|----------|------|-----------|
| adapter::types::unidirectional::AD | **Plug** (Output) | Q | Returns the latched value |
| adapter::types::unidirectional::AD | **Socket** (Input) | I | Receives the value to be latched and the clock event |

## Functionality

This component encapsulates an internal instance of the function block `iec61499::events::E_D_FF_ANY_TMIN`. The socket *I* returns both the clock event (via the adapter event output `E1`) and the data value (via the adapter data output `D1`). At each clock cycle, the internal flip-flop updates the current value from `I.D1` to its output `Q`. This signal is output via the plug *Q* (event `E1` and data `D1`).

The minimum dwell time `Tmin` is passed to the internal block during initialization and limits the frequency of clock events: Events arriving before the elapsed time of `Tmin` since the last clock cycle are suppressed.

## Technical Features
- **Adapter-based I/O**: The block uses unidirectional adapters (type `adapter::types::unidirectional::AD`) that combine events and data in a structured interface.
- **Event-driven minimum dwell time**: The configurable time `Tmin` prevents excessively fast clocking and protects downstream logic from overload.
- **Reuse**: The internal logic is implemented as a separate function block (`E_D_FF_ANY_TMIN`), which facilitates modular maintenance and testing.

## State Overview

The function block itself does not have an explicit state machine (no ECC definition). Its behavior is entirely determined by the embedded function block `E_D_FF_ANY_TMIN`. This operates as a **D flip-flop with a time filter**:

- **Idle State**: Waiting for the next clock event.
- **Clock Processing**: Checking whether the time interval `Tmin` has elapsed since the last clock cycle. If yes → Data transfer and generation of an output event. If no → Event ignored.
- **Initialization State**: Only when `INIT` is `Tmin` set and the internal timer reset.

## Application Scenarios
- **Data Acquisition with Minimum Interval**:

Sensor data should only be acquired if a specific time interval from the previous value is maintained (e.g., debouncing or sampling rate limiting).

- **Pulse Shaping / Trigger Management**:

The function block can be used as a "debounced" flip-flop in controllers to smooth signal edges and filter out interference pulses.

- **Adapter-Oriented Bus Architectures**:

Thanks to the adapter interface, the function block can be seamlessly integrated into existing unidirectional data flows, e.g., in sensor-actuator networks.

## Comparison with Similar Function Blocks

| Function Block | Feature | Difference |
|----------|-------------|-------------|
| **E_D_FF** | Standard D Flip-Flop | No time constraint; every clock event is processed. |
| **E_CTD** / **E_CTU** | Counter | Different basic function; counts events. |
| **AD_D_FF_TMIN** | D Flip-Flop with *Minimum Inter-disposal Time* | Prevents excessively fast clock sequences through configurable lock time. |

## Conclusion

The **AD_D_FF_TMIN** extends the classic D Flip-Flop with a time-based filter function, which is configured via the parameter `Tmin`. Its adapter interface allows for clean encapsulation of events and data in a single connector, simplifying integration into complex automation systems. The module is ideal for applications requiring a minimal event distance.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 E_CTU Event Counter Module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)

]
