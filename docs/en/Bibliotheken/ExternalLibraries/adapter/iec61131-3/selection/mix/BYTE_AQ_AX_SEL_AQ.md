# BYTE_AQ_AX_SEL_AQ

![BYTE_AQ_AX_SEL_AQ](./BYTE_AQ_AX_SEL_AQ.svg)

* * * * * * * * * *
## Introduction

The function block `BYTE_AQ_AX_SEL_AQ` is a composite function block (CFB) for event-driven, binary selection (multiplexing) of data of type `BYTE`. The block combines classic selection logic (equivalent to `SEL` from IEC 61131-3) with the advantages of the event-driven implementation of IEC 61499.

It allows for flexible selection between a directly connected byte input and a byte input via an adapter. The selection signal and the output signal are also transmitted via standardized adapters, enabling a highly modular and clear structure within the control network.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the reading and transfer of the directly connected data input `IN0`.

### **Event Outputs**

* *No direct event outputs.* (Event output is coupled via the output adapter `OUT`).

### **Data Inputs**

* **IN0** (BYTE): Directly connected data input whose value is captured when an event occurs at `EI0`.

### **Data Outputs**

* *No direct data outputs.* (Data is coupled via the output adapter `OUT`).

### **Adapter**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AQ`): The selected output of the module. Outputs the selected byte signal along with its corresponding update event.
* **IN1** (Socket, Type: `adapter::types::unidirectional::AQ`): Adapter-based data input for the second selectable byte signal, including its update event.
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): Adapter-based selector input (Boolean). Determines which of the two inputs is passed through to the output.

---

## Functionality

In the component's internal network, incoming data and events are synchronized and processed:

1. **Data Acquisition and Buffering:**
* The value of `IN0` is temporarily stored in the internal flip-flop `E_D_FF_ANY_IN0` when the event `EI0` occurs.
* The value of the adapter `IN1` (data `D1`) is temporarily stored in the flip-flop `E_D_FF_ANY_IN1` when the adapter event `IN1.E1` occurs.
* The selection signal of adapter `G` (data `D1`) is temporarily stored in flip-flop `E_D_FF` when the adapter event `G.E1` occurs.
2. **Selection Logic:**
* As soon as one of the inputs or the selector changes, the selection block `F_SEL` is called via the internal move blocks (`F_MOVE_IN0`, `F_MOVE_IN1`).
* * The function block `F_SEL` operates according to the following principle:
* If the selection signal **`G` = FALSE**, the value of **`IN0`** is passed to the output.
* If the selection signal **`G` = TRUE**, the value of **`IN1`** is passed to the output.
3. **Output Control:**
* The result of the selection is passed via `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`.
* Output Control:**
* The result of the selection is passed via `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`.
* This triggers the output adapter's event `OUT.E1` and simultaneously updates the data value `OUT.D1`.

This triggers the output adapter's event `OUT.E1` and simultaneously updates the data value `OUT.D1`.

...```
                  +-----------------------------------+
|        BYTE_AQ_AX_SEL_AQ          |
|                                   |
[EI0] -------->| EI0                               |
(BYTE) IN0 --->| IN0                               |
|                                   |
 [AQ-Socket] ---->| IN1                           OUT |======> [AQ-Plug]
|                                   |       (Selected Output)
[AX-Socket] ---->| G                                 |
                  +-----------------------------------+

---

## Technical Features

* **Secure Data Consistency:** The use of edge-triggered D flip-flops (`E_D_FF` and `E_D_FF_ANY`) in the internal network ensures that data values are only transferred when the corresponding event occurs. This prevents race conditions between asynchronous input signals.
* **Mixed Operation:** The component provides an elegant bridge between classic, pin-based wiring (`IN0`/`EI0`) and modern, adapter-based signal transmission.

---

## Status Overview

Since this is a composite function block (FB) without its own Execution Control Chart (ECC), its behavior is entirely determined by the interaction of the internal blocks:

* **Idle:** The block waits for events at `EI0`, `IN1.E1`, or `G.E1`.
* **Data Update:** Upon receiving an event, the respective path is updated, the selection is recalculated, and the data is immediately available at the adapter `OUT`.

--

## Application Scenarios

* **Switching Between Setpoints:** A system typically requires a fixed parameter (passed to `IN0` as a static value). Under certain operating conditions, however, switching to a dynamically calculated setpoint from another software module (transmitted via adapter `IN1`) is required.
* **Operating Mode Selection:** Selection of byte-based control words or state IDs depending on a higher-level automatic/manual switching operation (controlled by the selector adapter `G`).
* **Modular Signal Bundling:** Reduction of wiring effort in complex 4diac applications through the use of unidirectional adapters for signal forwarding.

---

## Comparison with Similar Function Blocks

* **Standard Selection Function Block `F_SEL`:** The classic `F_SEL` has no integrated event control and no adapter interfaces. It reacts purely in a data flow-oriented manner. `BYTE_AQ_AX_SEL_AQ` extends this functionality with event-driven storage and direct coupling to adapter channels.
* **Simple selectors without adapters:** Require manual routing and connecting of all event lines. This block encapsulates this logic and ensures a clean application diagram in the 4diac IDE.

---

## Conclusion

The `BYTE_AQ_AX_SEL_AQ` is an extremely useful auxiliary block for modular control architectures. It combines the robustness of event-based processing with the flexibility of adapters and is ideally suited for switching and multiplexing tasks of byte data in distributed systems.