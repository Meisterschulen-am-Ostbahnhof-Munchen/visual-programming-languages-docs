# E_REND_2

* * * * * * * * * *
## Introduction

`E_REND_2` is the generic 2-input variant of the rendezvous block `E_REND` (2 inputs). It only triggers `EO` once it has received at least one event since the last reset from **all** 2 inputs (`EI1`, `EI2`) — a logical AND across 2 asynchronous event streams.

![E_REND_2](E_REND_2.svg)

## Interface Structure

### **Event Inputs**

- **EI1**: Event input 1.
- **EI2**: Event input 2.
- **R (Reset)**: Resets the block to its initial state, discarding all events recorded so far.

### **Event Outputs**

- **EO**: Triggered once all 2 inputs have fired at least once since the last reset.

## Functionality

`E_REND_2` is implemented as a generic function block (`eclipse4diac::core::GenericClassName = 'GEN_E_REND'`) — the same C++ implementation underlies all `E_REND_n` variants; only the number of inputs differs. Internally, the block remembers which of the `EI1`…`EI2` inputs have already received at least one event. Once all 2 inputs are marked, `EO` is triggered and the internal marker is reset. An `R` event resets the marker at any time without triggering `EO`.

## Technical Features

- **Generic implementation**: Like `E_REND` (2 inputs) itself, `E_REND_2` is based on the same generic `GEN_E_REND` C++ class; the input count is fixed at compile time via the type definition.
- **Order-independent**: The inputs `EI1`, `EI2` do not need to arrive in any particular order.
- **Automatic reset after triggering**: After every `EO`, the block starts over from scratch.

## State Overview

The block internally tracks a bitmask of inputs that have already arrived; once the mask is complete, `EO` is triggered and the mask is cleared.

## Application Scenarios

- **Synchronizing 2 independent preconditions** before a follow-up step is triggered (e.g. 2 sensors must all have fired before a machine continues).
- **Extending `E_REND`** to more than two event sources without having to cascade multiple `E_REND` blocks.

## Comparison with similar function blocks

- **`E_REND`**: the 2-input base variant.
- `E_REND_3`, `E_REND_4`: the same generic implementation with a different input count.
- **`E_MERGE_2`**: the logical OR of multiple event inputs (fires on each individual event instead of only after all of them).

## Conclusion

`E_REND_2` extends the rendezvous principle of `E_REND` to 2 simultaneously synchronized event streams and is the generic, 2-input-instantiated variant of the same underlying implementation.
