# AL_AX_SEL_AL

![AL_AX_SEL_AL](./AL_AX_SEL_AL.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AL_AX_SEL_AL` is an event-driven selector (binary selection) for IEC 61499 systems in the 4diac IDE. It acts as a multiplexer, forwarding data from one of two input adapters to an output adapter based on the state of a selector signal. The block consistently leverages the advantages of adapters to neatly encapsulate data and event streams and minimize the complexity of the wiring in the application diagram.

## Interface Structure

Since this function block is internally structured as a network and is entirely based on adapter interfaces, it does not have any directly accessible, traditional input or output variables.

## **Event Inputs**
*No direct event inputs are available. Event control is handled implicitly via the connected adapters.*

### **Event Outputs**
*No direct event outputs are available. Event forwarding is handled implicitly via the output adapter.*

### **Data Inputs**
*No direct data inputs are available.*

### **Data Outputs**
*No direct data outputs are available.*

### **Adapters**

#### **Plugs**
* **`OUT`** (Type: `adapter::types::unidirectional::AL`):

The selected output. This adapter outputs the selected data (`D1`) and the associated update event (`E1`).


#### **Sockets**

* **`G`** (Type: `adapter::types::unidirectional::AX`):

The selector input (gate/selector). Controls which of the two inputs (`IN0` or `IN1`) is routed to the output.

* **`IN0`** (Type: `adapter::types::unidirectional::AL`):

The first selectable input channel. This is active and routed to the output when the selector `G` is in the state `FALSE` (or logic 0).

* **`IN1`** (Type: `adapter::types::unidirectional::AL`):

The second selectable input channel. This is active and is passed to the output when the selector `G` has the state `TRUE` (or logic 1).


---

## Functionality

The component implements classic multiplexer logic (equivalent to `SEL` in IEC 61131-3) in the IEC 61499 context:

1. **Event Handling & Buffering:**

When an event occurs on one of the input adapters (`IN0`, `IN1`) or the selector adapter (`G`), internal D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) capture the data values and store them temporarily.

2. **Data Type Conversion:**

The buffered data values are forwarded to the central selection block via internal transfer blocks (`F_MOVE` with the data type `LWORD`).

3. **Selection Logic (`F_SEL`):**

The core of the network evaluates the state of the selector `G`:

* If `G` equals `FALSE`, the signal from `IN0` is passed to the output.


* If `G` equals `TRUE`, the signal from `IN1` is passed to the output.

4. **Output:**

After a successful selection, the result is transferred via another flip-flop to the plug `OUT` and made available there simultaneously with an event (`OUT.E1`).

---

## Technical Features

* **Type Openness through LWORD Abstraction:** The internal use of `LWORD` (64-bit) for the copy operations (`F_MOVE`) allows for high flexibility in the data being transferred, as various bit and integer patterns can be transmitted without information loss.

* **Full Event Control:** Any change to any input or selector triggers an immediate recalculation. This ensures that consistent and up-to-date data is always available at the output.

---

## State Overview

| Selector State (`G.D1`) | Output Value (`OUT.D1`) | Trigger Event |

| :--- | :--- | :--- |

| `FALSE` (0) | Value of `IN0.D1` | Event on `IN0` or `G` |

| `TRUE` (1) | Value of `IN1.D1` | Event on `IN1` or `G` |

---

## Application Scenarios

* **Setpoint Switching:** Switching between a standard setpoint (`IN0`) and an alternative setpoint (`IN1`) based on an external control signal.

* **Manual/Automatic Operation:** Switching a control signal for a valve or motor between a manually specified value (e.g., from a visualization) and the calculated value of an automatic controller.


* * **Sensor Redundancy:** Dynamic switching to a backup sensor (`IN1`) if the primary sensor (`IN0`) is flagged as faulty via a diagnostic function (switching controlled by the fault bit on `G`).

---

## Comparison with Similar Function Blocks

Compared to a standard `SEL` function block from the IEC 61131-3 library, `AL_AX_SEL_AL` offers the following advantages:
* **Reduced Wiring Effort:** Encapsulation in adapters eliminates the need to run separate event and data lines. A single connection path per channel is sufficient.


---

Compared to a standard `SEL` function block from the IEC 61131-3 library, `AL_AX_SEL_AL` offers the following advantages:

* **Reduced Wiring Effort:** Encapsulation in adapters eliminates the need for separate event and data lines. A single connection path per channel is sufficient.

* * **Event Coupling:** The function block inherently responds to the event triggers integrated into the adapters, eliminating the need for manual event-based linking in the FBD (Function Block Diagram).

---

## Conclusion

The `AL_AX_SEL_AL` function block is an efficient and clean solution for switching tasks in complex 4diac applications. Through the consistent use of unidirectional adapters, it promotes modular software design and ensures clear control topologies while providing robust, event-driven signal processing.