# ATM_D_FF_TMIN
![ATM_D_FF_TMIN](./ATM_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block `ATM_D_FF_TMIN` implements a clock-controlled D flip-flop (data latch) that takes the incoming data value at a clock event and outputs it as a stored value. A special feature is the adjustable minimum time (`Tmin`) between two consecutive output events, which guarantees a defined dead time.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |
|-------|--------|----------------------------------|
| INIT | EInit | Initialization Request (with `Tmin`) |

### **Event Outputs**

| Name | Type | Comment |
|-------|--------|----------------------------------|
| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Comment |
|-------|--------|------------------------------------------------|
| Tmin | TIME | Minimum time interval between two EO events |

### **Data Outputs**
The function block has no direct data outputs. The stored value is provided via the adapter output `Q.D1`.

### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|------------------------------------------|----------------------|
| Input (Socket) | I | `adapter::types::unidirectional::ATM` | Value to be adopted |
| Output (Plug) | Q | `adapter::types::unidirectional::ATM` | Stored value |

The adapter `ATM` provides one event channel and one data channel (`E1`, `D1` for input; `E1`, `D1` for output).

## Functionality

1. **Initialization**: An event at `INIT` initializes the function block and adopts the parameter `Tmin`.

2. **Clocking**: An event at the adapter input `I.E1` (clock) causes the function block to take the current data value from `I.D1`. If the takeover is successful, the value is output at the adapter output `Q.D1`, and an event is simultaneously sent to `Q.E1`.

3. **Minimum Output Delay**: After each output event (`Q.E1`), an internal lock is activated. Only after the time specified in `Tmin` has elapsed can another clock event trigger a new output. If a new clock signal arrives within the lock time, it is ignored, or the output is delayed until `Tmin` expires (depending on the implementation of the internal function block `E_D_FF_ANY_TMIN`).

## Technical Features
- **Dead Time Control**: The parameter `Tmin` forces a minimum pause between two output events – useful for protecting downstream components or debouncing signal edges.
- **Internal Implementation**: The function block internally uses the function block `iec61499::events::E_D_FF_ANY_TMIN`, which provides the actual flip-flop logic with timing. `ATM_D_FF_TMIN` acts as an interface adapter for the adapter `ATM`.
- **Internal Implementation**: The function block internally uses the function block `iec61499::events::E_D_FF_ANY_TMIN`, which provides the actual flip-flop logic with timing control. `ATM_D_FF_TMIN` acts as an interface adapter for the adapter `ATM`.

**Default Time Control**: - **Adapter Interface**: Both input and output data are exchanged via unidirectional adapters, enabling loose coupling in the application.

## State Overview
Although no explicit state diagram is available, the following logical states can be derived:

1. **Ready**: Waiting for a clock event, no lock active.

2. **Set**: Value has been accepted and output; the lock `Tmin` is active.

3. **Locked**: During `Tmin`, incoming clock events are ignored or held back.

After the lock expires, the function block returns to the **Ready** state.

## Application Scenarios
- **Signal conditioning** in automation technology, where a switching signal needs to be re-evaluated after a defined minimum pause (e.g., dead time during valve switching).
- **Debouncing** of binary sensors where a downstream output may only be generated after a stable time of `Tmin`.
- **Synchronization** of data streams where a minimum packet gap must be maintained.

## Comparison with similar components
- **Standard D flip-flop** (e.g., `E_D_FF`): Provides an output immediately after each clock cycle – without any time constraint. The `ATM_D_FF_TMIN` extends this with the dead time `Tmin`.
- **Monostable flip-flops** (timers): Generate a pulse of defined length. The `ATM_D_FF_TMIN`, however, only disables the output without resetting the output level.

This component combines the properties of a flip-flop with an adjustable minimum delay time and is therefore particularly suitable for time-critical control tasks.

## Conclusion
ATM_D_FF_TMIN` is a specialized D-type flip-flop component that guarantees the minimum dwell time between two output events. The use of adapters simplifies integration into modular control applications, while the adjustable delay time offers high flexibility for different physical constraints. It is a valuable addition to the IEC 61499 library for discrete-time signal processing.
