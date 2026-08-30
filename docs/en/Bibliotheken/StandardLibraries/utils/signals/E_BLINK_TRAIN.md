# E_BLINK_TRAIN

![E_BLINK_TRAIN](https://github.com/user-attachments/assets/41c5817d-1229-455b-b5c9-e7ad4003e0c5)

* * * * * * * * * *
The function block `E_BLINK_TRAIN` simulates a flashing signal that is switched on and off for specific time intervals. The number of flash cycles can be limited. Unlike similar flashing function blocks, this FB always returns to the state `FALSE` when stopped.
![E_BLINK_TRAIN](E_BLINK_TRAIN.svg)

- `START`: Starts the periodic generation of events. Linked to the data inputs `TIMELOW`, `TIMEHIGH`, and `N`.
- `STOP`: Stops event generation.
- `CNF`: Acknowledges execution and returns the current output value `OUT`.
- `TIMELOW` (TIME): Time during which `OUT` has the value `FALSE`.
- `N` (UINT): Number of blink cycles to generate.
- `OUT` (BOOL): Output value that alternates between `TRUE` and `FALSE`. Starts with `FALSE`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

## Functionality

1. Upon a `START` event, the sum of `TIMELOW` and `TIMEHIGH` is calculated and used as the period for the blink cycle.
2. The function block generates `N` blink cycles, where `OUT` is set to `TRUE` for `TIMEHIGH` and to `FALSE` for `TIMELOW`.
3. Upon a `STOP` event, generation is terminated and `OUT` is reset to `FALSE`.
4. Each state change is confirmed via the `CNF` event.
- Uses internal function blocks `E_PULSE` (for timing) and `E_TRAIN` (for cycle limiting).
- The period duration is determined by adding `TIMELOW` and `TIMEHIGH`.
- Unlike some other blink function blocks, `FALSE` is always output upon stopping.
1. **Inactive**: `OUT` = `FALSE` (initial state or after `STOP`).
2. **Active**: Generates blink cycles according to the set times and number of cycles.
- `OUT` toggles between `TRUE` (`TIMEHIGH`) and `FALSE` (`TIMELOW`).
- Display of warning or status lights with a defined blink frequency.
- Control of periodic signals in industrial automation processes.
- Simulation of blink patterns for testing purposes.
- **CODESYS BLINK FB**: Retains the last state when stopped, while `E_BLINK_TRAIN` always reverts to `FALSE`.
- **Simple Timer FBs**: Do not offer an integrated limit on the number of cycles (`N`).
- [Exercise_035a3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)

The `E_BLINK_TRAIN` is a versatile function block for generating blinking signals with configurable times and a limited number of cycles. Its unique feature is that it reverts to `FALSE` when stopped, making it ideal for safety-critical applications. The clear interface structure and the internal use of proven timer FBs make it reliable and easy to use.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## 🛠️ Zugehörige Übungen

## Conclusion
