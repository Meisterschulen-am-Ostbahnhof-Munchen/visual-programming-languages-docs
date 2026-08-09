# AI_AX_SEL_AI

![AI_AX_SEL_AI](./AI_AX_SEL_AI.svg)

*(No image available)*

* * * * * * * * * *

The function block `AI_AX_SEL_AI` is a binary selector (multiplexer) for analog signals based on the IEC 61499 architecture. It serves to select one of two analog input signals based on a control signal (selector) and forward it to the output. The unique feature of this block lies in its consistent use of adapters, which significantly simplifies and structures the cabling within the 4diac-ide development environment.

The function block does not have traditional discrete inputs and outputs for data and events at its main level. Instead, all communication is implemented via standardized adapters.

*No direct event inputs available (fully encapsulated via adapters).*

*No direct event outputs available (fully encapsulated via adapters).*

*No direct data inputs available (fully encapsulated via adapters).*

*No direct data outputs available (fully encapsulated via adapters).*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): The selector input. This adapter provides the control signal (Boolean state) that determines which of the two analog inputs is routed to the output.
* **IN1** (Type: `adapter::types::unidirectional::AI`): Selectable analog input 1. This input is enabled when the selector signal `G` is in the state `TRUE` (1).
* **OUT** (Type: `adapter::types::unidirectional::AI`): Selected analog output. It outputs the signal of the currently active input (`IN0` or `IN1`).

---

#### **Plugs (Ausgangs-Schnittstellen)**

#### **Sockets (Eingangs-Schnittstellen)**

## Functionality

The module's internal logic controls the data and event flow as follows:

1. **Event Control & Data Acquisition:**
* Each time an event (`E1`) arrives at one of the input adapters (`IN0`, `IN1`, or `G`), the corresponding data element (`D1`) is temporarily stored via internal edge- or event-triggered memory modules (`E_D_FF` and `E_D_FF_ANY`).
* * Internal `F_MOVE` function blocks convert and pass the values (as data type `INT`) to the central selection function block.
2. **Selection Logic:**
* The core function block `F_SEL` (a standardized IEC 61131-3 selection function block) evaluates the control signal `G`.
* If the control signal `G` is `FALSE`, the value of `IN0` is selected.
* * If the control signal `G` is on `TRUE`, the value of `IN1` is selected.
3. **Output:**
* After successful selection, the selected value is passed via another `F_MOVE` block and an output flip-flop (`E_D_FF_ANY_OUT`) to the output plug `OUT`.
* Simultaneously, the output event `OUT.E1` is triggered to inform subsequent blocks about the value change.
* ---
* **Data Type Specification:** Internally, the function block uses the data type `INT` (integer) for analog values, which is defined by the parameterization of the internal `F_MOVE` instances.
* **Adapter-Based Architecture:** By encapsulating events and data in the adapters `AI` (Analog Input) and `AX` (Auxiliary Control), the number of connection lines in the higher-level system diagram is drastically reduced.
* **Event-Driven Propagation:** Every update of an input (regardless of whether it is the data or the selector) triggers the recalculation and output of an event at the output.

--

The function block operates purely on an event- and data-flow-driven basis. There are no complex internal states (no state machine/ECC in the classical sense), but rather a direct dependency of the output on the inputs:

| Selector input (`G.D1`) | Active path | Output value (`OUT.D1`) | Output event (`OUT.E1`) |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Value of `IN0.D1` | Triggered on every event |
| `TRUE` | `IN1` | Value of `IN1.D1` | Triggered on every event |

---

* **Redundant Sensors:** Switching between a primary and a secondary (backup) analog sensor in the event of a detected failure.
* **Manual/Automatic Switching:** Selection between a manually setpoint (e.g., via an HMI connected to `IN0`) and an automatically calculated controller setpoint (connected to `IN1`).
* **Recipe-Controlled Signal Redirection:** Dynamic assignment of analog process parameters based on the current operating state of a system.

--

* **Standard `F_SEL` (IEC 61131-3):** The classic `F_SEL` function block requires discrete pins for events and data. The `AI_AX_SEL_AI` module encapsulates this functionality in user-friendly adapter structures, increasing reusability and clarity in complex IEC 61499 applications.
* **Classic Multiplexers (e.g., MUX):** While a multiplexer often handles multiple channels (e.g., 4 or 8), this module is optimized as a slim, highly efficient 2-way selector switch for dedicated analog signals.

---

The `AI_AX_SEL_AI` module provides an elegant, adapter-based solution for the binary selection of analog signals in distributed control systems. Thanks to the clean separation and encapsulation of the interfaces in standardized adapters, it is ideally suited for use in modular and service-oriented automation architectures within Eclipse 4diac.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion