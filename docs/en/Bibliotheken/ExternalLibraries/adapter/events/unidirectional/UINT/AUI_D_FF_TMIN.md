# AUI_D_FF_TMIN
![AUI_D_FF_TMIN](./AUI_D_FF_TMIN.svg)

* * * * * * * * * * *
## Introduction
The function block **AUI_D_FF_TMIN** implements a data-locking D flip-flop (data latch) with a minimum inter-disposal time between two consecutive output events. It serves to receive values via the unidirectional **AUI** adapter and pass them on with a defined minimum delay to prevent an excessively rapid sequence of events at the output.
## Interface Structure

### **Event Inputs**

| Event | Comment |

|----------|-----------|

| **INIT** | Initialization request; configures the block with the parameter `Tmin`. |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| **INITO** | Confirmation of successful initialization. |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| **Tmin** | TIME | Minimum time that must elapse between two output events (`EO`). |

### **Data Outputs**

*No direct data outputs – the output values are provided via the `Q` adapter.*

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| **Plug** (Output) | **Q** | `adapter::types::unidirectional::AUI` | Provides the locked data value (event and data line). |

| **Socket** (Input) | **I** | `adapter::types::unidirectional::AUI` | Receives the data value to be locked (event and data line). |

## Functionality

1. **Initialization**

The block is initialized via the event input `INIT`, and the minimum time is set via `Tmin`.

2. **Data Transfer**

Every event arriving at the adapter input `I` via the event line `I.E1` transfers the corresponding data value `I.D1` to the flip-flop. The transferred value is immediately stored internally.

3. **Output with Minimum Time Delay**

The stored value is only output as an event on `Q.E1` and as a data value on `Q.D1` if at least `Tmin` of time has elapsed since the last output event. If a new transfer event occurs before this time has elapsed, the new value is stored, and the output is further delayed until the minimum time has been met.

3. **Output with Minimum Time Delay**

The output of the stored value occurs only as an event on `Q.E1` and as a data value on `Q.D1` if at least `Tmin` of time has passed since the last output event. If a new transfer event occurs before this time has elapsed, the new value is stored, and the output is further delayed until the minimum time has been met.

`` 4. **State Protection**

The block behaves like an edge-triggered D flip-flop, where each valid clock cycle (event on `I.E1`) takes over the current data value, but the actual transmission is time-limited.

## Technical Features
- **Adapter-Based Input/Output** – The block uses only the standardized unidirectional **AUI** adapter. This makes it easy to integrate into existing adapter-oriented architectures.
- **Reuse of Basic Components** – Internally, the IEC 61499 component `E_D_FF_ANY_TMIN` is used, which implements the time-limited throttling. This block encapsulates it and simplifies connection via adapters.
- **No Dedicated State Machines** – The behavior is entirely determined by the internal component; The outer function block is purely configurable and connective.

## State Overview

The function block does not have an externally visible state machine (ECC). Internally, the used `E_D_FF_ANY_TMIN` can have the following implicit states:

| State | Description |

|---------|--------------|

| **Idle** | Waiting for an event at input `I`. |

| **Timed** | Data has been received; output is held back until `Tmin` expires. |

| **Output** | Minimum time has been met – output event is sent. |

These states are transparent to the user.

## Application Scenarios
- **Sensor Value Smoothing** – Prevents a sensor that delivers measurements at short intervals from flooding the subsequent processing block with events.
- **Actuator Control with Minimum Switching Time** – Ensures that an actuator (e.g., a valve) can only be switched after a defined minimum pause to reduce wear.
- **Data Flow Limiting in Communication Lines** – Throttles the output rate of a data stream to prevent overloading the receiver.

## Comparison with Similar Components

| Component | Feature |

|----------|---------|

| **E_D_FF** (Standard D Flip-Flop) | No time limit; each event is output immediately. |

| **E_D_FF_ANY_TMIN** | Same behavior, but without adapter encapsulation; Direct event-/data-based connection. |

**AUI_D_FF_TMIN** (this block) | Combines D flip-flop functionality with time-based throttling and provides an adapter-based interface. |

## Conclusion

The **AUI_D_FF_TMIN** is a useful function block when data needs to be passed at time-controlled intervals. It simplifies the implementation of throttling logic in adapter-based IEC 61499 systems and is particularly suitable for applications in agricultural engineering and other time-critical control environments.
