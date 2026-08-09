# AIS_AX_SEL_AIS

![AIS_AX_SEL_AIS](./AIS_AX_SEL_AIS.svg)

* * * * * * * * * *

## Introduction

The function block **AIS_AX_SEL_AIS** is a binary selection block for the IEC 61499 architecture in the 4diac IDE. It dynamically selects between two unidirectional analog input signals based on the state of a selection signal (gate) and forwards the selected signal to the output.

Internally, the block uses the classic selection logic of the standardized `SEL` block (known from IEC 61131-3), but is fully optimized for event-driven execution according to IEC 61499 and encapsulates the data and event streams using standardized adapters.

## Interface Structure

The function block uses an adapter-based interface design. It has no directly accessible event- or data-based inputs and outputs at the main level, but handles all communication via plugs and sockets.

### **Event Inputs**

*No direct event inputs are available. Event processing is handled encapsulated via the adapter interfaces.*

### **Event Outputs**

*No direct event outputs are available. Event output is handled encapsulated via the output adapter.*

### **Data Inputs**

*No direct data inputs are available.*

### **Data Outputs**

*No direct data outputs are available.*

#### **Adapters**

#### **Sockets (Input Interfaces)**

* **G** (Type: `adapter::types::unidirectional::AX`):
The selector input (gate). Determines which of the two inputs (`IN0` or `IN1`) is routed to the output.

* **IN0** (Type: `adapter::types::unidirectional::AIS`):

The first selectable input channel. This channel is activated when the selector `G` is in the state `FALSE` (0).

* **IN1** (Type: `adapter::types::unidirectional::AIS`):

The second selectable input channel. This channel is activated when the selector `G` is in the state `TRUE` (1).

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AIS`):

The selected output channel. It provides the value of the currently active input channel and the corresponding update event.

---

## Functionality

Inside the FB, a network of standard function blocks synchronizes the adapter events and makes the logical selection:

1. **Event Synchronization & Signal Storage:**

Data arriving at the adapters `IN0`, `IN1`, and `G` is temporarily stored in data flip-flops (`E_D_FF_ANY` and `E_D_FF`, respectively) each time a corresponding adapter event (`E1`) arrives. This ensures that the data values are stably available for further processing.

The data arriving at the adapters `IN0`, `IN1`, and `G` are temporarily stored in data flip-flops (`E_D_FF_ANY` and `E_D_FF`) whenever a corresponding adapter event (`E1`) arrives. This ensures that the data values are stably available for further processing. 2. **Data Provisioning:**

The function blocks `F_MOVE_IN0` and `F_MOVE_IN1` copy the cached data (interpreted as data type `STRING`) and forward it to the actual selection core.

3. **Selection Process (F_SEL):**

The core function block `F_SEL` (type `iec61131::selection::F_SEL`) evaluates the state of the selector `G`:

* If `G` = `FALSE`, the value of `IN0` is selected.
* If `G` = `TRUE`, the value of `IN1` is selected.
4. **Output Transfer:**

The selection result is transferred via the function block `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`. This triggers the event `E1` at the output adapter `OUT` and places the selected data value at the output `D1`.

---

## Technical Features

* **Adapter Encapsulation:** By using unidirectional adapters (`AIS` and `AX`), the application diagram in the 4diac IDE remains uncluttered, as data and event lines are bundled into a single connection.
* **Asynchronous Event Handling:** Any change to one of the inputs (`IN0`, `IN1`) or to the selector (`G`) automatically retriggers the selection process and updates the output accordingly.
* **Asynchronous Event Handling:** * **Data Type Specification:** The internal data copiers (`F_MOVE`) are hard-coded to the data type `STRING`, indicating that the signals to be switched are transmitted as strings in the `AIS` adapter.

---

## State Overview

| Selector State (`G`) | Last Event on... | Active Output (`OUT.D1`) | Description |
| :--- | :--- | :--- | :--- |
**`FALSE`** | `IN0.E1` or `G.E1` | Value of `IN0.D1` | Input 0 is active. Changes to `IN1` have no effect on the output. |
| **`TRUE`** | `IN1.E1` or `G.E1` | Value of `IN1.D1` | Input 1 is active. Changes to `IN0` have no effect on the output. |

---

## Application Scenarios

* **Sensor Redundancy / Failsafe Systems:** Switching between a primary sensor and a backup sensor in case of signal loss or malfunction.
* **Operating Mode Selection:** Dynamically forwarding different parameter sets (e.g., automatic vs. manual setpoints) to an actuator. * **Signal Routing in Agricultural Machinery (ISOBUS Context):** Channel control for analog process values or status messages in complex control networks.

---

## Comparison with Similar Function Blocks

* **Classic `SEL` (IEC 61131-3):** The classic `SEL` function block does not have event control and is purely data flow-oriented. `AIS_AX_SEL_AIS` extends this principle to include event-based control for distributed systems.
* **Standard Selection Function Blocks without Adapters:** Typical IEC 61499 selection functions often use many individual event and data pins. This function block offers significantly improved maintainability and modularity in system design thanks to its adapter interfaces.

---

## Conclusion

The **AIS_AX_SEL_AIS** is a specialized and high-performance solution for signal switching in the 4diac IDE. Its strict use of adapters and reliable internal event processing make it ideally suited for clean, modular software architectures in the fields of industrial automation and agricultural technology.