# ARRAY2VALUES_4_BYTE

![ARRAY2VALUES_4_BYTE](ARRAY2VALUES_4_BYTE.svg)

* * * * * * * * * *

## Introduction

`ARRAY2VALUES_4_BYTE` splits a `BYTE` array of size 4 into 4 individual scalar variables `OUT_1`…`OUT_4`. It belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)) and converts array data into discrete individual values.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the split, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`.

### **Data Inputs**

- **IN** (`BYTE`, array size 4): The array to split (8-bit bit pattern).

### **Data Outputs**

- `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4` (`BYTE`): `OUT_i` corresponds to `IN[i-1]`, i.e. the i-th element of the array.

## Functionality

On `REQ`, every element of `IN` is copied to the corresponding scalar output `OUT_i` (`IN[0]` → `OUT_1`, …, `IN[3]` → `OUT_4`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md) and the other `ARRAY2VALUES_*` variants.
- **Fixed size 4**: For other array sizes of the same type see `ARRAY2VALUES_2_BYTE`, `ARRAY2VALUES_8_BYTE`, `ARRAY2VALUES_16_BYTE`, `ARRAY2VALUES_32_BYTE`.

## State Overview

Stateless: every `REQ` immediately results in a full split and `CNF`.

## Application Scenarios

- **Data preparation**: An upstream block delivers a `BYTE` array, but a downstream block needs discrete individual variables.
- **Interface adaptation** between array-based and variable-based block interfaces.

## Comparison with similar function blocks

- **[ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`VALUES2ARRAY_4_BYTE`**: the reverse direction — combines 4 individual values into an array.
- **`ARRAY2ARRAY_2_BYTE`**: copies the array unchanged instead of splitting it.

## Conclusion

`ARRAY2VALUES_4_BYTE` provides a simple, generically implemented split of a `BYTE` array of size 4 into 4 discrete individual variables and is suitable for adapting array-based to variable-based interfaces.
