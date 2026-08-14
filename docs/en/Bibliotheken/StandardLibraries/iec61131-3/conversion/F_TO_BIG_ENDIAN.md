# F_TO_BIG_ENDIAN

![F_TO_BIG_ENDIAN](F_TO_BIG_ENDIAN.svg)

* * * * * * * * * *
## Introduction

`F_TO_BIG_ENDIAN` converts a value to big-endian (most significant byte first) byte order. It belongs to the family of endian conversion functions needed for cross-platform exchange of binary data (e.g. over network protocols or with third-party systems).

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the conversion, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN** (ANY): The value to convert, of arbitrary data type.

### **Data Outputs**

- **OUT** (ANY): The converted value, same data type as `IN`.

## Functionality

On `REQ`, the block converts the natively encoded value `IN` into a big-endian (most significant byte first) byte sequence. The result is output via `OUT`, then `CNF` is triggered. The bit width of the data type stays unchanged — only the byte order is adjusted.

## Technical Features

- **Generic `ANY` data type**: `IN`/`OUT` adapt to whichever concrete data type is connected at compile time; the byte count follows from its size.
- **Pure byte reordering, no value reinterpretation**: The block only changes the arrangement of the bytes, not their meaning or sign.

## State Overview

Stateless: every `REQ` immediately results in the conversion and `CNF`.

## Application Scenarios

- **Network communication**: Many network protocols (e.g. TCP/IP headers) use big-endian ("network byte order"); `F_TO_BIG_ENDIAN` ensures the correct byte order when sending/receiving.
- **Interoperability with third-party systems**: Exchanging binary data with systems whose native byte order differs from the target platform's.

## Comparison with similar function blocks

- **`F_TO_LITTLE_ENDIAN`**: the same conversion direction, but for the other byte order.
- **`F_FROM_BIG_ENDIAN`**: the reverse direction for the same byte order.

## Conclusion

`F_TO_BIG_ENDIAN` provides a simple, generically typed byte-order conversion and is an important building block for correct interoperability with network protocols and third-party systems of differing endianness.
