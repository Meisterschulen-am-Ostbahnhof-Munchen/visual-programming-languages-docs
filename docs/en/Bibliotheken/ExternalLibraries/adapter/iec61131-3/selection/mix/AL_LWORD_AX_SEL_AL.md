# AL_LWORD_AX_SEL_AL

![AL_LWORD_AX_SEL_AL](./AL_LWORD_AX_SEL_AL.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `AL_LWORD_AX_SEL_AL` is used for the binary selection (multiplexing) of 64-bit data words (`LWORD`). It enables event-driven selection between two input signals and forwarding the selected signal to an output. The unique feature of this block lies in its hybrid architecture of classic IEC 61499 event/data interfaces and modern, adapter-based connections.

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acquisition and processing of the directly applied data value `IN1`.


### **Event Outputs**

* *(No direct event outputs available. Event output is encapsulated via the output adapter `OUT`)*

### **Data Inputs**

* **IN1** (LWORD): Selectable data input (read upon an event at `EI1`).

### **Data Outputs**

* *(No direct data outputs available. Data output is encapsulated via the output adapter `OUT`)*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN0** (Type: `adapter::types::unidirectional::AL`): Unidirectional adapter providing the first selectable input channel. It carries the event `E1` and the data `D1` (LWORD).

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional selector adapter. The received data bit `D1` (BOOL) controls which input is selected.

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AL`): Unidirectional output adapter that outputs the selected `LWORD` signal (`D1`) along with the trigger event (`E1`).


---

## Functionality
The module is internally based on a function block network that synchronizes the asynchronous input signals and controls the selection logic:

1. **Data Storage and Synchronization:**

Both the adapter inputs (`IN0`, `G`) and the direct input (`IN1` via `EI1`) are internally connected to event-driven D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively). Whenever an event arrives at one of the inputs, the corresponding data value is temporarily stored.


2. **Selection Logic (Multiplexer):**

The internal function block `F_SEL` (standard selection element) evaluates the control signal `G` (selector):

* If the signal from adapter `G` is **`FALSE`**, the value of **`IN0`** is selected.

* If the signal from adapter `G` is **`TRUE`**, the value of **`IN1`** is selected.


3. **Event and Data Output:**

As soon as an input value or the selection signal changes and has been recalculated, the selected value is passed to the adapter plug `OUT` via the output flip-flop. Simultaneously, the output event `E1` is triggered on the adapter.

---

## Technical Features
* **Asymmetrical Design:** The component combines an adapter input (`IN0`) and a standard pin input (`IN1`). This is particularly useful when a signal from an adapter-based bus structure needs to be compared with or switched against a local value generated within the application.


---

* **Asymmetrical Design:** The component combines an adapter input (`IN0`) and a standard pin input (`IN1`). This is especially useful when comparing or switching a signal from an adapter-based bus structure with a localized value generated within the application.


* **Event-driven data consistency:** By using `E_D_FF` (Event Double Flip-Flop) function blocks in the internal network, it is ensured that data changes are only processed when the corresponding event occurs.

---

## State overview
Since this is a pure data and event flow network (composite function block) without an internal state machine (ECC), the behavior can be described via the following signal paths:

* **Trigger via `G.E1`:** Updates the selector. The output `OUT` immediately reflects the input corresponding to the new selector state.

* **Trigger via `IN0.E1`:** Updates the data value `IN0`. If `G` is active on `FALSE`, this new value is immediately output to `OUT`.

* **Trigger via `EI1`:** Updates the data value `IN1`. If `G` is active on `TRUE`, this new value is immediately output to `OUT`.

---

## Application Scenarios
* **Signal Source Switching:** Switches between a standard process value (`IN0` via adapter) and a manually specified substitute value/constant (`IN1`).

* * **Operating Mode Selection:** Routing of different 64-bit control words or bitmasks depending on the selected plant status (automatic/manual operation via selector `G`).

* **Interface Conversion:** Integration of classic control signals into adapter-based program architectures.

---

## Comparison with Similar Function Blocks

* **F_SEL (Standard IEC 61131-3):** The standard function block `F_SEL` operates purely in a data flow-oriented manner and does not have event-based control or adapter support. `AL_LWORD_AX_SEL_AL` encapsulates this core function and makes it directly usable for event-driven adapter networks in the IEC 61499 context.

* **Standard Channel Selector (MUX):** Unlike a multiplexer, which selects many channels using integer indices, this component is a highly optimized binary 2-channel selector and requires only a Boolean signal for control.

---

## Conclusion
The `AL_LWORD_AX_SEL_AL` is a specialized auxiliary component that bridges the gap between traditional data inputs and modern, adapter-based communication structures. Its internal buffering ensures deterministic and event-driven signal transmission of 64-bit data values.