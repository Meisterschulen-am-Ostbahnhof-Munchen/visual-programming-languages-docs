# AQ_BYTE_AX_SEL_AQ

![AQ_BYTE_AX_SEL_AQ](./AQ_BYTE_AX_SEL_AQ.svg)

* * * * * * * * * *

## Introduction

The function block `AQ_BYTE_AX_SEL_AQ` is a binary selector (multiplexer) for byte signals, specifically designed for use in IEC 61499 systems (such as Eclipse 4diac). It enables event-driven selection between two byte input sources based on a selection signal. The block utilizes standardized, unidirectional adapter interfaces (`AQ` and `AX`) to efficiently and cleanly transmit data and control events.


## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the update and transfer of the data value at the local data input `IN1` (coupled with `IN1`).

### **Event Outputs**

* *No direct event outputs*. Event output is encapsulated via the adapter plug **OUT** (`OUT.E1`).

### **Data Inputs**

* **IN1** (BYTE): Local, selectable byte input value.

### **Data Outputs**

* *No direct data outputs*. Data output is encapsulated via the adapter plug **OUT** (`OUT.D1`).


### **Adapters**

* **Plugs (Connectors):**

* **OUT** (Type: `adapter::types::unidirectional::AQ`): The selected output adapter. It passes the selected byte signal (`D1`) along with the corresponding update event (`E1`).

* **Sockets (Ports):**

* **IN0** (Type: `adapter::types::unidirectional::AQ`): The first selectable byte input via an adapter interface (corresponds to the default input when selector = `FALSE`).

* **G** (Type: `adapter::types::unidirectional::AX`): The selector adapter (gate). The Boolean signal present here determines which input is passed through to the output.


---

## Functionality

The internal network of the `AQ_BYTE_AX_SEL_AQ` combines classic IEC 61131-3 selection logic (`F_SEL`) with the event-driven execution of IEC 61499:

1. **Data Acquisition and Synchronization:**

* The input data from `IN0` (adapter), `IN1` (direct input), and the selection signal `G` (adapter) are processed via event D flip-flops (`E_D_FF` and `G.E1`) upon arrival of events (`IN0.E1`, `EI1`, `G.E1`). The data is buffered (`E_D_FF_ANY`). This ensures that the data values remain consistent until the selection is processed.

* The buffered data is passed to the central selection element using `F_MOVE` function blocks.

2. **Selection Logic (`F_SEL`):**

* If the selection signal of the adapter `G` is for `FALSE`, the value of `IN0` is selected.

* If the selection signal of the adapter `G` is for `TRUE`, the value of `IN1` is selected.

3. **Output:**

* The selected value is passed to the output D flip-flop (`E_D_FF_ANY_OUT`).

* After successful selection, the event `OUT.E1` is triggered, and the selected byte value is made available to `OUT.D1`.


*```
          +-----------------------------------+
          |         AQ_BYTE_AX_SEL_AQ         |
          |                                   |
 (AQ) IN0 |==> [E_D_FF] --> [F_MOVE] ---\     |
          |                              +--> |
  (AX)  G |==> [E_D_FF] -------------> [F_SEL]==> OUT (AQ)
          |                              +--> |
      EI1 |--> [E_D_FF] --> [F_MOVE] ---/     |
      IN1 |--> [  ANY ]                       |
          +-----------------------------------+



---

## Technical Features

* **Event Decoupling:** By using D flip-flops for all inputs, any change to the inputs or the selector results in a consistent update of the output. "Slipping" of undefined states is prevented.

* **Adapter Connection:** The use of unidirectional adapters (`AQ` for analog/byte values, `AX` for binary values) drastically reduces the wiring effort in the higher-level function block diagram, as data and events are carried in a single connection.

---

## State Overview

The following table shows the behavior of output `OUT` depending on selector `G`:

| Selector State (`G.D1`) | Relevant Input | Output value (`OUT.D1`) | Triggering event at output (`OUT.E1`) |

:--- | :--- | :--- | :--- |

**FALSE** | `IN0` (via adapter) | Value of `IN0.D1` | Triggered by `IN0.E1` or `G.E1` |

**TRUE** | `IN1` (direct input) | Value of `IN1` | Triggered by `EI1` or `G.E1` |

---

## Application Scenarios

* **Manual/Automatic Switching:** Switching a byte setpoint between an automatic process value (supplied via the adapter `IN0`) and a manually specified byte value (via the local input `IN1`, e.g., from a visualization).

* **Signal Routing in Distributed Systems:** Dynamic routing of byte data streams in control networks where signals are transmitted via standardized adapter structures.

* **Sensor Redundancy:** Switching between a primary sensor byte and a substitute value upon fault detection via the gate signal `G`.


* ---

## Comparison with Similar Components

* **Standard `F_SEL` (IEC 61131-3):** The standard selection component operates purely on a data flow basis and has no event control or adapter support. `AQ_BYTE_AX_SEL_AQ` extends this functionality with full event control according to IEC 61499 and encapsulates the signals in adapters.

* **Standard `E_SEL`:** This component selects events but does not perform byte-wise data processing or adapter management.

--

## Conclusion

The `AQ_BYTE_AX_SEL_AQ` is a highly modular and robust component for signal control in modern 4diac applications. Through the consistent use of adapters, it integrates seamlessly into clean software architectures and minimizes potential sources of error in event-driven data processing of byte signals.