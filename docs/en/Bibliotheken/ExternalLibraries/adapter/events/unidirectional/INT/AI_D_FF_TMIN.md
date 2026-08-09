# AI_D_FF_TMIN

![AI_D_FF_TMIN](./AI_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction

The function block **AI_D_FF_TMIN** implements a D flip-flop (data latch) with a minimum inter-disposal time between successive output events. It serves as an adapter-encapsulated component that receives an asynchronously incoming data value via a socket, temporarily stores it during an active event, and passes it on via a plug. Output is only released again when the configured minimum time \( T_{\text{min}} \) has elapsed since the last output.
## Interface Structure

### **Event Inputs**

| Name | Type | With Variable | Comment |
|-------------|-------|--------------|------------------------------------|
| `INIT` | EInit | `Tmin` | Initialization Request |

### **Event Outputs**

| Label | Type | With Variable | Comment |
|-------------|-------|--------------|-------------|---------------------------------------|
| `INITO` | EInit | – | Initialization Confirmation |

### **Data Inputs**

| Label | Type | Comment |
|-------------|------|----------------------------------------------|
| `Tmin` | TIME | Minimum time interval between two EO events |

### **Data Outputs**

This function block does not have its own data outputs; output is exclusively via the adapter `Q`.

### **Adapter**

| Name | Type (Adapter) | Direction | Comment |
|-------------|------------------------------------|-----------|------------------------------|
| `I` | `adapter::types::unidirectional::AI` | Socket | Input data for latching |
| `Q` | `adapter::types::unidirectional::AI` | Plug | Latched Output Value |

## Functionality

This function block encapsulates the internal function block `E_D_FF_ANY_TMIN`, which implements the actual D flip-flop with timing control. The interconnection is as follows:

- The initialization event `INIT` is passed to the internal function block along with the parameter `Tmin`.
- A data latch is triggered by an event on socket `I` (adapter event `I.E1`). This event serves as the clock signal (`CLK`) for the flip-flop.

- The current data value of `I.D1` is taken at each clock cycle and made available at the output of the internal function block.

- The internal function block generates an event at output `EO`, which is passed on via the adapter `Q` as `Q.E1`.
- There must be at least `EO` time between two consecutive events. If another clock cycle occurs during this lock time, the data value is latched, but the output is only released after the lock time has expired.
- The event `INITO` confirms the completion of the initialization process.

## Technical Features

- **Adapter Interface:** Input and output are handled via unidirectional adapters of type `AI`. These enable loose coupling and easy reuse of the function block in different environments.
- **Minimum Output Time:** The parameter `Tmin` allows for targeted limitation of the event rate at the output. This prevents downstream components from being overloaded by excessively rapid event sequences.
- **Initialization Required:** Before first use, the function block must be initialized via `INIT`, as the internal state is set and `Tmin` is adopted during this phase.

## State Overview

The function block does not have an explicitly visible state machine; the timing behavior is entirely controlled by the internal function block `E_D_FF_ANY_TMIN`. The function block essentially goes through the following phases:

1. **Initialization** – After receiving `INIT`, the internal function block is configured.
2. **Waiting for Clock** – The function block waits for an event at socket `I`.
3. **Latching** – Upon receiving a clock signal, the data value is acquired and an output event is generated.
4. **Lockout Phase** – After the output, any further output event is delayed for the duration of `Tmin`.
5. **Ready** – After the lockout period expires, another clock signal can be processed.

## Application Scenarios

- **Sensor Data Acquisition:** An asynchronously operating sensor provides measured values that should only be transmitted to a control system at a defined minimum interval (e.g., temperature measurement with debouncing).
- **Buffering of Time-Critical Signals:** In automation applications where downstream processing modules tolerate a limited event rate, this module is used as a "rate limiter."
- **Synchronization:** This module can be used to synchronize cyclic processes by limiting the maximum update rate of an output signal.

## Comparison with Similar Modules

| Module | Description | Difference to AI_D_FF_TMIN |
-----------------|------------------------------------------------|-------------------------------------------------|
| `E_D_FF` | Simple D flip-flop without a time limit | No minimum time between output events |
| `E_D_FF_ANY` | D flip-flop for arbitrary data types | Also without time control |
| `AI_D_FF` | D-Flip-Flop with Adapter Interface | Missing `Tmin` Option |
| `E_CYCLE` | Clock Generator with Adjustable Period | Generates Periodic Events, No Latch |

The `AI_D_FF_TMIN` combines the functionality of an adapter-encapsulated flip-flop with a freely configurable output lock – a combination not found in standard flip-flops.

## Conclusion

AI_D_FF_TMIN` offers a compact solution for buffering and time-controlled data transmission via adapter interfaces. The integrated minimum output time protects downstream components from overload and enables robust signal processing in industrial control systems. Thanks to its modular adapter interface, the component can be flexibly integrated into a wide variety of 4diac networks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
