# BasicOne

![BasicOne](./BasicOne.svg)

* * * * * * * * * *

## Introduction

The **BasicOne** function block is a basic, event-driven block according to IEC 61499. It serves as a simple sequence element for initialization, execution of a main operation, and proper deinitialization. The block is particularly suitable for control sequences where a resource state (e.g., device ready) needs to be monitored and reset. The block is included in the package `logiBUS::utils::sequence::one`.

## Interface Structure

### **Event Inputs**

| Event | Type | Accompanying Data | Description |
| ---------- | ----- | ------------------- | -------------- |
| `INIT` | EInit | `QI` | Initialization request; the transition depends on the value of the qualifier `QI`. |
| `REQ` | Event | `QI`, `DI1` | Normal execution request; starts the main operation. |

### **Event Outputs**

| Event | Type | Accompanying Data | Description |
| ---------- | ----- | ------------------- | -------------- |
| `INITO` | Initialization | `QO` | Confirmation of successful initialization or deinitialization. |
| `CNF` | Event | `QO`, `DO1` | Confirmation of normal execution; outputs the current state. |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| `QI` | BOOL | Input qualifier – controls whether initialization is active (`TRUE`) or deinitializing (`FALSE`). Also affects the execution of the main operation. |
| `DI1` | BOOL | First data input; The output is only transferred to `DO1` during normal operation if initialization (`QI = TRUE`) is active. |

### **Data Outputs**

| Name | Type | Description |
|------|-----|---------------|
| `QO` | BOOL | Output qualifier – reflects the value of `QI` after an action (except after deinitialization: then `FALSE`). |
| `DO1` | BOOL | First data output; During a normal operation, the value is `DI1` if `QI = TRUE` is present, otherwise `FALSE`. |

### **Adapter**

None.

## Functionality

The function block goes through a clearly defined lifecycle:

1. **Start State (START)**: After startup, the function block waits for a `INIT` event.
2. **Initialization (Init)**: If `INIT` is received with `QI = TRUE`, the function block executes the *initialize* algorithm. This sets `QO := QI` (i.e., `TRUE`). Then, `INITO` is sent, and the function block transitions to the **Initialized** state.
3. **Normal Operation (NormalOp)**: In the **Initialized** state, a `REQ` event can initiate normal operation. The *normalOperation* algorithm sets `QO := QI` (still `TRUE`) and, if `QI = TRUE` is present, transfers the value from `DI1` to `DO1`. Afterward, `CNF` is sent, and the function block automatically returns to **Initialized**.

The normalOperation* algorithm sets `QO := QI` (still `TRUE`) and transfers the value from `DI1` to `DO1`. 4. **DeInitialization**: If a `INIT` event with `QI = FALSE` is received in the **Initialized** state, the function block executes the *deInitialize* algorithm. This sets `QO := FALSE` and `DO1 := FALSE`. Subsequently, `INITO` is sent, and the function block returns to the **START** start state.

Important: The normal operation is only executed if `QI = TRUE` is present. In the `REQ` event, the algorithm is executed, but `DO1` remains unchanged (it is not set to `DI1`; instead, the last value or the default value `FALSE` remains as defined by the algorithm – in `QI = FALSE`, the IF condition is not met, therefore `DO1` does not change).

`QI = FALSE``

## Technical Features

- **Event Dependency of QI**: The transitions `INIT[TRUE = QI]` and `INIT[FALSE = QI]` demonstrate that the same event, `INIT`, triggers different state transitions depending on the value of `QI`. This enables compact control of initialization and deinitialization via a single event.
- **Automatic Fallback**: After a `REQ` event, the function block returns to the **Initialized** state without an external event (transition with condition `1`). This simplifies integration into cyclic processes.
- **No Self-Locking**: The function block does not block; after each successful execution, it is ready for the next event.

## State Overview

| State | Description | Possible Actions |
| --------- | -------------- | ------------------- |
| `START` | Initial idle state after system startup or deinitialization. | Waits for `INIT` with `QI = TRUE`. |
| `Init` | Initialization phase; sets `QO = QI`. | Executes the *initialize* algorithm, sends `INITO`. |
| `Initialized` | Waiting state after successful initialization. | Can respond to `REQ` (starts NormalOp) or to `INIT` with `QI = FALSE` (starts DeInit). |
| `NormalOp` | Executes the main operation; transfers `DI1` to `DO1` (only if `QI = TRUE`). | Executes the *normalOperation* algorithm, sends `CNF`. |
| `DeInit` | Deinitialization phase; sets `QO = FALSE` and `DO1 = FALSE`. | Executes the *deInitialize* algorithm, sending `INITO`. |

## Application Scenarios

- **Initializing a Component**: A device must be configured upon power-up. Using `INIT` (QI=TRUE), the device state is set to "ready." `REQ` then executes the actual logic cyclically.
- **Resource Management**: The function block can be used as a simple sequencer for one-time initialization and subsequent deinitialization (e.g., for a database connection).
- **Safety-Oriented Control**: The qualifier `QI` ensures that the output `DO1` can only accept the input value if the function block is initialized. Deinitialization resets all outputs (`FALSE`).

## Comparison with similar building blocks

- **BasicBOOLEAN**: A simple Boolean building block without a state machine that only reacts to an event and passes a value. `BasicOne`, on the other hand, offers an explicit initialization and deinitialization sequence.
- **SR Flip-Flop**: A memory building block with set and reset capabilities. `BasicOne` is more of a state machine that implements a single start and stop operation, but does not have a hold function.
- **SimpleCycle**: A cyclic building block that repeatedly performs the same operation. `BasicOne`It distinguishes between initialization and cyclic execution, allowing for a clean separation.

## Conclusion

The function block `BasicOne` is an excellent basic element for control projects that require controlled initialization, reliable operation, and defined deinitialization. Its simple state machine and dependency on the qualifier `QI` make it flexible and easy to use without unnecessary complexity. It is suitable for both newcomers to the IEC 61499 world and experienced developers who need clear, reusable function blocks.
