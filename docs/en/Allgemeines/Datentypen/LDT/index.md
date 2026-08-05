# Data Type Details: LDT
## Description
The **LDT** (Long Date and Time) data type combines date and high-resolution time in a single 64-bit element.
## Normative Definition
According to **DIN EN 61131-3** (Table 10, No. 15b):
| Property | Value |
| :--- | :--- |
| **Bits** | 64 Bits |
| **Default Value** | `LDT#1970-01-01-00:00:00` |

## Literal Representation
Literals begin with the prefix `LDT#` or `LONG_DATE_AND_TIME#`.

## Examples
- `LDT#2026-01-17-12:00:00.000000000`
- `LONG_DATE_AND_TIME#1984-06-25-15:36:55.360227400`
