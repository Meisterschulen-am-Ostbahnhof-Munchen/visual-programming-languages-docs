# F_SPLIT_LTOD

![F_SPLIT_LTOD](F_SPLIT_LTOD.svg)

* * * * * * * * * *
## Introduction

`F_SPLIT_LTOD` splits a `LTIME_OF_DAY` value into its individual date/time components (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`). It is the reverse of [F_CONCAT_LTOD](F_CONCAT_LTOD.md), which combines the same individual components back into a `LTIME_OF_DAY` value.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the split, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Data Inputs**

- **IN** (`LTIME_OF_DAY`): The date/time value to split.

### **Data Outputs**

- **HOUR** (USINT): hour.
- **MINUTE** (USINT): minute.
- **SECOND** (USINT): second.
- **MILLISECOND** (UDINT): millisecond.

## Functionality

On `REQ`, `IN` is split into its individual components, output via `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`. `CNF` is then triggered.

## Technical Features

- **Fixed output types**: Unlike [F_CONCAT_LTOD](F_CONCAT_LTOD.md) (generic `ANY_INT`), the outputs here are fixed to concrete integer types chosen to fit each value's range (e.g. `USINT` for month/day, whose range is small).

## State Overview

Stateless: every `REQ` immediately results in the split and `CNF`.

## Application Scenarios

- **Displaying/processing individual date/time components**, e.g. for a formatted display on a panel or for calculations that only need a specific component.
- **Logging**: Breaking a timestamp down into its individual values for structured log output.

## Comparison with similar function blocks

- **[F_CONCAT_LTOD](F_CONCAT_LTOD.md)**: the reverse direction — combines individual components into a `LTIME_OF_DAY` value.

## Conclusion

`F_SPLIT_LTOD` provides a simple, direct split of a `LTIME_OF_DAY` value into its individual components, complementing the corresponding merge function [F_CONCAT_LTOD](F_CONCAT_LTOD.md).
