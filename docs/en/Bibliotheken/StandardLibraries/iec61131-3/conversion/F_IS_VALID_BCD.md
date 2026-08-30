# F_IS_VALID_BCD

![F_IS_VALID_BCD](F_IS_VALID_BCD.svg)

* * * * * * * * * *

## Introduction

`F_IS_VALID_BCD` checks whether a bit string contains valid BCD (Binary Coded Decimal) data — i.e. whether every nibble (4-bit group) represents a value between `0` and `9`. It validates BCD-encoded values before they are converted.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the check, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN** (ANY_BIT): The bit string to check (`BYTE`, `WORD`, `DWORD`, or `LWORD`).

### **Data Outputs**

- **OUT** (BOOL): `TRUE` if every nibble of `IN` holds a valid BCD value (`0`–`9`); `FALSE` if at least one nibble holds an invalid value (`10`–`15`, i.e. `A`–`F`).

## Functionality

On `REQ`, the algorithm's ST statement `OUT := IS_VALID_BCD(IN)` checks nibble by nibble whether every 4-bit group of `IN` represents a valid decimal digit (`0`–`9`), and outputs the result via `OUT`. `CNF` is then triggered.

## Technical Features

- **`ANY_BIT` input**: Accepts bit strings of any width (`BYTE`, `WORD`, `DWORD`, `LWORD`); the number of nibbles checked follows from their size.
- **Pre-check for BCD conversion**: A useful companion to the `*_BCD_TO_*` conversion blocks (cf. `F_BYTE_BCD_TO_USINT` etc.), catching invalid input data before the actual conversion.

## State Overview

Stateless: every `REQ` immediately results in the check and `CNF`.

## Application Scenarios

- **Validating fieldbus/protocol data** transmitted in BCD encoding, before converting it to a numeric value.
- **Error detection** for incorrectly transmitted or misinterpreted bit strings meant to be interpreted as BCD.

## Comparison with similar function blocks

- **[F_IS_VALID](F_IS_VALID.md)**: the same basic idea of validity checking, but for floating-point numbers instead of BCD bit strings.
- **`F_BYTE_BCD_TO_USINT`** and related conversion blocks: implicitly rely on the same BCD validity assumption; `F_IS_VALID_BCD` makes the check explicit and usable upstream.

## Conclusion

`F_IS_VALID_BCD` provides a simple upstream check for BCD-encoded bit strings and protects downstream BCD conversion blocks from invalid input data.
