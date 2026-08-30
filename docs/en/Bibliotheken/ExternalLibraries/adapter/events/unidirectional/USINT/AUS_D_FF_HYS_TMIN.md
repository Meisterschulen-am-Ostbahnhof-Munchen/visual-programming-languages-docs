# AUS_D_FF_HYS_TMIN

![AUS_D_FF_HYS_TMIN](./AUS_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **AUS_D_FF_HYS_TMIN** implements a data-triggered flip-flop (D flip-flop) with hysteresis and a minimum inter-event time. It is structured as a sub-application (FB network) that delegates the actual logic to the inner block `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`. This block serves to latch an analog or discrete value with a predefined hysteresis band and simultaneously limit the event rate (via the adapter input) to a configurable minimum interval.

## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Description |
|----------|-------|-----------------------|---------------------------------------------------|
| `INIT` | EInit | `HYSTERESIS`, `Tmin` | Initialization request; sets hysteresis and minimum time. |

### **Event Outputs**

| Event | Type | With Variables | Description |
|----------|-------|----------------|------------------------------------------------|
| `INITO` | EInit | – | Confirmation of completed initialization. |

### **Data Inputs**

| Name | Type | Description |
| -------------- | ---------- | ------------------------------------------------------------------ |
| `HYSTERESIS` | ANY_NUM | Hysteresis band – Threshold difference that must be exceeded/fallen below for a new value to be latched. |
| `Tmin` | TIME | Minimum time interval between two incoming events (inter-arrival time). |

### **Data Outputs**

– No direct data outputs are available. The latched value is output via the adapter plug `Q`.

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ------------- | -------------------------------------- | --------------------------------------------------------------------------- |
| `I` | Socket (In) | `adapter::types::unidirectional::AUS` | Receives the event to be latched and the corresponding data value. |
| `Q` | Plug (Out) | `adapter::types::unidirectional::AUS` | Outputs the processed event and the latched data value. |

## Functionality

This function block operates as a pure encapsulation of an internal flip-flop. After starting, `INIT` must first be called with the parameters `HYSTERESIS` and `Tmin`. Afterwards, events (via `I.E1`) and associated data values (via `I.D1`) can be received via the adapter socket `I`.

- Each event at input `I.E1` is forwarded to the internal function block `E_D_FF_ANY_HYS_TMIN`.
- The data `I.D1` is compared with the hysteresis band: The flip-flop is only updated if the new value lies outside the deadband defined by the hysteresis around the last latched value.
- Additionally, the time since the last valid event is monitored (`Tmin`). If an event occurs too soon (shorter than `Tmin`) after the previous one, it is ignored.
- A valid, latched event is output via the adapter plug `Q` as `Q.E1`, and the corresponding data value as `Q.D1`.

The internal function block handles all the logic; the outer block serves as an interface wrapper that connects the events and data accordingly.

## Technical Features

- **Adapter Interface:** Communication takes place via the unidirectional adapters `adapter::types::unidirectional::AUS`. This enables a clear separation of event and data flow and easy reuse in different contexts.
- **Hysteresis:** Prevents constant switching due to noisy signals. The latched value only changes when the input leaves the hysteresis band.
- **Minimum Inter-Event Time (`Tmin`):** Debounces events and prevents bursts. Only events with a minimum interval of `Tmin` are accepted.
- **Compact Encapsulation:** The function block (FB) contains no independent behavior but forms a logical unit comprising initialization, event processing, and output – ideal for modular control architectures.

## State Overview

Since the function block does not have its own state diagram (the logic resides within the internal FB), the state behavior results from the interaction of event control and the parameters:

1. **Initialization (`INIT` – `INITO`)**: After startup, the internal FB is configured. Only then can events be processed.
2. **Waiting for Incoming Event**: The function block is passive until an event arrives via `I.E1`.
3. **Event Check** (internal):

- Time Check: Is the interval to the last event ≥ `Tmin`?
- Hysteresis Check: Does the new value exceed the old value by more than `HYSTERESIS`?
1. **Output**: If the check is successful, `Q.E1` is triggered and the new data value is passed to `Q.D1`.
2. **Return to Waiting State**.

## Application Scenarios

- **Sensor Evaluation with Noise:** An analog value (e.g., temperature, pressure) should only trigger a switching operation if it shows a significant change (hysteresis) and does not occur too rapidly (debouncing).
- **Frequency Limiting:** In communication protocols where an event must not be processed more frequently than a certain rate.
- **Safety-Critical Applications:** Preventing false triggers caused by short-duration interference pulses (minimum time between two edges).

## Comparison with Similar Components

| Component | Properties |
| ------------------------------ | ------------------------------------------------------------------------------- |
| Standard D Flip-Flop | Latches on every rising edge without hysteresis or time limit. |
| `E_D_FF_HYS` (without Tmin) | Hysteresis only, no time debouncing. |
| E_D_FF_TMIN` (without Hys) | Minimum time only, no hysteresis. |
| AUS_D_FF_HYS_TMIN` | Combines hysteresis **and** minimum time – more robust against noise and bursts. |

This component is therefore particularly suitable when both effects (signal tolerance and time limiting) are required simultaneously.

## Conclusion

AUS_D_FF_HYS_TMIN`This is a specialized D-flip-flop wrapper that offers reliable, debounced data latching through a combination of hysteresis and minimal event interval time. Its encapsulation as a sub-application with adapter interfaces makes it easy to integrate into larger control networks. Initialization via `INIT` ensures a defined startup configuration. This component is an ideal solution for applications requiring robust threshold detection with noise suppression and frequency limiting.
