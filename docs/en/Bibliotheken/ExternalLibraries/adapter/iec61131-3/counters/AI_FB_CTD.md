# AI_FB_CTD

![AI_FB_CTD](./AI_FB_CTD.svg)

* * * * * * * * * *

## Introduction

The function block **AI_FB_CTD** is a down counter for integer values, standardized according to IEC 61499-2. It consistently uses adapter interfaces (AX, AI) to transport events and data. The block is implemented as a wrapper around the classic IEC 61131 function block `FB_CTD` and enables a modular, adapter-based connection in 4diac IDE networks. Every incoming event via the counter controllers (CD, LD, PV) updates the internal counter and triggers an output event.

## Interface Structure

### **Event Inputs**

The function block does not have direct, separate event inputs. The necessary events are provided via the **Socket Adapters** (CD, LD, PV) – each of these modules carries an event (E1) that triggers the counter logic.

| Socket | Event (in the adapter) | Description |
| -------- | ----------------------- | ------------------------------ |
| CD | E1 | Counting event (down counter) |
| LD | E1 | Load event (set to PV) |
| PV | E1 | Default update |

### **Event Outputs**

| Name | Type | Description |
|------|--------|-----------------------------------------------------------|
| CNF | Event | Acknowledge event after each counter update (CD, LD, PV) |

Additionally, the output events are also transmitted via the **Plug Adapters** Q and CV (E1 each).

### **Data Inputs**

There are no direct data inputs. All data values are transmitted via the socket adapters:

- **CD** provides the down count pulse (D1) – a logical value that decrements the counter.
- **LD** provides the charge signal (D1) – a logical value that sets the counter to the current PV value.
- **PV** provides the setpoint value (D1) – an integer that is loaded as the new meter reading.

### **Data Outputs**

There are no direct data outputs. The output data is provided via the plug adapters:

- **Q** provides the meter status (D1) – BOOL, TRUE if the meter reading is ≤ 0.
- **CV** provides the current meter reading (D1) – INT.

### **Adapters**

| Label | Direction | Type | Description |
| ------------- | ---------- | ----------------------------------- | ------------------------------------------------------ |
| CD | Socket | `adapter::types::unidirectional::AX` | Counter input (event + data) for counting down |
| LD | Socket | `adapter::types::unidirectional::AX` | Load input (event + data) for setting to PV |
| PV | Socket | `adapter::types::unidirectional::AI` | Default input (event + data) for the preset value |
| Q | Plug | `adapter::types::unidirectional::AX` | Output signal (event + data) – counter ≤ 0 |
| CV | Plug | `adapter::types::unidirectional::AI` | Output counter value (event + current counter reading) |

## Functionality

The function block internally contains a function block `iec61131::counters::FB_CTD`, which implements the actual counting logic. The function is as follows:

1. An event at **CD** (via `CD.E1`), **LD** (`LD.E1`), or **PV** (`PV.E1`) triggers the internal function block via its event input `REQ`.
2. The internal function block evaluates the associated data:

- On a **CD** event, the counter is decremented by 1 (if the associated date is TRUE).
- On a **LD** event, the counter is set to the current value of **PV** (if the load date is TRUE).
- In the event of a **PV** event, the default value is updated internally (the counter remains unchanged).
1. After processing, the internal FB generates its `CNF` event. This is distributed to the external outputs:

- `CNF` (direct event output)
- `Q.E1` (event of plug adapter Q)
- `CV.E1` (event of plug adapter CV)
1. Simultaneously, the following data is transferred:

- `FB_CTD.Q` (BOOL) → `Q.D1`
- `FB_CTD.CV` (INT) → `CV.D1`

` Note: The output event is triggered **with every update** (i.e., on CD, LD, or PV). A simple value change without an event (On-Change) is not implemented.

## Technical Features

- **License and Origin**: This function block is licensed under the **Eclipse Public License 2.0** (EPL 2.0). It was developed as teaching material for the master craftsman schools at Ostbahnhof.
- **Adapter-Based Communication**: Unlike classic FB interfaces, all inputs and outputs are implemented via adapters (AX, AI). This enables flexible, hierarchical wiring and reuse in complex control architectures.
- **On-Change Filter**: The function block fires the output event on **every** input event, regardless of an actual value change. If change detection is required, the use of an **AX_D_FF** (Differentiator Flip-Flop) as a pre-filter is recommended (see also the copyright notice in the XML).
- **Internal FB**: The counting logic is based on the standard module `FB_CTD`From IEC 61131 (adapted for 4diac). This ensures deterministic behavior and compatibility with PLC programs.

## State Overview

The function block does not have an explicit state machine. The only internal variable is the **current counter value** (integer). This value is modified by the following events:

- Initial value: 0 (or set to PV via LD)
- CD event: Counter = Counter - 1 (if the associated date is TRUE, otherwise no change)
- LD event: Counter = PV (if the loading date is TRUE)
- PV event: PV value is stored internally; the counter remains unchanged.

Therefore, a graphical state machine is not required.

## Application Scenarios

- **Inventory Counter**: Decrementing an inventory level upon removal (CD), resetting via LD after replenishment.

- **Event Counter with Threshold**: Counts events until 0 is reached, then triggers a signal (Q).

- **Time/Pulse Control**: Used as a pulse counter in conjunction with a clock (CD) and specifying the desired number of events (PV).
- **Adapter Integration**: In modular control systems where events and data are to be encapsulated via standardized adapter interfaces.

## Comparison with Similar Components

| Component | Counting Direction | Interfaces | Special Feature |
----------------- | -------------- | ---------------------- | --------------------------------------------------- |
| **AI_FB_CTD** | Downward | Adapters only (AX, AI) | Output on every update |
| **AI_FB_CTU** | Upward | Adapters only (AX, AI) | Upward counter, analog structure |
| **FB_CTD** (Standard) | Downward | Direct Events/Data | Classic Variable Connection, without Adapter |
| **FB_CTUD** | Both | Direct | Combined Increment/Decrement Counter, Extended Logic |

The **AI_FB_CTD** stands out due to its consistent use of adapters, making it ideal for hierarchical and reusable control models. Unlike the standard FB_CTD, separate data and event inputs are eliminated – everything is handled via the adapters.

## Conclusion

The `AI_FB_CTD` is a flexible, adapter-based down counter for integer values that translates the proven counting logic from IEC 61131 into a modern, modular interface landscape. It is ideally suited for use in distributed control systems according to IEC 61499, where encapsulation and reusability are paramount. Its ease of use (three input events, two output adapters) and clear documentation make it a solid foundation for counter applications. For change detection, it is recommended to use a `AX_D_FF` upstream.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
