# LWORD_AL_AX_SEL_AL

![LWORD_AL_AX_SEL_AL](./LWORD_AL_AX_SEL_AL.svg)

*No image available*

* * * * * * * * * *

## Introduction

The function block `LWORD_AL_AX_SEL_AL` is used for binary selection (multiplexing) of data of type `LWORD` (64-bit unsigned integer). It allows selection between a directly applied data value and a data value provided via an adapter interface, based on the state of a selector signal. The result is then made available via an output adapter. The block combines classic variable interfaces with modern, adapter-based communication for event-driven 4diac systems.

## Interface Structure

### **Event Inputs**

* **EI0**: Sets the value of the input variable `IN0`. When this event occurs, the value is read into `IN0` and processed.

### **Event Outputs**

* *No direct event outputs.* (Event output is encapsulated via the output adapter `OUT`).

### **Data Inputs**

* **IN0** (LWORD): A selectable input variable `LWORD` directly connected to the function block.

### **Data Outputs**

* *No direct data outputs.* (Data output is encapsulated via the output adapter `OUT`).

### **Adapters**

* **IN1** (Socket, Type: `adapter::types::unidirectional::AL`): A unidirectional input adapter that provides a selectable `LWORD` value (`D1`) and the corresponding update event (`E1`).
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector adapter. It provides the control signal (`D1` as a Boolean) and a trigger event (`E1`). It determines which of the inputs is connected to the output. ...IN1** (Socket, Type: qzmsdocs00009qz): A unidirectional input adapter that provides a selectable qzmsdocs00009qz value (`D1`) and the corresponding update event (`E1`). * **OUT** (Plug, Type: `adapter::types::unidirectional::AL`): The output adapter that outputs the selected `LWORD` value (`D1`) along with an acknowledgment event (`E1`).

---

## Functionality

The internal logic of the component is based on the classic IEC 61131-3 `SEL` selection principle, which has been extended with event-driven memory stages.

1. **Latching:**

As soon as an event arrives at one of the inputs (`EI0` for `IN0`, `IN1.E1` for `IN1`, or `G.E1` for the selection signal `G`), the corresponding data value is temporarily stored in an internal flip-flop (`E_D_FF` or `E_D_FF_ANY`). This ensures that even asynchronously arriving data changes are processed consistently.

2. **Value Transfer:**

The cached data for `IN0` and `IN1` are transferred to the selection block via copy function blocks (`F_MOVE_IN0` and `F_MOVE_IN1`).

3. **Selection Logic (`F_SEL`):**

The block `F_SEL` performs the actual selection:

* If the selector `G` = **`FALSE`**, the value of **`IN0`** is passed to the output.
* If the selector `G` = **`TRUE`**, the value of **`IN1`** is passed to the output.
4. **Output:**

The selected value is passed via another copy block (`F_MOVE_OUT`) to an output flip-flop and output via the adapter `OUT` with the event `E1`.

---

## Technical Features

* **Hybrid Interface:** This component bridges the gap between classic variable-based wiring (`IN0` via data pin) and adapter-based modularization (`IN1`, `G`, and `OUT` via adapters).
* **Event Decoupling via Flip-Flops:** By using `E_D_FF` (or `E_D_FF_ANY`) on all input paths, it is ensured that any trigger on any input path results in a recalculation and a corresponding output at the adapter `OUT`.
* * **Type Conformity:** All internal operations and data paths for the values `IN0`, `IN1`, and `OUT` are strictly designed for the data type `LWORD` (64-bit).

---

## State Overview

Since this is a composite function block (FB / FBNetwork), its behavior is determined by the interaction of the internal blocks:

| Event Source | State Selector `G` | Internal Action | Result at Adapter `OUT` |
| :--- | :--- | :--- | :--- |
| `EI0` | `FALSE` | `IN0` is updated, `F_SEL` passes through `IN0` | `OUT.D1` = `IN0`, event `OUT.E1` is triggered |
| `EI0` | `TRUE` | `IN0` is updated, `F_SEL` continues to pass through `IN1` | `OUT.D1` = `IN1`, event `OUT.E1` is triggered |
| `IN1.E1` | `FALSE` | `IN1` is updated, `F_SEL` continues to pass through `IN0` | `OUT.D1` = `IN0`, event `OUT.E1` is triggered |
| `IN1.E1` | `TRUE` | `IN1` is updated, `F_SEL` switches to `IN1` | `OUT.D1` = `IN1`, event `OUT.E1` is triggered |
| `G.E1` | Switch to `FALSE` | Selector changes, `F_SEL` switches to `IN0` | `OUT.D1` = `IN0`, event `OUT.E1` is triggered |
| `G.E1` | Switch to `TRUE` | Selector changes, `F_SEL` switches to `IN1` | `OUT.D1` = `IN1`, event `OUT.E1` is triggered |

---

## Application Scenarios

* **Switching between local and remote setpoint:** `IN0` can serve as a default or substitute value calculated locally in the FB network, while `IN1` feeds in a dynamic value supplied via a bus system or another module (via adapter).
* * **Mode Selection in Controllers:** Signal source switching during manual/automatic operation, where the selector `G` specifies the operating mode.
* **Redundant Data Paths:** Fast switching between two signal sources in case of a sensor or communication device failure.

---

## Comparison with Similar Function Blocks

* **Standard `F_SEL`:** The classic IEC 61131-3 `F_SEL` function block has only basic data inputs and no integrated event control or adapter support. It requires external logic to operate reliably in an event-driven IEC 61499 environment.
* * **`LWORD_AL_AX_SEL_AL` vs. other type variants:** Analogous implementations exist for other data types (e.g., for `DWORD`, `REAL`).etc.). This specific component is optimized exclusively for 64-bit data widths (`LWORD`).

---

## Conclusion

The `LWORD_AL_AX_SEL_AL` is a highly specialized, modular selection component for IEC 61499 applications. By encapsulating the memory and selection logic in combination with flexible adapter interfaces, it simplifies the design of clear and maintainable applications in industrial automation, especially when large data word widths need to be reliably switched.