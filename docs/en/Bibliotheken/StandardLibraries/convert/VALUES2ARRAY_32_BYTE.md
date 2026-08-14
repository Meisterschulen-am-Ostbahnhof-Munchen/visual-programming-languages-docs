# VALUES2ARRAY_32_BYTE

![VALUES2ARRAY_32_BYTE](VALUES2ARRAY_32_BYTE.svg)

* * * * * * * * * *
## Introduction

`VALUES2ARRAY_32_BYTE` combines 32 individual `BYTE` scalar variables `IN_1`…`IN_32` into a `BYTE` array of size 32. It is the reverse of `ARRAY2VALUES_32_BYTE` and belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)).

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8`, `IN_9`, `IN_10`, `IN_11`, `IN_12`, `IN_13`, `IN_14`, `IN_15`, `IN_16`, `IN_17`, `IN_18`, `IN_19`, `IN_20`, `IN_21`, `IN_22`, `IN_23`, `IN_24`, `IN_25`, `IN_26`, `IN_27`, `IN_28`, `IN_29`, `IN_30`, `IN_31`, `IN_32`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8`, `IN_9`, `IN_10`, `IN_11`, `IN_12`, `IN_13`, `IN_14`, `IN_15`, `IN_16`, `IN_17`, `IN_18`, `IN_19`, `IN_20`, `IN_21`, `IN_22`, `IN_23`, `IN_24`, `IN_25`, `IN_26`, `IN_27`, `IN_28`, `IN_29`, `IN_30`, `IN_31`, `IN_32` (`BYTE`): The 32 individual values (8-bit bit pattern) to be combined into the array.

### **Data Outputs**

- **OUT** (`BYTE`, array size 32): `OUT[i-1]` corresponds to `IN_i`.

## Functionality

On `REQ`, every input value `IN_i` is written to the corresponding element `OUT[i-1]` (`IN_1` → `OUT[0]`, …, `IN_32` → `OUT[31]`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md) and the other `VALUES2ARRAY_*` variants.
- **Fixed size 32**: For other array sizes of the same type see `VALUES2ARRAY_2_BYTE`, `VALUES2ARRAY_4_BYTE`, `VALUES2ARRAY_8_BYTE`, `VALUES2ARRAY_16_BYTE`.

## State Overview

Stateless: every `REQ` immediately results in a full merge and `CNF`.

## Application Scenarios

- **Building an array from individual values**: Several discrete `BYTE` variables need to be passed as an array to a downstream block that expects an array interface.
- **Interface adaptation** between variable-based and array-based block interfaces.

## Comparison with similar function blocks

- **[VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`ARRAY2VALUES_32_BYTE`**: the reverse direction — splits an array into 32 individual values.

## Conclusion

`VALUES2ARRAY_32_BYTE` provides a simple, generically implemented merge of 32 `BYTE` individual values into an array and is suitable for adapting variable-based to array-based interfaces.
