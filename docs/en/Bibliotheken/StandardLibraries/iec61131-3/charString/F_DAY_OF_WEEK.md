# F_DAY_OF_WEEK

![F_DAY_OF_WEEK](F_DAY_OF_WEEK.svg)

* * * * * * * * * *
## Introduction

`F_DAY_OF_WEEK` determines the day of the week, as a number, from a date (`DATE`). It is a simple calendar-calculation function block per IEC 61131-3.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the calculation, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN** (DATE): The input date.

### **Data Outputs**

- **OUT** (USINT): The day of the week (`0` = Sunday, `1` = Monday, …, `6` = Saturday).

## Functionality

On `REQ`, the algorithm's ST statement `OUT := DAY_OF_WEEK(IN)` computes the day of the week for `IN` and outputs it via `OUT`. `CNF` is then triggered.

## Technical Features

- **`0`–`6` encoding**: Sunday is `0`, Saturday is `6` — this encoding should be kept in mind when comparing against other, possibly Monday-based day-of-week conventions.

## State Overview

Stateless: every `REQ` immediately results in the calculation and `CNF`.

## Application Scenarios

- **Day-of-week-dependent control logic**: e.g. different operating programs on weekdays vs. weekends.
- **Display/logging**: Outputting the day of the week alongside a date in displays or log entries.
- **Scheduling**: Checking whether a computed date falls on a particular day of the week.

## Comparison with similar function blocks

- **[F_SPLIT_DATE](F_SPLIT_DATE.md)**: splits a date into year/month/day, but does not compute a day of the week.

## Conclusion

`F_DAY_OF_WEEK` provides a simple calendar calculation to determine the day of the week from a `DATE` value and is suitable for day-of-week-dependent control and display logic.
