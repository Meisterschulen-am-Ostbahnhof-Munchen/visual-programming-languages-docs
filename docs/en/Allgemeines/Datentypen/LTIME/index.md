# Data Type Details: LTIME

## Description

The **LTIME** (Long Time) data type is used to represent high-resolution time durations with a width of 64 bits.
## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 12b):
| Property | Value |
| :--- | :--- |
| **Bits** | 64 bits |
| **Default Value** | `LTIME#0s` |
| **Resolution** | Nanoseconds |

## Literal Representation

LTIME literals begin with the prefix `LT#` or `LTIME#`.

### Units (in addition to TIME)

- `us`: Microseconds
- `ns`: Nanoseconds

### Examples

- `LT#10ns` (10 nanoseconds)
- `LTIME#1000d12h30m5s12ms_450us_200ns` (Maximum precision)
- `LT#14.7s` (Decimal representation of the smallest unit is allowed)