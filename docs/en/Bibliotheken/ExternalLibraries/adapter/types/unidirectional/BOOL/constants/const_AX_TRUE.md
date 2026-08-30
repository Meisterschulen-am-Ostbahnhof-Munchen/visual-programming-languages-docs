# const_AX_TRUE

![const_AX_TRUE](const_AX_TRUE.svg)

* * * * * * * * * *

## Introduction

`const_AX_TRUE` is a simple constant block that writes the fixed value `TRUE` to an [AX](../AX.md) adapter plug on initialization. It is used to feed statically wired Boolean constants into an AX adapter network without wiring a separate event and data line for it.

## Interface Structure

### **Event Inputs**

- **INIT**: initialization request. Triggers the constant value being written to plug `OUT`.

### **Event Outputs**

- **INITO**: confirms completion of the initialization.

### **Data Inputs**

- None. The value `TRUE` is hard-wired into the block (`Parameter Name="D1" Value="TRUE"` on plug `OUT`).

### **Data Outputs**

- None directly; the value is only made available through adapter `OUT`.

### **Adapters**

- **OUT** (Plug, type `AX`): on `INIT`, outputs the fixed value `TRUE` through its `E1`/`D1` adapter event.

## Functionality

When the event `INIT` arrives, `const_AX_TRUE` triggers two internal connections: `INIT` is forwarded directly to `OUT.E1`, so the `OUT` plug fires its adapter event carrying the hard-parameterized data value `D1 = TRUE`. `INIT` is also forwarded to `INITO`, letting the caller know that initialization has completed.

## Technical Details

- The value `TRUE` is stored as a `Parameter` attribute directly on `OUT`'s `AdapterDeclaration` element, not as runtime data -- the block has no way to output a different value at runtime. If a runtime-configurable start value is needed, use [initval_AX](../initval/initval_AX.md) instead.
- Pure wiring logic with no ECC/state machine of its own (a composite FB with no internal function block instances).

## State Overview

The block is stateless: every `INIT` event immediately results in `TRUE` being output on `OUT` and confirmed via `INITO`.

## Application Scenarios

- Initializing AX adapter connections with a fixed `TRUE` start value, e.g. as an enable constant
- Test setups where an AX input needs a fixed value without a real sensor or upstream block
- Replacing a manually wired constant connection in generic, AX-adapter-based networks

## ⚖️ Comparison with Similar Blocks

Compare with [const_AX_FALSE](const_AX_FALSE.md), which uses the same mechanism for the value `FALSE`, and with [initval_AX](../initval/initval_AX.md), which serves the same purpose but with a value configurable at runtime via `INIT_VAL` instead of a hard-wired one.

## Conclusion

`const_AX_TRUE` is the simplest way to initialize an AX adapter plug with a fixed `TRUE` constant, and fits anywhere the value is known at design time and no runtime configuration is required.
