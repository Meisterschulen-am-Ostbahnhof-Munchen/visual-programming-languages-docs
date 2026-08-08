# AR_AX_SEL_AR

![AR_AX_SEL_AR](./AR_AX_SEL_AR.svg)

* * * * * * * * * *
## Introduction

The function block `AR_AX_SEL_AR` is used for binary selection between two analog input signals transmitted via adapters. Based on the state of a selector signal, one of the two inputs is passed through to the output.

By consistently using adapters instead of traditional discrete data and event pins, the complexity of the wiring in the higher-level IEC 61499 application diagram is significantly reduced.

## Interface Structure

Since this function block relies entirely on adapter-based communication, it has no direct, traditional event or data interfaces at the top level. All communication is handled via the declared adapters.


### **Event Inputs**
*No direct event inputs available (events are received via the adapter interfaces).*

### **Event Outputs**
*No direct event outputs available (events are sent via the adapter interfaces).*

### **Data Inputs**
*No direct data inputs available.*

### **Data Outputs**
*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **G** (Type: `adapter::types::unidirectional::AX`):

The selector adapter. The signal present here controls which of the two inputs (`IN0` or `IN1`) is passed to the output.

### * **IN0** (Type: `adapter::types::unidirectional::AR`):

The first selectable signal input. This value is passed to output `OUT` when selector `G` is in state `FALSE` (0).

* **IN1** (Type: `adapter::types::unidirectional::AR`):

The second selectable signal input. This value is passed to output `OUT` when selector `G` is in state `TRUE` (1).


#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AR`):

The selected output adapter. It provides the value of the currently active input, including the corresponding update event.


 ---

## Functionality

Inside the function block `AR_AX_SEL_AR` is a network of standard IEC 61131-3 and IEC 61499 components that process the adapter signals:

1. **Event and Data Acquisition:**

As soon as an event `E1` arrives at one of the input adapters (`IN0`, `IN1`, or `G`), it is intercepted by internal edge-triggered flip-flops (`E_D_FF` or `E_D_FF_ANY`). The corresponding data values (`D1`) are temporarily stored.

2. **Data Conversion:**

The values of the analog inputs are routed through conversion blocks of type `F_MOVE` (configured to data type `REAL`) to ensure consistent data processing.

3. **Selection Logic (Multiplexing):**

The standard selection block `F_SEL` performs the actual selection:

* If the value of `G.D1` equals `FALSE`, the signal from `IN0` is passed to the output.


* If the value of `G.D1` is equal to `TRUE`, the signal is passed on to `IN1`.

4. **Output:**

The selected signal is passed via another `F_MOVE` block to the output flip-flop `E_D_FF_ANY_OUT`. This flip-flop generates the output event `E1` at plug `OUT` and makes the selected value available to `OUT.D1`.


---

## Technical Features

* **Unidirectional Adapter Structure:** The function block uses unidirectional adapter types (`AR` for analog values, `AX` for binary values), ensuring clear and interference-free signal direction within the system.

* **Type Consistency:** Internally, the function block uses the data type `REAL` for analog signals (configured via the attributes of the `F_MOVE` function blocks).

* **Event-Driven:** The output is recalculated and updated immediately as soon as either the selection `G` changes or new values are signaled at the inputs `IN0` or `IN1`.


---

## State Overview

The behavior can be described using the following simple logic table:

| State Selector (`G.D1`) | Value at Output (`OUT.D1`) | Triggering Event |

| :--- | :--- | :--- |

| `FALSE` | Value of `IN0.D1` | Event at `IN0.E1` or Change at `G.E1` |

| `TRUE` | Value of `IN1.D1` | Event at `IN1.E1` or Change at `G.E1` |


---

## Application Scenarios

* **Sensor Redundancy:** Switching between a primary and a secondary analog sensor (e.g., temperature sensor or pressure sensor) in case of primary sensor failure.

* **Manual/Automatic Switching:** Optionally applying an automatic control value (e.g., calculated by a PID controller) or a manually specified setpoint to an actuator.

* **Signal Routing:** Dynamic path selection in more complex process engineering or agricultural control applications.

--

## Comparison with Similar Function Blocks

Compared to the standard IEC 61131 function block `F_SEL`, `AR_AX_SEL_AR` offers the advantage of complete encapsulation via adapters. While the standard `F_SEL` requires events and data to be wired and synchronized separately in the network, `AR_AX_SEL_AR` reduces the wiring effort in the higher-level system to just three connections (two input adapters, one output adapter) plus the selection signal.

---

## Conclusion

The `AR_AX_SEL_AR` is an extremely useful auxiliary component for IEC 61499 applications. By abstracting the data and event streams into standardized adapter channels, it ensures a streamlined application design and simplifies the implementation of switching and redundancy logic for analog signals.