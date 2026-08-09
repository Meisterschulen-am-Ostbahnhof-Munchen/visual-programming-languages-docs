# ADI_D_FF_HYS

![ADI_D_FF_HYS](./ADI_D_FF_HYS.svg)

* * * * * * * * * *
## Introduction

The function block **ADI_D_FF_HYS** implements a data-timed (D) flip-flop with adjustable hysteresis. It receives values via a unidirectional adapter input `I` and outputs the state, including hysteresis, via the adapter output `Q`. The hysteresis bandwidth is set during the initialization event `INIT`.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|------|----------------------------------|
| `INIT` | EInit | Sets the hysteresis bandwidth (in conjunction with `HYSTERESIS`). |

### **Event Outputs**

| Event | Type | Description |
|----------|------|----------------------------------|
| `INITO` | EInit | Confirms the execution of `INIT`. |

### **Data Inputs**

| Variable | Type | Description |
|----------------|-----|----------------------------------|
| `HYSTERESIS` | DINT | Hysteresis bandwidth (integer value). |

### **Data Outputs**

This function block does not have direct data outputs; The latched value is provided via the adapter `Q`.

### **Adapter**

| Interface | Type | Direction | Description |
|---------------|-----|----------|----------------------------------|
| `I` | `adapter::types::unidirectional::ADI` | Socket | Input value (consisting of Event `E1` and Data `D1`). |
| `Q` | `adapter::types::unidirectional::ADI` | Plug | Latched output value (consisting of Event `E1` and Data `D1`). |

**Note:** The `ADI` (unidirectional) adapter provides one event channel (E1) and one data channel (D1) by default.

## Functionality

1. **Initialization**

An event at `INIT` transfers the value to `HYSTERESIS` and sets the internal hysteresis bandwidth for the flip-flop. The initialization event is then passed directly to `INITO`.

2. **Data Transfer**

The input adapter `I` delivers the current data value to `I.D1` with each event at `I.E1`.

The internal function block `E_D_FF_ANY_HYS` adopts this value according to the configured hysteresis:

- If the input value is **above** the upper threshold (stored value + hysteresis), the output is set to `1`.
- If the input value is **below** the lower threshold (stored value - hysteresis), the output is set to `0`.
- If the value remains within the hysteresis range, the output does not change.
3. **Output**

The internally latched value is passed to the data output `Q.D1`. Simultaneously, an event is triggered at `Q.E1` to signal data processing to downstream logic blocks.

## Technical Features

- **Parameterizable Hysteresis:** The hysteresis bandwidth can be adjusted at runtime via `INIT` and `HYSTERESIS` (integer value, data type `DINT`).
- **Adapter-Based Communication:** The function block uses fully unidirectional adapters, enabling a clean separation of signal flow and event control. This makes it particularly suitable for modular and distributed signal processing.
- **Internal Implementation:** The hysteresis logic is implemented using the standardized function block `E_D_FF_ANY_HYS` from the library `logiBUS::signalprocessing::hysteresis`.
- **No Delay Due to INIT:** The initialization (`INIT → INITO`) is passed through in the same cycle; the hysteresis is available from the following cycle.

## State Overview

The component does not have an explicit state machine, but is based on the internal state of the D flip-flop `E_D_FF_ANY_HYS`. This stores:

- The current output value (latched).
- The last input value received (for hysteresis analysis).

The output only changes when the new input value leaves the hysteresis band.

## Application Scenarios

- **Debouncing of Sensor Switches:** Turn-on and turn-off thresholds with hysteresis prevent edge noise.
- **Threshold Monitoring with Delayed Release:** Temperature, pressure, or level control with defined turn-on and turn-off points.
- **Digitization of Analog Signals:** Conversion of a continuous range of values into a stable binary value (Schmitt trigger behavior).
- **Control of actuators with hysteresis:** Prevents rapid on/off switching, e.g., with thermostats or pumps.

## Comparison with similar function blocks

| Function block | Properties |
|----------------------|----------------------------------------------------|
| **E_D_FF** | Standard D flip-flop without hysteresis (direct transfer). |
| **E_D_FF_ANY_HYS** | Identical function, but with direct data ports instead of adapters. |
| **Schmitt trigger** | Similar behavior, but hysteresis cannot be configured at runtime. |

The **ADI_D_FF_HYS** offers particularly flexible integration into heterogeneous systems thanks to its adapter interface, while the hysteresis can be configured at runtime.

## Conclusion

The **ADI_D_FF_HYS** is a robust, configurable D flip-flop with hysteresis, ideally suited for signal processing with stable switching thresholds. The use of unidirectional adapters facilitates integration into process-level control applications and enables a clear separation of data transport and event control.
