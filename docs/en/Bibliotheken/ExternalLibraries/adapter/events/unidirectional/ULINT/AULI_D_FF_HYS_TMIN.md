# AULI_D_FF_HYS_TMIN

![AULI_D_FF_HYS_TMIN](./AULI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
The function block **AULI_D_FF_HYS_TMIN** implements a clock-edge-triggered D flip-flop (data latch) with hysteresis and a minimum dwell time between successive events. It is typically used to smooth noisy or fluctuating input signals and suppress unwanted rapid switching. The block communicates via standardized unidirectional adapters.

| Event | Type | Comment |
|----------|-----|-----------|
| `INIT` | `EInit` | Initialization request. Sets the parameters hysteresis and minimum time. |
| Event | Type | Comment |
|----------|-----|-----------|
| `INITO` | `EInit` | Confirmation of successful initialization. |
| Variable | Type | Comment |
|----------|-----|-----------|
| `HYSTERESIS` | `ULINT` | Hysteresis band as an unsigned integer. The output only changes its value when the input exceeds the band. |
| `Tmin` | `TIME` | Minimum time between two triggered events at the output. Prevents excessively fast switching. |

No direct data outputs. The latched information is provided via the `Q` adapter.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Adapter | Direction | Type | Comment |
|---------|----------|-----|-----------|
| `I` (Socket) | **Input** | `adapter::types::unidirectional::AULI` | Receiving adapter that provides the signal to be latched. Contains the event and data signals `E1` and `D1`. |
| `Q` (Plug) | **Output** | `adapter::types::unidirectional::AULI` | Output adapter that provides the currently held value. Signal `E1` indicates a value change, `D1` contains the value. |

## Functionality

The function block internally uses the function block `E_D_FF_ANY_HYS_TMIN`, which implements the actual logic. The operation is as follows:

1. **Initialization:** An event `INIT` transfers the parameters `HYSTERESIS` and `Tmin` into the internal function block.
3. **Hysteresis:** The new output value is only adopted if the difference between the current input `D1` and the last valid output exceeds the hysteresis value.
4. **Minimum Time:** After each adoption (output of an event on `Q.E1`), no further adoption is permitted for the duration `Tmin`.
5. **Output:** On a valid edge, the new value is output via `Q.D1`, and an event is generated on `Q.E1`.
- **Hysteresis:** Suppresses noise or small fluctuations at the input by defining a deadband. The output only changes in the case of significant deviations.
- **Minimum Dwell Time (`Tmin`):** Enforces a pause between successive output events. This ensures compliance with minimum switching times due to mechanical or system requirements.
- **Adapter Interface:** The use of a unidirectional adapter type enables loose coupling and reusability in different environments.
- **Internal Function Block:** The actual logic is outsourced to a typed function block, which improves testability and maintainability.

The function block does not have its own explicit states, but delegates to the internal function block. However, the essential behaviors can be described as follows:

| Phase | Description |
|-------|--------------|
| **Initial** | After power-on, `HYSTERESIS` and `Tmin` are not yet applied. A `INIT` event must set the parameters. |
| **Ready** | After successful initialization, the function block waits for clock events at input `I.E1`. |
| **Lock (Tmin active)** | After an output event, any further takeover is blocked for the duration `Tmin`. |
| **Takeover (on valid edge)** | If the hysteresis is exceeded and no lock is present, the current input value is adopted and output. |

- **Sensor Signal Debouncing:** A push button or proximity switch delivers a fluctuating signal. Hysteresis and a minimum time ensure a clean switching edge.
- **Data Logic with Signal Conditioning:** In automation technology, where a digital input value can be acquired but distorted by noise or bounce.
- **Time-Controlled Actuators:** If an actuator requires a minimum switching time (e.g., valves), `Tmin` prevents excessively fast actuation.

| Function Block | Properties |
|----------|---------------|
| **Simple D-FF** | No hysteresis, no delay – instantly responds to every clock edge. |
**D-FF with Hysteresis** | Contains only the hysteresis band, no time limit between outputs. |
**D-FF with Tmin** | Minimum dwell time only, without hysteresis – can still switch quickly in noisy environments. |
**AULI_D_FF_HYS_TMIN** | Combines hysteresis and minimum dwell time – more robust against noise and protects downstream components from excessively fast switching. |

The **AULI_D_FF_HYS_TMIN** offers a reliable combination of hysteresis and time limiting for clock-controlled signal takeovers. It is particularly suitable for industrial control systems where interference must be suppressed and actuators protected. The modular adapter interface facilitates integration into existing IEC 61499 applications.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion