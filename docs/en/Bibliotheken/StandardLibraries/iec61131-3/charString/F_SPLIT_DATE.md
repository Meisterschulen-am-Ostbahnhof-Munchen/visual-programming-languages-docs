# F_SPLIT_DATE

![F_SPLIT_DATE](F_SPLIT_DATE.svg)

* * * * * * * * * *
## Introduction

`F_SPLIT_DATE` splits a `DATE` value into its individual date/time components (`YEAR`, `MONTH`, `DAY`). It is the reverse of [F_CONCAT_DATE](F_CONCAT_DATE.md), which combines the same individual components back into a `DATE` value.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the split, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `YEAR`, `MONTH`, `DAY`.

### **Data Inputs**

- **IN** (`DATE`): The date/time value to split.

### **Data Outputs**

- **YEAR** (UINT): year.
- **MONTH** (USINT): month.
- **DAY** (USINT): day.

## Functionality

On `REQ`, `IN` is split into its individual components, output via `YEAR`, `MONTH`, `DAY`. `CNF` is then triggered.

## Technical Features

- **Fixed output types**: Unlike [F_CONCAT_DATE](F_CONCAT_DATE.md) (generic `ANY_INT`), the outputs here are fixed to concrete integer types chosen to fit each value's range (e.g. `USINT` for month/day, whose range is small).

## State Overview

Stateless: every `REQ` immediately results in the split and `CNF`.

## Application Scenarios

- **Displaying/processing individual date/time components**, e.g. for a formatted display on a panel or for calculations that only need a specific component.
- **Logging**: Breaking a timestamp down into its individual values for structured log output.

## Comparison with similar function blocks

- **[F_CONCAT_DATE](F_CONCAT_DATE.md)**: the reverse direction — combines individual components into a `DATE` value.

## Conclusion

`F_SPLIT_DATE` provides a simple, direct split of a `DATE` value into its individual components, complementing the corresponding merge function [F_CONCAT_DATE](F_CONCAT_DATE.md).
