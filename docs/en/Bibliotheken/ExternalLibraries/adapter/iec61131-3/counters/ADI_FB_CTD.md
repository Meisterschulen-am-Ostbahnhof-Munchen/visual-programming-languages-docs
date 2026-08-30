# ADI_FB_CTD

![ADI_FB_CTD](./ADI_FB_CTD.svg)

* * * * * * * * * *

## Introduction

The **ADI_FB_CTD** is a down counter for values of type `DINT` that communicates exclusively via ADI adapters. It encapsulates an internal standard counter and enables counting down, loading a default value, and outputting the current counter value – all via standardized adapter interfaces.

## Interface Structure

### **Event Inputs**

The FB does not have direct event inputs. Events are provided via the adapter sockets **CD**, **LD**, and **PV**.

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| CNF | Event | Acknowledgement signal output after each processing of an incoming event. |

### **Data Inputs**

No direct data inputs; data is provided via the adapter sockets.

### **Data Outputs**

No direct data outputs; data is provided via the adapter plugs.

### **Adapter**

| Name | Type | Direction | Description |
| ------ | ----- | ---------- | -------------- |
| CD | `adapter::types::unidirectional::AX` | Socket (Input) | Countdown event; the data value (D1) is passed to the internal counter as a CD pulse. |
| LD | `adapter::types::unidirectional::AX` | Socket (Input) | Load the counter with the current value of **PV**; The data value (D1) signals the charging process. |
| PV | `adapter::types::unidirectional::ADI` | Socket (Input) | Preset value as `DINT`; the event (E1) triggers an update of the internal PV register. |
| Q | `adapter::types::unidirectional::AX` | Plug (Output) | Output signal indicating whether the meter reading has reached zero (e.g., `TRUE` for zero). |
| CV | `adapter::types::unidirectional::ADI` | Plug (Output) | Current meter reading as `DINT`; output with each update. |

## Functionality

The ADI_FB_CTD uses an internal IEC 61131 counter (`FB_CTD_DINT`). All communication takes place via ADI adapters that combine an event (E1) and a data value (D1):

- An event at the **CD** socket causes the internal counter to decrement its current value by **1**.
- An event at the **LD** socket loads the counter to the value last provided via **PV**.
- An event at the **PV** socket updates the default value in the internal register; the counter itself is not changed. Only a subsequent LD event takes over the new value.

All incoming events (CD, LD, and PV) are routed to the common `REQ` input of the internal counter. The internal function block distinguishes between counting and loading based on the data values. Upon completion of the action, the event `CNF` is triggered, simultaneously operating the output adapters **Q** and **CV** and setting the event output `CNF`.

## Technical Features

- **Always Active Output:** The function block outputs an event on the **Q** adapter with **every** update (via CD, LD, or PV) – even if the corresponding data value does not change. If a triggering output is only desired upon an actual state change, a filter block such as `AX_D_FF` must be placed upstream.
- **Adapter-Based Interface:** All inputs and outputs are implemented as ADI adapters. This enables loose coupling and easy reusability in modular control architectures.
- **Internal Standard Counter:** The counting logic is based on an established IEC 61131 component and is therefore robust and reliable.

## State Overview

The FB does not have its own state machine. Its behavior is determined by the internal `FB_CTD_DINT`, which can operate in the following modes:

- **Loading:** When an event occurs at the **LD** adapter, the counter is set to the current PV value.
- **Counting:** When an event occurs at the **CD** adapter, the counter is decremented.
- **Waiting:** No event is present; the counter retains its current value.

After each processing step, the FB is immediately ready for the next event (no blocking).

## Application Scenarios

- **Workpiece Counting:** A sensor reports each passing workpiece as an event on **CD**. The counter decrements from a predefined starting value (**PV**) to zero. When the counter reaches zero, a signal (e.g., "Container full") can be output via **Q**.
- **Time Delay:** In combination with a clock, the counter functions as a down timer, the remaining time of which is read via **CV**.
- **Control of Processes:** The current counter value (**CV**) serves as a parameter for subsequent steps (e.g., positioning, quantity control).

## Comparison with Similar Function Blocks

- **CTU (Up Counter)** – counts only upwards; ADI_FB_CTD only downwards.
- **CTUD (Up/Down Counter)** – can count in both directions; ADI_FB_CTD is specialized for one direction.
- **Standard IEC 61499 Counters** – use separate event and data ports, while ADI_FB_CTD unifies the interfaces via adapters.
- **ADI_FB_CTU** – structurally identical, but with upcount logic (also available as an adapter version).

The advantage of the adapter version lies in its more modular, reusable interface; the disadvantage is the higher level of abstraction and the need for filtering when required.

## Conclusion

The ADI_FB_CTD is a reliable downcounter for `DINT` values, which, thanks to its consistently adapter-based interface, integrates ideally into loosely coupled control architectures. The fact that the **Q** output triggers with every update must be considered during system design. Thanks to the internal standard counter, the counting logic is robust and proven – a reliable component for downcounting scenarios.
