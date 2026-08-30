# FB_TON_LTIME

![FB_TON_LTIME](FB_TON_LTIME.svg)

* * * * * * * * * *

## Introduction

The function block `FB_TON_LTIME` is the `LTIME` variant (64-bit duration, nanosecond resolution) of the standard timer block `FB_TON` (on-delay). It behaves functionally identically to `FB_TON`, but uses data type `LTIME` instead of `TIME` for `PT`/`ET`.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers execution, linked with `IN` and `PT`.

### **Event Outputs**

- **CNF**: Confirms execution, linked with `Q` and `ET`.

### **Data Inputs**

- **IN** (BOOL): Input signal.
- **PT** (LTIME): Preset time.

### **Data Outputs**

- **Q** (BOOL): Output signal, see Functionality.
- **ET** (LTIME): Elapsed time since the timing started.

## Functionality

Q only becomes TRUE once IN has been continuously TRUE for PT. If IN falls back to FALSE before PT elapses, Q stays FALSE. Internally, the block (analogous to `FB_TON`) holds the internal helper variables `MEM` and `StartTime` to track edge transitions of `IN` and the start time of the measurement — at `LTIME` resolution instead of `TIME`.

## Technical Features

- **`LTIME` instead of `TIME`**: Provides 64-bit nanosecond resolution instead of the 32-bit millisecond resolution of `TIME`, relevant for very long or very precise timing.
- **Functionally identical to `FB_TON`**: Same timing behaviour, only the data type of `PT`/`ET` differs.

## State Overview

See `FB_TON` — identical state behaviour, just with `LTIME` values instead of `TIME`.

## Application Scenarios

- **Timing with very high precision or very long duration**, where the millisecond resolution or value range of `TIME` is insufficient.
- **Consistent `LTIME` usage** in applications that work with `LTIME` throughout, to avoid data type conversions.

## Comparison with similar function blocks

- **`FB_TON`**: the same functionality with `TIME` instead of `LTIME`.

## Conclusion

`FB_TON_LTIME` provides the same on-delay functionality as `FB_TON`, but with `LTIME` resolution, and is suitable for applications working with high-resolution time values throughout.
