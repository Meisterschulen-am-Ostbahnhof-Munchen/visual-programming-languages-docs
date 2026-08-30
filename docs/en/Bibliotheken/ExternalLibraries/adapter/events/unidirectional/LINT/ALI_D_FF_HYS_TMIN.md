# ALI_D_FF_HYS_TMIN

![ALI_D_FF_HYS_TMIN](./ALI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **ALI_D_FF_HYS_TMIN** implements a data-driven D flip-flop with an adjustable hysteresis width (threshold band) and a minimum waiting time between two consecutive output events. It is used for debouncing and stabilizing signal transitions in industrial automation, particularly when a signal should only be considered valid after it has left a defined tolerance range and a minimum time has elapsed since the last valid edge.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|-------|-----------|
| INIT | EInit | Initialization request – sets the hysteresis width and the minimum time. |

### **Event Outputs**

| Name | Type | Comment |
|-------|-------|-----------|
| INITO | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Name | Type | Comment |
| ------------ | ------ | ----------- |
| HYSTERESIS | LINT | Hysteresis band as an integer value (LINT). |
| Tmin | TIME | Minimum time between two output events (Inter-Disposal Time). |

### **Data Outputs**

*No direct data outputs available.*

The function block outputs its status via the adapter **Q** (see Adapters).

### **Adapters**

| Type | Name | Direction | Comment |
| `adapter::types::unidirectional::ALI` | I | Socket | Input adapter – provides the signal to be received (event and data value). |
| `adapter::types::unidirectional::ALI` | Q | Plug | Output adapter – outputs the last valid data value and an event. |

The adapter type `ALI` includes an event (E1) and a data value (D1) and is used for unidirectional communication between function blocks.

## Functionality

The function block **ALI_D_FF_HYS_TMIN** is implemented as a composition and internally uses the function block `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`. Its operation can be described as follows:

1. **Initialization** – The **INIT** event sets the **HYSTERESIS** and **Tmin** parameters. After successful initialization, **INITO** is triggered.
2. **Signal Acquisition** – Every event at socket **I** (event **I.E1**) is interpreted as a clock edge. The corresponding data value **I.D1** is only transferred to internal memory if it is outside the hysteresis band around the currently stored value (i.e., the change exceeds the hysteresis).
3. **Minimum Time Control** – After a valid value is acquired, output via plug **Q** (event **Q.E1** and value **Q.D1**) is only enabled after at least **Tmin** has elapsed since the last output event. This suppresses unwanted rapid signal changes.
4. **Signal Acquisition** – After a valid value is acquired, output via plug **Q** (event **Q.E1** and value **Q.D1**) is only enabled after at least **Tmin** has elapsed since the last output event. This suppresses unwanted rapid signal changes.

5. **Output** – Once the minimum time has elapsed, the new value is output via the output adapter **Q**. The function block then waits for the next input event.

## Technical Features

- **Hysteresis Data Width** – The hysteresis is defined as a LINT (64-bit integer); this allows for the processing of very large value ranges.
- **Time Parameters** – The minimum inter-disposal time **Tmin** is specified as IEC-61499-`TIME` (e.g., `T#10ms`).
- **Adapter-Based Coupling** – The use of the adapters `ALI` allows loose coupling between signal-generating and signal-processing function blocks. The socket **I** receives the data, and the plug **Q** provides it.
- **Type of Dependency** – The function block is based on the internal FB `E_D_FF_ANY_HYS_TMIN`, which implements the actual hysteresis and timing logic. The outer function block merely encapsulates the adapter interface.

## State Overview

The function block goes through the following states:

1. **INIT** – Waiting for initialization parameters.
2. **IDLE** – Ready; waiting for an event on socket **I**.
3. **SAMPLE** – An event has arrived; the data value is checked for exceeding the hysteresis.

- *Hysteresis violated:* The value is ignored, returning to **IDLE**.
- *Hysteresis satisfied:* Transition to state **WAIT_TMIN**.
1. **WAIT_TMIN** – The new value is saved; release is delayed by **Tmin**.

- After the time has elapsed, output is made via **Q**, and the data returns to **IDLE**.

A formal state machine is not visible via the XML interface, but it can be deduced from the behavior of the internal flip-flop.

## Application Scenarios

- **Sensor Value Smoothing** – A digital sensor (e.g., rotary encoder) delivers values that fluctuate briefly due to vibrations or noise. Hysteresis prevents small fluctuations from being interpreted as valid changes.
- **Button Debouncing** – For mechanical contacts, **Tmin** ensures that bouncing events within a specific time do not result in multiple output events.
- **Measurement Acquisition with Dead Time** – In dosing or positioning systems, the minimum time between two valid measurements must be maintained to avoid overloading the system dynamics.

## Comparison with Similar Components

| Component | Hysteresis | Minimum Time | Adapter Interface |
| ---------- | ----------- | ------------- | ---------------------- |
| `E_D_FF` (simple) | No | No | No (direct I/O) |
| `E_D_FF_HYS` | Yes | No | No |
| `ALI_D_FF_HYS_TMIN` | Yes | Yes | Yes (adapter usage) |

The function block described here combines the advantages of hysteresis and minimum time intervals and, thanks to its adapter interface, is particularly well-suited for a modular, event-driven architecture according to IEC 61499.

## Conclusion

The **ALI_D_FF_HYS_TMIN** module provides a robust solution for the stable acquisition of signals in harsh environments. The combination of hysteresis and minimal output time effectively suppresses both amplitude fluctuations and time bounces. Its adapter-based input and output capabilities make it flexible for use in complex automation networks.
