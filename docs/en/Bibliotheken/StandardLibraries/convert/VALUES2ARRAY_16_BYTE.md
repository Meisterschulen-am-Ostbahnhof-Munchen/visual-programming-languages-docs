# VALUES2ARRAY_16_BYTE

![VALUES2ARRAY_16_BYTE](VALUES2ARRAY_16_BYTE.svg)

* * * * * * * * * *
## Introduction

`VALUES2ARRAY_16_BYTE` combines 16 individual `BYTE` scalar variables `IN_1`…`IN_16` into a `BYTE` array of size 16. It is the reverse of `ARRAY2VALUES_16_BYTE` and belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)).

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8`, `IN_9`, `IN_10`, `IN_11`, `IN_12`, `IN_13`, `IN_14`, `IN_15`, `IN_16`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8`, `IN_9`, `IN_10`, `IN_11`, `IN_12`, `IN_13`, `IN_14`, `IN_15`, `IN_16` (`BYTE`): The 16 individual values (8-bit bit pattern) to be combined into the array.

### **Data Outputs**

- **OUT** (`BYTE`, array size 16): `OUT[i-1]` corresponds to `IN_i`.

## Functionality

On `REQ`, every input value `IN_i` is written to the corresponding element `OUT[i-1]` (`IN_1` → `OUT[0]`, …, `IN_16` → `OUT[15]`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md) and the other `VALUES2ARRAY_*` variants.
- **Fixed size 16**: For other array sizes of the same type see `VALUES2ARRAY_2_BYTE`, `VALUES2ARRAY_4_BYTE`, `VALUES2ARRAY_8_BYTE`, `VALUES2ARRAY_32_BYTE`.

## State Overview

Stateless: every `REQ` immediately results in a full merge and `CNF`.

## Application Scenarios

- **Building an array from individual values**: Several discrete `BYTE` variables need to be passed as an array to a downstream block that expects an array interface.
- **Interface adaptation** between variable-based and array-based block interfaces.

## Comparison with similar function blocks

- **[VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`ARRAY2VALUES_16_BYTE`**: the reverse direction — splits an array into 16 individual values.

## Conclusion

`VALUES2ARRAY_16_BYTE` provides a simple, generically implemented merge of 16 `BYTE` individual values into an array and is suitable for adapting variable-based to array-based interfaces.
