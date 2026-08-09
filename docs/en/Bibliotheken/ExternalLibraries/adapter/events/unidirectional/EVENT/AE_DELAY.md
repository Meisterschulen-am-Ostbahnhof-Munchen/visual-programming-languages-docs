# AE_DELAY

* * * * * * * * * *
## Introduction

The **AE_DELAY** function block is a wrapper for the standard IEC 61499 function block `E_DELAY`, specifically designed for use with **Event Adapters (AE)**. It enables the delayed forwarding of events within an adapter-based architecture. Instead of conventional event pins, this function block uses adapter sockets and plugs to receive start and stop signals and output the delayed event.
## Interface Structure

The function block encapsulates the functionality of an on-delay timer in adapter interfaces.

### **Event Inputs**

| Name | Comment |
| :--- | :--- |
| **REQ** | Used to update the time value at data input `DT`. |

### **Event Outputs**

This function block does not have direct event outputs at the main level. All output events are routed via the adapter `EO`.

### **Data Inputs**

| Name | Data Type | Comment |
| :--- | :--- | :--- |
| **DT** | TIME | **Delay Time**: The duration by which the input event should be delayed. |

### **Data Outputs**

This function block does not have any data outputs.

### **Adapter**

| Name | Type | Kind | Comment |
| :--- | :--- | :--- | :--- |
| **START** | adapter::types::unidirectional::AE | Socket (Input) | Starts the time delay (internally triggers `START`). |
**STOP** | adapter::types::unidirectional::AE | Socket (Input) | Stops/cancels the time delay (internally triggers `STOP`). |
**EO** | adapter::types::unidirectional::AE | Plug (Output) | **Event Output**: Outputs the event after the specified time elapses, `DT`. |

## Functionality

The **AE_DELAY** block acts as a bridge between the adapter world and the classic `E_DELAY` timer:

1. **Initialization:** The desired delay time is set via the data input `DT`. This can be updated via the event `REQ`.
2. **Starting the Timer:** When an event (usually `E1`) arrives at the adapter socket **START**, it is internally forwarded to the `START` input of the embedded `E_DELAY` block. The timer then starts running.
3. **Time Expiration:** Once the time `DT` has elapsed, the internal timer generates an event. This is forwarded to the adapter plug **EO** (event `E1`).
4. **Stopping:** When an event arrives at the adapter socket **STOP**, the running timer is immediately stopped and reset. No event is generated at output `EO`.

## Technical Details

* **Package Membership:** The function block is part of the package `adapter::events::unidirectional::timers`.
* **Encapsulation:** It contains an instance of `iec61499::events::E_DELAY`.
* **Adapter Type:** Uses the unidirectional event adapter `AE` (`adapter::types::unidirectional::AE`), which typically carries a single event (`E1`).

## State Overview

The function block itself does not have an explicit state machine (ECC) because it is a composite network (FB). The behavior is entirely determined by the internal `E_DELAY`:

* **Idle:** Waiting for an event at the `START` adapter.
* **Timing:** After receiving a signal at `START`, the timer `DT` starts.
* **Triggered:** After `DT` expires, the signal is sent to `EO`, and the block returns to the idle state.
* **Reset:** A signal at `STOP` during the *Timing* phase immediately resets the block to the idle state.

## Application Scenarios

* **Adapter-Based Controllers:** Ideal for systems that rely heavily on adapter connections to reduce the "spaghetti code" of individual connections.
* **Delayed Signal Chains:** Inserting delays into an event chain that is logically grouped by adapters.
* **Process Control:** Delayed start of units or processes controlled via standardized AE interfaces.

## ⚖️ Comparison with Similar Function Blocks

| Function Block | Difference |
| :--- | :--- |
| **E_DELAY** | The standard function block with direct event pins (START, STOP, EO). **AE_DELAY** is the wrapper for this.
| **E_CYCLE** | Generates periodic events, while **AE_DELAY** forwards an event only once with a delay.
| **AE_SPLIT** | Used to split adapter events, but does not offer time delay. |

## Conclusion

The **AE_DELAY** is an indispensable tool for developers who want to leverage the advantages of 4diac adapters (reduced connection complexity, clear interface definitions) without sacrificing fundamental timing functions like delays. It seamlessly integrates the proven `E_DELAY` into modern, adapter-based application designs.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
