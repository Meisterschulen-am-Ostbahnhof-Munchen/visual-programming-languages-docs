# E_D_FF_TMIN

* * * * * * * * * *
## Introduction

`E_D_FF_TMIN` combines `E_D_FF` (clocked `BOOL` latch with change detection) with [E_TMIN](E_TMIN.md) (minimum spacing time): changes to `Q` are still latched immediately, but the change event `EO` is additionally limited to at most one trigger per `Tmin` interval.

![E_D_FF_TMIN](E_D_FF_TMIN.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization, carries `Tmin`.
- **CLK**: Clock event, latches `D` into `Q`.
    - **Connected data**: `D`

### **Event Outputs**

- **INITO**: Confirms the initialization.
- **EO**: Change event throttled to `Tmin`.
    - **Connected data**: `Q`

### **Data Inputs**

- **D** (BOOL): The value to be latched.
- **Tmin** (TIME): Minimum spacing between two `EO` events.

### **Data Outputs**

- **Q** (BOOL): The last latched value.

## Functionality

`CLK` internally triggers the encapsulated `E_D_FF`, whose `D`/`Q` data connection is forwarded directly to the outer `D`/`Q` ports. Only when `E_D_FF` detects an actual value change (`Q := D`) does it trigger its own `EO` — this is forwarded to the `EI` input of the internal [E_TMIN](E_TMIN.md), which only passes the event through to the outer `EO` output if at least `Tmin` has passed since the last pass-through.

## Technical Features

- **Two-stage filtering**: first content-based change detection (`E_D_FF`), then time-based throttling (`E_TMIN`) — `Q` itself is not affected by this and is always current, even while `EO` is being throttled.
- **Pure wiring of two standard blocks**, no ECC of its own.

## State Overview

Stateless wiring logic; see `E_D_FF` (change detection) and [E_TMIN](E_TMIN.md) (time throttling) for the respective internal states.

## Application Scenarios

- **Low-noise status reporting of a `BOOL` signal**: A digital state changes frequently over short periods (bouncing, noise); `EO` should only trigger at most every `Tmin`, while `Q` always shows the current value.

## Comparison with similar function blocks

- **`E_D_FF`**: the same change detection, but without time throttling.
- **[E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**: the same functionality for arbitrary data types instead of just `BOOL`.
- **[E_TMIN](E_TMIN.md)**: the internally used throttling logic.

## Conclusion

`E_D_FF_TMIN` provides a change-detecting `BOOL` latch with a guaranteed minimum spacing between change events and is suitable for low-noise event forwarding of digital signals.
