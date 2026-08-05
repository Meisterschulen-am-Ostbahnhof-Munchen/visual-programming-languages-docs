# ADI_D_FF_HYS_TMIN
![ADI_D_FF_HYS_TMIN](./ADI_D_FF_HYS_TMIN.svg)
* * * * * * * * * *
## Introduction
The function block **ADI_D_FF_HYS_TMIN** implements a data latch (D flip-flop) with hysteresis and a minimal time delay between successive output events. It serves for stable and interference-free signal transmission in industrial control applications based on unidirectional adapters.
## Interface Structure

### **Event Inputs**
- **INIT** (EInit): Initialization request. This event input initializes the block with the parameters `HYSTERESIS` and `Tmin`.

### **Event Outputs**
- **INITO** (EInit): Initialization confirmation. Outputted after successful initialization.

### **Data Inputs**
- **HYSTERESIS** (DINT): Hysteresis band. Defines the switching threshold to prevent output chatter.
- **Tmin** (TIME): Minimum time between two output events (Inter-Arrival Time). Prevents excessively rapid switching.

### **Data Outputs**

This module does not have its own data outputs. The output data is provided via an adapter.

### **Adapters**
- **I** (Socket, Type: `adapter::types::unidirectional::ADI`): The value to be latched is received via this adapter input (event and data).
- **Q** (Plug, Type: `adapter::types::unidirectional::ADI`): The latched value is output via this adapter output (event and data).

## Functionality

The function block internally uses the FB `E_D_FF_ANY_HYS_TMIN`. It processes the events (`I.E1`) and data (`I.D1`) received via the adapter **I**. The actual latching function uses hysteresis, which is defined by the parameter `HYSTERESIS`. Additionally, a minimum waiting time `Tmin` is maintained between two output events to suppress an excessively high event frequency. Output is provided via the adapter **Q** (`Q.E1` and `Q.D1`). Initialization (`INIT`) sets the parameters and activates the internal FB.

## Technical Features
- **Adapter-Based Communication:** The function block uses unidirectional adapters (`ADI`) for data exchange. This enables loose coupling of data and events.
- **Configurable Hysteresis:** The hysteresis width can be set application-specifically to suppress noise or bounce effects.
- **Minimum Event Interval Time:** The maximum output frequency can be limited using `Tmin`, which helps to reduce the load on subsequent processing units.

## State Overview

The function block has two stable internal states (e.g., HIGH/LOW or TRUE/FALSE) that represent the latched output value. A state change only occurs if the incoming value (via **I**) exceeds the hysteresis threshold and the time elapsed since the last output event is at least `Tmin`. Otherwise, the event is suppressed.

| State | Description |

|---------|--------------|

| LOW | Output value is logic 0 or low |

| HIGH | Output value is logic 1 or high |

Changes between states occur according to the hysteresis and timing conditions.

## Application Scenarios
- **Debouncing of switches or sensors:** Prevents multiple switching cycles due to mechanical bouncing.
- **Signal smoothing in process automation:** Suppresses small disturbances or noise on analog or digital signals.
- **Event rate limiting:** Protects subsequent functions from excessively rapid event sequences, e.g., in counters or communication interfaces.

## Comparison with Similar Components

A conventional D flip-flop (e.g., `E_D_FF`) switches on every clock cycle without hysteresis or time delay. The `ADI_D_FF_HYS_TMIN`, on the other hand, offers:

- **Hysteresis:** Prevents oscillations with slowly changing or noisy signals.
- **Minimal Inter-Arrival Time:** Reduces the event rate and enables precise timing control.
- **Adapter Interface:** Specifically designed for use in complex, adapter-based function block networks.

## Conclusion

The `ADI_D_FF_HYS_TMIN` is a robust functional block for reliable signal processing with hysteresis and timing control. It is particularly suitable for applications requiring noise-free, filtered, and rate-limited transmission of events and data—typically in industrial control systems based on the 4diac framework and unidirectional adapters.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]