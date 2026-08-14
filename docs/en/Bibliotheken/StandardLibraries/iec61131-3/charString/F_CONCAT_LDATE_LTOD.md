# F_CONCAT_LDATE_LTOD

![F_CONCAT_LDATE_LTOD](F_CONCAT_LDATE_LTOD.svg)

* * * * * * * * * *
## Introduction

`F_CONCAT_LDATE_LTOD` concatenates a date (`LDATE`) and a time of day (`LTIME_OF_DAY`) into a combined `LDATE_AND_TIME` timestamp. It is the `L`-prefixed (64-bit resolution) counterpart to `F_CONCAT_DATE_TOD`.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the concatenation, carries `IN1` and `IN2`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN1** (LDATE): The date.
- **IN2** (LTIME_OF_DAY): The time of day.

### **Data Outputs**

- **OUT** (LDATE_AND_TIME): The combined date and time timestamp.

## Functionality

On `REQ`, `IN1` (date) and `IN2` (time of day) are combined into an `LDATE_AND_TIME` value and output via `OUT`. `CNF` is then triggered.

## Technical Features

- **`L` data types**: Uses the high-resolution `LDATE`/`LTIME_OF_DAY`/`LDATE_AND_TIME` types with nanosecond resolution instead of the classic `DATE`/`TIME_OF_DAY`/`DATE_AND_TIME` types.

## State Overview

Stateless: every `REQ` immediately results in the concatenation and `CNF`.

## Application Scenarios

- **Combining separately captured, high-resolution date and time information** in control systems that work with `L` time types throughout.

## Comparison with similar function blocks

- **`F_CONCAT_DATE_TOD`**: the same functionality with the classic `DATE`/`TIME_OF_DAY`/`DATE_AND_TIME` types.
- **[F_CONCAT_LDT](F_CONCAT_LDT.md)**: instead combines individual fields (`YEAR`, `MONTH`, …) rather than already-complete `LDATE`/`LTIME_OF_DAY` values.

## Conclusion

`F_CONCAT_LDATE_LTOD` provides the high-resolution variant of date/time concatenation and is suitable for applications working with `L` time types throughout.
