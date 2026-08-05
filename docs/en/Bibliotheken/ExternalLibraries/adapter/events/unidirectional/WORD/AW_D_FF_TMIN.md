# AW_D_FF_TMIN
(Image of the function block – not included in the XML, therefore no image)
![AW_D_FF_TMIN](./AW_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The **AW_D_FF_TMIN** is a composed IEC 61499 function block (a type of data latch flip-flop) that receives an incoming data value on an adapter, takes over upon an event, and passes it on to an output adapter with a minimal delay between two consecutive output events. It serves as a reliable buffer, extending the output events to a minimum time defined by the parameter `Tmin`.

## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|-------|-----------|

| `INIT` | EInit | Initialization request; sets the minimum inter-event time `Tmin`. |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|-----------|

| `INITO` | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Data | Type | Comment |

|-------|-------|-----------|

| `Tmin` | TIME | Minimum time (e.g., `T#100ms`) that must elapse between two consecutive output events (`Q.E1`). |

### **Data Outputs**

The function block (FB) has no direct data outputs; the latching value is provided via the adapter `Q`.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| `Socket` | `I` | `adapter::types::unidirectional::AW` | Value to be latched (input adapter). Contains the event and data interfaces `I.E1` and `I.D1`. |

| `Plug` | `Q` | `adapter::types::unidirectional::AW` | Latched value (output adapter). Contains the event and data interfaces `Q.E1` and `Q.D1`. |

## Functionality

The **AW_D_FF_TMIN** encapsulates the IEC 61499 standard function block `E_D_FF_ANY_TMIN`. The operation is as follows:

1. **Initialization**

The parameter `Tmin` is passed to the inner function block via the event input `INIT`. After successful initialization, `INITO` is output.

2. **Data Latching**

When an event arrives at the adapter input `I.E1`, the data value simultaneously present at `I.D1` is adopted (edge-triggered D flip-flop).

3. **Output with Minimum Time**

The latched value is output at the adapter output `Q.D1`. Simultaneously, an event is generated on `Q.E1` – but only if at least the time `Tmin` has elapsed since the last event on `Q.E1`. This ensures that the output events do not follow each other faster than allowed by `Tmin`.

4. **Further Cycles**

Each new event on `I.E1` repeats the latching and the timed output.

## Technical Features
- The function block is specified according to IEC 61499-1 Annex A and uses the adapter type definition `adapter::types::unidirectional::AW`.
- The implementation is based on the reproducible function block `E_D_FF_ANY_TMIN`, which provides the actual latch and timing logic.
- The minimum inter-event time `Tmin` is set at runtime via `INIT` and cannot be changed during operation.
- The function block is released under the Eclipse Public License 2.0 (EPL-2.0), version 1.0 (2026-05-15, HR Agrartechnik GmbH).

## State Overview

The internal function block `E_D_FF_ANY_TMIN` has an implicit state machine:

- **Initialization State**: The configuration is applied after `INIT`; Upon success, `INITO` is sent.
- **Operating State**: After initialization, the function block waits for events at `I.E1`. With each event, the data value is latched, timer monitoring is started, and output is only released if the minimum time `Tmin` has elapsed since the last output event.
- **Wait State**: If an output event cannot yet be released (because the time since the last event is less than `Tmin`), the latched value is held until the required delay has elapsed. Only then is `Q.E1` triggered.

## Application Scenarios
- **Signal Debouncing**: Prevents mechanical or communication-related bounces from affecting a downstream process in rapid succession.
- **Clock Control with Minimum Pulse Duration**: Ensures that subsequent components have a minimum time between processing steps.
- **Data Stream Synchronization**: Bufferes a data value and passes it on with a defined minimum delay to smooth jitter.

## Comparison with Similar Components

| Component | Feature | Difference |

|----------|-------------|-------------|

| `E_D_FF` | Simple D flip-flop without a time limit | No control over the maximum output frequency. |

| `SR_FF` | Set-Reset flip-flop | No edge-triggered data transfer. |

| `E_D_FF_ANY_TMIN` (direct) | Like AW_D_FF_TMIN, but a pure event/data function block | Does not have an adapter interface; the variant with an adapter increases interchangeability and encapsulation in pluggable components. |

## Conclusion

The **AW_D_FF_TMIN** is a maintenance-friendly, adapter-based D-latch function block that combines the acquisition of a data value with a configurable minimum time between output events. By using a standardized adapter type, it can be easily integrated into hierarchical modules and offers a robust solution for time-critical signal chains in IEC 61499 systems.
