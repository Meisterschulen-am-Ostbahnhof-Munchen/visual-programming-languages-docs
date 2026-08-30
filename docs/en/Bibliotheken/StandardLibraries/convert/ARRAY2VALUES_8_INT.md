# ARRAY2VALUES_8_INT

![ARRAY2VALUES_8_INT](ARRAY2VALUES_8_INT.svg)

* * * * * * * * * *

## Introduction

`ARRAY2VALUES_8_INT` splits a `INT` array of size 8 into 8 individual scalar variables `OUT_1`…`OUT_8`. It belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)) and converts array data into discrete individual values.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the split, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`, `OUT_5`, `OUT_6`, `OUT_7`, `OUT_8`.

### **Data Inputs**

- **IN** (`INT`, array size 8): The array to split (16-bit signed integer).

### **Data Outputs**

- `OUT_1`, `OUT_2`, `OUT_3`, `OUT_4`, `OUT_5`, `OUT_6`, `OUT_7`, `OUT_8` (`INT`): `OUT_i` corresponds to `IN[i-1]`, i.e. the i-th element of the array.

## Functionality

On `REQ`, every element of `IN` is copied to the corresponding scalar output `OUT_i` (`IN[0]` → `OUT_1`, …, `IN[7]` → `OUT_8`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md) and the other `ARRAY2VALUES_*` variants.
- **Fixed size 8**: For other array sizes of the same type see .

## State Overview

Stateless: every `REQ` immediately results in a full split and `CNF`.

## Application Scenarios

- **Data preparation**: An upstream block delivers a `INT` array, but a downstream block needs discrete individual variables.
- **Interface adaptation** between array-based and variable-based block interfaces.

## Comparison with similar function blocks

- **[ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`VALUES2ARRAY_8_INT`**: the reverse direction — combines 8 individual values into an array.
- **`ARRAY2ARRAY_8_INT`**: copies the array unchanged instead of splitting it.

## Conclusion

`ARRAY2VALUES_8_INT` provides a simple, generically implemented split of a `INT` array of size 8 into 8 discrete individual variables and is suitable for adapting array-based to variable-based interfaces.
