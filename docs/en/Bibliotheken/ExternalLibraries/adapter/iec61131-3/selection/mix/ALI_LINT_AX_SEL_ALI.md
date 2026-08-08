# ALI_LINT_AX_SEL_ALI

![ALI_LINT_AX_SEL_ALI](./ALI_LINT_AX_SEL_ALI.svg)

* * * * * * * * * *

## Introduction
The function block `ALI_LINT_AX_SEL_ALI` is used for binary selection between two input values of type `LINT` (Large Integer). A binary selector controls which of the two values is passed to the output. The block combines the classic selection logic of IEC 61131-3 with the event-driven architecture of IEC 61499, using application-specific adapters for signal transmission.

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acceptance of the data input value `IN1`.


### **Event Outputs**
* *No direct event outputs are available at the block level.* Event forwarding is handled encapsulated via the adapter interfaces (e.g., `OUT.E1`).

### **Data Inputs**
* **IN1** (LINT): Selectable input value 1 (Alternative 1).

### **Data Outputs**
* *No direct data outputs are available at the block level.* Data output is handled encapsulated via the output adapter.

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::ALI`): The selected output value.

* **IN0** (Socket, Type: `adapter::types::unidirectional::ALI`): Selectable input value 0 (Alternative 0).

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): Binary selector (gate) that determines which of the two inputs (`IN0` or `IN1`) is passed through to the output.

---

## Functionality
The component operates internally as an event-driven multiplexer:

1. **Signal Latching:** As soon as events arrive at the inputs (`IN0`, `IN1`, or `G`), the incoming data values are temporarily stored via internal D flip-flops (`E_D_FF` and `E_D_FF_ANY`). This ensures that the data remains consistent and is only updated when events are active. 2. **Data Copying:** The cached values are transferred to the central selection block via the `F_MOVE` function block.

3. **Selection Logic (F_SEL):** The internal standard function block `F_SEL` evaluates the state of the selector `G`:

- If the selector `G` is **FALSE** (0), the value of `IN0` is selected.

- If the selector `G` is **TRUE** (1), the value of `IN1` is selected.


4. **Output:** The selected value is passed to the data field of the `OUT` adapter, and the corresponding event (`OUT.E1`) is triggered simultaneously.

---

## Technical Features
* **Use of Adapters:** By using sockets and plugs, the number of necessary connections in the higher-level system diagram is significantly reduced.

* **Data Type Specific:** The function block is specifically optimized for the `LINT` data type (64-bit integer).

* **Edge and Event Synchronization:** The internal logic ensures that every change at the inputs is processed deterministically, and only valid state changes trigger an event at the output `OUT`.

---

## State Overview

| Event Triggers | Selector state (`G`) | Resulting output value (`OUT.D1`) | Triggered output event |

| :--- | :--- | :--- | :--- |

Event on `IN0.E1` | `FALSE` (0) | Value of `IN0.D1` | `OUT.E1` |

Event on `IN0.E1` | `TRUE` (1) | *No change (old value remains)* | *No event* |


Event `EI1` | `TRUE` (1) | Value of `IN1` | `OUT.E1` |

| Event `EI1` | `FALSE` (0) | *No change (old value remains)* | *No event* |

| Event on `G.E1` (change to 0) | `FALSE` (0) | Value of `IN0.D1` | `OUT.E1` |

| Event on `G.E1` (change to 1) | `TRUE` (1) | Value of `IN1` | `OUT.E1` |

---

## Application Scenarios

* **Switching Signal Sources:** Dynamic selection between a standard sensor reading (via `IN0` as an adapter) and a manually specified substitution value or parameter (via `IN1` as a direct input).

* **Operating Mode Selection:** Switching setpoints (e.g., recipe numbers, counter limits) in the `LINT` format based on the current system status (automatic/manual operation via selector `G`).


* ---

## Comparison with Similar Components

Compared to a simple IEC 61131-3 `F_SEL` component, the `ALI_LINT_AX_SEL_ALI` offers:
* Full integration into the event-driven IEC 61499 environment.

* Reduced wiring effort through the encapsulation of events and data in the `ALI` and `AX` adapters.

* Automatic data buffering, which prevents transient signal changes without an event trigger from being incorrectly processed.

--

## Conclusion
The `ALI_LINT_AX_SEL_ALI` component is a specialized and high-performance solution for conditional signal forwarding of 64-bit integer values. Through its adapter-based interface, it promotes a clean, modular and easily readable application design in 4diac-IDE.