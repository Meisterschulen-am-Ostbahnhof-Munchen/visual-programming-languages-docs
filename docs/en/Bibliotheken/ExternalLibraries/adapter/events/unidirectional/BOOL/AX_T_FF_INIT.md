# AX_T_FF_INIT
![AX_T_FF_INIT](./AX_T_FF_INIT.svg)

* * * * * * * * * *
## Introduction
The function block **AX_T_FF_INIT** implements a triggered toggle flip-flop with an initialization function. It can be set to a defined start state via an INIT event and subsequently toggles between the SET and RESET states with each CLK event. The current state is provided via an adapter output. This block is particularly suitable for applications where an output signal needs to be switched at each clock cycle, with the initial state defined by initialization.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| INIT | EInit | Initialization request; triggers the initialization of the flip-flop. The corresponding data inputs QI and Q_INIT are evaluated. |
| CLK | Event | Clock input; the internal state toggles between SET and RESET with each event. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| INITO | EInit | Initialization confirmation; output after successful initialization or deinitialization. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| QI | BOOL | Input qualifier; controls whether actions are actually executed (TRUE = active). |
| Q_INIT | BOOL | Value assigned to the flip-flop during initialization (TRUE = SET, FALSE = RESET). |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| QO | BOOL | Output qualifier; reflects the value of QI if an action has been performed, otherwise FALSE. |

### **Adapters**

| Name | Type | Comment |
|------|-----|-----------|
| Q | Adapter `adapter::types::unidirectional::AX` | Adapter output that passes the current flip-flop state (TRUE or FALSE) to connected function blocks. |

## Functionality

The function block has the following internal states: START, Init, DeInit, SET, and RESET.

1. **Initialization (INIT Event)**

- On an INIT event with **QI = TRUE**, the system transitions from the start state to the **Init** state.
- In the Init state, the algorithm *initialize* is executed: `QO := QI`.
- Subsequently, the output qualifier QO is set to TRUE, and the **INITO** event is output.
- Depending on the value of **Q_INIT**, the transition occurs:

If Q_INIT = TRUE → transition to the **SET** state

If Q_INIT = FALSE → transition to the **RESET** state

2. **Toggle Operation (CLK Event)**

- Starting from **SET** or **RESET**, the state changes with each **CLK** event:
- From SET → RESET (and vice versa)
- Upon exiting the states, the corresponding algorithms are executed:
- **SET**: `QO := QI;` If QI = TRUE, **Q.D1 = TRUE** is assigned to the adapter output.
- **RESET**: `QO := QI;` If QI = TRUE, **Q.D1 = FALSE** is assigned to the adapter output.
- In both cases, the event **Q.E1** is output (via the adapter).

3. **Deinitialization (INIT event with QI = FALSE)**

- If an INIT event with **QI = FALSE** occurs during operation (in SET or RESET), the function block switches to the **DeInit** state.
- The *deInitialize* algorithm sets `QO := FALSE`.
- **INITO** is output, and the function block returns to the start state.

The function block remains in the start state until an INIT event with QI = TRUE occurs. Toggle operation is not possible without initialization.

## Technical Features
- **Adapter-based output signal**: The current flip-flop state is not provided as a simple data output, but via an **adapter** (`adapter::types::unidirectional::AX`). This enables flexible and typed communication with other function blocks that use the same adapter.
- **State-Dependent Execution**: The actions (setting/resetting the adapter output) are only executed if the qualifier **QI** = TRUE. If QI = FALSE, the adapter output is not changed, but the state still changes.
- **Initialization with Start Value**: The initial state after initialization can be specifically defined via the input **Q_INIT** (TRUE = set, FALSE = reset).

## State Overview

| State | Meaning |
|---------|-----------|
| START | Waiting for first INIT event. |
| Init | Initialization is in progress; QO is set to QI, then transition to SET or RESET depending on Q_INIT. |
| DeInit | Deinitialization is in progress; QO is set to FALSE, return to START. |
| SET | Flip-flop is in the set state; Adapter output Q.D1 = TRUE (when QI=TRUE). |
| RESET | Flip-flop is in the reset state; adapter output Q.D1 = FALSE (when QI=TRUE). |

The state transitions are controlled by the INIT event (with a corresponding condition on QI) and CLK.

## Application Scenarios
- **Controlling outputs with toggle function**: A digital output should switch between on and off with each clock cycle, e.g., for blink signals or pulse trains.
- **Initializable state machines**: In automation systems where a process must assume a defined start state (set or reset) after a reset.
- **Adapter-based communication**: Devices using the same adapter can directly read the flip-flop state without relying on separate data outputs.

## Comparison with similar devices

| Criterion | AX_T_FF_INIT | Simple Toggle Flip-Flop (without INIT) | SR Flip-Flop |
-----------|--------------|------------------------------|-------------|
Initialization | Yes, via INIT with Q_INIT | No, state undefined after startup | No (set/reset via separate inputs) |
State Change | Clocked by CLK | Clocked by CLK | Asynchronous via S and R |
Output | Via adapter (typed) | Often as a BOOL data output | BOOL data output |
Qualifier QI | Controls whether an action is executed | Not present | Not present |

Compared to a simple toggle flip-flop, the **AX_T_FF_INIT** offers the possibility of defined initialization and uses an adapter for the output, which simplifies configuration in complex systems.

## Conclusion

The function block **AX_T_FF_INIT** is a versatile building block for clocked toggle operations with initialization logic. Its combination of INIT and CLK events, the QI qualifier, and the adapter output allows for precise control of the state behavior. It is particularly suitable for industrial automation applications where a defined start value and clocked switching are required.
