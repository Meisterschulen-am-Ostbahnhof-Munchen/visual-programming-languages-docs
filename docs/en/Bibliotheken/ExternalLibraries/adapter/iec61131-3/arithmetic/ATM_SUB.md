# ATM_SUB

![ATM_SUB](./ATM_SUB.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_SUB** subtracts two time values (type TIME) via fully adapter-based interfaces: `IN2` is subtracted from `IN1`, and the result is written to the output adapter only on an actual value change. Unlike the generic `ATM_ADD_*` blocks, ATM_SUB is implemented as a hand-wired composite FB that maps change detection explicitly through its own sub-blocks.

## Interface Structure

### **Event Inputs**

None -- triggering happens exclusively via the adapter sockets `IN1`/`IN2`.

### **Event Outputs**

No explicit event outputs in the interface list. The result is provided via the output adapter **OUT**, whose event (E1) is only sent on an actual value change.

### **Data Inputs**

None.

### **Data Outputs**

None. The subtraction result is output via the output adapter **OUT** as a data value (D1).

### **Adapters**

- **IN1** (Adapter, type `adapter::types::unidirectional::ATM`): Minuend.
- **IN2** (Adapter, type `adapter::types::unidirectional::ATM`): Subtrahend.
- **OUT** (Adapter, type `adapter::types::unidirectional::ATM`): Result of `IN1 - IN2`.

## Functionality

An event at **IN1.E1** or **IN2.E1** internally triggers the function block **F_SUB** (type `iec61131::arithmetic::F_SUB`), which computes `IN1.D1 - IN2.D1`. The result then passes through **F_MOVE** (type `iec61131::selection::F_MOVE`, hardwired with `DataType="TIME"`) into an **E_D_FF_ANY** block (type `iec61499::events::E_D_FF_ANY`). This block compares the new value with the last stored one and only lets the event through to **OUT.E1** if the value has actually changed -- the new value is written to **OUT.D1** in every case.

## Technical Features

- **Explicit change detection as a composite structure:** Unlike the generic `GEN_ATM_*` blocks, which implement change detection in C++, ATM_SUB maps it via the `F_SUB → F_MOVE → E_D_FF_ANY` chain inside the FBNetwork.
- **F_MOVE as a type anchor:** The `F_MOVE` block carries the `DataType="TIME"` attribute, pinning the generic `ANY` data path to `TIME` before it is fed into `E_D_FF_ANY`.
- **Fully adapter-based:** Both operands and the result are implemented as `ATM` adapters; there are no classic data inputs/outputs.

## State Overview

The block implicitly holds the last output value in the internal `E_D_FF_ANY` storage:

- **Wait** for an event at IN1.E1 or IN2.E1
- **Compute** IN1 − IN2 via F_SUB
- **Compare** against the value stored in E_D_FF_ANY
- **Output**: OUT.D1 is always updated, OUT.E1 is only sent on an actual change

## Application Scenarios

- Calculating remaining durations or differences between two time values, e.g., target minus actual time.
- Reducing downstream event load when the result does not change across multiple cycles.

## Comparison with Similar Function Blocks

- **ATM_ADD_2/3/4:** Add instead of subtracting; implemented as generic `GEN_ATM_ADD` blocks (change detection in C++, not a visible FBNetwork).
- **F_SUB:** The direct, adapter-free subtraction block without its own change detection, used internally by ATM_SUB.

## Conclusion

`ATM_SUB` provides a fully adapter-based subtraction of two time values with explicit, FBNetwork-visible change detection. It is particularly suitable wherever differences between time values are needed and unnecessary follow-up events for an unchanged result should be avoided.
