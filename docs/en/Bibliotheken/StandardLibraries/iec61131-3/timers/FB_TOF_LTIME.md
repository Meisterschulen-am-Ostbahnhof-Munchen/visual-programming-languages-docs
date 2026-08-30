# FB_TOF_LTIME

![FB_TOF_LTIME](FB_TOF_LTIME.svg)

* * * * * * * * * *

## Introduction

The function block `FB_TOF_LTIME` is the `LTIME` variant (64-bit duration, nanosecond resolution) of the standard timer block `FB_TOF` (off-delay). It behaves functionally identically to `FB_TOF`, but uses data type `LTIME` instead of `TIME` for `PT`/`ET`.

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

Q becomes TRUE immediately when IN switches to TRUE. When IN switches to FALSE, Q stays TRUE for the duration PT before falling back to FALSE. Internally, the block (analogous to `FB_TOF`) holds the internal helper variables `MEM` and `StartTime` to track edge transitions of `IN` and the start time of the measurement — at `LTIME` resolution instead of `TIME`.

## Technical Features

- **`LTIME` instead of `TIME`**: Provides 64-bit nanosecond resolution instead of the 32-bit millisecond resolution of `TIME`, relevant for very long or very precise timing.
- **Functionally identical to `FB_TOF`**: Same timing behaviour, only the data type of `PT`/`ET` differs.

## State Overview

See `FB_TOF` — identical state behaviour, just with `LTIME` values instead of `TIME`.

## Application Scenarios

- **Timing with very high precision or very long duration**, where the millisecond resolution or value range of `TIME` is insufficient.
- **Consistent `LTIME` usage** in applications that work with `LTIME` throughout, to avoid data type conversions.

## Comparison with similar function blocks

- **`FB_TOF`**: the same functionality with `TIME` instead of `LTIME`.

## Conclusion

`FB_TOF_LTIME` provides the same off-delay functionality as `FB_TOF`, but with `LTIME` resolution, and is suitable for applications working with high-resolution time values throughout.
