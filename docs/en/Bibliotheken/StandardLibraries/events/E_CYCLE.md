# E_CYCLE

## Introduction

The `E_CYCLE` is a function block according to IEC 61499 that serves as a periodic event generator. After starting, the block repeatedly fires an output event (`EO`) at a defined time interval (`DT`). It is the fundamental tool for creating clocks and cyclic sequences.
![E_CYCLE](E_CYCLE.svg)
## Interface Structure

### **Event Inputs**

- **START**: Starts the periodic generation of `EO` events.
- **Related Data**: `DT`
- **STOP**: Stops the generation of `EO` events.

### **Event Outputs**

- **EO (Event Output)**: The cyclically triggered output event.

### **Data Inputs**

- **DT (Delay Time)**: The time interval between individual `EO` events (data type: `TIME`).

## Functionality

The functionality of `E_CYCLE` is internally based on a feedback loop with a `E_DELAY` block.

1. **Starting the Cycle**:
- A `START` event at the input triggers the internal timer with the duration specified at the `DT` input.
- After this time `DT` has elapsed, the first `EO` event is triggered at the output.
2. **Cyclic Operation**:
- The triggered `EO` event is immediately fed back internally to the timer's start input.
- This immediately restarts the timer, and after another time interval `DT`, the next `EO` event is triggered.
- This process repeats continuously, generating a periodic sequence of `EO` events at intervals of `DT`.
3. **Stopping the Cycle**:
- A `STOP` event at the input breaks the internal feedback loop.
- The timer stops, and no further `EO` events are generated until another `START` event occurs.

## Technical Features

- **Event Generator**: The module generates a chain of events, not a continuous state (such as a square wave). To implement blinking, the `EO` event would, for example, trigger a `E_T_FF` (toggle flip-flop).
- **Precise timing control**: Enables precise definition of the cycle time via the `TIME` data type.
- **Event-driven architecture**: All control (start/stop) is purely event-based.

## Application scenarios

- **Clock generator**: Periodically triggers other function blocks at a fixed clock rate (e.g., for sampling or calculations).
- **Blinker/warning lights**: As a pulse generator for a downstream flip-flop to produce a visual signal.
- **Watchdog**: Periodically sends a "life sign." If the signal is absent, an error can be detected.
- **Test Automation**: Generation of periodic stimuli for systems under test.

## ⚖️ Comparison with similar components

| Feature | E_CYCLE | E_DELAY | E_PULSE (hypothetical) |
|--------------|-------------------------|------------------------------|------------------------------|
| Function | Periodic Clock | Single Delay | Single Pulse of Fixed Duration |
| Repetition | Continuous | Once per `START` event | Once per `REQ` event |
| Control | START/STOP | START/STOP | REQ |

## 🛠️ Related exercises

* [Uebung_007](../../../Uebungen/test_B/Uebungen_doc/Uebung_007.md)
* [Uebung_007_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007_AX.md)
* [Uebung_007a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a1.md)
* [Uebung_007a1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a1_AX.md)
* [Uebung_007a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a2.md)
* [Uebung_007a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a2_AX.md)
* [Uebung_007a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_008](../../../Uebungen/test_B/Uebungen_doc/Uebung_008.md)
* [Uebung_009](../../../Uebungen/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_020c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
* [Uebung_020c3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e2.md)
* [Uebung_020e2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020f2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
* [Uebung_020f2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_084](../../../Uebungen/test_B/Uebungen_doc/Uebung_084.md)
* [Uebung_152](../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Exercise_153](../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion

The `E_CYCLE` function block is an essential tool for all applications requiring periodic or cyclic logic. It easily implements a clock generator whose frequency can be precisely set via the `DT` parameter. Its purely event-based behavior makes it an efficient and fundamental component in the IEC 61499 system architecture.
