# E_D_FF_ANY_HYS_TMIN

![E_D_FF_ANY_HYS_TMIN](./E_D_FF_ANY_HYS_TMIN.svg)

* * * * * * * * * *

The function block `E_D_FF_ANY_HYS_TMIN` is a composite function block for IEC 61499-based systems. It implements an edge-triggered D flip-flop (data latch) with integrated threshold hysteresis and a minimum time interval limit (`Tmin`) for outgoing events.

This block is used to filter continuous or high-frequency changes in a numerical input signal. A new output event is only generated if the signal change exceeds the defined hysteresis and a defined minimum time interval has elapsed since the last output event. This effectively prevents so-called "event flooding" in distributed control systems.

| Event | Type | Description | Associated Data |
| :--- | :--- | :--- | :--- |
| **INIT** | EInit | Initializes the function block and sets the minimum time limit. | `Tmin` |
| **CLK** | Event | Clock signal. When this event occurs, the value at input `D` is evaluated. | `D`, `HYSTERESIS` |
| Event | Type | Description | Associated Data |
| :--- | :--- | :--- | :--- |
| **INITO** | EInit | Confirmation of successful initialization. | None |
| **EO** | Event | Triggered when a CLK event has caused a valid change to the output value `Q` and the minimum time `Tmin` has elapsed. | `Q` |
| Variable | Type | Description |
| :--- | :--- | :--- |
| **D** | ANY_NUM | The input value (Data) to be stored. |
| **HYSTERESIS** | ANY_NUM | The hysteresis band. Determines how much `D` must differ from the current output value `Q` to trigger a change. |
| **Tmin** | TIME | The minimum time interval that must elapse between two consecutive `EO` events. |
| Variable | Type | Description |
| :--- | :--- | :--- |
| **Q** | ANY_NUM | The stored and filtered output value (latched value). |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block does not use any adapters.

## Functionality

The module internally combines two specialized function blocks:

1. A hysteresis memory module (`E_D_FF_ANY_HYS`)
2. A time-limited event timer (`E_TMIN`)

As soon as an event arrives at input `CLK`, the internal module `E_D_FF_ANY_HYS` reads the current value from `D`.

- If the difference between the new value `D` and the currently stored value `Q` lies outside the range defined by `HYSTERESIS`, `Q` is updated with the new value and an internal event is forwarded to the limiter `E_TMIN`.
- If the change lies within the hysteresis band, the value remains unchanged and no event is forwarded.

The function block `E_TMIN` monitors the forwarding of this event to the output `EO`. It ensures that at least the time interval `Tmin` elapses between two `EO` events. Rapidly successive events are delayed or filtered accordingly to protect the subsequent logic from excessive event load.

- **Generic Data Types (`ANY_NUM`):** By using the generic data type `ANY_NUM` for `D`, `HYSTERESIS`, and `Q`, the function block is highly reusable and can be used for various numeric types (e.g., `INT`, `REAL`, `LREAL`).
- **Combined Filtering:** The function block combines amplitude filtering (hysteresis) and time filtering (Tmin) in a single component.

1. **Uninitialized:** The function block is waiting for the event `INIT`.
2. **Initialized / Ready:** The function block has configured `Tmin` and is waiting for events at input `CLK`.
3. **Value Change Blocked (Hysteresis):** A `CLK` event arrives, but the change in `D` is too small. `Q` remains unchanged; there is no `EO`.
4. **Value Change Active (Time Delay/Filtering):** A `CLK` event arrives, and the change is large enough. When `Tmin` expires, `Q` is updated and `EO` is immediately output. If `Tmin` is still active, the timer's protection function is activated.

- **Analog Sensor Value Processing:** Attenuation and noise reduction for noisy analog measurements (e.g., temperature, pressure, or fill level).
- **Network-Friendly Data Transmission:** Reduction of publish events in IoT or SCADA systems (e.g., MQTT). Data is only sent when a value has changed significantly, but at most every "X" seconds.
- **Resource Efficiency in PLC Controllers:** Relieving the CPU of cyclic calculations that would be triggered by high-frequency signal changes.

- ## Comparison with Similar Components

- **`E_D_FF`:** Stores values directly at each clock cycle without hysteresis or time limiting. This results in extremely high event density with turbulent signals.
- **`E_D_FF_ANY_HYS`:** While it does have hysteresis, it offers no protection against rapid, continuous signal changes (e.g., during fast ramps), which would still generate too many events. `E_D_FF_ANY_HYS_TMIN` solves this problem with the integrated `Tmin` component.

The `E_D_FF_ANY_HYS_TMIN` is an extremely useful component for signal conditioning in industrial environments. It combines value-based filtering with time-based rate limiting. This makes it ideal for stable control architectures where sensor values need to be precisely acquired, but downstream systems must be protected from overload.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
