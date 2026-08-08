# AB_AX_SEL_AB

![AB_AX_SEL_AB](./AB_AX_SEL_AB.svg)

* * * * * * * * * *
## Introduction

The function block `AB_AX_SEL_AB` is a composite function block for IEC 61499 that implements binary selection at the adapter level. Based on a control signal from a selector adapter (`G`), it selects between the signals of two input adapters (`IN0` and `IN1`) and forwards the selected signal to an output adapter (`OUT`).

This block is particularly suitable for event-driven architectures where data streams need to be routed flexibly without disrupting the encapsulation of the adapter interfaces.

## Interface Structure

Since this is an adapter-based function block, the classic event and data inputs are completely encapsulated within the adapter interfaces.

### **Event Inputs**
*No direct event inputs are available. Control is achieved via events within the adapters.*

### **Event Outputs**
*No direct event outputs are available. Signaling is achieved via events within the output adapter.*

### **Data Inputs**
*No direct data inputs are available.*

### **Data Outputs**
*No direct data outputs are available.*

### **Adapter**

| Name | Direction | Type | Description |

| :--- | :--- | :--- | :--- |

| **OUT** | Plug (Consumer) | `adapter::types::unidirectional::AB` | The selected output. Outputs the forwarded signal. |

| **IN0** | Socket (Provider) | `adapter::types::unidirectional::AB` | First selectable input (selected when selector `G` is in state `FALSE`). |

| **IN1** | Socket (Provider) | `adapter::types::unidirectional::AB` | Second selectable input (selected when selector `G` is in state `TRUE`). |

| **G** | Socket (Provider) | `adapter::types::unidirectional::AX` | Selector adapter (control signal for selection). |


*Note on adapter types:*

* `AB` represents a unidirectional adapter that carries a byte data signal (`D1`/`D`) and an event (`E1`).

* `AX` represents a unidirectional adapter that carries a Boolean data signal (`D1`/`D`) and an event (`E1`).


## Functionality

Inside the function block is a network of standard function blocks (IEC 61131-3 and IEC 61499) that implements the logic:

1. **Event and Data Acquisition:**

* When an event (`IN0`, `IN1`, `G`) arrives at one of the input adapters (`IN0`, `IN1`, `G`), the corresponding value (`D1`) is temporarily stored via an edge-triggered memory element (D flip-flop `E_D_FF` or `E_D_FF_ANY`).

2. **Data Conversion / Buffering:**

* The function blocks `F_MOVE_IN0` and `F_MOVE_IN1` copy the byte values of the inputs to the selection element.

3. **Selection Logic (`F_SEL`):**

* The standard selection function block `F_SEL` (from the IEC 61131-3 Library) performs the actual selection:

* If the signal from the selector adapter `G` equals `FALSE`, the signal from `IN0` is passed through to the output.

* If the signal from selector adapter `G` equals `TRUE`, the signal from `IN1` is passed through to the output.

4. **Output:**

* The selected value is transferred via another conversion block (`F_MOVE_OUT` with data type `BYTE`) to an output flip-flop (`E_D_FF_ANY_OUT`).

* This flip-flop generates the corresponding output event (`OUT.E1`) at plug `OUT` and provides the selected data value (`OUT.D1`).


## Technical Features

* **Event-driven data routing:** Any change to the inputs `IN0` or `IN1`, as well as to the selector `G`, triggers an update and calculation of the output. No cyclic polling occurs.

* **Decoupling via memory elements:** The use of `E_D_FF` and `E_D_FF_ANY` ensures that the data is consistently transferred and that no uncontrolled signal changes (race conditions) occur at the output.


* **Decoupling via memory elements:** The use of `E_D_FF` and `E_D_FF_ANY` ensures that the data is transferred consistently and that no uncontrolled signal changes (race conditions) occur at the output.

* * **Typing:** The internal processing of the data is fixed to the data type `BYTE` (defined via the attribute `DataType="BYTE"` on the `F_MOVE` blocks).

## State Overview

| State Selector `G` | Event at Input | Behavior at Output `OUT` |

| :--- | :--- | :--- |

| `FALSE` | Event at `IN0` | Value from `IN0` is passed to `OUT`; Event `OUT.E1` is triggered. |

| `FALSE` | Event sent to `IN1` | The value of `IN1` is updated internally, but **not** passed to `OUT`. |

| `TRUE` | Event sent to `IN0` | The value of `IN0` is updated internally, but **not** passed to `OUT`. |

| `TRUE` | Event sent to `IN1` | The value of `IN1` is passed to `OUT`; Event `OUT.E1` is triggered. |

| Switch `FALSE` $\rightarrow$ `TRUE` | Event on `G` | The currently stored value of `IN1` is passed to `OUT`; `OUT.E1` is triggered. |

| Switch `TRUE` $\rightarrow$ `FALSE` | Event on `G` | The currently stored value of `IN0` is passed to `OUT`; `OUT.E1` is triggered. |

## Application Scenarios

* **Signal Switching at the Field Level:** Switching between the signal from an active sensor (`IN1`) and a predefined substitute/error value (`IN0`) in case of a fault.

* **Manual/Automatic Switching:** Forwarding of control bytes, whereby values from the automatic control are used in automatic mode (`G = TRUE`), while manually specified values are sent to the actuators in manual mode (`G = FALSE`).

* **Recipe or Mode Selection:** Dynamic path selection for configuration or status data in complex process controls.


* ## Comparison with Similar Function Blocks

Compared to the standard function block `F_SEL`, `AB_AX_SEL_AB` operates directly at the adapter level.

* While `F_SEL` requires manual wiring of discrete data lines and separate trigger events, `AB_AX_SEL_AB` encapsulates this logic.

* This saves engineering time, reduces the number of visible connections in the 4diac IDE Application Editor, and minimizes potential errors when linking data and event streams.

## Conclusion

The `AB_AX_SEL_AB`is a robust and reusable auxiliary building block for signal routing based on byte adapters. Through the consistent encapsulation of the selection and synchronization logic, it significantly contributes to the clarity and modularization of control programs in the 4diac IDE.