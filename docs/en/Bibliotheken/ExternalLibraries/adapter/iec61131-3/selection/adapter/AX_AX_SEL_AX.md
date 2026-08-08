# AX_AX_SEL_AX

<!-- Bild des FB falls vorhanden (Platzhalter) -->
<!-- ![AX_AX_SEL_AX](AX_AX_SEL_AX.png) -->

![AX_AX_SEL_AX](./AX_AX_SEL_AX.svg)

* * * * * * * * * *
## Introduction
The function block `AX_AX_SEL_AX` is used for binary selection between two Boolean signals transmitted via standardized adapters. It represents an IEC 61499-compliant encapsulation of the classic IEC 61131-3 `SEL` function. By using adapters, both the data values and the associated events are transmitted together, which significantly reduces the wiring effort in control application design.

## Interface Structure

### **Event Inputs**
*This function block does not have direct event inputs. Event control is handled entirely via the adapters.*

### **Event Outputs**

*This function block has no direct event outputs. Event output is handled entirely via the adapters.*

### **Data Inputs**
*This function block has no direct data inputs.*

### **Data Outputs**
*This function block has no direct data outputs.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN0** (Type: `adapter::types::unidirectional::AX`):

Selectable input adapter 0. The value applied here is passed to the output when the selection signal `G` is in the state `FALSE`.

* **IN1** (Type: `adapter::types::unidirectional::AX`):

Selectable input adapter 1. The value applied here is passed to the output when the selection signal `G` is in the state `TRUE`.

* **G** (Type: `adapter::types::unidirectional::AX`):

Selector adapter. Determines which of the two inputs (`IN0` or `IN1`) is connected to the output.


#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AX`):

Output adapter that outputs the selected signal (`D1`) and the corresponding confirmation event (`E1`).


---

## Functionality
Internally, the `AX_AX_SEL_AX` is based on an event-driven network that processes the input signals from the sockets and outputs them via the plug:

1. **Event Detection:** Every arrival of an event (`E1`) at the adapters `IN0`, `IN1`, or `G` triggers an internal edge-triggered flip-flop (`E_D_FF` or `E_D_FF_ANY`, respectively).

2. **Data Buffering & Transport:** The data values (`D1`) from the adapters are forwarded to the central selection block `F_SEL` via conversion blocks of type `F_MOVE` (configured to data type `BOOL`).

3. **Selection Logic:**

* If the signal at adapter `G` equals `FALSE`, the internal block `F_SEL` switches the value of `IN0` to the output.


* * ... * If the signal at adapter `G` equals `TRUE`, the value of `IN1` is set to the output.

4. **Output:** The selected value is passed to the flip-flop of the output adapter, which triggers the event `OUT.E1` and updates the data point `OUT.D1`.

---

## Technical Features
* **Typing to BOOL:** The internal data copiers (`F_MOVE`) are hard-coded to the data type `BOOL`. Therefore, this specific function block is optimized for selecting Boolean states.

* **Event Synchronization:** The internal use of `E_D_FF` and `E_D_FF_ANY` ensures that data changes at the inputs are immediately and consistently transferred to the output without any cycle delay.

---

## State Overview

Since this is a composite function block (FB), its behavior is directly determined by the data and event flow:

| State Selector `G.D1` | Output `OUT.D1` | Behavior on Event at Inputs |

| :--- | :--- | :--- |

| `FALSE` | Value of `IN0.D1` | Events at `IN0.E1` or `G.E1` trigger an update of `OUT.E1`. |

| `TRUE` | Value of `IN1.D1` | Events at `IN1.E1` or `G.E1` trigger an update of `OUT.E1`. |

--

## Application Scenarios
* **Operating Mode Switching:** Switching between an automatic and a manual command (e.g., opening/closing a valve).

* **Signal Redundancy:** Selection between a primary control signal and a backup signal in case of a failure.


**Signal Redundancy:** Selection between a primary control signal and a backup signal in case of a failure. * **Compact Application Development:** Reduce "spaghetti code" and unwieldy line connections in 4diac-ide by utilizing adapter technology.

---

## Comparison with Similar Components

* **Standard `F_SEL`:** The classic `F_SEL` component requires separate event connections (`REQ` / `CNF`) and data lines for each channel. `AX_AX_SEL_AX` simplifies this by encapsulating it in three input adapters and one output adapter.

* **Multiplexer (MUX):** While a multiplexer can switch between a large number of channels, the `AX_AX_SEL_AX`, as a binary selector, is specialized for exactly two channels, making it more resource-efficient and easier to configure.


---

## Conclusion
The `AX_AX_SEL_AX` is a practical tool for structured application development in IEC 61499. It combines the proven selection logic of IEC 61131 with the modern advantages of adapter-based signal transmission in the 4diac-ide.