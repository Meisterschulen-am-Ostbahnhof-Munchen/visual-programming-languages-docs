# Exercise_012f: Numeric Value Input PHYS and Storage in Non-Volatile Memory (NVS) with Subapplication

* * * * * * * * * *
## Introduction

This exercise demonstrates the processing of a physical numeric value (PHYS) and its permanent storage in non-volatile memory (NVS). The value is configured via an input object pool, written to the NVS, and can then be output via a qualifier block. The exercise is implemented as a nested subapplication, with the innermost sub-block containing all the logic.
## Function Blocks (FBs) Used

The exercise consists of a main sub-block, which contains another sub-block. This innermost sub-block encapsulates the actual processing logic with three internal FBs.

### Sub-module: Exercise_012f_sub

- **Type**: `Uebungen::Uebung_012f_sub`
- **Interface**:
- Event output: `IND` (Event)
- Data inputs: `KEY` (STRING), `stObj` (NumericObjectPool_S)
- Data output: `VALUEO` (REAL)
- **Internal Function Blocks Used**:
- **NumericValue_PHYS** (`isobus::UT::io::NumericValue::NumericValue_PHYS`)
- Parameters: `QI` = `TRUE`
- Event output: `IND` → triggered when a valid value is present
- Data input: `stObj` (NumericObjectPool_S – configuration of the physical object)
- Data output: `rPhys` (REAL) – the read physical value
- **NVS** (`logiBUS::storage::esp32_nvs::NVS`)
- Parameters: `QI` = `TRUE`, `DEFAULT_VALUE` = `REAL#0.0`
- Event inputs: `INIT`, `SET`, `GET`
- Event outputs: `INITO` `SETO`, `GETO`
- Data inputs: `KEY` (STRING), `VALUE` (REAL)
- Data output: `VALUEO` (REAL) – the read or written value
- **Q_NumericValue_PHYS** (`isobus::UT::Q::Q_NumericValue_PHYS`)
- Event input: `REQ`
- Data inputs: `stObj` (NumericObjectPool_S), `rPhys` (REAL)
- Data output: (none visible in the XML, used for qualification/forwarding)
- **Functionality**:

The sub-module The NVS block receives the configuration data `KEY` and `stObj` from an external source. After the NVS block is initialized (event `INITO`), an event `GET` is immediately triggered to load the last stored value. If a valid physical value is present (event `IND` from `NumericValue_PHYS`), it is stored in the NVS along with the current value `rPhys` via `SET`. The loaded or stored value is processed via the qualifier block `Q_NumericValue_PHYS` and made available at output `VALUEO`. Events `SETO` and `GETO` are forwarded to the external output `IND`.

## Program Flow and Connections

The flow is event-driven:

1. **Initialization**: Upon startup, the NVS block receives a `INIT` event (not visible on the network, but implicitly transmitted by the environment). The function block acknowledges with `INITO` and immediately triggers a `GET` event (connection `NVS.INITO` -> `NVS.GET`). This reads the value stored under the passed `KEY` from the NVS.
2. **Value Update**: As soon as the `NumericValue_PHYS` function block has detected a valid physical value, it sends a `IND` event. This triggers the `SET` input of the NVS, which then stores the current `rPhys` value under the specified `KEY`.
2. **Value Update**: As soon as the `NumericValue_PHYS` function block has detected a valid physical value, it sends a `IND` event. This triggers the `SET` input of the NVS, causing the current `rPhys` value to be stored under the specified `KEY`.
3. **Output**: After both a `GET` (during initialization) and a `SET` (after saving), the result is forwarded via `NVS.VALUEO` to the `Q_NumericValue_PHYS` block and directly to the output `VALUEO`. The qualifier block formats the value according to the configuration (`stObj`).
4. **Signal Pass-Through**: The event outputs `SETO` and `GETO` of the NVS are passed through to the external output `IND`, thus informing the higher-level system of changes.

**Data Connections**:

- `stObj` (external) → `NumericValue_PHYS.stObj` (physical object configuration)
- `KEY` (external) → `NVS.KEY` (storage key)
- `NumericValue_PHYS.rPhys` → `NVS.VALUE` (value to be stored)
- `NVS.VALUEO` → `Q_NumericValue_PHYS.rPhys` (value to be forwarded)
- `stObj` (external) → `Q_NumericValue_PHYS.stObj` (output configuration)
- `NVS.VALUEO` → `VALUEO` (external Output)

## Summary

The exercise `Uebung_012f` demonstrates how a physical measurement value (via the `NumericValue_PHYS` block) is read, persistently stored in non-volatile memory (`NVS`), and output via a qualifier block. The storage key and object configuration are passed externally, enabling flexible reuse. Event-driven coupling ensures the correct sequence of reading, writing, and outputting. This structure is particularly suitable for applications where values need to be restored from memory after power-up.
