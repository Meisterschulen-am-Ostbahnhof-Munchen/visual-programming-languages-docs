# I_TD_TD
![I_TD_TD](./I_TD_TD.svg)

* * * * * * * * * *
## Introduction
The function block **I_TD_TD** is a wrapper around the base block `I_TD` and generates a combined IEC 61131-3 date/time struct (type `DT`) from the individual time and date components. It serves as an interface to an ISOBUS-compliant time/date service (PGN 65254) and provides the processed time information as well as local time offsets as separate outputs.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| INIT | EInit | Service Initialization, controlled by qualifier `QI` |

### **Event Outputs**

| Name | Type | Carrying Data |
|------|-----|--------------------|
| INITO | EInit | `QO`, `STATUS` |
| IND | Event | `QO`, `timestamp_data`, `STATUS`, `Q_timeout`, `LOCAL_MINUTE_OFFSET`, `LOCAL_HOUR_OFFSET` |
| TIMEOUT | Event | `timestamp_timeout`, `STATUS`, `Q_timeout` |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| QI | BOOL | Input Qualifier (Controls the Initialization Process) |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| QO | BOOL | Output Qualifier (Processing Status) |
| STATUS | STRING | Status Message |
| Q_timeout | BOOL | Timeout Flag |
| timestamp_timeout | DINT | Timeout Timestamp |
| timestamp_data | DINT | Timestamp of valid data |
TD | DT | Combined time/date (IEC 61131-3 `DT`) |
LOCAL_MINUTE_OFFSET | SINT | Local minute offset (SPN 1601, Unit: 1 min/bit, Offset -125) |
LOCAL_HOUR_OFFSET | SINT | Local hour offset (SPN 1602, Unit: 1 h/bit, Offset -125) |

### **Adapter**

No adapters available.

## Functionality

The function block encapsulates the following steps:

1. **Initialization**

An event at input `INIT` starts the internal function block `I_TD` (`I_CORE`). This block executes its own initialization sequence and confirms with `INITO`. The qualifiers `QO` and `STATUS` are passed to the corresponding outputs.

2. **Cyclic Time/Date Capture**

Once the internal function block is ready, it cyclically generates a `IND` event. This event triggers the downstream function block `F_CONCAT_DT`. `F_CONCAT_DT` combines the individual components (year, month, day, hour, minute, second) provided by `I_TD` into a `DT` struct. The millisecond component is fixed at 0. After concatenation is complete, a `CNF` event is generated, which activates the external `IND` output, along with all other data outputs (timestamps, offsets, etc.).

3. **Timeout**

If the internal service reports a timeout, the `TIMEOUT` event is activated at the output. The associated data (`timestamp_timeout`, `STATUS`, `Q_timeout`) are taken directly from the inner block.

4. **Forwarding the Raw Data**

The outputs `timestamp_data`, `timestamp_timeout`, `LOCAL_MINUTE_OFFSET`, and `LOCAL_HOUR_OFFSET` are taken unchanged from `I_TD`.

## Technical Features
- **Wrapper Principle**

This block simplifies the handling of the ISOBUS time service by combining the individual time components into a platform-compatible `DT` struct. The user does not need to perform any custom chaining of year, month, etc.

- **ISO 11783-7 compliant**

The underlying service corresponds to PGN number 65254 and provides the SPNs (1601, 1602) required by ISO 11783-7 for local time offsets. The attribute information (scaling, offset) is stored in the output variables.

- **Timestamp handling**

Separate timestamps (`DINT`) are provided for both valid data and timeout events, allowing the sequence and recency of events to be tracked.

- **Event-driven process**

Processing is purely event-driven. Each cycle is initiated by the `IND` of the internal component and ends with the `IND` of the wrapper.

## State Overview

The function block does not have an explicit internal state machine that would be visible to the user. However, the process can be divided into the following phases:

1. **Idle State** – After initialization, the function block waits for the first `IND` of `I_TD`.

2. **Active Processing** – `IND` of `I_TD` triggers `F_CONCAT_DT`; subsequently, the outer `IND` is output.

3. **Timeout State** – If `I_TD` times out, `TIMEOUT` is output.

4. **Initialization Phase** – The internal module is initialized during `INIT` and `INITO`.

## Application Scenarios
- **ISOBUS Control Units**

Used in agricultural control units that regularly query the current UTC time and the local time offset from the ISOBUS bus and require this data as a uniform data type (`DT`) for display or logging.

- **Time Synchronization**

Used in systems that rely on an exact time base, e.g., recording devices (loggers), GPS-based applications, or process controls.

- **Wrapper for IEC 61131-3 Compatibility**

If subsequent function blocks do not expect access to individual time components, but only to a `DT` struct, `I_TD_TD` can serve as a link.

## Comparison with Similar Function Blocks
- **I_TD (Basic Function Block)**

Returns the time components as separate outputs (YEAR, MONTH, DAY, etc.). The user would have to concatenate them manually to a `DT`. `I_TD_TD` does this automatically and also adds the raw data timestamps.

- **Other Time/Date Wrappers**

Some implementations use direct system time functions. `I_TD_TD` is specifically optimized for use in an ISOBUS context and provides the required SPN attributes as well as timeout handling.

## Conclusion

I_TD_TD` extends the standardized ISOBUS time block `I_TD` by adding a direct output of the IEC 61131-3 date-time type `DT`. This simplifies integration into control applications that do not want to perform a separate date conversion. The transparent transmission of raw data and timeout information, as well as the consistent event handling, make this block a practical and standards-compliant component for ISOBUS-based systems.
