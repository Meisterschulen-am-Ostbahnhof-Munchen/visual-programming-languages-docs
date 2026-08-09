# AUDI_AX_SEL_AUDI

![AUDI_AX_SEL_AUDI](./AUDI_AX_SEL_AUDI.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AUDI_AX_SEL_AUDI` serves as a binary selector (selection switch) for unidirectional communication adapters. Based on the state of a control signal at a selector adapter, it allows the data and event stream between two alternative input adapters to be redirected to a single output adapter.

The block encapsulates the necessary synchronization and conversion logic to ensure a clean separation of events and data flows within IEC 61499 applications.

## Interface Structure

### **Event Inputs**

*No direct event inputs are defined on the block interface. Event processing is fully encapsulated via the connected adapters.*

### **Event Outputs**

*No direct event outputs are defined on the function block interface. Event forwarding is handled entirely via the output adapter.*

### **Data Inputs**

*No direct data inputs are available.*

### **Data Outputs**

*No direct data outputs are available.*

### **Adapters**

#### **Sockets (Input Connections)**

* **IN0** (Type: `adapter::types::unidirectional::AUDI`):

First selectable input adapter. Data and events arriving here are passed through to the output when the selection signal `G` has the logical state `FALSE` (or `0`).

* **IN1** (Type: `adapter::types::unidirectional::AUDI`):

Second selectable input adapter. Data and events arriving at this adapter are passed to the output when the selection signal `G` has the logical state `TRUE` (or `1`).

* **G** (Type: `adapter::types::unidirectional::AX`):

Selector adapter. The signal on this adapter determines which of the two inputs (`IN0` or `IN1`) is routed to the output.

#### **Plugs (Output Connections)**

* **OUT** (Type: `adapter::types::unidirectional::AUDI`):

Output adapter. Outputs the data and the corresponding trigger event of the currently selected input.

---

## Functionality

The internal behavior of the function block is implemented by a network of standard function blocks:

1. **Event and Data Synchronization**:

The signals received via the sockets (`IN0`, `IN1`, `G`) are first processed through edge- or level-triggered D flip-flops (`E_D_FF` and `E_D_FF_ANY`). This ensures that data values (`D1`) and events (`E1`) are processed synchronously.

2. **Data Conversion**:

The synchronized data values from the two inputs are transferred to the selection block via two transfer blocks (`F_MOVE` with the data type `UDINT`).

3. **Selection Control**:

The function block `F_SEL` (IEC 61131-3 Selection) performs the actual logical switching:

* If the control signal of the adapter `G` is `0` (`FALSE`), the value of `IN0` is selected.
* If the control signal of the adapter `G` is `1` (`TRUE`), the value of `IN1` is selected.
4. **Output**:

The selected result is transferred via another transfer block (`F_MOVE_OUT`) to the output flip-flop `E_D_FF_ANY_OUT`. This flip-flop generates the output event `OUT.E1` and makes the selected data value available to `OUT.D1`.

---

## Technical Features

* **UDINT Data Processing**: Although the adapters are of the generic type `AUDI`, the user data (`D1`) is explicitly processed and transmitted internally as `UDINT` (Unsigned Double Integer / 32-bit integer).
* **Event-driven behavior**: Any change to the inputs or the selector triggers a recalculation via the internal coupling network and the output event of the adapter `OUT`.
* **Encapsulation**: By using adapters instead of individual event and data ports, the wiring effort in the overall system diagram is drastically reduced.

---

## State overview

Since the function block is structured as a function block network, it does not have a classic state machine (ECC). The logical behavior can instead be described using the following function table:

| State Selector (`G.D1`) | Triggering event | Active data path | Value at output (`OUT.D1`) | Event at output (`OUT.E1`) |
| :--- | :--- | :--- | :--- | :--- |
| `FALSE` | Event on `IN0.E1` or `G.E1` | `IN0` -> `OUT` | Equivalent to `IN0.D1` | Triggered |
| `TRUE` | Event on `IN1.E1` or `G.E1` | `IN1` -> `OUT` | Equivalent to `IN1.D1` | Triggered |

---

## Application Scenarios

* **Setpoint Switching**: Switching between an automatic setpoint (e.g., from a PID controller at `IN1`) and a manual setpoint (e.g., from a visualization at `IN0`) via a selection signal at `G`.
* **Sensor Redundancy**: Fail-safe switching between a primary sensor and a backup sensor in case of signal interference.
* **Recipe Control**: Selection of different predefined parameter profiles during operation.
* ---

## Comparison with Similar Function Blocks

Compared to the standard selection function block `F_SEL` from the IEC 61131-3 library, `AUDI_AX_SEL_AUDI` offers the advantage of direct interaction with structured, unidirectional adapters (`AUDI` and `AX`). Using the standard `F_SEL` function block would require manually splitting all event and data lines of the adapters, connecting them individually, and then reconnecting them, which is error-prone and makes the application diagram cluttered.

--

## Conclusion

The `AUDI_AX_SEL_AUDI` function block offers an elegant, clean, and reusable solution for signal switching in 4diac-based control architectures. Through the consistent use of adapters, he makes a significant contribution to the modularity and clarity of complex control programs.