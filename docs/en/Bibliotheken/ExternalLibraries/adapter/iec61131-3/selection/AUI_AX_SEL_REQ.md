# AUI_AX_SEL_REQ
![AUI_AX_SEL_REQ](./AUI_AX_SEL_REQ.svg)

* * * * * * * * * *
## Introduction
The function block **AUI_AX_SEL_REQ** is a binary selector block controlled by an event input (REQ). Based on a selection criterion provided by an **adapter** (G), it selects between two input values (IN0, IN1) and outputs the result at output OUT. The block serves as a compact, reusable component for signal selection in automation applications and extends the functionality of a simple toggle switch with event-driven operation.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Serves as the trigger for the selection process. The value of adapter G is read, the selection is made, and the result is provided at the output. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| CNF | Triggered as soon as the selection process is complete and the output OUT contains a valid value. |

### **Data Inputs**

| Input | Data Type | Description |
|---------|----------|--------------|
| IN0 | UINT | First selectable input value. |
| IN1 | UINT | Second selectable input value. |

### **Data Outputs**

| Output | Data Type | Description |
|---------|----------|--------------|
| OUT | UINT | Selected value – either IN0 or IN1, depending on the selector criterion supplied via adapter G. |

### **Adapter**

| Adapter | Type | Description |
|---------|-----|--------------|
| G | adapter::types::unidirectional::AX | Bidirectional adapter that provides the selector criterion (e.g., a Boolean signal) and an associated event (E1, D1). The value of D1 determines which input (IN0 when D1 = 0, IN1 when D1 = 1) is passed through to OUT. |

## Functionality

The function block implements the selection via an internal function block **F_SEL** (type: `iec61131::selection::F_SEL`). The event chaining works as follows:

1. A **REQ** event at the input or an event from **Adapter G (E1)** is forwarded to the internal **F_SEL.REQ**.

2. The value present at **G.D1** via the adapter is passed to the selector input **F_SEL.G**.

3. The data values **IN0** and **IN1** are passed directly to the corresponding inputs of **F_SEL**.

4. The internal function block performs the binary selection: If **G.D1 = 0**, **IN0** is output to **F_SEL.OUT**; otherwise, **IN1** is output.

5. The result is output to **OUT**, and the event **F_SEL.CNF** triggers the output **CNF**.

Thus, the selection is triggered either by an external REQ event or by an event (E1) from the adapter. The output OUT remains active after execution until the next selection process.

## Technical Features
* **Adapter-Based Selection:** The use of adapter G (type AX) enables flexible coupling with other function blocks or hardware interfaces that provide a uniform selection signal.
* **Event-Driven:** Both the external REQ event and the event from the adapter can trigger the process. This allows for both cyclic and event-driven querying.
* **Type Safety:** The inputs are defined as UINT (unsigned integer); the function block operates exclusively with this data type.

## State Overview

The function block is purely functional and does not have its own finite state machine. The internal logic is entirely covered by the included **F_SEL** block, which performs a combinational selection process in an event-driven manner. Upon triggering REQ or Adapter-E1, the output OUT is set discretely; there are no internal states or delays.

## Application Scenarios
* **Configurable Signal Selection:** In machine controls where switching between two sensors or measured values (e.g., speed, pressure) is required, depending on a control signal.
* **Parameterizable Operating Modes:** Selection between two parameter sets (e.g., IN0 = Normal Operation, IN1 = Test Mode) via a central selector signal.
* **Error Value Substitution Circuit:** If a primary value (IN0) is invalid, the substitute value (IN1) can be activated via the adapter.
* **Adapter-Mediated Control:** Connection to higher-level systems that send a selection criterion via an AX adapter (e.g., a digital output of a PLC).
*
## Comparison with Similar Function Blocks

Compared to the standard **F_SEL** (IEC 61131-3), **AUI_AX_SEL_REQ** offers event-driven encapsulation with adapter connectivity. While F_SEL operates in pure function block languages without events, AUI_AX_SEL_REQ is specifically optimized for event-driven execution in 61499 systems. In contrast to a **MUX block** (multiplexer with more than two inputs), this block is limited to two selection options and uses a dedicated adapter instead of an additional data input for selection.

## Conclusion

The **AUI_AX_SEL_REQ** offers an elegant and standardized way to implement binary selection in 61499-based automation systems. The integration of an adapter keeps the interface flexible, and the event-driven execution ensures deterministic processing. It is particularly suitable for applications where the selection criterion is not provided as a direct data signal, but via directed communication (adapter).
