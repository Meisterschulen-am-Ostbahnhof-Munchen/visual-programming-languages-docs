# AX_F_TRIG

* * * * * * * * * *
The function block **AX_F_TRIG** (Boolean falling edge detection) is used to detect a falling edge (change from TRUE to FALSE) based on an adapter interface. It is specifically designed for use with the unidirectional adapter type `AX`.
The block checks the Boolean value received via the adapter and triggers an output event if this value is `FALSE`. In the context of event chains where the adapter's event signals a value change, this corresponds to the detection of a falling edge.

The block has an adapter interface (socket) for input and an event output.

This block does not have direct event inputs. Event control is handled via the adapter.

* **EO** (Event Output): This event is triggered when a falling edge (or a logical FALSE state) is detected at the adapter.

This function block has no direct data inputs. The data is obtained via the adapter.

This function block has no direct data outputs.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

* **QI** (Type: `adapter::types::unidirectional::AX`): The input socket. The function block receives both the trigger event and the Boolean value to be checked via this adapter.
* *Comment:* Value to be checked for a falling edge.

## Functionality

The **AX_F_TRIG** is implemented as a composite function block (FB). Its internal logic is based on processing the signals from the `QI` adapter:

1. The `QI` adapter provides an event (`E1`) and a Boolean data value (`D1`).
2. These signals are passed to a D flip-flop (`E_D_FF`). The event acts as the clock (CLK), and the data as the input (D).
3. The flip-flop stores the value and triggers an acknowledgment event.
4. A downstream `E_SWITCH` component evaluates the output state (`Q`) of the flip-flop.
5. If the value `FALSE` (logic 0) is present, `E_SWITCH` passes the event to output **EO**.
6. If the value `TRUE` (logic 1) is present, no event is generated at output **EO**.

In summary: If the adapter sends an event and the transmitted data value is `FALSE`, the function block `EO` fires.

* **Adapter Integration:** The function block encapsulates the logic for splitting the `AX` adapter into individual events and data for logical processing.
* **Composite Network:** The implementation is achieved purely through the interconnection of standard IEC 61499 components (`E_D_FF`, `E_SWITCH`) and contains no custom algorithms in ST or C++.

Since it is a Composite Function Block, the **AX_F_TRIG** does not have its own ECC (Execution Control Chart). Its state is implicitly determined by the state of the internal components (especially the D flip-flop `E_D_FF`).

* **Signal Processing:** Used in systems that utilize `AX` adapters to communicate binary state changes.
* **Event Filtering:** Blocks events as long as the associated data signal is `TRUE` and allows them to pass if it is `FALSE`.
* **E_F_TRIG:** The standard function block for falling edge detection in IEC 61499. It uses separate event (`EI`) and data inputs (`QI`) instead of an adapter.
* **AX_R_TRIG:** The direct counterpart to this function block. It detects a rising edge (change to `TRUE`) using the same adapter type.
* **E_SWITCH:** A generic switch that routes events based on a Boolean value. **AX_F_TRIG** is essentially a specialization of this for adapters.

The **AX_F_TRIG** is a specialized utility block for structured event processing in 4diac. It significantly simplifies working with `AX` adapters by abstracting the logic for detecting the "low" state (falling edge) and directly providing it as the event `EO`, without requiring the user to manually split and examine the adapter signal.

---

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de