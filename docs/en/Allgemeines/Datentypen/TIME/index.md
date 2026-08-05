# Data Type Details: TIME

## Description
The **TIME** data type is used to represent durations of time (relative time).

## Normative Definition
According to **DIN EN 61131-3** (Table 10, No. 12a):

| Property | Value |

| :--- | :--- |

| **Bits** | Usually 32 bits (implementation-dependent) |

| **Default Value** | `T#0s` |

## Literal Representation
TIME literals always begin with the prefix `T#` or `TIME#`.


### Units
The following units can be combined (in descending order):

- `d`: Days
- `h`: Hours
- `m`: Minutes
- `s`: Seconds
- `ms`: Milliseconds

### Syntax Rules
- Underscores (`_`) are permitted for better readability.

- Negative durations are possible using a minus sign after the hash symbol (`T#-...`).

- Units can be mixed (e.g., days and milliseconds).


### Examples

- `T#10ms` (10 milliseconds)
- `T#2h_30m` (2 hours and 30 minutes)
- `T#5d4h3m2s1ms` (Combination of all units)
- `TIME#14ms` (Alternative notation)
- `T#-5s` (Negative duration of 5 seconds)
- `T#25h_15m` (Unit overflow is allowed, corresponds to 1 day, 1 hour, 15 minutes)

## 🛠️ Related Exercises

* [Exercise_020j2_AX_sub](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020j2_AX_sub.md)]

* [Exercise_072c](../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)]


