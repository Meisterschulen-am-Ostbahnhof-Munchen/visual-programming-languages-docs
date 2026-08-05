# AS_D_FF_HYS

![AS_D_FF_HYS](./AS_D_FF_HYS.svg)

* * * * * * * * * *

## Introduction

The function block **AS_D_FF_HYS** implements a data-triggered flip-flop (D-latch) with **hysteresis** (switching hysteresis). This component is typically used in signal processing to smooth noisy or fluctuating input signals and create defined switching points. It features an event input `INIT` to set the hysteresis value, as well as two adapter interfaces: an input adapter `I` for the signal to be latched and an output adapter `Q` for the latched and hysteresis-filtered output signal.


## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |

|--------|--------|---------------------|-----------|

| `INIT` | EInit | Sets the hysteresis value | `HYSTERESIS` |

### **Event Outputs**

| Name | Type | Comment |

|---------|--------|----------------------|

| `INITO` | EInit | Confirmation of INIT processing |

### **Data Inputs**

| Name | Type | Comment |

|--------------|------|-------------------------------|

| `HYSTERESIS` | SINT | Hysteresis Bandwidth (Integer Value) |

### **Data Outputs**

No direct data outputs – the output value is provided via the `Q` adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|---------------------------------------------|------------------------------------|

| Socket | `I` | `adapter::types::unidirectional::AS` | Input Signal (Value and Clock) |

| Plug | `Q` | `adapter::types::unidirectional::AS` | Output signal (latched with hysteresis) |

The `AS` (unidirectional) adapters typically have an event port `E1` and a data port `D1`. The socket `I` provides the clock signal via `I.E1` and the data value to be latched via `I.D1`. The plug `Q` outputs an event via `Q.E1` and the filtered output value via `Q.D1`.



The socket `I` provides the clock signal via `I.E1` and the data value to be latched via `I.D1`. ## Functionality

The FB receives a clock signal (event `I.E1`) and a data value (`I.D1`) via the adapter `I`. With each clock cycle, the current data value is compared to the last output value, taking the hysteresis band into account. The output `Q.D1` only changes if the new input value is outside the interval `[letzter Ausgangswert - HYSTERESIS , letzter Ausgangswert + HYSTERESIS]`. This suppresses small fluctuations (noise) around the set operating point.

The event `INIT` is used for the one-time configuration of the hysteresis value. The hysteresis value from the data input `HYSTERESIS` is used for this purpose. After successful initialization, the event `INITO` is triggered.

The function block (FB) internally uses the block `E_D_FF_ANY_HYS` from the library `logiBUS::signalprocessing::hysteresis`, which implements the actual flip-flop logic with hysteresis.

## Technical Features

- The hysteresis value is defined as `SINT` (signed integer).

- The actual signal processing is implemented by a subordinate FB (`E_D_FF_ANY_HYS`), which is not directly accessible to the user.

- The adapter interface allows loose coupling of the function block to other components.

- The event `INIT` does not process a value – the hysteresis parameters can only be set before initial operation. Subsequent changes are only possible by resending `INIT`.

## State Overview

The function block (FB) has **no explicit state machine** that is externally visible. Internally, the current output value is stored. Hysteresis creates a state memory: The output does not change with every input change, but only when the hysteresis thresholds are exceeded or fallen below.

## Application Scenarios

- **Debouncing of Switch Contacts** – Suppression of bounce and short interference pulses.

- **Threshold Switches with Hysteresis** – e.g., temperature controllers that separate on and off points.

- **Signal Smoothing in Sensors** – Processing noisy analog values into discrete states.

- **Data Latch with Noise Suppression** – for slow but noisy data signals.

## Comparison with Similar Function Blocks

| Function Block | Property | Difference to AS_D_FF_HYS |

-------------------|-----------------------------------------------------|-----------------------------------------------------|

| `E_D_FF` | Classic D flip-flop without hysteresis | No filtering; output follows each clock cycle. |

| `E_D_FF_HYS` | D flip-flop with hysteresis (same logic) | No dedicated `INIT` input; hysteresis is set via data if necessary. |

| `AS_FF_HYS` | Flip-flop with hysteresis and dedicated adapter interface | Possibly different coupling, similar function. |


## Conclusion

The `AS_D_FF_HYS` combines a D flip-flop with adjustable hysteresis and encapsulates the complex logic in an easy-to-use, adapter-based component. It is particularly suitable for applications where noisy discrete signals need to be processed cleanly and with defined switching points. Initial configuration via `INIT` allows for flexible adaptation to various noise environments.