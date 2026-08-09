# ADI_AX_SEL_ADI

![ADI_AX_SEL_ADI](./ADI_AX_SEL_ADI.svg)

*No image available*

* * * * * * * * * *

## Introduction

The function block `ADI_AX_SEL_ADI` is used for binary selection between two analog or integer input signals transmitted via unidirectional adapters. Based on the state of a digital selector signal, either the value of the first or the second input is passed through to the output.

The block is implemented as a composite function block (FB) and uses internally standardized selection and copy functions according to IEC 61131-3, which have been adapted for the event-driven IEC 61499 adapter architecture.

## Interface Structure

The interface of this function block is implemented entirely via adapters. There are no direct elementary data or event inputs outside of the adapter structures.

### **Event Inputs**

*No direct event inputs available (events are received via the adapter interfaces).*

### **Event Outputs**

*No direct event outputs available (events are sent via the adapter interfaces).*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Plugs (Connectors - Outputs)**

* **OUT** (Type: `adapter::types::unidirectional::ADI`):

The selected output. Sends the selected data signal (`D1`) and the associated update event (`E1`).

#### **Sockets (Inputs)**

* **IN0** (Type: `adapter::types::unidirectional::ADI`):

First selectable input. This value is passed through to the output when the selection signal `G` is set to `FALSE` (0).

* **IN1** (Type: `adapter::types::unidirectional::ADI`):

Second selectable input. This value is passed through to the output when the selection signal `G` is set to `TRUE` (1).

* **G** (Type: `adapter::types::unidirectional::AX`):

The selector (gate) for controlling the selection process. A change in state controls the switching between `IN0` and `IN1`.

---

## Functionality

The internal structure of `ADI_AX_SEL_ADI` operates purely event-driven:

1. **Input Acquisition**:

When an event (`E1`) arrives at one of the inputs (`IN0`, `IN1`) or at the selector (`G`), the corresponding internal data value (`D1`) is acquired via event-driven memory elements (`E_D_FF_ANY` or `E_D_FF`).

2. **Data Buffering**:

The function blocks `F_MOVE_IN0` and `F_MOVE_IN1` copy the data (interpreted as data type `DINT`) to the central selection function block `F_SEL`.

3. **Selection Logic**:

The function block `F_SEL` (corresponding to the classic `SEL` standard function block from IEC 61131-3) evaluates the control signal `G`:

* If the signal from adapter `G` is equal to `FALSE`, the signal from `IN0` is selected.
* If the signal from adapter `G` is equal to `TRUE`, the signal from `IN1` is selected.
4. **Output**:

The selected value is passed via `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`. This flip-flop sets the value `D1` on output adapter `OUT` and immediately triggers the corresponding event `OUT.E1` to inform downstream components about the data change.

---

## Technical Features

* **Adapter Encapsulation**: By using adapters (`ADI` and `AX`), the number of visible connection lines in the 4diac application diagram is drastically reduced, improving clarity and maintainability.
* **Data Type Specification**: The internal copy operations (`F_MOVE_IN0`, `F_MOVE_IN1`, and `F_MOVE_OUT`) are permanently configured for the data type `DINT` (Double Integer).
* **Real-Time Pass-Through**: The function block responds instantly to every edge of the input signals as well as the selection signal.
* ---

## State Overview

Since this is a purely data-flow and event-driven network function block (Composite FB), it does not have an internal state machine (ECC). Its behavior can be described statically as follows:

| State Selector `G` | Event at Input | Behavior at Output `OUT` |
| :--- | :--- | :--- |
| `FALSE` | Any Event | `OUT.D1` receives the value of `IN0.D1`; `OUT.E1` is triggered. |
| `TRUE` | Any Event | `OUT.D1` receives the value from `IN1.D1`; `OUT.E1` is triggered. |

--

## Application Scenarios

* **Manual/Automatic Switching**: Selection between a manually specified setpoint (e.g., via an HMI at `IN1`) and an automatically calculated controller setpoint (at `IN0`).
* **Sensor Redundancy**: Switching to a backup sensor (`IN1`) if diagnostic logic detects a fault in the main sensor (`IN0`) and sets the signal `G` to `TRUE`.
* **Recipe Control**: Dynamic selection of various predefined process parameters during operation.

---

## Comparison with Similar Function Blocks

* **Standard `F_SEL`**: The standard selection function block works with elementary data types and requires explicit event connections for triggers and confirmations. `ADI_AX_SEL_ADI` fully automates this process via structured adapter channels.
* **Analog Multiplexers**: Unlike multiplexers with an indefinite number of channels, this function block specializes in fast and efficient binary selection (1 out of 2).

---

## Conclusion

The `ADI_AX_SEL_ADI` is an extremely useful auxiliary function block for IEC 61499 applications in the 4diac IDE. It combines the proven selection logic of IEC 61131-3 with the modern, clean design principles of adapter-based event-oriented communication.