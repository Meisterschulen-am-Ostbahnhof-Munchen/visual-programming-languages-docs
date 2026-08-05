# AI_D_FF_HYS
![AI_D_FF_HYS](./AI_D_FF_HYS.svg)
* * * * * * * * * *
## Introduction
The function block **AI_D_FF_HYS** implements a clock-controlled D flip-flop (data latch) with configurable hysteresis. It serves to stably lock a binary or analog input signal and filter out disturbances in the signal waveform. The hysteresis prevents constant switching due to minor signal changes (bouncing, noise), thus ensuring a clean, latency-free output state.
## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Description |

|----------|-------|----------------|-----------------------------|

| INIT | EInit | HYSTERESIS | Initialization and Hysteresis Band Setting |

### **Event Outputs**

| Event | Type | Description |

|----------|-------|--------------------------|

| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Description |

|-------------|------|----------------------------------------|

| HYSTERESIS | INT | Hysteresis Bandwidth (e.g., in digital steps) |

### **Data Outputs**

This function block does not have direct data outputs. The locked value is provided via the **Adapter Plug Q**.

### **Adapter**

| Name | Type | Direction | Description |

|-------------|-----|----------|---------------------------------------------------|

| I | AI | Socket | Input adapter: Clock signal (**E1**) and data (**D1**) |

| Q | AI | Plug | Output adapter: Latched value (**D1**) and associated event (**E1**) |

The adapter type used, `adapter::types::unidirectional::AI`, is a unidirectional data and event channel. The clock (E1) and data (D1) values are received via socket **I**; the latched value (D1) is output via plug **Q** along with an acknowledgment event (E1).

## Functionality

1. **Initialization**

The module is activated by the **INIT** event. The passed value **HYSTERESIS** is stored as the hysteresis band. After successful initialization, **INITO** is triggered.

2. **Data Latching**

After initialization, the module waits for a clock signal at adapter **I** (event **I.E1**). With each clock event, the current data value **I.D1** is read.

The internal function block `E_D_FF_ANY_HYS` compares the incoming value with the last latched value, taking the hysteresis into account:

- If the new value exceeds the old value by more than half the hysteresis, the new value is adopted (set).
- If it falls short of the old value by more than half the hysteresis, the new value is adopted (reset).
- For smaller differences, the output remains unchanged.

The latched value determined in this way is provided at adapter **Q**: **Q.D1** contains the digital value, and event **Q.E1** signals the update.

``` ## Technical Features

- **Adapter-Based Communication**

All data and event exchange occurs via adapters. This enables loose coupling between the flip-flop and the connected components and facilitates reuse in different contexts.

- **Hysteresis for Noise Suppression**

Hysteresis prevents flip-flop behavior in the presence of noise or bouncing signals. The bandwidth is passed as an integer (INT) and can be reset at runtime via **INIT**.

- **No Direct Data Outputs**

The latched value is only accessible via the **Q** adapter. This enforces structured signal routing within the overall system.

- **Embedded Function Block**

The actual flip-flop with hysteresis is implemented by the internal function block `E_D_FF_ANY_HYS`, which encapsulates complexity and simplifies maintenance.

## State Overview

The function block (FB) does not have explicit states in the sense of a finite automaton. After the **INIT** operation, it is in an operating state where it waits for clock events. A subsequent **INIT** call resets the hysteresis and initializes the internal logic.

| State | Description |

|----------------------|-----------------------------------------------|

| Initialized | Ready for processing after a successful **INIT** |

| Waiting for Clock | Expecting an **I.E1** event at the input adapter |

| Data Processing | Upon **I.E1**: Hysteresis comparison and, if necessary, acceptance |

## Application Scenarios
- **Debouncing of Switches and Sensors**

A mechanical contact produces bouncing signals. Hysteresis suppresses short-term changes and only passes on stable states.

- **Noise Reduction for Analog Signals**

An analog-to-digital converter (ADC) delivers noisy values. Hysteresis prevents constant switching between adjacent quantization levels.

- **State Memory in Controllers**

This component can be used as a simple D flip-flop to clock a digital value and hold it until the next clock signal.

- **Interface Between Asynchronous and Synchronous Systems**

This adapter allows the connection of components with different event clocks by using the flip-flop as a buffer.

## Comparison with Similar Components

| Component | Hysteresis | Clock Input | Output Type | Special Feature |

-------------------|-----------|-------------|-----------------------|----------------------------------|

**AI_D_FF_HYS** | Yes | Yes | Adapter (AI) | Flexible Adapter Coupling | ... Standard D-FF (61499) | No | Yes | Direct Data Outputs | No Noise Suppression |

SR Flip-Flop | No | No | Direct | Set/Reset, No Clock |

Schmitt Trigger | Yes | No | Analog Threshold | Threshold Only, No Memory |

The AI_D_FF_HYS combines the features of a clocked D flip-flop with adjustable hysteresis and offers platform-independent integration into IEC 61499 systems via its adapter interface.

## Conclusion

The **AI_D_FF_HYS** is a robust and flexible functional block for clocked signal locking with hysteresis. It is particularly suitable for applications where noise needs to be filtered out of the input signal without sacrificing the functionality of a simple clock flip-flop. The adapter-based interface promotes modular, reusable designs and makes the component a valuable element in automation technology and signal processing.