# F_NOT_BOOL_INIT

![F_NOT_BOOL_INIT](./F_NOT_BOOL_INIT.svg)

* * * * * * * * * *
The function block `F_NOT_BOOL_INIT` implements the logical negation (NOT) of a Boolean input signal and extends the basic NOT function with an initialization mechanism. It is designed as a standardized block according to IEC 61131-3 for use in programmable logic controllers (PLCs). During initialization, the function block allows a first negation to be triggered and the resulting value to be provided at the output before normal cyclic operation begins.

| Event | Type | With Variables | Description |
|----------|-------|----------------|---------------|
| `INIT` | EInit | `IN` | Initialization request – the function block is initialized once and the input is negated. |
| `REQ` | Event | `IN` | Normal processing request – the logical negation is applied to the current input value. |
| Event | Type | With Variables | Description |
|----------|-------|---------------|--------------|
| `INITO` | EInit | `OUT` | Initialization confirmation – output after successful initialization. |
| `CNF` | Event | `OUT` | Confirmation of normal processing – sent to `REQ` after each execution. |
| Variable | Type | Description |
|----------|--------|--------------|
| `IN` | BOOL | Input value to be negated. |
| Variable | Type | Description |
|----------|--------|--------------|
| `OUT` | BOOL | Negated value of the input (`NOT IN`). |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

None.

## Functionality

The function block delegates the actual negation function to the internal function block `F_NOT` (from the library `iec61131::bitwiseOperators`). Processing is event-driven:

- **For `INIT`:** The input value `IN` is immediately transferred via the data connection to the internal function block `F_NOT`. Simultaneously, the event `REQ` is sent to the internal function block, which calculates the negation and passes the result to the output `OUT`. After this operation is completed, the event `INITO` is output at the main function block. This sets the output `OUT` with the negated initial value.
- **For `REQ` (during operation):** The current value of `IN` is passed to the internal `F_NOT` and negated. The result is written to `OUT`, and then the event `CNF` is triggered.

Thus, both `INIT` and `REQ` result in the same core functionality (negation), but differ in the triggered event: `INIT` generates `INITO`, and `REQ` generates `CNF`.

- The function block does not contain its own algorithmic logic, but uses an internal sub-function (`F_NOT`). This promotes reuse and consistency.
- The initialization mechanism allows the output to be assigned the negated input even before the first "normal" call – useful in PLC programs where start values need to be defined.
- The function block does not contain its own algorithmic logic, but uses an internal sub-function (`F_NOT`). This promotes reuse and consistency.
- The initialization mechanism allows the output to be set to the negated input even before the first "normal" call – useful in PLC programs where start values need to be defined.

- The simultaneous use of `INIT` and `REQ` enables a clear separation between startup behavior and cyclic operation.

- By including the input variables in the events (WITH), it is ensured that the data is always up-to-date.

The function block (FB) does not have an explicit state machine, as all logic is implemented in the internal network. The following behavior is implicit:

1. **Initial State:** After the PLC starts, outputs and internal values are undefined.
2. **After `INIT`:** The output `OUT` is set to the negated value of `IN`; the FB is ready for operation.
3. **After `REQ`:** For each `REQ` pulse, the negation is performed again, and `OUT` is updated.

A repeated triggering of `INIT` (e.g., after a reset) leads to re-initialization and sets `OUT` to the negated current input value.

- **Initializing a Control Output:** An output should assume the negated value of a sensor signal during the startup phase before the cyclic program starts.
- **Error Monitoring:** During a startup sequence, it is checked whether an input signal has the negated state of an enable signal.
- **Safety Logic:** Used in safety functions where an initial negation step is mandatory (e.g., NOT operation after system startup).

| Function Block | Description | Difference to `F_NOT_BOOL_INIT` |
--------------------|-----------------------------------------------|----------------------------------|
| `F_NOT` (Standard) | Pure negation without an initialization event. | The `INIT`/`INITO` pair is missing; the output is undefined after system startup. |
| `F_NOT_BOOL_INIT` | Like `F_NOT`, but with an explicit initialization event. | Offers defined start behavior and outputs a separate acknowledgment event upon initialization. |

The standard `F_NOT` is sufficient if the start behavior is controlled by the higher-level control sequence. The initializable function block is advantageous when the function block itself should have control over its first execution.

F_NOT_BOOL_INIT` is a useful function block that extends the simple NOT operation with an initialization facility. It is particularly suitable for PLC applications where a defined start value for the negated output is required. Thanks to the clear event control and the internal use of the proven `F_NOT` function block, the implementation remains robust and well-organized. The function block represents a useful extension of the IEC 61131 bit operators.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion