# ALR_D_FF_TMIN
![ALR_D_FF_TMIN](./ALR_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_D_FF_TMIN** implements a clock-edge-triggered data latch flip-flop (D flip-flop) with a minimum inter-disposal time (MIT) between two consecutive event outputs. It enables the latching of a data value upon receiving an event and ensures that the output event pulse does not occur faster than a definable time interval. This is particularly useful for protecting downstream systems from overload or for maintaining minimum time intervals in event communication.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |
|----------|-------|----------------------------------------------------|
| INIT | EInit | Initialization Request; Sets the minimum time `Tmin` |

### **Event Outputs**

| Event | Type | Comment |
|----------|-------|------------------------------------------|
| INITO | EInit | Confirmation of successful initialization |

### **Data Inputs**

| Name | Type | Comment |
|------|------|---------------------------------------------|
| Tmin | TIME | Minimum wait time between two EO events |

### **Data Outputs**

*No dedicated data outputs available – the latched value is provided via the adapter output.*

### **Adapter**

| Adapter | Direction | Type | Comment |
| Adapter | Direction | Type | Comment |
| Adapter | Direction | Type | Comment |
| Tmin | TIME | Minimum wait time between two EO events |

### **Data Outputs**

### **Adapter**

| Adapter | Direction | Type | Comment |
| Adapter | | ... |---------|----------|-------------|-----------------------------------|
| I | Socket | ALR (unidirectional) | Input value (`D1`) and clock (`E1`) |
| Q | Plug | ALR (unidirectional) | Output value (`D1`) and acknowledgement (`E1`) |

The unidirectional adapter `ALR` has an event input `E1` and a data input `D1` (socket side) and an event output `E1` and a data output `D1` (plug side). The exact semantics of `E1` and `D1` are application-specific; here, `E1` serves as the clock signal and `D1` as the data value to be latched.

## Functionality
After initialization (INIT), the function block operates as follows:

1. An **event at the input adapter `I.E1`** triggers the latch operation. The current value `I.D1` is internally adopted.

2. The latched value is immediately output at the output adapter `Q.D1`.

3. Simultaneously, an event `Q.E1` is triggered – but only after at least `Tmin` has elapsed since the last output event.

If another `I.E1` event arrives within the waiting time, it is ignored (or processed only after `Tmin` has elapsed). The minimum delay is implemented by the internal function block `E_D_FF_ANY_TMIN`.

The data value is updated on every valid clock cycle, but the event output is delayed.

## Technical Features
- **Composite Function Block**: The function block is implemented as a composite function block and internally uses the function block `iec61499::events::E_D_FF_ANY_TMIN`. The logic of the actual flip-flop and the timing control are encapsulated there.
- **Universal Time Interval**: `Tmin` can be set at runtime via INIT and is not fixed.
- **Buffered Events**: Since the event output is delayed, incoming clock events can be lost during the waiting period unless the internal function block buffers them (not specified here). Typically, they are simply ignored.
- **Adapter-based interface**: The use of adapters enables flexible interconnection in modular control applications without the need for hardwiring.

## State overview

The function block does not have explicit states but operates event-driven:

- **Idle**: Waiting for `I.E1` (after INIT).
- **Latching**: The data value is transferred upon `I.E1`, and `Q.E1` is triggered after `Tmin` has expired.
- **Blocked**: While `Tmin` has not yet expired, further `I.E1` are ignored.
- After the waiting period expires, the function block returns to the idle state.

## Application Scenarios
- **Sensor Signal Debouncing**: A sensor delivers events faster than the subsequent controller can process them. `Tmin` defines the minimum interval.
- **Pulse Width Limiting**: Ensures that actuator controls are not switched too quickly in succession (e.g., valves, motors).
- **Clock Synchronization**: When a data value is latched with an asynchronous clock and only passed on after a defined dead time.
- **Safety Functions**: Prevents "rapid-fire" commands in critical applications.

## Comparison with Similar Function Blocks
- **E_D_FF_ANY_TMIN**: This is the internal function block – it offers the same functionality, but without the adapter interface. `ALR_D_FF_TMIN` encapsulates this in a more user-friendly, adapter-based form.
- **Standard IEC 61499 D flip-flops**: These often lack time-based control of output events. The function block described here extends this functionality with the `Tmin` delay.
- **Function block with TON/Timer**: A simple timer would only trigger after a delay but would not hold a data value. The combination with a latch is specific.

## Conclusion
The function block `ALR_D_FF_TMIN` combines the features of a D flip-flop with an adjustable minimum time between event outputs. Thanks to its adapter technology and simple initialization, it can be flexibly deployed in IoT, automation, or control environments. It is particularly suitable for applications that require temporal decoupling between data acquisition and event transmission.
