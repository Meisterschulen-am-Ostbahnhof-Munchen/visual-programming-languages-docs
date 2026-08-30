# Data Type Details: DATE_AND_TIME (DT)

## Description

The **DATE_AND_TIME** data type (abbreviated **DT**) combines a calendar date and time of day into a single element.

## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 15a):

| Property | Value |
| :--- | :--- |
| **Bits** | Usually 32 bits (implementation dependent) |
| **Default Value** | `DT#1970-01-01-00:00:00` |

## Literal Representation

Literals begin with the prefix `DT#` or `DATE_AND_TIME#`. The format follows the scheme `YYYY-MM-DD-hh:mm:ss.ss`.

### Examples

- `DT#2026-01-17-12:00:00`
- `DATE_AND_TIME#1984-06-25-15:36:55.36`
- `dt#2010-09-22-00:00:00`
