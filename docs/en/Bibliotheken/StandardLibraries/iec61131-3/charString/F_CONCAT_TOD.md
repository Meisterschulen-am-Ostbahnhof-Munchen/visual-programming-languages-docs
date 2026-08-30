# F_CONCAT_TOD

![F_CONCAT_TOD](F_CONCAT_TOD.svg)

* * * * * * * * * *

## Introduction

`F_CONCAT_TOD` combines individual date/time components (`HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`) into a composite `TIME_OF_DAY` value. It is the reverse of [F_SPLIT_TOD](F_SPLIT_TOD.md), which splits the same `TIME_OF_DAY` value back into its individual components.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **HOUR** (ANY_INT): hour.
- **MINUTE** (ANY_INT): minute.
- **SECOND** (ANY_INT): second.
- **MILLISECOND** (ANY_INT): millisecond.

### **Data Outputs**

- **OUT** (`TIME_OF_DAY`): The value composed from the individual components.

## Functionality

On `REQ`, the input values `HOUR`, `MINUTE`, `SECOND`, `MILLISECOND` are combined into a `TIME_OF_DAY` value and output via `OUT`. `CNF` is then triggered.

## Technical Features

- **`ANY_INT` inputs**: The date/time components accept any integer type, simplifying wiring with differently typed source values.
- **No documented range checking**: The block assumes plausible input values (e.g. `MONTH` 1–12); explicit validation is the caller's responsibility.

## State Overview

Stateless: every `REQ` immediately results in the merge and `CNF`.

## Application Scenarios

- **Building timestamps** from separately captured or computed individual values, e.g. from sensor data, user input, or communication protocols.
- **Configuration evaluation**: Combining date/time components held in individual variables into a usable `TIME_OF_DAY` value.

## Comparison with similar function blocks

- **[F_SPLIT_TOD](F_SPLIT_TOD.md)**: the reverse direction — splits a `TIME_OF_DAY` value into its individual components.
- **`F_CONCAT_DATE_TOD`**: instead combines an already-complete `DATE` and `TIME_OF_DAY` value into `DATE_AND_TIME`, rather than from individual fields.

## Conclusion

`F_CONCAT_TOD` provides a simple, direct merge of individual date/time values into a `TIME_OF_DAY` value, complementing the corresponding split function [F_SPLIT_TOD](F_SPLIT_TOD.md).
