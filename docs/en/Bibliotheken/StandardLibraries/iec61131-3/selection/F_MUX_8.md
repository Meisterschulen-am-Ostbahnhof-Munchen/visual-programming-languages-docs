# F_MUX_8

![F_MUX_8](F_MUX_8.svg)

* * * * * * * * * *
## Introduction

`F_MUX_8` is the generic 8-input variant of the standard multiplexer block `F_MUX` (cf. `F_MUX_2`/`F_MUX_3`/`F_MUX_4`). Based on the selector `K`, it picks one of 8 input values (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`, `IN8`) and outputs it via `OUT`.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the selection, carries `K` and `IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`, `IN8`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **K** (ANY_INT): Selects one of the 8 inputs (`0`-based).
- `IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`, `IN8` (ANY): The 8 candidate input values.

### **Data Outputs**

- **OUT** (ANY): The selected input value: `IN1` when `K = 0`, `IN2` when `K = 1`, `IN3` when `K = 2`, `IN4` when `K = 3`, `IN5` when `K = 4`, `IN6` when `K = 5`, `IN7` when `K = 6`, `IN8` when `K = 7`.

## Functionality

On `REQ`, depending on the value of `K`, the corresponding input (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`, `IN8`) is passed through to `OUT`: `IN1` when `K = 0`, `IN2` when `K = 1`, `IN3` when `K = 2`, `IN4` when `K = 3`, `IN5` when `K = 4`, `IN6` when `K = 5`, `IN7` when `K = 6`, `IN8` when `K = 7`. `CNF` is then triggered.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_F_MUX'`, the same C++ base as `F_MUX_2`/`F_MUX_3`/`F_MUX_4`; only the number of inputs differs per instantiation.
- **`ANY` data type**: Both inputs `IN1`…`IN8` and `OUT` are generically typed and adapt to the connected data type when wired.
- **`0`-based selector**: `K = 0` selects `IN1`, `K = 7` selects `IN8`.

## State Overview

Stateless: every `REQ` immediately results in the selection and `CNF`.

## Application Scenarios

- **Multi-way selection with more than 4 sources**: Wherever a selection is needed among more than the 4 inputs supported by `F_MUX_4`, without cascading multiple `F_MUX` blocks.
- **Signal switching**: Selecting one of several sensor or source signals based on a control value `K`.

## Comparison with similar function blocks

- **`F_MUX_7`**: the same generic implementation with 7 instead of 8 inputs.
- **`F_SEL`**: binary selection between exactly two values based on a `BOOL` selector, functionally a special case of `F_MUX_2`.

## Conclusion

`F_MUX_8` extends the multiplexer principle of `F_MUX_2`/`F_MUX_3`/`F_MUX_4` to 8 selectable inputs and is the generic, 8-input-instantiated variant of the same underlying implementation.
