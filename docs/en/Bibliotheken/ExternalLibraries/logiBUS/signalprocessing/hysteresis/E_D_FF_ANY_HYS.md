# E_D_FF_ANY_HYS
![E_D_FF_ANY_HYS](./E_D_FF_ANY_HYS.svg)
* * * * * * * * * *
## Introduction
The function block **E_D_FF_ANY_HYS** implements a data latch flip-flop with adjustable hysteresis. It takes a numeric input value `D` and outputs `Q`, but only if the difference between the current output `Q` and the new input `D` exceeds a predefined threshold (`HYSTERESIS`). This effectively suppresses small, unwanted fluctuations (e.g., noise).
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|-------------|

| `CLK` | Event | Clock signal; the latch operation is triggered on a rising edge. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|-------------|

| `EO` | Event | Outputs after successful transfer from `D` to `Q` (i.e., when the hysteresis condition is met). |

### **Data Inputs**

| Name | Type | Description |

|------|-----|-------------|

| `D` | ANY\_NUM | The value to be latched. |

| `HYSTERESIS` | ANY\_NUM | Hysteresis band; the minimum absolute change between `Q` and `D` that triggers a takeover. |

### **Data Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `Q` | ANY\_NUM | The currently latched value. |

### **Adapters**

No adapters.

## Functionality

The component has an internal state machine with the states `START` and `SET`. After startup, it is in state `START`. Upon the first `CLK` event, it switches to state `SET` and executes the algorithm `LATCH`, regardless of the hysteresis. During this process, `Q := D` is set and the event `EO` is triggered.

`Q := D` is set and the event `EO` is triggered. In each subsequent call to ``CLK`` in state ``SET``, it is checked whether the absolute difference between the current ``Q`` and the new ``D`` is greater than or equal to ``HYSTERESIS``. The condition is:

``GE(SUB(MAX(D, Q), MIN(D, Q)), HYSTERESIS)``

`* `MAX(D, Q)`` and ``MIN(D, Q)`` return the larger and smaller of the two numbers, respectively.

`* `SUB(...)`` calculates the positive difference (absolute value).

`* `GE(...)`` checks whether this difference is greater than or equal to ``HYSTERESIS``.

``` Only if this condition is **true** is the algorithm `LATCH` executed again (Q := D) and `EO` sent. If the condition is false, `Q` remains unchanged and no event is output. The state remains `SET` in both cases.

## Technical Features
* **Generic Data Type:** The inputs and outputs `D`, `HYSTERESIS`, and `Q` are declared as `ANY_NUM`. The function block can therefore be used with any IEC 61499 numeric types (e.g., `INT`, `REAL`, `LREAL`), as long as all three values have the same specific type.
* **Hysteresis Function:** Hysteresis is implemented as the magnitude of the difference between the old and new values. This means the switching direction is irrelevant – exceeding the threshold in either direction triggers a takeover.
* **Initial Behavior:** The value is always taken over on the first `CLK` after startup (no hysteresis check). This corresponds to an output initialization.

## State Overview

The function block contains a very simple two-state automatic state machine:

| State | Description |

|---------|--------------|

| `START` | Initial state after the block starts. Waits for the first `CLK` event. |

| `SET` | Operating state. The hysteresis condition is evaluated on each `CLK` event. |

**Transitions:**

* `START` → `SET`: on each `CLK` event (without a condition).
* `SET` → `SET`: if `CLK` **and** the hysteresis condition is met (i.e., `GE(SUB(MAX(D,Q), MIN(D,Q)), HYSTERESIS) == true`), then `LATCH` is executed and `EO` is output.
* `SET` → `SET`: if `CLK` **without** the condition being met, no algorithm is executed, and no event occurs.
* There is no transition back to `START` – the controller remains permanently in `SET` after the first `CLK`.

## Application Scenarios
* **Stabilizing Sensor Signals:** If an analog sensor (e.g., temperature, pressure, level) delivers unstable values due to noise or small fluctuations, this function block can smooth the output. Example: Level measurement with a distance sensor where small ripples on the liquid surface should be ignored.
* **Switching Hysteresis in Control Systems:** In two-point controllers or comparators, this function block can be used to prevent constant switching on and off (fluttering). The `HYSTERESIS` value defines the dead zone.
* **Value takeover with deadband:** At the MES/SCADA level, monitored process values can only be updated when the value changes significantly – this reduces data traffic and alarm overload.

## Comparison with similar function blocks

| Function block | Function | Difference |

|----------|----------|-------------|

| `E_D_FF` | Standard D flip-flop (Boolean values only) | Takes over each clock cycle immediately, no hysteresis, only `BOOL` type. |

| `E_D_FF_ANY` | D flip-flop for any data type (no hysteresis) | Same function as `E_D_FF`, but generic. Takes over each clock cycle immediately. |

| `E_D_FF_ANY_HYS` (this block) | D flip-flop with hysteresis for any numeric type | Only accepts when there is a sufficient deviation. |

The key advantage of `E_D_FF_ANY_HYS` is the combination of a generic data type (`ANY_NUM`) and configurable hysteresis, enabling flexible and robust signal processing.

## Conclusion

The function block **E_D_FF_ANY_HYS** extends the classic D flip-flop with a hysteresis function for numeric values. It is ideally suited for applications where small changes need to be suppressed without relying on a dedicated Boolean threshold switch. Thanks to its generic type, it can be used in a wide variety of control and automation scenarios. Its simple state logic and clear interface make it efficient and easy to understand.