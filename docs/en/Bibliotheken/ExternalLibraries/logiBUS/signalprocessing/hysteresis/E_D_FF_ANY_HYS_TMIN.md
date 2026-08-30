# E_D_FF_ANY_HYS_TMIN

![E_D_FF_ANY_HYS_TMIN](./E_D_FF_ANY_HYS_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **E_D_FF_ANY_HYS_TMIN** is a D flip-flop (data latch) with hysteresis that additionally enforces a minimum inter-disposal time between successive output events. It serves to stably transfer an analog or discrete value while simultaneously suppressing fast noise and excessively frequent state transitions.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |
| ---------- | ------- | ------------------------------------------------------ |
| `INIT` | EInit | Initialization Request; Parameter `Tmin` is passed |
| `CLK` | Event | Clock signal; takes the current value from `D` and applies hysteresis |

### **Event Outputs**

| Event | Type | Description |
| ---------- | ------- | ----------------------------------------------------------- |
| `INITO` | EInit | Initialization confirmation |
| `EO` | Event | Outputs when output `Q` changes **and** the minimum time `Tmin` has elapsed since the last `EO` |

### **Data Inputs**

| Name | Type | Description |
| -------------- | ---------- | --------------------------------------------------------- |
| `D` | ANY_NUM | Value to be inherited from `CLK` |
| `HYSTERESIS` | ANY_NUM | Hysteresis band: Changes smaller than this amount are ignored |
| `Tmin` | TIME | Minimum time between two consecutive `EO` events |

### **Data Outputs**

| Name | Type | Description |
| |------|----------|-----------------------------------------------------|
| `Q` | ANY_NUM | Output value – the last valid latched value |

### **Adapter**

None.

## Functionality

The function block consists internally of two functional blocks:

1. **`E_D_FF_ANY_HYS`** – A D flip-flop with hysteresis: On a `CLK` event, the current value of `D` is compared with the stored value. Only if the difference exceeds the value of `HYSTERESIS` is the output `Q` set to the new value and an internal event sent to the subsequent block.
2. **`E_TMIN`** – A timer that ensures that at least the time `Tmin` has elapsed between two `EO` events.

Procedure:

- `INIT` initializes the timer of `E_TMIN` with the parameter `Tmin`.
- A `CLK` triggers the hysteresis flip-flop.
- When the flip-flop detects a state change, it generates an internal event (`E_D_FF_ANY_HYS.EO`).
- This event is forwarded to `E_TMIN.EI`. `E_TMIN` checks whether the required minimum time (`Tmin`) has elapsed since the last output (`EO`). If so, `EO` is set at the output; otherwise, the event is discarded.
- The output value (`Q`) is passed directly from the flip-flop to the data output.

## Technical Features

- **Generic Data Type** `ANY_NUM`: The function block can work with various numeric data types (INT, REAL, LREAL, …).
- **Hysteresis** suppresses small fluctuations (e.g., sensor noise) and prevents unwanted oscillation.
- **Minimum Event Interval `Tmin`** limits the maximum output frequency and protects subsequent processing steps from overload.
- **No State Machine Visible**: The functionality is fully implemented through the internal network structure of blocks `E_D_FF_ANY_HYS` and `E_TMIN`.

## State Overview

Since the function block consists of two sub-blocks internally, no separate state diagram is defined in the XML. The key behaviors are:

- Initialized (`INIT` → `INITO`)
- Clocking (`CLK`) → Takeover of `D` with hysteresis
- Change in `Q` triggers timer check
- Timer allows or blocks the output of `EO`

## Application Scenarios

- **Signal conditioning** for slow measured variables (e.g., temperature, fill level) where small fluctuations should be ignored and a minimum update rate must be maintained.
- **Debouncing** of digital or analog switching contacts that must be transmitted with a delay.
- **Control engineering** with a limited switching frequency to protect actuators.
- **Data preprocessing** in IoT edge devices that shouldn't send every small event.

## Comparison with similar modules

| Module | Hysteresis | Minimum event interval | Application area |
| -------------------------------- | ----------- | ---------------------- | -------------------------------------- |
| `E_D_FF` (simple) | No | No | Pure data acquisition without filtering |
| `E_D_FF_ANY_HYS` | Yes | No | Hysteresis, but no frequency limiting |
| `E_D_FF_ANY_HYS_TMIN` (this one) | Yes | Yes | Complete filtering with noise and frequency limiting |

## Conclusion

The `E_D_FF_ANY_HYS_TMIN` combines two proven mechanisms – hysteresis and minimum event delay – in a single functional module. This makes it particularly suitable for harsh environments where measured values need to be stabilized and communication load reduced. Its generic data type interface makes it versatile.
