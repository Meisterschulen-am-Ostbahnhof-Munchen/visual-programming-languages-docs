# TIME_ATM_AX_SEL_ATM

![TIME_ATM_AX_SEL_ATM](./TIME_ATM_AX_SEL_ATM.svg)

*No image available*

* * * * * * * * * *
## Introduction

The function block `TIME_ATM_AX_SEL_ATM` is used for binary selection between two time values (data type `TIME`) based on a selection signal.

The block combines the classic selection logic of the IEC 61131-3 `SEL` block with the event-driven architecture of IEC 61499. The use of standardized, unidirectional adapters enables clean encapsulation and a reduction in the number of interconnects in complex control networks.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the acquisition and processing of the data input `IN0`.

### **Event Outputs**

*(No direct event outputs are declared. Event forwarding is encapsulated via the output adapter `OUT`)*

### **Data Inputs**

* **IN0** (`TIME`): The first selectable time value. This value is passed through to the output when the selection signal of the adapter `G` is in the state `FALSE`.

### **Data Outputs**

*(No direct data outputs declared. Data is transmitted encapsulated via the output adapter `OUT`)*

### **Adapters**

* **OUT** (Plug, Type: `adapter::types::unidirectional::ATM`): The selected output adapter. This adapter outputs the selected time value (`D1`) along with the corresponding acknowledgment event (`E1`).
* **IN1** (Socket, Type: `adapter::types::unidirectional::ATM`): The second selectable time value received via this adapter (`D1` as the time value, `E1` as the trigger event). This value is selected when the selection signal is `TRUE`.
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector adapter. The Boolean signal (`D1`) determines which input is connected to the output. The event `E1` triggers the recalculation.
...* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector adapter. The Boolean signal (qzmsdocs000 ---

## Functionality

The behavior of the function block is based on an internal network of standard function blocks:

1. **Data Acquisition and Synchronization:**

When an event occurs at one of the inputs (`EI0`, `IN1.E1`, or `G.E1`), the respective value is stabilized and temporarily stored using D flip-flops (`E_D_FF` or `E_D_FF_ANY`).

2. **Value Transfer:**

The data is transferred to the central selection block `F_SEL` via internal move blocks (`F_MOVE`).

3. **Selection Logic:**

The function block `F_SEL` evaluates the control signal from the adapter `G`:

* If `G.D1` = `FALSE`, the value of `IN0` is selected.
* If `G.D1` = `TRUE`, the value of `IN1.D1` is selected.
4. **Output:**

The selected value is passed to the plug `OUT`. The initial event `OUT.E1` signals to the subsequent system that a new valid time value is present at `OUT.D1`.

                  +-------------------------+
|  TIME_ATM_AX_SEL_ATM    |
(TIME) IN0 ---->                         |
  (Event) EI0 ---->                         |     +-----------+
|                         |====>|    OUT    | (Plug: ATM)
  (Socket) IN1 ===>                         |     +-----------+
(Socket)   G ===>                         |
                  +-------------------------+

---

## Technical Features

* **Event Decoupling:** By using D flip-flops in the internal network, the data values are decoupled from the trigger events. This prevents uncontrolled state changes due to asynchronously arriving events.
* **Adapter-Oriented Design:** Minimizes wiring complexity in 4diac-IDE, as time and control signals are bundled and routed via adapter lanes (`ATM` and `AX`).

---

## State Overview

| Selection Signal (`G.D1`) | Trigger Event | Selected Output (`OUT.D1`) |
| :--- | :--- | :--- |
| `FALSE` | `EI0` / `G.E1` | Value of `IN0` |
| `TRUE` | `IN1.E1` / `G.E1` | Value of `IN1.D1` |

---

## Application Scenarios

* **Switching Process Times:** Dynamic selection between two different timer runtimes (e.g., switching between a fast "standard interval" and a slower "maintenance interval" in a process control system).
* **Recipe Control:** Time-controlled processes where different delay times must be applied depending on the operating mode (e.g., automatic vs. manual operation).
* ---

## Comparison with Similar Components

Compared to a classic, purely data-flow-oriented selector component (such as the IEC 61131-3 `SEL`):

* **Advantage:** The `TIME_ATM_AX_SEL_ATM` operates entirely event-driven. An output event is only generated when input data or the selection signal actually changes.
* **Structure:** By using adapters instead of individual pins, the application diagram remains clear even with many signal paths.

--

## Conclusion

The `TIME_ATM_AX_SEL_ATM` is a specialized and robust auxiliary component for the structured selection of time values. It is ideally suited for modular architectures where clarity and event-discrete processing are paramount.