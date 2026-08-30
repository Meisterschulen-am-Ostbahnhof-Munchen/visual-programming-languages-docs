# initval_ADI

![initval_ADI](initval_ADI.svg)

* * * * * * * * * *

## Introduction

`initval_ADI` is the configurable initialization block for the [ADI](../ADI.md) adapter (data type `DINT`, 32-bit signed integer): it accepts a start value as a data input at initialization time and writes it to a `ADI` adapter plug. This replaces the formerly common practice of feeding a constant comparison value in via a mixed adapter/elementary block.

## Interface Structure

### **Event Inputs**

- **INIT**: initialization request, carries `INIT_VAL`. Triggers `INIT_VAL` being written to plug `OUT`.

### **Event Outputs**

- **INITO**: confirms completion of the initialization.

### **Data Inputs**

- **INIT_VAL** (DINT): the start value written to adapter `OUT` when `INIT` arrives.

### **Data Outputs**

- None directly; the value is only made available through adapter `OUT`.

### **Adapters**

- **OUT** (Plug, type `ADI`): on `INIT`, outputs the value passed via `INIT_VAL` through its `E1`/`D1` adapter event.

## Functionality

When the event `INIT` arrives (carrying `With Var="INIT_VAL"`), `initval_ADI` links two internal data paths: `INIT_VAL` is copied to `OUT.D1` via a data connection, and `INIT` is forwarded to `OUT.E1` via an event connection -- so the `OUT` plug fires its adapter event carrying the value just supplied. `INIT` is also forwarded to `INITO`, letting the caller know that initialization has completed.

## Technical Details

- The output value is not parameterized in the block itself but supplied fresh via `INIT_VAL` on every `INIT` call -- so the block can also be used outside a pure initialization phase to dynamically set a `ADI` value.
- Pure wiring logic with no ECC/state machine of its own (a composite FB with no internal function block instances); the data connection `INIT_VAL → OUT.D1` must be evaluated before the event connection so that `OUT.E1` carries the current value -- this is guaranteed by IEC 61499's `FBNetwork` connection execution order and needs no separate wiring.

## State Overview

The block is stateless: every `INIT` event immediately results in `INIT_VAL` being written to `OUT` and confirmed via `INITO`.

## Application Scenarios

- Initializing `ADI` adapter connections with a project- or parameter-dependent start value (e.g. from a configuration variable)
- Replacement for the removed "mixed" adapter/elementary comparison blocks: a constant `DINT` value is fed onto a `ADI` adapter via `initval_ADI` and can then be used together with the pure adapter-based `ADI` comparison blocks.
- A reusable block template for test setups where different `ADI` start values need to be tried out

## ⚖️ Comparison with Similar Blocks

Compare with [initval_AX](../../BOOL/initval/initval_AX.md), which uses the same wiring mechanism for the `BOOL` data type. Unlike `const_AX_TRUE`/`const_AX_FALSE` (which only exist for `AX`), `initval_ADI` does not parameterize the output value in the block itself, but takes it from the data input `INIT_VAL`.

## Conclusion

`initval_ADI` provides simple, reusable initialization logic for the `ADI` adapter and makes the output value freely configurable via `INIT_VAL`. It is the right fit wherever a `DINT` start value isn't already fixed at design time, or as a replacement for a removed mixed comparison block.
