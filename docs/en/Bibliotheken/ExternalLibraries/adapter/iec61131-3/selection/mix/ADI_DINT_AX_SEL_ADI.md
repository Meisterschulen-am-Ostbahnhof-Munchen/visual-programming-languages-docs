# ADI_DINT_AX_SEL_ADI

![ADI_DINT_AX_SEL_ADI](./ADI_DINT_AX_SEL_ADI.svg)

*No image available*

* * * * * * * * * *
## Introduction
The function block `ADI_DINT_AX_SEL_ADI` is used for binary selection between two data streams of type `DINT` (Double Integer). The block combines the classic selection logic according to IEC 61131-3 (`F_SEL`) with the event-driven architecture of IEC 61499. Through the use of adapters, it enables clean, modular, and flexible signal wiring in complex control systems.

## Interface Structure

### **Event Inputs**
* **EI1**: Triggers the update and transfer of the data input value `IN1`.

### **Event Outputs**

* *No direct event outputs on the main interface.* Event output is encapsulated via the output adapter `OUT`.

### **Data Inputs**
* **IN1** (DINT): Selectable data input (passed through to the output when the selector is activated).

### **Data Outputs**
* *No direct data outputs on the main interface.* Data is transmitted encapsulated via the output adapter `OUT`.

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::ADI`): The selected output channel. Outputs the selected `DINT` value and the corresponding validity event.

### * **IN0** (Socket, Type: `adapter::types::unidirectional::ADI`): Selectable input channel 0. Provides the first `DINT` alternative value via an adapter connection.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector channel. Receives the Boolean control signal that determines which input is selected.

---

## Functionality
This component operates as a binary multiplexer (switch) for `DINT` signals. Selection is controlled by the signal at adapter `G`:

* If selector `G` is set to **FALSE**, the value from adapter **IN0** is switched to output adapter **OUT**.


* If selector `G` is set to **FALSE**, the value from adapter **IN0** is switched to output adapter **OUT**.

* * If the selector `G` is set to **TRUE**, the value from data input **IN1** is switched to output adapter **OUT**.

### Internal Signal Flow:

1. **Central Storage:** Data values received via the interfaces (`IN0`, `IN1`, `G`) are temporarily stored in internal flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) upon arrival of the respective trigger signal.

2. **Selection:** The internal function block `F_SEL` evaluates the selector's state and switches the corresponding data path.


### Internal Signal Flow:** 3. **Output:** The result is transferred to the output adapter `OUT` via an internal shift block (`F_MOVE`) and simultaneously signaled with an event (`OUT.E1`).

---

## Technical Features
* **Adapter Coupling:** By using unidirectional adapters (`ADI` for data, `AX` for control events), the number of necessary connection lines in the higher-level function block diagram is drastically reduced.

* **Event Consistency:** The internal data flip-flops ensure that data changes are only processed and forwarded when the corresponding event occurs. This prevents transient glitches.

* **Hybrid Interface:** This module allows the combination of an adapter-based source (`IN0`) and a classic pin-based signal source (`IN1`).

---

## State Overview
The module's behavior is determined by incoming events (event-driven execution):

| Triggering Event | Condition / State Selector (G) | Action / Effect |

| :--- | :--- | :--- |

| **G.E1** (Selector Change) | `G.D1` changes to `FALSE` | The value of `IN0` is passed to `OUT`; event `OUT.E1` is triggered. |

| **G.E1** (Selector Change) | `G.D1` changes to `TRUE` | The value of `IN1` is passed to `OUT`; event `OUT.E1` is triggered. |

| **IN0.E1** (New Value at IN0) | `G` is `FALSE` | The new value of `IN0` is passed directly to `OUT` and signaled. |

| **IN0.E1** (New Value at IN0) | `G` is `TRUE` | The value is updated internally, but has no direct effect on `OUT`. |

| **EI1** (New value at IN1) | `G` is `TRUE` | The new value of `IN1` is passed directly to `OUT` and signaled. |

| **EI1** (New value at IN1) | `G` is `FALSE` | The value is updated internally, but has no direct effect on `OUT`. |


---

## Application Scenarios

* **Setpoint Switching (Manual/Automatic):** Switching between an automatic setpoint (e.g., supplied via adapter `IN0` from a profile generator) and a manually entered fixed value (`IN1`).

* **Sensor Redundancy:** Selection between two redundant measured values (scaled as `DINT`), based on an upstream diagnostic flag passed to the selector `G`.

* **Parameterization:** Dynamic loading of various configuration or recipe DINT values depending on machine states.


* ---

## Comparison with Similar Components

* **Standard `F_SEL`:** The classic IEC 61131-3 selection block operates purely on a data flow basis. It has no event-driven control and no adapter interfaces. `ADI_DINT_AX_SEL_ADI` encapsulates this logic and makes it suitable for distributed, event-driven execution in IEC 61499 environments.

* **Standard Multiplexer:** Unlike generic multiplexers with a variable number of inputs, this component is optimized precisely for two channels and the specific data types `DINT` (via `ADI` adapter) and `BOOL` (via `AX` adapter), which minimizes the potential for errors during configuration.


---

## Conclusion
The `ADI_DINT_AX_SEL_ADI` is an extremely useful auxiliary module for modular control applications in 4diac. It elegantly solves the task of event-driven signal switching at the system level and, thanks to its adapter structure, contributes significantly to clear and maintainable application networks.