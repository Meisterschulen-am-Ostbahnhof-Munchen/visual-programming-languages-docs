# FB_TP_LTIME

![FB_TP_LTIME](FB_TP_LTIME.svg)

* * * * * * * * * *

## Introduction

The function block `FB_TP_LTIME` is the `LTIME` variant (64-bit duration, nanosecond resolution) of the standard timer block `FB_TP` (pulse). It behaves functionally identically to `FB_TP`, but uses data type `LTIME` instead of `TIME` for `PT`/`ET`.

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

A rising edge of IN triggers a TRUE pulse of fixed duration PT on Q, regardless of how long IN stays TRUE. Internally, the block (analogous to `FB_TP`) holds the internal helper variables `MEM` and `StartTime` to track edge transitions of `IN` and the start time of the measurement — at `LTIME` resolution instead of `TIME`.

## Technical Features

- **`LTIME` instead of `TIME`**: Provides 64-bit nanosecond resolution instead of the 32-bit millisecond resolution of `TIME`, relevant for very long or very precise timing.
- **Functionally identical to `FB_TP`**: Same timing behaviour, only the data type of `PT`/`ET` differs.

## State Overview

See `FB_TP` — identical state behaviour, just with `LTIME` values instead of `TIME`.

## Application Scenarios

- **Timing with very high precision or very long duration**, where the millisecond resolution or value range of `TIME` is insufficient.
- **Consistent `LTIME` usage** in applications that work with `LTIME` throughout, to avoid data type conversions.

## Comparison with similar function blocks

- **`FB_TP`**: the same functionality with `TIME` instead of `LTIME`.

## Conclusion

`FB_TP_LTIME` provides the same pulse functionality as `FB_TP`, but with `LTIME` resolution, and is suitable for applications working with high-resolution time values throughout.
