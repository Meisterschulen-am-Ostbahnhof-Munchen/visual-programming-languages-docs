# AX_SEL_AUDI
![AX_SEL_AUDI](./AX_SEL_AUDI.svg)

* * * * * * * * * *
## Introduction
The function block **AX_SEL_AUDI** implements a binary selection function according to IEC 61131-3. It selects one of two input values (IN0, IN1) and outputs it via an adapter. The selection is controlled by an adapter input that provides an event and a selection signal. The block is designed for modular, adapter-based architectures.
## Interface Structure
### **Event Inputs**

| Event | Comment |
|----------|-----------|
| **EI0** | Sets input IN0 (connected to IN0). The event is used to update the value of IN0. |
| **EI1** | Sets input IN1 (connected to IN1). The event is used to update the value IN1. |

### **Event Outputs**

This function block has no explicit event outputs. Events are output exclusively via the **OUT** adapter (see Adapters).

### **Data Inputs**

| Variable | Type | Comment |
|----------|-------|-----------------------------------|
| **IN0** | UDINT | First selectable input value. |
| **IN1** | UDINT | Second selectable input value. |

### **Data Outputs**

This function block has no explicit data outputs. The selected value is output via the **OUT** adapter (see Adapters).

### **Adapters**

| Adapter | Direction | Type (Packet) | Comment |
|---------|----------|-------------|-----------|
| **G** | Socket | `adapter::types::unidirectional::AX` | Provides the control signal for selection: Event **E1** and Data Value **D1** (e.g., BOOL, 0 = IN0, 1 = IN1). |
| **OUT** | Plug | `adapter::types::unidirectional::AUDI` | Outputs the result of the selection: Event **E1** and Data Value **D1** (UDINT). |

## Functionality

1. **Setting Input Values:** The current values of **IN0** and **IN1** are stored in the internal context via the events **EI0** and **EI1**, respectively (the events are associated with the respective data).

2. **Trigger Selection:** An event on **G.E1** triggers the selection. The internal function block **F_SEL** (IEC 61131-3 `SELECTION`) evaluates the control signal **G.D1**.

- If **G.D1 = 0**, **IN0** is selected.
- If **G.D1 = 1**, **IN1** is selected.

3. **Output:** The selected value is output via **OUT.D1**. Simultaneously, an event is generated on **OUT.E1** to inform downstream function blocks.

The following internal network summarizes the functionality:

G.E1 ──► F_SEL.REQ
F_SEL.CNF ──► OUT.E1

G.D1 ──► F_SEL.G
IN0  ──► F_SEL.IN0
IN1  ──► F_SEL.IN1
F_SEL.OUT ──► OUT.D1
## Technical Features
- **Adapter-Based Input/Output:** Instead of classic input/output variables, adapters (plug/socket) are used. This enables loose coupling and reuse in different environments.
- **Internal IEC Block:** The core logic (F_SEL) is a standardized function block according to IEC 61131-3. AX_SEL_AUDI encapsulates this and adds adapter interfaces.
- **Versioning:** The block is currently in version 3.0, originally developed by TU Wien (2012) and subsequently updated.

## State Overview

The block does not have an explicit state machine. The processes are purely event-driven:

- **Waiting:** The function block waits for an event on **G.E1**.
- **Selection:** Upon receiving G.E1, the selection is performed immediately, and the result is output to OUT.
- **Update:** Events EI0 and EI1 can reset the input values at any time, but only take effect with the next selection.

## Application Scenarios
- **Signal Switching:** Selection between two sensor signals (e.g., temperature/pressure values) based on a control signal (e.g., operating mode).
- **Mode Change:** Switching between different control parameters or setpoints in a controller.
- **Redundancy:** If a signal fails, the control signal can be used to switch to an alternative signal.

## Comparison with Similar Function Blocks

| Function Block | Properties |
|----------|---------------|
| **F_SEL** (Standard) | Pure function block implementation without adapters; uses classic input/output variables. |
| **AX_SEL_AUDI** | Encapsulates F_SEL and adds adapter interfaces; Suitable for adapter-based architectures. |
**MUX blocks** | Multi-channel selection (e.g., 4-to-1), often with an additional index input. AX_SEL_AUDI is limited to two channels. |

## Conclusion

**AX_SEL_AUDI** is a compact, adapter-based function block for binary signal selection. It simplifies its use in modular control architectures by combining standard selection logic with modern adapter interfaces. Its clear event control and simple operation make it a robust solution for typical switching and selection tasks in automation technology.
