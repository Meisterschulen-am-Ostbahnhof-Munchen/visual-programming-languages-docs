# AR_D_FF_HYS_TMIN
![AR_D_FF_HYS_TMIN](./AR_D_FF_HYS_TMIN.svg)
* * * * * * * * * *
## Introduction
The **AR_D_FF_HYS_TMIN** function block implements a data latch (D flip-flop) with a hysteresis function and a minimal delay between successive output events at the output adapter. It serves for the stable acquisition and transmission of analog values via unidirectional AR adapters, suppressing edge noise and limiting the output frequency.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-------|--------------|

| INIT | EInit | Initialization request; passes the parameters HYSTERESIS and Tmin to the internal logic. |

### **Event Outputs**

| Event | Type | Description |

|----------|-------|--------------|

| INITO | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Variable | Type | Description |

|-------------|------|--------------|

| HYSTERESIS | REAL | Hysteresis band: A change in the input value must exceed this amount for a new value to be latched. |

| Tmin | TIME | Minimum time between two output events (inter-disposal time). Prevents overly rapid switching. |

### **Data Outputs**
The FB does not have its own data outputs; the output data is provided via the **Q** adapter.

### **Adapter**

| Name | Type | Direction | Description |

|-------------|-------------------------------------------------|----------|--------------|

| **I** | adapter::types::unidirectional::AR (Socket) | Input | Provides the value to be latched via **I.D1** and the clock signal via **I.E1**. |

| **Q** | adapter::types::unidirectional::AR (Plug) | Output | Provides the latched value via **Q.D1** and signals an update via **Q.E1**. |

## Functionality

The function block works internally with a sub-function block of type `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`.

1. **Initialization**: During the **INIT** event, the parameters **HYSTERESIS** and **Tmin** are passed to the internal logic. After successful initialization, **INITO** is output.

2. **Data Acquisition**: At each clock event on adapter **I.E1**, the currently present value **I.D1** is compared with the last stored value.

- A change is only made if the absolute difference between **I.D1** and the stored value is greater than **HYSTERESIS**.
- If the difference is smaller, the old value remains unchanged (hysteresis function).

3. **Time-Limited Output**: As soon as the new value has been acquired, the output signal **Q.D1** is updated. However, the corresponding event **Q.E1** is only sent if at least the time interval **Tmin** has elapsed since the last **Q.E1**. This limits the maximum output frequency.

- A change is only made if the time interval **Tmin** has elapsed since the last **Q.E1**. The entire behavior can be viewed as a clock-controlled, hysteresis-enabled signal-hold block with output blocking.

## Technical Features
- **Hysteresis**: Suppresses noise and small fluctuations in the input signal. A new state is only assumed when the change exceeds the **HYSTERESIS** value.
- **Minimum Interval Time (Tmin)**: Prevents an excessively high event rate at the output. This is particularly advantageous for downstream, computationally intensive, or communication-limited systems.
- **Adapter-Based Interfaces**: Both input and output use the unidirectional AR adapter, which combines data and events. This simplifies the modular chaining of signal processing blocks.

## State Overview

The function block (FB) does not have an explicit finite state machine (FSM) at the top level, as the state logic is encapsulated in the internal sub-FB. The logical behavior, however, corresponds to a D flip-flop with extended conditions:

- **Idle State**: Waiting for the next clock cycle (I.E1).
- **Check State**: Comparison of the new value with the stored value, taking hysteresis into account.
- **Output State**: Update of **Q.D1** and, if **Tmin** has expired, send of **Q.E1**.

A graphical state machine can be derived from the internal sub-FB if required.

## Application Scenarios
- **Measurement Acquisition with Noise Suppression**: Smoothing of sensor signals (e.g., temperature, pressure) and transmission only when significant changes occur.
- **Time-Controlled Process Outputs**: Control of actuators that must not be driven faster than a predefined clock frequency.
- **Signal Conditioning in Fieldbus Systems**: Reduction of bus load by limiting the event rate without information loss due to hysteresis.
- **Cascading Flip-Flops**: Used as a stabilized intermediate stage in data chains with multiple sampling stages.

## Comparison with Similar Components
- **Simple D Flip-Flop (e.g., E_D_FF)**: Has neither hysteresis nor an output time limit. Changes its output on every clock cycle, regardless of the change magnitude or frequency.
- **Hysteresis Flip-Flop (e.g., E_D_FF_HYS)**: Includes hysteresis but no minimum interval time. Events can follow each other very quickly if the hysteresis is constantly exceeded.
- **Limited-Time Flip-Flop (No Hysteresis)**: Only the minimum output time is observed; small value changes are still processed immediately, which can lead to oscillations.

The **AR_D_FF_HYS_TMIN** combines both mechanisms, thus offering a robust solution for practical measurement and control tasks.

## Conclusion

The **AR_D_FF_HYS_TMIN** function block is a versatile tool for reliable signal routing in automation systems. By combining hysteresis and minimal inter-disposal time, typical problems such as noise, flicker, and overload of downstream processing stages are effectively avoided. The adapter-based interface facilitates integration into existing modular architectures.