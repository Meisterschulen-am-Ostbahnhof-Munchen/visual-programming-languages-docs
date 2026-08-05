# AUDI_D_FF_HYS_TMIN
No image available
![AUDI_D_FF_HYS_TMIN](./AUDI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_D_FF_HYS_TMIN** implements a clock-edge-triggered data latch (D flip-flop) with a hysteresis function and a minimum dwell time between output events (EO). It serves to reliably and cleanly acquire a data value while simultaneously suppressing noise and undesirably fast switching operations. The function block encapsulates the logic of an internal component `E_D_FF_ANY_HYS_TMIN` and provides the inputs/outputs via standardized adapters.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |

| INIT | EInit | Initialization request, sets hysteresis and minimum time |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|---------------------------------------------|

| INITO | EInit | Initialization confirmation |

### **Data Inputs**

| Variable | Type | Comment |

|--------------|-------|-----------------------------------------------------------|

| HYSTERESIS | UDINT | Hysteresis band (width of the dead zone for noise suppression) |

| Tmin | TIME | Minimum time between two consecutive output events |

### **Data Outputs**

No direct data outputs – the output data is provided via the **Q** adapter.

### **Adapter**

| Name | Type | Direction | Comment |

|-------------|------------------------------------|----------|----------------------------|

| I | `adapter::types::unidirectional::AUDI` | Input | Data value to be received |

| Q | `adapter::types::unidirectional::AUDI` | Output | Latched value |

## Functionality

1. **Initialization** – The parameters `HYSTERESIS` and `Tmin` are set via the event input `INIT`. After successful initialization, `INITO` is output.

2. **Data Latch** – Each event at the adapter input `I.E1` is interpreted as a clock signal (CLK). The current data value from `I.D1` is adopted.

3. **Hysteresis** – The output value only changes if the difference between the new and old values exceeds the hysteresis band (`HYSTERESIS`). This suppresses small fluctuations (e.g., noise).

4. **Minimum Time** – After an output event (`Q.E1`), no further output event is generated for the duration `Tmin`, even if new clock signals are present at the input. This prevents an excessively high output event rate.

The function block (FB) internally uses the block `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`, which implements the described logic.

## Technical Features
- **Adapter-Based Input/Output** – The FB communicates via standardized unidirectional adapters of type `AUDI`. This enables type-safe and modular integration with other function blocks.
- **Configurable Hysteresis** – The hysteresis width can be adjusted at runtime using `HYSTERESIS`.
- **Minimum Time Between Events** – The minimum time `Tmin` between two output events protects downstream components from overload and defines a maximum update rate.
- **Initialization Required** – Before initial operation, the FB must be configured using `INIT`; otherwise, the internal parameters are undefined.

## State Overview
The function block (FB) does not have an explicit state machine in the XML. Its behavior is entirely determined by the internal block `E_D_FF_ANY_HYS_TMIN`. The following states can be logically derived:

- **Initial** – After a reset, waits for `INIT`.
- **Ready** – After `INIT` and `INITO`, ready to receive data.
- **Waiting for Clock** – Awaits an event at `I.E1`.
- **Processing** – Data is being evaluated, hysteresis is being checked.
- **Output Locked** – After an output event, the `Tmin` timer starts running, during which no further output is possible.

## Application Scenarios
- **Sensor Value Wiring** – Stabilization of analog or digital sensor signals with hysteresis (e.g., level, temperature, pressure) and update rate limitation.
- **Clock Edge-Triggered Data Acquisition** – Reliable reading of values from noisy environments when a minimum time between value changes is required.
- **Actuator Control** – Protection of actuators from excessively rapid switching by limiting the output event frequency.

## Comparison with Similar Components
- **Standard D Flip-Flop (e.g., `E_D_FF`)** – No hysteresis and no time limit; responds to every clock edge without filtering.
- **D Flip-Flop with Hysteresis (e.g., `AUDI_D_FF_HYS`)** – Includes hysteresis, but no minimum time between output events.
- **AUDI_D_FF_HYS_TMIN** – Combines both features: hysteresis for noise suppression and `Tmin` for limiting the event rate.

## Conclusion
The FB `AUDI_D_FF_HYS_TMIN` offers a robust, configurable solution for clock-driven data acquisition in industrial automation environments. By combining hysteresis and minimal inter-event time, it is particularly suitable for applications with noisy signals or limited output bandwidth. The adapter-based interface facilitates integration into existing systems and promotes reusability.
