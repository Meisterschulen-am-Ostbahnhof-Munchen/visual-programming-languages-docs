# Data Type Details: DATE

## Description
The **DATE** data type is used to represent a calendar date.

## Normative Definition
According to **DIN EN 61131-3** (Table 10, No. 13a):

| Property | Value |

| :--- | :--- |

| **Bits** | Usually 32 bits (implementation dependent) |

| **Default Value** | `D#1970-01-01` |

## Literal Representation
DATE literals begin with the prefix `D#` or `DATE#`. The format follows the scheme `YYYY-MM-DD`.


### Examples

- `D#2026-01-17`
- `DATE#1984-06-25`
- `d#2010-09-22` (Lowercase prefix is allowed)