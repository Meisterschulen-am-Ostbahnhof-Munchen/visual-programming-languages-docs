# ARRAY2ARRAY_2_INT

![ARRAY2ARRAY_2_INT](ARRAY2ARRAY_2_INT.svg)

* * * * * * * * * *

## Introduction

`ARRAY2ARRAY_2_INT` is a service interface function block that copies a `INT` array of size 2 unchanged from `IN` to `OUT`. It belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)) and serves as a pure type/interface bridge between two `INT` arrays of the same size.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the copy operation, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN** (`INT`, array size 2): The source array (16-bit signed integer).

### **Data Outputs**

- **OUT** (`INT`, array size 2): The destination array, identical values to `IN`.

## Functionality

On `REQ`, the 2 elements of `IN` are copied unchanged to `OUT`, then `CNF` is triggered. No type conversion or value change takes place — the block exists solely to decouple two array variables of identical type and size.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as all other `ARRAY2ARRAY_*` variants (e.g. [ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)); only array size and data type differ per instantiation.
- **Fixed size 2**: For other array sizes of the same type see `ARRAY2ARRAY_8_INT`.

## State Overview

Stateless: every `REQ` immediately results in a full copy and `CNF`.

## Application Scenarios

- **Interface decoupling**: One block provides a `INT` array of size 2 as output, another expects a separate input array — `ARRAY2ARRAY_2_INT` acts as a bridge with no side effects.
- **Data routing** of fixed-size `INT` arrays between parts of a 4diac application.

## Comparison with similar function blocks

- **[ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`ARRAY2ARRAY_8_INT`**: the same implementation with array size 8 instead of 2.
- **`ARRAY2VALUES_2_INT`**: splits the array into 2 individual scalar variables instead.

## Conclusion

`ARRAY2ARRAY_2_INT` provides a simple, generically implemented one-to-one copy of a `INT` array of size 2 and serves as an uncomplicated interface bridge between like-typed array variables.
