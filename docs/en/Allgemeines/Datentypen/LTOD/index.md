# Data Type Details: LTOD
## Description
The **LTOD** (Long Time of Day) data type represents the time of day with a high resolution of 64 bits (nanosecond precision).
## Normative Definition
According to **DIN EN 61131-3** (Table 10, No. 14b):
| Property | Value |
| :--- | :--- |

| **Bits** | 64 bits |

| **Default Value** | `LTOD#00:00:00` |

## Literal Representation
Literals begin with the prefix `LTOD#` or `LONG_TIME_OF_DAY#`.

### Examples
- `LTOD#15:36:55.360227400`
- `LONG_TIME_OF_DAY#00:00:00.000000001`
