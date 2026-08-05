# AR_D_FF_TMIN
![AR_D_FF_TMIN](./AR_D_FF_TMIN.svg)
* * * * * * * * * *
## Introduction
The function block **AR_D_FF_TMIN** implements a data latch (D flip-flop) with one input and one output adapter. It is characterized by the optional specification of a minimum time (`Tmin`) between successive event outputs. The core of the function block is based on the standard function block `E_D_FF_ANY_TMIN`, which handles the actual flip-flop logic and the timing.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|----------------------------------|

| INIT | EInit | Initialization Request (with parameter `Tmin`) |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|---------------------------------|

| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |

|------|------|--------------------------------------------|

| Tmin | TIME | Minimum Delay Between Two EO Events |

### **Data Outputs**

No standalone data outputs; the value is output via the `Q` adapter.

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|---------------------------------------------------|-------------------------|

| Socket | I | `adapter::types::unidirectional::AR` | Value to be transferred |

| Plug | Q | `adapter::types::unidirectional::AR` | Latched value |

The adapter `adapter::types::unidirectional::AR` combines one event (`E1`) and one data word (`D1`) per direction.

## Functionality
The function block works internally with the function block `E_D_FF_ANY_TMIN`:

1. **Initialization**: An event at `INIT` passes the parameter `Tmin` to the internal function block. Then, `INITO` is output.

The adapter `INITO` is output. 2. **Flip-flop operation**: An event at the adapter input `I.E1` (socket) is forwarded to the **CLK** input of the internal flip-flop. Simultaneously, the data value `I.D1` is passed to the **D** input of the flip-flop.

3. **Output**: The internally generated state (`Q`) and the associated event (`EO`) are passed to the adapter output `Q` (plug) – after adhering to the set minimum time `Tmin`. The event `Q.E1` and the data value `Q.D1` represent the latched value.

4. **Timing**: The parameter `Tmin` defines the minimum time that must elapse between two consecutive `EO` events. If the frequency of input events exceeds this limit, the output is delayed or blocked accordingly.

## Technical Features
- **Adapter-Based Communication**: The function block uses only unidirectional AR adapters, making it suitable for loosely coupled or distributed systems.
- **Reuse of a Standard Function Block**: The core logic is provided by the IEC 61499 standard function block `E_D_FF_ANY_TMIN` – thus, the functionality is standards-compliant and extensible.
- **Configurable Lockout Time**: The minimum time `Tmin` is passed for initialization and cannot be changed during runtime (except via a new INIT cycle).

## State Overview
The FB itself does not have its own state diagram. Its behavior is entirely determined by the embedded standard function block `E_D_FF_ANY_TMIN`. After the INIT phase, this block is in a wait state and switches to an output state with each CLK event, provided the `Tmin` time has elapsed.

## Application Scenarios
- **Signal Debouncing**: When a sensor signal (e.g., via `I`) should only be passed on with a minimum pause to suppress bounce or noise.
- **Event Rate Limitation**: In control or monitoring systems where downstream components must not be operated faster than a defined rate.
- **Secure Data Transfer**: The latched value remains stable until the next CLK event (at the adapter input) arrives.

## Comparison with Similar Function Blocks
- **AR_D_FF** (without TMIN): A pure D flip-flop function block without a time limit on the output events. It is suitable for real-time applications without delay requirements.
- **AR_D_FF_TMIN**: Extends the basic function block with the ability to limit the event rate, which is often necessary in industrial control systems with time constraints.
- **AR_SR_FF**: Implements set-reset logic – unlike the D flip-flop implemented here, the output is not clock-controlled.

## Conclusion

The `AR_D_FF_TMIN` is a functionally enhanced D flip-flop device that combines latch functionality with a configurable minimum time between output events. Its adapter-based interface and the use of a standardized core make it a flexible and standards-compliant component for time-critical control applications in the IEC 61499 environment.