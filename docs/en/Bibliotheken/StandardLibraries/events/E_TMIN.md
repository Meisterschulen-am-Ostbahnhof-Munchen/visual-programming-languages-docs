# E_TMIN

* * * * * * * * * *

## Introduction

`E_TMIN` (minimum inter-arrival time) is a composite function block that only forwards incoming events at `EI` to `EO` if at least the time span `Tmin` has passed since the last forwarded event. It acts as an event throttle (rate limiter) for arbitrary event streams.

![E_TMIN](E_TMIN.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization, carries `Tmin`.
- **EI**: Incoming event to be throttled.

### **Event Outputs**

- **INITO**: Confirms the initialization.
- **EO**: The throttled output event.

### **Data Inputs**

- **Tmin** (TIME): Minimum spacing between two consecutive `EI` events that actually result in `EO`.

## Functionality

Internally, `E_TMIN` uses an `E_REND` (rendezvous of two events) and an `E_DELAY`: when `EI` arrives, it is forwarded to `E_REND.EI1`. `E_REND` fires `EO` once it has received at least one event on both `EI1` and `EI2` — initially `EI2` is already "pre-filled" via `INIT`, so the first `EI` is passed through immediately. Every event let through by `E_REND` simultaneously starts `E_DELAY` with time `Tmin`; only once it elapses does it deliver the next `EI2` event to `E_REND`, meaning the next `EI` can pass through at the earliest after `Tmin`.

## Technical Features

- **Built from two standard elements**: `E_TMIN` is pure wiring composed of `E_REND` and `E_DELAY`, with no ECC of its own.
- **First event unthrottled**: The first `EI` after `INIT` is passed through immediately; throttling only kicks in afterwards.
- **Building block for the `_TMIN` family**: Used internally by [E_D_FF_TMIN](E_D_FF_TMIN.md) and [E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md) to additionally throttle their `EO` outputs.

## State Overview

Stateless wiring logic: `E_REND` internally remembers whether an `EI2` (from `E_DELAY`) has already arrived, `E_DELAY` restarts after every event it lets through.

## Application Scenarios

- **Throttling rapidly changing sensor events** so downstream logic (e.g. logging, network transmission) isn't overloaded by too high an event rate.
- **Building block inside [E_D_FF_TMIN](E_D_FF_TMIN.md)/[E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)** to additionally time-limit change events.

## Comparison with similar function blocks

- **`E_REND`**: the internally used synchronization basis, without a time component.
- **`E_DELAY`**: the internally used timer.
- **[E_D_FF_TMIN](E_D_FF_TMIN.md) / [E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**: additionally combine `E_TMIN` with a data latch (`E_D_FF`/`E_D_FF_ANY`).

## Conclusion

`E_TMIN` is a simple but effective event-throttling block composed of two standard elements (`E_REND`, `E_DELAY`) that guarantees a minimum spacing time between passed-through events.
