# Numbers and Number Systems

## 🎧 Podcast

## Number Systems

- [ISOBUS Terminals: Understanding Numbers – NumberVariable, InputNumber & OutputNumber explained ](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Terminals-Zahlen-verstehen--NumberVariable--InputNumber--OutputNumber-erklrt-e36aatd)
### Decimal System (Base 10)

The familiar system with the digits 0 to 9. It is mostly used in programming for human-readable values such as setpoints, counters, or time values.

*Example:* `125`

### Binary System (Base 2)

Since computers and controllers work internally with states (on/off, 0/1), the binary system is the most fundamental system. It consists only of the digits `0` and `1`.

*Example:* `2#1011` (corresponds to 11 in decimal)

### Hexadecimal system (base 16)

The hexadecimal system is particularly useful for programmers because a byte (8 bits) can be represented exactly by two hexadecimal digits (0-9 and A-F). It offers a compact representation of bit patterns.

In IEC 61131-3, hexadecimal numbers are designated with the prefix `16#`.

The hexadecimal system is particularly useful for programmers because a byte (8 bits) can be represented exactly by two hexadecimal digits (0-9 and A-F). *Example:* `16#FF` (corresponds to 255 in decimal or `2#11111111` in binary)

---

## Literals in IEC 61131-3 / IEC 61499

Literals are values hard-coded in the program code. Type prefixes can be used to tell the controller how to interpret a value.

Integers can be specified without decimal places.

- `1234` (Decimal)
- `-567` (Negative)
- `16#ABCD` (Hexadecimal)
- `2#1010_0101` (Binary, underscores for readability)

Values with decimal places or in scientific notation.

- `1.234`
- `-0.5`
- `1.0E-3` (equivalent to 0.001)
### Floating Point Numbers (Real)

### Integer Numbers

### Typed literals

Sometimes it is important to explicitly specify the data type to avoid ambiguity.

- `INT#15`
- `UINT#15`
- `REAL#15.0`
- `TIME#5s` (Duration of 5 seconds)

---

## Mathematical Background

For deeper insights into the set theory of numbers (natural, integer, real numbers), the following concepts provide a good foundation:

- **Natural Numbers (ℕ):** Positive integers {1, 2, 3, ...} – often used as the basis for `UINT` (Unsigned Integer).
- **Integers (ℤ):** Numbers without decimal places, including zero and negative numbers – basis for `INT`, `DINT`, `LINT`.
- **Real Numbers (ℝ):** Numbers with decimal places – basis for `REAL` and `LREAL`.
