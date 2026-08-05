# AQ_D_FF_TMIN
![AQ_D_FF_TMIN](./AQ_D_FF_TMIN.svg)
* * * * * * * * * *
## Introduction
The function block **AQ_D_FF_TMIN** implements a data-locking D flip-flop with a minimum inter-disposal time (MIT) between two consecutive output events (EOs). It serves as an extension of a simple D flip-flop, adding time-based debouncing or minimum-distance control, and is connected to the signal transmitter and receiver via adapters.
## Interface Structure

### **Event Inputs**

| Event | Type | With Variable | Comment |

|----------|-----|--------------|-----------|

| INIT | EInit | Tmin | Initialization request, sets the minimum MIT. |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|-----------|

| INITO | EInit | Initialization confirmation. |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| Tmin | TIME | Minimum waiting time between two output events (EO). |

### **Data Outputs**

No dedicated data outputs; the latched signal is output via the adapter `Q`.

### **Adapters**

| Type | Label | Direction | Comment |

### **Adapters**

| Type | Label | Direction | Comment |

### |-----|-------------|----------|-----------|

| `adapter::types::unidirectional::AQ` | I | Socket (Input) | Latching value, containing one data signal (D1) and one event signal (E1). |

| `adapter::types::unidirectional::AQ` | Q | Plug (Output) | Latched value, containing one data signal (D1) and one event signal (E1). |

## Functionality

This function block encapsulates an internal function block of type `iec61499::events::E_D_FF_ANY_TMIN`. This functions like an edge-triggered D flip-flop, where the event `I.E1` serves as the clock signal and `I.D1` as the data input. The output event `EO` is only output at adapter `Q.E1` if at least the time specified in `Tmin` has elapsed since the last output event. The data value at output `Q.D1` corresponds to the value `I.D1` present at the time of the rising edge at `I.E1`.

The initialization (`INIT`) passes the parameter `Tmin` to the internal function block, thus defining the timing condition.

## Technical Features
- **Minimum Interval Time (Tmin):** Prevents excessively rapid succession of output events, e.g., for debouncing or limiting the update rate.

``` - **Adapter-Based Communication:** The function block (FB) uses unidirectional adapters (`AQ`) that bundle both data and events, enabling loose coupling between the signal source and sink.

- **IEC 61499-Compliant:** Complies with the 61499-1 Annex A standard and utilizes the event/data flows of the standard.

## State Overview

The FB does not have an explicit public state machine. Its behavior is determined by the internal FB `E_D_FF_ANY_TMIN`, which has the last latched value as its state and a wait logic. Simplified representation:

| State | Meaning |

|---------|-----------|

| Initialized | Ready after INIT, Tmin is set |

| Ready | Waiting for clock (I.E1) |

| Latched | Data value has been accepted; output event will be released after Tmin has elapsed |

| Waiting | Tmin is running – output event is blocked |

A detailed state representation can be found in the source code of the internal function block.

## Application Scenarios
- **Signal Smoothing/Debouncing:** Preventing multiple triggers with mechanical pushbuttons or rapid signal changes.
- **Data Rate Limiting:** Limiting the output frequency of measured values in monitoring systems.
- **Synchronization of Asynchronous Signals:** Forwarding a data value with a defined minimum time interval.
- **Control of Slow Actuators:** Ensuring that actuators are not controlled faster than their mechanical response time allows.

## Comparison with Similar Function Blocks

| Function Block | Special Feature |

|----------|--------------|

| `AQ_D_FF` / `E_D_FF` | Simple D flip-flop without a time limit on the output. |

`AQ_D_FF_TMIN` (this FB) | Extended by a minimum delay Tmin between output events. |

`AQ_D_FF_TMAX` (hypothetical) | Limits the maximum time between two output events. |

Compared to a standard D flip-flop, `AQ_D_FF_TMIN` offers additional protection against excessively rapid succession of output events, which is often necessary in practice.

## Conclusion

The function block `AQ_D_FF_TMIN` combines the functionality of a D flip-flop with an adjustable minimum delay at the output. Thanks to its adapter interfaces and IEC 61499 compliance, it can be easily integrated into industrial control applications where both data acquisition and temporal decoupling of events are required. It offers a robust solution for signal processing and actuator control with defined temporal constraints.