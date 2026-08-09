# Data Type Details: LDATE

## Description

The **LDATE** (Long Date) data type represents a calendar date with a width of 64 bits and allows for a significantly larger time frame.
## Normative Definition

According to **DIN EN 61131-3** (Table 10, No. 13b):
| Property | Value |
| :--- | :--- |
| **Bits** | 64 bits |
| **Default Value** | `LD#1970-01-01` |
| **Unit** | Nanoseconds since 1970-01-01 |

## Literal Representation

LDATE literals begin with the prefix `LD#` or `LDATE#`.

### Examples

- `LD#2026-01-17`
- `LDATE#2012-02-29` (Leap year support)
