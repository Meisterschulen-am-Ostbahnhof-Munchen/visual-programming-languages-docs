# E_D_FF_ANY_TMIN

* * * * * * * * * *
## Introduction

`E_D_FF_ANY_TMIN` is the generically-typed variant of [E_D_FF_TMIN](E_D_FF_TMIN.md): it combines [E_D_FF_ANY](E_D_FF_ANY.md) (change-detecting latch for arbitrary data types) with [E_TMIN](E_TMIN.md) (minimum spacing time), making it suitable for any data type, not just `BOOL`.

![E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.svg)

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

- **D** (ANY): The value to be latched, of arbitrary data type.
- **Tmin** (TIME): Minimum spacing between two `EO` events.

### **Data Outputs**

- **Q** (ANY): The last latched value.

## Functionality

Identical to [E_D_FF_TMIN](E_D_FF_TMIN.md), but with [E_D_FF_ANY](E_D_FF_ANY.md) instead of `E_D_FF`: `CLK` triggers the internal change detection (`NE(Q, D)`), whose `EO` is forwarded to the internal [E_TMIN](E_TMIN.md), which throttles it to at least `Tmin` between two triggers of `EO`.

## Technical Features

- **ANY typing**: can be instantiated with any data type supported by the target environment (e.g. `TIME`, `REAL`, `DINT`).
- **Two-stage filtering**: content-based change detection (`E_D_FF_ANY`) plus time-based throttling (`E_TMIN`); `Q` is unaffected by this and always current.

## State Overview

Stateless wiring logic; see [E_D_FF_ANY](E_D_FF_ANY.md) (change detection) and [E_TMIN](E_TMIN.md) (time throttling).

## Application Scenarios

- **Low-noise forwarding of arbitrary measurements**: A `REAL` or `TIME` value fluctuates slightly, but `EO` should only trigger at most every `Tmin` — e.g. to limit the transmission rate to an upstream system.

## Comparison with similar function blocks

- **[E_D_FF_ANY](E_D_FF_ANY.md)**: the same change detection, but without time throttling.
- **[E_D_FF_TMIN](E_D_FF_TMIN.md)**: the same functionality, but fixed to `BOOL`.
- **[E_TMIN](E_TMIN.md)**: the internally used throttling logic.

## Conclusion

`E_D_FF_ANY_TMIN` provides a generically-typed, change-detecting latch with a guaranteed minimum spacing between change events, for arbitrary data types.
