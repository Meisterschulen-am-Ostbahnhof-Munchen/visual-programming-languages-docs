# AUI_D_FF_HYS_TMIN

![AUI_D_FF_HYS_TMIN](./AUI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Introduction

The function block **AUI_D_FF_HYS_TMIN** is a data storage device (D flip-flop) with adjustable hysteresis and a minimum intermediate event time (`Tmin`). It is connected to other function blocks via adapter interfaces (socket `I` and plug `Q`). The internal core corresponds to function block `E_D_FF_ANY_HYS_TMIN` from the library `logiBUS::signalprocessing::hysteresis`. The initialization defines the parameters. Afterward, for each incoming event at input `I.E1`, the current value from `I.D1` is taken, filtered, and output via `Q.D1`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|--------|--------------------------------------|

| INIT | EInit | Initialization Request |

### **Event Outputs**

| Name | Type | Comment |

|--------|--------|---------------------------------|

| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |

|------------|-------|--------------------------------------------|

| HYSTERESIS | UINT | Hysteresis Band |

| Tmin | TIME | Minimum Intermediate Arrival Time of EI Events |

### **Data Outputs**

No standalone data outputs – the output value is transmitted via the `Q` adapter.

### **Adapter**

| Type | Name | Comment |

|-------------------------------------------------------|-------------|---------------------|

| `adapter::types::unidirectional::AUI` (Socket) | I | Value to be stored |

| `adapter::types::unidirectional::AUI` (Plug) | Q | Stored Value |

The adapter `AUI` is a unidirectional type that bundles an event and a data value (`E1` and `D1`).

## Functionality

1. **Initialization**

Upon the event `INIT`, the parameters `HYSTERESIS` (as UINT) and `Tmin` (as TIME) are passed to the internal module. After successful initialization, `INITO` is triggered.


2. **Operation**

The internal function block `E_D_FF_ANY_HYS_TMIN` operates as a clocked D flip-flop with hysteresis and a time limit:

- An event at `I.E1` (Clock) takes the current data value from `I.D1`.

- The taken value is only passed on as a valid output `Q.D1` if the interval to the last valid event is greater than or equal to `Tmin`.

- Additionally, the value is smoothed with a hysteresis (band `HYSTERESIS`): Small changes below the hysteresis threshold are suppressed.

- The output is signaled via the event `Q.E1`.


3. **Result**

The output adapter `Q` returns the last assumed, filtered value.

## Technical Features

- **Hysteresis** in conjunction with a **minimum time between two events** prevents both noise and excessively rapid state changes.

- The function block is implemented as an **adapter wrapper** – it uses standardized unidirectional AUI adapters for input and output.

- The implementation delegates all logic to the function block `E_D_FF_ANY_HYS_TMIN`, which is universally designed for any data type. Here, it is used in the context of the AUI adapter.

## State Overview

The function block does not have an explicit internal state machine. The behavior is represented by the internal function block:

- **Idle:** Waits for the next event on `I.E1`.

- **Sampling:** The data value is captured upon arrival of `I.E1`.

- **Filtering:** Checks against hysteresis and minimum time.

- **Output:** If successful, `Q.E1` is triggered and the new value is assigned to `Q.D1`.

## Application Scenarios

- **Sensor Value Acquisition** in agricultural technology (see Copyright HR Agrartechnik GmbH): Processing of analog or digital signals with debouncing and minimum sampling rate.

- **Control Components** in automation systems where noise suppression and a minimum pulse duration are required.

- **Data Logic** in distributed systems that must respond to asynchronous events with stability requirements.

## Comparison with Similar Components

| Component | Property |

|----------|-------------|

| `E_D_FF` | Simple D flip-flop without hysteresis or time limit |

| `E_D_FF_HYS` | D flip-flop with hysteresis, but without `Tmin` |

| `E_D_FF_HYS_TMIN` (this FB) | Combines hysteresis *and* minimal time interval → more robust against noise and burst events |

## Conclusion

The `AUI_D_FF_HYS_TMIN` offers a compact and reliable solution for signal-processing data acquisition, suppressing unwanted interference pulses through hysteresis and time limiting. The adapter interface facilitates integration into existing 4diac projects using standardized, unidirectional AUI connections.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]