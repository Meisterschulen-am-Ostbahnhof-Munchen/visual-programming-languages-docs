# VALUES2ARRAY_8_INT

![VALUES2ARRAY_8_INT](VALUES2ARRAY_8_INT.svg)

* * * * * * * * * *

## Introduction

`VALUES2ARRAY_8_INT` combines 8 individual `INT` scalar variables `IN_1`…`IN_8` into a `INT` array of size 8. It is the reverse of `ARRAY2VALUES_8_INT` and belongs to the generic `GEN_ARRAY2ARRAY` family (cf. [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)).

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the merge, carries `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- `IN_1`, `IN_2`, `IN_3`, `IN_4`, `IN_5`, `IN_6`, `IN_7`, `IN_8` (`INT`): The 8 individual values (16-bit signed integer) to be combined into the array.

### **Data Outputs**

- **OUT** (`INT`, array size 8): `OUT[i-1]` corresponds to `IN_i`.

## Functionality

On `REQ`, every input value `IN_i` is written to the corresponding element `OUT[i-1]` (`IN_1` → `OUT[0]`, …, `IN_8` → `OUT[7]`), then `CNF` is triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_ARRAY2ARRAY'`, the same C++ base as [VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md) and the other `VALUES2ARRAY_*` variants.
- **Fixed size 8**: For other array sizes of the same type see .

## State Overview

Stateless: every `REQ` immediately results in a full merge and `CNF`.

## Application Scenarios

- **Building an array from individual values**: Several discrete `INT` variables need to be passed as an array to a downstream block that expects an array interface.
- **Interface adaptation** between variable-based and array-based block interfaces.

## Comparison with similar function blocks

- **[VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.md)**: the same generic implementation for data type `LREAL`.
- **`ARRAY2VALUES_8_INT`**: the reverse direction — splits an array into 8 individual values.

## Conclusion

`VALUES2ARRAY_8_INT` provides a simple, generically implemented merge of 8 `INT` individual values into an array and is suitable for adapting variable-based to array-based interfaces.
