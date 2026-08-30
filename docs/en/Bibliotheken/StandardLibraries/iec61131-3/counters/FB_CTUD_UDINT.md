# FB_CTUD_UDINT

![FB_CTUD_UDINT](FB_CTUD_UDINT.svg)

* * * * * * * * * *

## Introduction

The function block `FB_CTUD_UDINT` is a combined up/down counter for data type `UDINT` (32-bit unsigned integer). It counts up on `CU` and down on `CD`, can be loaded with a preset value `PV` via `LD`, and reset to `0` via `R`.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers execution, linked with `CU`, `CD`, `R`, `LD`, `PV`.

### **Event Outputs**

- **CNF**: Confirms execution, linked with `QU`, `QD`, `CV`.

### **Data Inputs**

- **CU** (BOOL): Count up when `TRUE`.
- **CD** (BOOL): Count down when `TRUE`.
- **R** (BOOL): Reset — sets `CV` to `0`, takes priority over `LD`/`CU`/`CD`.
- **LD** (BOOL): Load — loads `PV` into `CV`, provided `R` is not active.
- **PV** (UDINT): Preset value compared against `CV`.

### **Data Outputs**

- **QU** (BOOL): `TRUE` when `CV >= PV`.
- **QD** (BOOL): `TRUE` when `CV <= 0`.
- **CV** (UDINT): Current count value.

## Functionality

On every `REQ` event, the block evaluates the inputs in the following priority: if `R` is active, `CV := 0`. Otherwise, if `LD` is active, `CV := PV`. If neither `R` nor `LD` is active and `CU`/`CD` are not active at the same time, `CV` is incremented by 1 on `CU` (provided `CV < 4294967295`) or decremented by 1 on `CD` (provided `CV > 0`). Finally, `QU := CV >= PV` and `QD := CV <= 0` are computed.

## Technical Features

- **Prioritization**: `R` (reset) takes priority over `LD` (load), which in turn takes priority over the actual counting operation.
- **Simultaneous `CU`+`CD`**: If both are `TRUE` at the same time, no count change occurs (`NOT(CU AND CD)` condition in the algorithm's ST).
- **Range limiting**: The count value is clamped at `4294967295` (the maximum value of `UDINT`) on the upper end and at `0` on the lower end.

## State Overview

1. **Reset**: `R = TRUE` → `CV := 0`.
2. **Load**: `R = FALSE`, `LD = TRUE` → `CV := PV`.
3. **Counting**: `R = FALSE`, `LD = FALSE` → `CV` is adjusted based on `CU`/`CD`.
4. **Output**: `QU`/`QD` are recomputed from the current `CV`, `CNF` is triggered.

## Application Scenarios

- **Bidirectional counting tasks with a large value range**, e.g. piece counts or position values that need both incrementing and decrementing and can exceed the range of `UINT`/`DINT`.
- **Fill-level or buffer counting**, where `QU`/`QD` act as upper/lower-bound signals for downstream logic.

## Comparison with similar function blocks

- **`FB_CTUD`**: the same functionality for data type `INT`.
- **`FB_CTUD_DINT`/`FB_CTUD_LINT`/`FB_CTUD_ULINT`**: the same functionality for other integer types.
- **`FB_CTU_UDINT`/`FB_CTD_UDINT`**: the pure up- or down-counter variants for `UDINT`, without the combined `LD` function.

## Conclusion

`FB_CTUD_UDINT` provides a complete up/down counter with load and reset functionality for the `UDINT` value range, closing the gap between the already available `FB_CTUD_*` variants for other data types.
