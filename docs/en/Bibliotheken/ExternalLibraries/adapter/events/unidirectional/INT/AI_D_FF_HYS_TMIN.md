# AI_D_FF_HYS_TMIN
![AI_D_FF_HYS_TMIN](./AI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AI_D_FF_HYS_TMIN** implements a data latch (D flip-flop) with a hysteresis band and a minimum time between successive event outputs. It serves as a robust signal processing component that suppresses noise and fast edge transitions and only passes on stable state changes.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|----------|-----|-----------|
| INIT | EInit | Initialization Request (sets hysteresis band and Tmin) |

### **Event Outputs**

| Event | Type | Comment |
|----------|-----|-----------|
| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Variable | Type | Comment |
|--------------|-------|-----------|
| HYSTERESIS | INT | Hysteresis Band (value in the same unit as the input signal) |
| Tmin | TIME | Minimum time between two event outputs (E1 on the Q adapter) |

### **Data Outputs**

This function block does not have its own data outputs. The latched value is provided via the output adapter **Q**.

### **Adapters**

| Adapter | Type | Comment |
|---------|-----|-----------|
| **I** | adapter::types::unidirectional::AI | Input adapter: provides the signal to be processed (via event E1 and data D1) |
| **Q** | adapter::types::unidirectional::AI | Output adapter: outputs the latched value (via event E1 and data D1) |

## Functionality
The function block internally uses the subroutine **E_D_FF_ANY_HYS_TMIN** from the *logiBUS::signalprocessing::hysteresis* library. Overview of its functionality:

1. **Initialization**

The parameters `HYSTERESIS` and `Tmin` are received via the **INIT** event input. After successful initialization, **INITO** is sent.

2. **Signal Processing**

- A new value is received via the **I** adapter (event **E1** with the corresponding data value **D1**).
- The function block compares the new value with the currently stored (latched) value, taking the hysteresis band into account:
- A change is only accepted if the difference between the new value and the old value is greater than `HYSTERESIS`.
- Additionally, the time elapsed since the last event output must be at least `Tmin`. Only when both conditions are met is the new value accepted and output via the **Q** adapter (event **E1** and data **D1**).

3. **Output**

The currently valid latched value is provided via the **Q** adapter. An event is sent to **Q.E1** for every valid state change.

## Technical Features
- **Hysteresis** – Suppresses noise and rapid fluctuations by only accepting a change if it exceeds the hysteresis band.
- **Minimum Time Between Events (Tmin)** – Prevents overly frequent outputs (e.g., due to high-frequency signals or bouncing). Events are only released after a period of `Tmin` has elapsed since the last event.
- **Adapter-Based Interface** – Input and output are handled via unidirectional adapters, allowing for flexible integration with other components.

## State Overview
The component does not have explicitly named states. The internal flip-flop operates as a bistable element with two stable states (high/low or the last valid value). State transitions are controlled by the hysteresis and timing conditions.

## Application Scenarios
- **Sensor Value Debouncing** – Smoothing of analog or digital input signals (e.g., temperature, pressure, level) when thresholds are exceeded.
- **Noise Peak Filtering** – Prevention of false triggers caused by short-term disturbances.
- **Time-controlled signal monitoring** – When changes should only be reported at specific intervals (e.g., for logging or update rates).
- **Interface decoupling** – Used as a stabilized intermediate between a fast signal transmitter and a slow-moving actuator.

## Comparison with similar components

| Component | Key difference |
|----------|--------------------------|
| **E_D_FF** (simple D flip-flop) | No hysteresis band, no minimum time – accepts every change immediately. |
| **AI_D_FF_HYS** (without Tmin) | Includes hysteresis, but no time limit for the output. |
| **AI_D_FF_TMIN** (without hysteresis) | Includes only the minimum time, but no hysteresis. |
| **AI_D_FF_HYS_TMIN** (this one) | Combines both filters: hysteresis and time limiting. |

## Conclusion
The **AI_D_FF_HYS_TMIN** is a versatile function block for robust signal conditioning. Its combination of hysteresis and minimum interval makes it ideal for applications requiring both noise-resistant and time-controlled state changes. The adapter-based interface facilitates integration into modular automation systems.
