# AL_D_FF_TMIN

![AL_D_FF_TMIN](./AL_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction

The AL_D_FF_TMIN function block implements an edge-triggered D flip-flop (data latch) with an adjustable minimum inter-disposal time. It receives a data value upon an incoming event, stores it, and outputs it—along with its own event—only after the specified minimum time has elapsed. This limits the output event rate.
## Interface Structure

### **Event Inputs**

- **INIT**: Initialization request; sets the parameter Tmin for the minimum time between output events.

### **Event Outputs**

- **INITO**: Confirmation of successful initialization.

### **Data Inputs**

- **Tmin** (TIME): Minimum time interval that must be maintained between two consecutive output events (EO).

### **Data Outputs**

- No direct data outputs – the latched values are transmitted exclusively via the output adapter Q.

### **Adapters**

- **I** (Socket, Type: `adapter::types::unidirectional::AL`): Input adapter for the value to be latched. The latch pulse is received via the event interface (E1), and the data value to be latched is provided via the data interface (D1).
- **Q** (Plug, Type: `adapter::types::unidirectional::AL`): Output adapter for the stored value. An event (E1) is sent and the currently stored data value (D1) is output for each successful latch operation.

## Functionality

The module internally uses the predefined flip-flop module `E_D_FF_ANY_TMIN`.

As soon as an event arrives at the input adapter (I.E1), the simultaneously present data value (I.D1) is received and stored internally. However, the output event (Q.E1) is only generated if at least the time interval specified by Tmin has elapsed since the last output event. Only then is the stored value passed on to the output adapter (Q.D1). Initialization with INIT sets the parameter Tmin and must be performed before first use.

## Technical Features

- **Minimum time between output events**: The delay Tmin limits the frequency of output events – useful for preventing bus overloads or limiting the actuator control rate.
- **Adapter Interfaces**: Coupling is achieved via standardized, unidirectional adapters (`adapter::types::unidirectional::AL`). This allows the function block to be flexibly integrated into various applications.
- **Edge-Triggered**: The internal flip-flop reacts to the rising edge of the event at the input adapter (I.E1).

## State Overview

The function block does not have an explicitly displayed state machine. Its behavior is determined by the internal D flip-flop with time control:

- After successful initialization (INIT → INITO), the function block waits for an event at the input adapter I.
- Upon an event, the incoming data value is latched. Immediately afterward, it is checked whether the time elapsed since the last output event has already exceeded Tmin.
- If yes: The output event is generated immediately.
- If no: The output is blocked until the waiting time has expired; then the output is generated.
- Events received during the wait time may be ignored or buffered (depending on the internal implementation of the underlying function block) – typically, only the most recent data value is considered for the next output.

## Application Scenarios

- **Synchronization of time-critical controllers** where data must not be updated more frequently than at a predefined interval.
- **Debouncing of signals** or throttling of event sequences in communication networks.
- **Simple state machines** that react to external events and must maintain a minimum response time (e.g., in automation technology or the control of physical actuators).

## Comparison with Similar Function Blocks

- **AL_D_FF**: A simple D flip-flop without a minimum time between output events – AL_D_FF_TMIN extends this with the Tmin control and adapter interfaces.

**AL_D_FF_TMIN** - **E_D_FF_ANY_TMIN**: The underlying generic flip-flop that can be used directly (without adapter encapsulation). AL_D_FF_TMIN encapsulates this in a plug-and-play adapter format.

- **R_TRIG / F_TRIG**: Detect rising and falling edges, respectively, but do not store data values and do not offer an adjustable output delay.

## Conclusion

The AL_D_FF_TMIN function block provides a reliable, edge-triggered D-latch function with an adjustable minimum time between output events. By using standardized adapter interfaces, it is easily integrated into IEC 61499 applications and is particularly suitable for applications that require limiting the event rate or time-controlled data release.
