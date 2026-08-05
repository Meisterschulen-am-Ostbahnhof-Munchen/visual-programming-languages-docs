# AX_R_TRIG
* * * * * * * * * *
## Introduction
The function block **AX_R_TRIG** (Boolean rising edge detection) is used to detect a rising edge based on a Boolean signal provided via an adapter. It is specifically designed for use with unidirectional adapters of type `AX` and only forwards an event if the transmitted data value is `TRUE`.
## Interface Structure
The function block primarily uses an adapter interface for communicating input data and events.

### **Event Inputs**
This function block does not have direct event inputs. Events are received via the adapter `QI`.

### **Event Outputs**
* **EO**: (Event Output) Confirmation that a rising edge (or a high signal) has been detected.

### **Data Inputs**

This function block has no direct data inputs. Data is received via the adapter `QI`.

### **Data Outputs**

This function block has no direct data outputs.

### **Adapters**
* **QI** (Socket): Of type `adapter::types::unidirectional::AX`. This adapter provides the value to be checked (Boolean) and the corresponding event.
* Typically expects an event (e.g., `E1`) and a Boolean value (e.g., `D1`).

## Functionality

The component is implemented as a Composite Function Block (CFB) and is based on the internal circuitry of a D flip-flop (`E_D_FF`) and an event switch (`E_SWITCH`).

1. As soon as an event is received via the **QI** adapter, it is routed to the clock input of the internal `E_D_FF`.

2. Simultaneously, the Boolean data value is loaded from the adapter into the flip-flop.

3. The flip-flop passes the stored value to a `E_SWITCH`.

4. If the value of `TRUE` is high, the `E_SWITCH` switches on and triggers the output event **EO**.

5. If the value `FALSE` (Low), the event is blocked and **EO** is not triggered.

Technically, the function block acts as a gate that only allows the adapter event to pass if the adapter data is `TRUE`. In an event-driven system that only sends when values change, this corresponds to the logic of edge detection (0 -> 1).

## Technical Features
* **Internal Structure:** Uses standard IEC 61499 function blocks (`E_D_FF`, `E_SWITCH`).
* **Adapter-based:** Unlike classic trigger blocks, which have separate `CLK` and `QI` inputs, this block encapsulates the signals in a `AX` adapter.

## State Overview
Since this is a Composite Function Block, it does not have its own state machine (ECC). Its behavior is determined solely by the data flow and the interconnection of its internal sub-blocks.

## Application Scenarios
* **Signal Filtering:** Forwarding of events only when a specific state is active.
* **Adapter Logic:** Use in systems that rely heavily on adapter connections to minimize wiring complexity.
* **Start Trigger:** Triggers processes as soon as a Boolean flag within an adapter structure changes to `TRUE`.

## ⚖️ Comparison with similar function blocks
* **E_R_TRIG:** The standard function block for event-based rising edge detection with separate event and data inputs. `AX_R_TRIG` is the equivalent for adapter connections.
* **R_TRIG:** The classic PLC function block (IEC 61131-3) that is polled cyclically. `AX_R_TRIG`, on the other hand, operates purely event-driven.

## Conclusion

The **AX_R_TRIG** is a specialized component for the 4diac environment that seamlessly integrates the logic of rising edge detection or a high-pass filter into designs using `AX` adapters. It simplifies the network by eliminating the need to explicitly split adapter signals for testing.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
