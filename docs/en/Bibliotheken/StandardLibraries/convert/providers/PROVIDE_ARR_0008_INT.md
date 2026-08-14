# PROVIDE_ARR_0008_INT

![PROVIDE_ARR_0008_INT](PROVIDE_ARR_0008_INT.svg)

* * * * * * * * * *
## Introduction

`PROVIDE_ARR_0008_INT` provides a fixed-size `INT` array container of size 8 as an `InOut` variable `D1`. It belongs to the generic `GEN_INIT_ARR` family: a series of identically structured blocks that only differ in array size and data type, used to make an array that can be pre-filled with start values at design time available inside a 4diac application.

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization request, carries `D1`.

### **Event Outputs**

- **INITO**: Confirms the initialization, carries `D1`.

### **In/Out Variables**

- **D1** (`INT`, array size 8, index 0…7): The array container (16-bit signed integer per element). Can be pre-filled with start values in the FB instance editor (e.g. `[16#01, 16#00, ...]` for `BYTE`).

## Functionality

On `INIT`, the block reads the `InOut` array `D1` (which may already be pre-filled with start values at design time) and immediately confirms this via `INITO`, forwarding `D1` unchanged. The block performs no computation of its own — it acts as a declarative container whose content is set via the FB instance parameterization.

## Technical Features

- **Generic implementation**: `eclipse4diac::core::GenericClassName = 'GEN_INIT_ARR'`, the same C++ base as all other `PROVIDE_ARR_*` variants; array size and data type are fixed per instantiation via the type definition.
- **InOut instead of separate input/output**: `D1` is a single `InOut` variable — pre-filling and provisioning happen through the same variable, there is no separate copy.
- **Fixed size 8**: Other sizes of the same or different data types: none.

## State Overview

Stateless: `INIT` reads `D1` and confirms immediately via `INITO`, without modifying the content.

## Application Scenarios

- **Configuration arrays**: Providing fixed, pre-filled tables (e.g. calibration values, lookup tables, protocol header bytes) as a reusable block that can be parameterized at design time.
- **Test data generation**: Providing a predefined `INT` array for test setups without manually re-wiring the array in every application.

## Comparison with similar function blocks

- none: the same generic implementation with a different array size or data type.
- **`ARRAY2ARRAY_8_INT`**: copies an already existing array instead of providing/pre-filling one.

## Conclusion

`PROVIDE_ARR_0008_INT` provides a simple, design-time pre-fillable `INT` array container of fixed size 8 and is suitable for configuration and test-data arrays intended for reuse across 4diac applications.
