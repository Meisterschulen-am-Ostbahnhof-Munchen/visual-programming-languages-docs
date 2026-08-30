# E_REND_4

* * * * * * * * * *

## Introduction

`E_REND_4` is the generic 4-input variant of the rendezvous block `E_REND` (2 inputs). It only triggers `EO` once it has received at least one event since the last reset from **all** 4 inputs (`EI1`, `EI2`, `EI3`, `EI4`) — a logical AND across 4 asynchronous event streams.

![E_REND_4](E_REND_4.svg)

## Interface Structure

### **Event Inputs**

- **EI1**: Event input 1.
- **EI2**: Event input 2.
- **EI3**: Event input 3.
- **EI4**: Event input 4.
- **R (Reset)**: Resets the block to its initial state, discarding all events recorded so far.

### **Event Outputs**

- **EO**: Triggered once all 4 inputs have fired at least once since the last reset.

## Functionality

`E_REND_4` is implemented as a generic function block (`eclipse4diac::core::GenericClassName = 'GEN_E_REND'`) — the same C++ implementation underlies all `E_REND_n` variants; only the number of inputs differs. Internally, the block remembers which of the `EI1`…`EI4` inputs have already received at least one event. Once all 4 inputs are marked, `EO` is triggered and the internal marker is reset. An `R` event resets the marker at any time without triggering `EO`.

## Technical Features

- **Generic implementation**: Like `E_REND` (2 inputs) itself, `E_REND_4` is based on the same generic `GEN_E_REND` C++ class; the input count is fixed at compile time via the type definition.
- **Order-independent**: The inputs `EI1`, `EI2`, `EI3`, `EI4` do not need to arrive in any particular order.
- **Automatic reset after triggering**: After every `EO`, the block starts over from scratch.

## State Overview

The block internally tracks a bitmask of inputs that have already arrived; once the mask is complete, `EO` is triggered and the mask is cleared.

## Application Scenarios

- **Synchronizing 4 independent preconditions** before a follow-up step is triggered (e.g. 4 sensors must all have fired before a machine continues).
- **Extending `E_REND`** to more than two event sources without having to cascade multiple `E_REND` blocks.

## Comparison with similar function blocks

- **`E_REND`**: the 2-input base variant.
- `E_REND_2`, `E_REND_3`: the same generic implementation with a different input count.
- **`E_MERGE_4`**: the logical OR of multiple event inputs (fires on each individual event instead of only after all of them).

## Conclusion

`E_REND_4` extends the rendezvous principle of `E_REND` to 4 simultaneously synchronized event streams and is the generic, 4-input-instantiated variant of the same underlying implementation.
