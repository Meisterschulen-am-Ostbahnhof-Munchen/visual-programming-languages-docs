# initval_AX

![initval_AX](initval_AX.svg)

* * * * * * * * * *

## Introduction

`initval_AX` is the configurable counterpart to the [const_AX_TRUE](../constants/const_AX_TRUE.md)/[const_AX_FALSE](../constants/const_AX_FALSE.md) blocks: instead of a hard-wired value, it accepts a Boolean start value as a data input at initialization time and writes it to an [AX](../AX.md) adapter plug.

## Interface Structure

### **Event Inputs**

- **INIT**: initialization request, carries `INIT_VAL`. Triggers `INIT_VAL` being written to plug `OUT`.

### **Event Outputs**

- **INITO**: confirms completion of the initialization.

### **Data Inputs**

- **INIT_VAL** (BOOL): the start value written to adapter `OUT` when `INIT` arrives.

### **Data Outputs**

- None directly; the value is only made available through adapter `OUT`.

### **Adapters**

- **OUT** (Plug, type `AX`): on `INIT`, outputs the value passed via `INIT_VAL` through its `E1`/`D1` adapter event.

## Functionality

When the event `INIT` arrives (carrying `With Var="INIT_VAL"`), `initval_AX` links two internal data paths: `INIT_VAL` is copied to `OUT.D1` via a data connection, and `INIT` is forwarded to `OUT.E1` via an event connection -- so the `OUT` plug fires its adapter event carrying the value just supplied. `INIT` is also forwarded to `INITO`, letting the caller know that initialization has completed.

## Technical Details

- Unlike `const_AX_TRUE`/`const_AX_FALSE`, the output value is not parameterized in the block itself but supplied fresh via `INIT_VAL` on every `INIT` call -- so the block can also be used outside a pure initialization phase to dynamically set an AX value.
- Pure wiring logic with no ECC/state machine of its own (a composite FB with no internal function block instances); the data connection `INIT_VAL → OUT.D1` must be evaluated before the event connection so that `OUT.E1` carries the current value -- this is guaranteed by IEC 61499's `FBNetwork` connection execution order and needs no separate wiring.

## State Overview

The block is stateless: every `INIT` event immediately results in `INIT_VAL` being written to `OUT` and confirmed via `INITO`.

## Application Scenarios

- Initializing AX adapter connections with a project- or parameter-dependent start value (e.g. from a configuration variable)
- Dynamically setting an AX value at runtime when `const_AX_TRUE`/`const_AX_FALSE`'s hard-wired value is not sufficient
- A reusable block template for test setups where different AX start values need to be tried out

## ⚖️ Comparison with Similar Blocks

Compare with [const_AX_TRUE](../constants/const_AX_TRUE.md) and [const_AX_FALSE](../constants/const_AX_FALSE.md), which use the same wiring mechanism but parameterize the output value in the block itself instead of taking it from a data input.

## Conclusion

`initval_AX` provides the same simple initialization logic as `const_AX_TRUE`/`const_AX_FALSE`, but makes the output value freely configurable via `INIT_VAL`, making it the right fit wherever the start value isn't already fixed at design time.
