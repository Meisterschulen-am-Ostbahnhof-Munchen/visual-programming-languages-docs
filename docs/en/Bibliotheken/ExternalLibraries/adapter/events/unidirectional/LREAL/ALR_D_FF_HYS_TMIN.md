# ALR_D_FF_HYS_TMIN

![ALR_D_FF_HYS_TMIN](./ALR_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Introduction

The function block **ALR_D_FF_HYS_TMIN** implements a clock-controlled D-latch (flip-flop) with adjustable hysteresis for data acquisition and a minimal time delay between successive output events. It processes an analog or Boolean value via an adapter input and outputs the buffered value via an adapter output. The hysteresis prevents unintended switching due to fluctuating input values, while the minimum time (Tmin) limits the event frequency at the output.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|----------|-------|----------------------------------|
| INIT | EInit | Initialization Request (sets hysteresis and Tmin) |

### **Event Outputs**

| Event | Type | Comment |
|----------|-------|-----------------------------------|
| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |
|------------|-------|-------------------------------------------------|
| HYSTERESIS | LREAL | Hysteresis band for data transfer |
| Tmin | TIME | Minimum time between two output events |

### **Data Outputs**

The FB does not have its own data outputs. The latched value is provided via the adapter output `Q`.

### **Adapter**

| Direction | Name | Type (unidirectional) | Comment |
|----------|------|----------------------|------------------------------------|
| Socket | I | ALR | Input value to be latched |
| Plug | Q | ALR | Output value (latched) |

## Functionality

The function block (FB) is implemented as a composite block that internally uses an FB of type `E_D_FF_ANY_HYS_TMIN` (from the library `logiBUS::signalprocessing::hysteresis`). The functionality in detail:

1. **Initialization (INIT)**: Upon the event `INIT`, the parameters `HYSTERESIS` and `Tmin` are passed to the internal FB. The internal FB is initialized and acknowledged with `INITO`.
2. **Data Transfer**: An event at the adapter input `I.E1` triggers the clock (`CLK`) of the internal flip-flop. Simultaneously, the data value `I.D1` is transferred as a new input `D`.
3. **Hysteresis**: The value is only transferred if the deviation from the currently latched value is greater than or equal to the set hysteresis. This prevents constant switching due to small fluctuations.
4. **Minimum Time (Tmin)**: After each output event (`EO`), a delay of `Tmin` is observed before another output event can be generated. Events arriving within this delay period are ignored.
5. **Output**: The latched value is provided via the adapter output `Q.D1`, and an event (`Q.E1`) signals the update.

## Technical Features

- **Hysteresis**: The function block operates with an adjustable hysteresis band. The actual implementation (whether symmetrical or with thresholds) depends on the internal function block. A Schmitt trigger characteristic is common.
- **Time-Controlled Output**: `Tmin` limits the maximum output frequency. This is useful for reducing the load on downstream components or ensuring a minimum signal duration.
- **Adapter Interface**: The use of adapters (`ALR`) enables loose coupling between the data value and the event – an event implicitly carries the corresponding data value.
- **Reusability**: The FB is built from a standardized hysteresis flip-flop and can be easily adapted to other data formats.

## State Overview

Since the function block consists of several internal states (e.g., waiting for clock signal, hysteresis check, waiting for minimum time), a simplified state description is given here:

1. **Initialized** (after INIT and INITO)
2. **Ready** – waits for an event at input `I.E1`
3. **Hysteresis Check** – compares the new value with the latched value
- If the hysteresis limit is exceeded: the new value is adopted, and the process transitions to **Waiting for Minimum Time**
- Otherwise: returns to **Ready** without output
4. **Waiting for Minimum Time** – after the minimum time has elapsed, the output event `Q.E1` is generated, and the latched value is displayed at `Q.D1`Output; then return to **Ready**

## Application Scenarios

- **Analog Switching Thresholds**: Monitoring of sensors (e.g., temperature, pressure) with adjustable hysteresis and a minimum switching pause to suppress bounce or noise.
- **Digital Signal Conditioning**: Processing of square wave signals with noise, where hysteresis stabilizes the edges and Tmin enforces a defined pulse duration.
- **Stepper Motor Control**: Latching of position values with hysteresis to counter mechanical vibrations, accompanied by time-debouncing of the output commands.
- **Safety-Critical Systems**: Minimum time between output changes prevents excessively rapid state transitions and protects subsequent actuators.

## Comparison with Similar Function Blocks

| Function Block | Properties | Difference to ALR_D_FF_HYS_TMIN |
-----------------------------------|---------------------------------------------------------------------|------------------------------------------------------------|
| Simple D flip-flop (D_FF) | No hysteresis, no timing | No signal stabilization or frequency limiting |
| Schmitt trigger (e.g., S_TRIG) | Hysteresis only, no timing, often only binary | Differs with analog values and forced pauses |
| Edge-triggered latch with dead time | Timing (dead time) present, but usually without hysteresis | Combination of both effects (hysteresis + Tmin) |
| Filter block (e.g., FILTER) | Noise reduction, e.g., as a low-pass filter, no discrete state change | Explicit latch with event output and adjustable hysteresis |

This block combines the advantages of hysteresis with a minimal event spacing function, making it particularly suitable for harsh industrial environments.

## Conclusion

The **ALR_D_FF_HYS_TMIN** is a robust, configurable function block for reliable signal processing with hysteresis and time-based debouncing. It is suitable for all applications requiring a soft threshold and limiting the output event frequency. The adapter-based interface facilitates integration into complex control architectures.
