# AX_SR_SYM_INIT

![AX_SR_SYM_INIT](./AX_SR_SYM_INIT.svg)

* * * * * * * * * *
## Introduction
The function block **AX_SR_SYM_INIT** implements an event-driven, bistable flip-flop (set-reset) with symmetrical start-up behavior and special initialization logic. It extends the classic SR flip-flop with a qualified initialization and deinitialization sequence, where the output state is specified via the input `Q_INIT`, and the entire logic is only active if the qualifier `QI` has the value `TRUE`.

## Interface Structure
### **Event Inputs**

| Event | Type | Description |

|----------|-----|--------------|

| INIT | EInit | Initialization request; linked to `QI` and `Q_INIT` |

| S | Event | Sets output `Q` (via adapter) |

| R | Event | Resets output `Q` |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|---------------|

| INITO | EInit | Initialization confirmation; linked to `QO` |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| QI | BOOL | Input qualifier – controls whether actions are executed |

| Q_INIT | BOOL | Desired value of the output `Q` after initialization |

### **Data Outputs**

| Variable | Type | Description |

|----------|-------|--------------|

| QO | BOOL | Output qualifier – reflects the value of `QI` at the time of the triggering event |

### **Adapters**

| Adapter | Type | Description |

|---------|-----|--------------|

| Q | adapter::types::unidirectional::AX | Flip-flop value – set/reset via the interface |

## Functionality
The function block has four main states: `START`, `Init`, `DeInit`, `SET`, and `RESET`.

- **`START`** – Wait state after system startup.

- **`Init`** – Activated when `INIT` and `QI = TRUE` are both present. In this state, the algorithm `initialize` is executed, which sets `QO := QI`. The state then branches depending on `Q_INIT`:

- If `Q_INIT = TRUE` is present, the system switches to the `SET` state (the flip-flop is set).

- If `Q_INIT = FALSE` is present, the system switches to the `RESET` state (the flip-flop is reset).



``` - **`DeInit`** – Activated when `INIT` and `QI = FALSE` occur (from states `SET` or `RESET`). The algorithm `deInitialize` sets `QO := FALSE`. Afterwards, the state reverts to `START`.

- **`SET`** – Reached by the event `S` (from `RESET` or after initialization with `Q_INIT=TRUE`). The algorithm `SET` sets `QO := QI` and writes the value `TRUE` to the adapter output `Q.D1` **only if `QI = TRUE`**. A subsequent `S` has no effect as long as the state `SET` is active.

- **`RESET`** – This is reached by the event `R` (from `SET` or after initialization with `Q_INIT=FALSE`). The algorithm ``RESET`` sets ``QO := QI`` and writes the value ``FALSE`` to ``Q.D1`` **only if ``QI = TRUE``**. A subsequent ``R`` has no effect.

The transitions between ``SET`` and ``RESET`` are triggered only by the events ``S`` and ``R``, respectively. The INIT transitions can result from either stable state in ``DeInit`` if ``QI = FALSE`` is present.
...``` ## Technical Features

- **Qualifier-Dependent Actions**: The actual change to the flip-flop output (`Q.D1`) only occurs if `QI = TRUE` is present. Otherwise, only the output qualifiers (`QO`) are updated; the adapter remains unchanged.

- **Symmetrical Startup**: The device can be initialized with either a "set" or a "reset" state, depending on the value of `Q_INIT`.

- **Deinitialization**: If `QI = FALSE` is present during initialization, the device is set to the `DeInit` state, which clears the output qualifier and then returns to the startup state.

- **Guard Conditions**: The state transitions use conditions like `INIT[TRUE = QI]` or `[FALSE = Q_INIT]` to precisely control the logic.

## State Overview

- **START** → Idle state after startup.

- **Init** → Initialization run (only with `QI=TRUE`).

- **DeInit** → Deinitialization run (only with `QI=FALSE`).

- **SET** → Stable state in which `Q.D1 = TRUE` is set (if previously set).

- **RESET** → Stable state in which `Q.D1 = FALSE` is reset (if previously reset).


Transitions:

- `START` → `Init` : if `INIT` & `QI=TRUE`
- `Init` → `SET` : if `Q_INIT=TRUE`
- `Init` → `RESET` : if `Q_INIT=FALSE`
- `SET` → `RESET` : if `R`
- `RESET` → `SET`: if `S`
- `SET` → `DeInit`: if `INIT` & `QI=FALSE`
- `RESET` → `DeInit`: if `INIT` & `QI=FALSE`
- `DeInit` → `START`: automatically after completion of the DeInit algorithm

## Application Scenarios

- **Control of actuators with defined start behavior**: A motor or valve should perform a certain action after being switched on. Assume a specific state (e.g., closed = `Q=FALSE`), depending on an initialization specification.

- **Qualified State Changes**: In systems where an enable signal (`QI`) allows the actual value change, while the qualifier output (`QO`) signals validity.

- **Resettable Initialization Routine**: A component can be set or reset by an INIT call, but can later be put into a defined idle state by another INIT call with `QI=FALSE`.


## Comparison with Similar Function Blocks

- **Standard SR Flip-Flop (e.g., `SR` or `AX_SR`)**: Simple set/reset without initialization or qualifier. `AX_SR_SYM_INIT` additionally offers a qualified initialization and deinitialization process.

- **Function Blocks with INIT Interface (e.g., `E_SR` with `INIT`)**: These often lack pronounced deinitialization or a qualifier. The function block presented here differs in its symmetrical behavior – both setting and resetting can be specified in the INIT step.

- **Function Blocks with Adapter (`unidirectional::AX`)**)**: These are used to transmit the state externally via a standardized adapter interface. The `AX_SR_SYM_INIT` encapsulates this logic in a function block.

## Conclusion
The `AX_SR_SYM_INIT` is a versatile function block for applications that require qualified startup and initialization behavior. By combining event control, qualifier logic, and an adapter interface, it is particularly suitable for modular automation solutions according to IEC 61499, where a defined system startup and clean deinitialization are required.