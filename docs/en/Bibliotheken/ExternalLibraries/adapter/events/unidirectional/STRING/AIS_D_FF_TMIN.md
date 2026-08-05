# AIS_D_FF_TMIN
![AIS_D_FF_TMIN](./AIS_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_D_FF_TMIN** implements a data-dependent flip-flop (D flip-flop) with a minimum inter-disposal time (MIT) between two consecutive output events (EOs). It latches an incoming data value via an AIS adapter and outputs it only when the minimum time specified by the parameter `Tmin` has elapsed since the last EO. This suppresses excessively rapid signal changes and ensures a defined signal delay.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|----------|------|-----------|
| `INIT` | EInit | Initialization Request (with `Tmin`) |

### **Event Outputs**

| Event | Type | Comment |
|----------|------|-----------|
| `INITO` | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Variable | Type | Comment |
|----------|------|-----------|
| `Tmin` | TIME | Minimum time interval between two EO events |

### **Data Outputs**
The FB has no data outputs of its own. Output is exclusively via the adapter plug (see below).

### **Adapter**

| Direction | Label | Adapter Type | Comment |
|----------|-------------|------------|-----------|
| **Plug** (Output) | `Q` | `adapter::types::unidirectional::AIS` | Latched output value |
| **Socket** (Input) | `I` | `adapter::types::unidirectional::AIS` | Input value to be latched |

The adapter `AIS` is unidirectional and delivers the actual signals via the event/data interfaces `E1` and `D1`.

## Functionality
Internally, the function block consists of a nested function block `E_D_FF_ANY_TMIN` (from the IEC 61499 library).

Processing proceeds as follows:

1. **Initialization**: Upon the event `INIT`, the parameter `Tmin` is forwarded to the internal function block, which is then initialized. Subsequently, `INITO` is triggered.

2. **Latch Operation**: An event `E1` arriving at **socket `I`** (connected to the internal `CLK`) transfers the simultaneously received data value `D1` (connected to `D`) into the flip-flop.

3. **Minimum Delay**: The internal function block checks whether at least the time `Tmin` has elapsed since the last output event (`EO`).

- If the condition is met, the latched data is output via the **plug `Q`** (event `E1` and data value `D1`).
- Otherwise, the value is held back until the required waiting time has elapsed.

This ensures that output events do not occur faster than specified by `Tmin`.

## Technical Features
- **Adaptor-based I/O**: The signals are not routed as separate input/output variables, but rather via standardized unidirectional AIS adapters. This allows for flexible interconnection with other components or subsystems.
- **Maintaining a minimum delay**: The delay prevents "noise" or excessively rapid signal changes, which can lead to malfunctions in time-critical systems.
- **Internal IEC 61499 Standard Function Block (FB)**: The implementation uses the library's own `E_D_FF_ANY_TMIN`, ensuring high reliability and reusability.

## State Overview
The FB itself does not have any explicitly modeled states in the XML definition. Its behavior is entirely determined by the internal FB `E_D_FF_ANY_TMIN`. This typically goes through the following phases (simplified):

- **Idle**: Waiting for a clock event at input `I.E1`.
- **Sampling**: Upon a clock event, the current data value `I.D1` is taken.
- **Delay**: After the takeover, the time elapsed since the last `EO` is compared to `Tmin`. If the time falls below the minimum, the system enters a wait state.
- **Output**: After the minimum time has elapsed, the latched data is output via `Q.E1` and `Q.D1`.

## Application Scenarios
- **Signal Smoothing**: Suppression of bounces or short pulses at digital inputs.
- **Cycle Control**: Ensuring that an output signal is updated only at a defined minimum interval (e.g., every 100 ms).
- **Interface Buffering**: Buffering values between system components with different speeds, while maintaining a minimum update rate.
- **Automation Technology**: Control of actuators that require mechanical dead times or minimum switching intervals.

## Comparison with Similar Function Blocks
- **Simple D Flip-Flop (without timing)**: A standard D flip-flop outputs the latched value immediately with the next clock event – without a delay limit. `AIS_D_FF_TMIN` adds the additional timing condition.
- **Monostable Flip-Flop**: A monostable function block generates a pulse of fixed duration; the function block described here, however, does not maintain a pulse duration but rather a minimum interval between outputs.
- **IEC-61499 `E_D_FF_ANY`**: This is the basic version without a time limit. `E_D_FF_ANY_TMIN` extends this variant with the `Tmin` parameter.

## Conclusion

The `AIS_D_FF_TMIN` offers a robust way to latch digital signals with an adjustable minimum output delay. Thanks to the use of AIS adapters and internal IEC 61499 standard components, it is both flexible and reliable. It is particularly suitable for automation tasks where rapid signal changes need to be suppressed or defined minimum pauses between output events must be maintained.
