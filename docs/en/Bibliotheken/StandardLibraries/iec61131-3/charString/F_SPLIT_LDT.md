# F_SPLIT_LDT

![F_SPLIT_LDT](F_SPLIT_LDT.svg)

* * * * * * * * * *
## Introduction

`F_SPLIT_LDT` splits a `LDATE_AND_TIME` value into its individual date/time components (`YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`). It is the reverse of [F_CONCAT_LDT](F_CONCAT_LDT.md), which combines the same individual components back into a `LDATE_AND_TIME` value.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the split, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Data Inputs**

- **IN** (`LDATE_AND_TIME`): The date/time value to split.

### **Data Outputs**

- **YEAR** (UINT): year.
- **MONTH** (USINT): month.
- **DAY** (USINT): day.
- **HOUR** (USINT): hour.
- **MINUTE** (USINT): minute.
- **SECOND** (USINT): second.
- **MILLISECOND** (UDINT): millisecond.

## Functionality

On `REQ`, `IN` is split into its individual components, output via `YEAR`, `MONTH`, `DAY`, `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`. `CNF` is then triggered.

## Technical Features

- **Fixed output types**: Unlike [F_CONCAT_LDT](F_CONCAT_LDT.md) (generic `ANY_INT`), the outputs here are fixed to concrete integer types chosen to fit each value's range (e.g. `USINT` for month/day, whose range is small).

## State Overview

Stateless: every `REQ` immediately results in the split and `CNF`.

## Application Scenarios

- **Displaying/processing individual date/time components**, e.g. for a formatted display on a panel or for calculations that only need a specific component.
- **Logging**: Breaking a timestamp down into its individual values for structured log output.

## Comparison with similar function blocks

- **[F_CONCAT_LDT](F_CONCAT_LDT.md)**: the reverse direction — combines individual components into a `LDATE_AND_TIME` value.

## Conclusion

`F_SPLIT_LDT` provides a simple, direct split of a `LDATE_AND_TIME` value into its individual components, complementing the corresponding merge function [F_CONCAT_LDT](F_CONCAT_LDT.md).
