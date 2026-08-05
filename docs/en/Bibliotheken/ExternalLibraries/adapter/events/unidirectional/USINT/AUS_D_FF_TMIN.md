# AUS_D_FF_TMIN

![AUS_D_FF_TMIN](./AUS_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AUS_D_FF_TMIN** implements a clock-controlled D-latch (data flip-flop) with a minimum inter-disposal time between two consecutive output events (EO). It is particularly suitable for applications where an incoming value (via an adapter socket) is received and may only be output again after a configurable minimum time has elapsed. Initialization is performed via the standard event input **INIT**.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment | With Variable |

|------|-----|------------|--------------|

| INIT | EInit | Init Request | Tmin |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| INITO | EInit | Init Confirmation |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| HYSTERESIS | ANY_NUM | Hysteresis band (currently not connected to the internal network) |

| Tmin | TIME | Minimum time interval between two EO events |

### **Data Outputs**

No direct data outputs – output data is provided exclusively via the **Adapter Plug Q**.

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

Socket | I | adapter::types::unidirectional::OFF | Value to be transferred (contains event E1 and data D1) |

Plug | Q | adapter::types::unidirectional::OFF | Transferred output value (contains event E1 and data D1) |

## Functionality
The function block internally contains a pre-built FB **E_D_FF_ANY_TMIN** (from the library `iec61499::events`). This function block takes the current data value from the Clock input upon each incoming event and passes it on to the output – but only if the time elapsed since the last output event is at least **Tmin**.



``` - During the **INIT** event, the parameter *Tmin* is passed to the internal function block.

- An event on **I.E1** (adapter socket) acts as the clock for the internal flip-flop.

- The latched data value appears on **Q.D1** (adapter plug) and is simultaneously acknowledged with an event on **Q.E1** – provided the timing condition is met.

- The **HYSTERESIS** parameter is declared but is not used in the current network. It can be used for future expansions or for manual wiring.

## Technical Features
- **Minimum time between outputs**: The output of the latched value is only enabled when the time elapsed since the last **EO** is ≥ *Tmin*. This prevents an excessively high event rate at the output.

- **Adapter Interface**: Input and output are implemented as unidirectional adapters of type **OFF**, allowing the module to be easily integrated into existing adapter-based architectures.

- **Hysteresis Parameter**: Although not directly wired, the *HYSTERESIS* input is available – for example, to implement Schmitt-trigger-like behavior in later versions.

## State Overview
The internal FB **E_D_FF_ANY_TMIN** has a memory for the last acquired data value. This state is updated with each clock event (I.E1). An explicit state machine is not present at the top level; the behavior results from the logic of the underlying flip-flop.

## Application Scenarios

- **Sensor Value Debouncing**: On and off thresholds with a minimum repetition rate.


- **Data Buffer with Output Limit**: Prevents downstream consumers from being flooded with too many updates.

- **Timed Latch Function**: A value is only transferred if the last output was longer than *Tmin*.

## Comparison with Similar Components

| Component | Properties |

|----------|---------------|

| **E_D_FF** (Simple D Flip-Flop) | Transfers a value immediately at each clock cycle, no time control. |

| **AUS_D_FF_TMIN** | Like **E_D_FF**, but with an additional minimum time between output events. |

| **R_TRIG / F_TRIG** | Detect edges, but do not store a data value. |


The **AUS_D_FF_TMIN** is therefore particularly suitable for time-critical applications where a minimum sampling or update rate must be maintained.

## Conclusion

The **AUS_D_FF_TMIN** is a useful extension module for the D flip-flop, providing time-decoupling of the output. Thanks to its adapter interface and simple configuration via **Tmin**, it can be flexibly integrated into IEC 61499 systems. The existing but unused **HYSTERESIS** input offers potential for future functional extensions.