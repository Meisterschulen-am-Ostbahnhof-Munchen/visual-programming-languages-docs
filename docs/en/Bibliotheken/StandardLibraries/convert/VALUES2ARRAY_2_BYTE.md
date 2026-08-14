# VALUES2ARRAY_2_BYTE

![VALUES2ARRAY_2_BYTE](VALUES2ARRAY_2_BYTE.svg)

* * * * * * * * * *
## Introduction

`VALUES2ARRAY_2_BYTE` combines 2 individual `BYTE` scalar variables `IN_1`…`IN_2` into a `BYTE` array of size 2. It is the reverse of `ARRAY2VALUES_2_BYTE` and belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)).

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `IN_1`, `IN_2`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- `IN_1`, `IN_2` (`BYTE`): The 2 individual values (8-bit bit pattern) to be combined into the array.

### **Data Outputs**

- **OUT** (`BYTE`, array size 2): `OUT[i-1]` corresponds to `IN_i`.

## Functionality

On `REQ`, every input value `IN_i` is written to the corresponding element `OUT[i-1]` (`IN_1` → `OUT[0]`, …, `IN_2` → `OUT[1]`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md) and the other `VALUES2ARRAY_*` variants.
- **Fixed size 2**: For other array sizes of the same type see `VALUES2ARRAY_4_BYTE`, `VALUES2ARRAY_8_BYTE`, `VALUES2ARRAY_16_BYTE`, `VALUES2ARRAY_32_BYTE`.

## State Overview

Stateless: every `REQ` immediately results in a full merge and `CNF`.

## Application Scenarios

- **Building an array from individual values**: Several discrete `BYTE` variables need to be passed as an array to a downstream block that expects an array interface.
- **Interface adaptation** between variable-based and array-based block interfaces.

## Comparison with similar function blocks

- **[VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`ARRAY2VALUES_2_BYTE`**: the reverse direction — splits an array into 2 individual values.

## Conclusion

`VALUES2ARRAY_2_BYTE` provides a simple, generically implemented merge of 2 `BYTE` individual values into an array and is suitable for adapting variable-based to array-based interfaces.
