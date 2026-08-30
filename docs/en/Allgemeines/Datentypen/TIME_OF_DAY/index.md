# Data Type Details: TIME_OF_DAY (TOD)

## Description

The **TIME_OF_DAY** data type (abbreviated **TOD**) is used to represent the time of day.

## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 14a):

| Property | Value |
| :--- | :--- |
| **Bits** | Usually 32 bits (implementation dependent) |
| **Default Value** | `TOD#00:00:00` |

## Literal Representation

Literals begin with the prefix `TOD#` or `TIME_OF_DAY#`. The format follows the scheme `hh:mm:ss.ss`.

### Examples

- `TOD#15:36:55.36`
- `TIME_OF_DAY#08:00:00`
- `tod#23:59:59.999`
