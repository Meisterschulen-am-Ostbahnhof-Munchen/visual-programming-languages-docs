# F_CONCAT_DATE

![F_CONCAT_DATE](F_CONCAT_DATE.svg)

* * * * * * * * * *
## Introduction

`F_CONCAT_DATE` combines individual date/time components (`YEAR`, `MONTH`, `DAY`) into a composite `DATE` value. It is the reverse of [F_SPLIT_DATE](F_SPLIT_DATE.md), which splits the same `DATE` value back into its individual components.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `YEAR`, `MONTH`, `DAY`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **YEAR** (ANY_INT): year.
- **MONTH** (ANY_INT): month.
- **DAY** (ANY_INT): day.

### **Data Outputs**

- **OUT** (`DATE`): The value composed from the individual components.

## Functionality

On `REQ`, the input values `YEAR`, `MONTH`, `DAY` are combined into a `DATE` value and output via `OUT`. `CNF` is then triggered.

## Technical Features

- **`ANY_INT` inputs**: The date/time components accept any integer type, simplifying wiring with differently typed source values.
- **No documented range checking**: The block assumes plausible input values (e.g. `MONTH` 1–12); explicit validation is the caller's responsibility.

## State Overview

Stateless: every `REQ` immediately results in the merge and `CNF`.

## Application Scenarios

- **Building timestamps** from separately captured or computed individual values, e.g. from sensor data, user input, or communication protocols.
- **Configuration evaluation**: Combining date/time components held in individual variables into a usable `DATE` value.

## Comparison with similar function blocks

- **[F_SPLIT_DATE](F_SPLIT_DATE.md)**: the reverse direction — splits a `DATE` value into its individual components.
- **`F_CONCAT_DATE_TOD`**: instead combines an already-complete `DATE` and `TIME_OF_DAY` value into `DATE_AND_TIME`, rather than from individual fields.

## Conclusion

`F_CONCAT_DATE` provides a simple, direct merge of individual date/time values into a `DATE` value, complementing the corresponding split function [F_SPLIT_DATE](F_SPLIT_DATE.md).
