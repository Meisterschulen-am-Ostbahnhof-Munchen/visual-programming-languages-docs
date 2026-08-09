# ATM_AX_TONOF

![ATM_AX_TONOF](./ATM_AX_TONOF.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_AX_TONOF** implements a combined on/off delay timer. It is designed as a standard timer module according to IEC 61499 and uses only adapter interfaces for communication. This allows it to be flexibly integrated into various communication structures. The module processes a Boolean input signal and outputs the delayed signal – both the on delay (ON-Delay) and the off delay (OFF-Delay) are configured via separate adapters.
## Interface Structure

### Event Inputs

| Name | Type | Description |
|------|--------|--------------------------------------------------------------|
| R | Event | Resets the timer. Both running delays are aborted, and output Q is immediately set to FALSE. |

### Event Outputs

The function block does not have any independent event outputs. The output event is provided via the output adapter **Q** (see Adapters).

### Data Inputs

The function block does not have any direct data inputs. All necessary data (Boolean input and delay times) is read via the adapter interfaces.

### Data Outputs

There are also no dedicated connections for data outputs. The current output state (BOOL) is output via the output adapter **Q**.

### Adapters

| Name | Direction | Type | Description |
|--------|----------|------------------|------------------------------------------------------------------------------------------------------|
| IN | Socket | AX (unidirectional) | Input adapter that triggers execution via its event E1 and provides the Boolean input value via its data D1. |
| PT_ON | Socket | ATM (unidirectional) | Adapter for the power-on delay time (TIME). The value is provided via D1. |
| PT_OFF | Socket | ATM (unidirectional) | Adapter for the power-off delay time (TIME). The value is provided via D1. |
| Q | Plug | AX (unidirectional) | Output adapter. Event E1 signals the update of the output value; data D1 contains the Boolean state of Q (TRUE or FALSE). |

## Functionality

The function block operates according to the following sequence:

- When the input signal **IN** changes from FALSE to TRUE, the timer starts the power-on delay with the time **PT_ON**. After this time has elapsed, the output **Q** is set to TRUE.
- When **IN** changes from TRUE to FALSE, the timer starts the power-off delay with the time **PT_OFF**. After this time has elapsed, **Q** is set to FALSE.
- An event at the reset input **R** immediately stops both running timers and sets **Q** to FALSE, regardless of the current state of **IN**.

The internal implementation uses the standardized function block **E_TONOF** from the IEC 61499 library. This ensures defined, robust timing behavior.

## Technical Features

- **Adapter-based interface**: All inputs and outputs are handled via adapters (AX, ATM) instead of discrete event and data ports. This facilitates integration into modular systems and allows for a clean separation of communication and logic.
- **Standard compliance**: The function block is classified as a standard timer according to IEC 61499 and can be used in any 4diac IDE project.
- **Reset function**: The separate reset input enables immediate resetting without dependence on the current timer state.
- **Reusable adapter types**: The AX and ATM adapters are used multiple times in the application, so no additional type definitions are required.

## State Overview

The internal timer **E_TONOF** cycles through the following states:

1. **IDLE**: No delay active. Output Q = state of IN (if updated after a previous delay).
2. **START_ON**: After the rising edge of IN – the timer for PT_ON runs.
3. **START_OFF**: After the falling edge of IN – the timer for PT_OFF runs.
4. **RESET**: Triggered by the event R, this interrupts any active timer and returns to the IDLE state with Q = FALSE.

## Application Scenarios

- **Delayed Switching On and Off of Actuators**: For example, to prevent bouncing or to stagger switching operations.
- **Motor Protection**: Switch-on delay prevents frequent switching on/off cycles; switch-off delay enables a defined overrun.
- **Door Control**: ON delay for time-delayed closing after release, OFF delay for automatic opening after a waiting period.
- **HMI Filtering**: Suppression of short, unwanted signal changes through adjustable dead times.

## Comparison with similar function blocks

- **E_TON (TON)**: Implements only an on delay; the output is set to TRUE after the delay and remains TRUE as long as IN=TRUE.
- **E_TOF (TOF)**: Implements only an off delay; the output is set to TRUE immediately when IN=TRUE and falls back to FALSE after the delay when IN=FALSE.
- **E_TONOF**: Combines both delays in one function block. The **ATM_AX_TONOF** extends this concept with an adapter interface, thus simplifying integration with other adapter-based components. It offers the same functionality but with increased flexibility in system integration.

**E_TONOF**: Combines both delays in one function block.
## Conclusion

The **ATM_AX_TONOF** is a powerful timer function block for delayed on/off switching operations. Its adapter-based interface allows it to be seamlessly integrated into modular automation solutions while remaining fully compliant with the IEC 61499 standard. Combining ON delay and OFF delay in a single block reduces wiring effort and simplifies application development. Thanks to its separate reset input and robust internal implementation, it is suitable for a wide range of industrial applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
