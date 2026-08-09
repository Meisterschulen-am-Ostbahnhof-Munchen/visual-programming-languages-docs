# INT_AI_AX_SEL_AI

![INT_AI_AX_SEL_AI](./INT_AI_AX_SEL_AI.svg)

* * * * * * * * * *
## Introduction

The function block `INT_AI_AX_SEL_AI` serves as a binary selector (selection block) for analog integer values (`INT`). It allows selection between a locally defined integer input value and an external analog value provided via an adapter, based on the state of a selection signal (via an adapter). The result is then made available via an analog output adapter.

## Interface Structure

### **Event Inputs**

| Name | Type | Description | Associated Data |
| :--- | :--- | :--- | :--- |
| **EI0** | Event | Sets or updates the local input value `IN0`. | `IN0` |

### **Event Outputs**

*This function block does not have direct, classic event outputs. Event forwarding occurs exclusively via the adapter interfaces (especially the plug `OUT`).*

### **Data Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **IN0** | INT | Selectable local input value (integer). |

### **Data Outputs**

*This function block does not have direct, classic data outputs. Data forwarding occurs via the adapter interfaces.*

### **Adapters**

#### **Plugs (Output Adapters)**

| Name | Type | Description |
| :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::AI` | The selected analog output value (unidirectional analog input adapter). Transmits the selected value (`D1`) and the associated update event (`E1`). |

#### **Sockets (Input Adapters)**

| Name | Type | Description |
| :--- | :--- | :--- |
| **IN1** | `adapter::types::unidirectional::AI` | Selectable analog input value fed in via an adapter. |
| **G** | `adapter::types::unidirectional::AX` | Selector input (control signal) for selecting the active channel. |

--

## Functionality

The module is internally based on a logical network that adapts the behavior of a classic IEC 61131-3 `SEL` module for the 4diac environment:

1. **Input Synchronization:**

Both the local input `IN0` and the data arriving via the adapters `IN1` and `G` are buffered using edge-triggered D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively). This ensures that data values and events are processed synchronously.

2. **Data Conversion / Buffering:**

The values of `IN0` and `IN1` are transferred to the central selection block via corresponding transfer blocks (`F_MOVE_IN0` and `F_MOVE_IN1`).

3. **Selection Logic (`F_SEL`):**

The internal block `F_SEL` evaluates the control signal of the adapter `G`:

If the selection signal `G` is **FALSE** (0), the value of **IN0** (local input) is passed through to the output.

- If the selection signal `G` is **TRUE** (1), the value of **IN1** (adapter input) is passed through to the output.
4. **Output:**

The selected value is transferred via the converter `F_MOVE_OUT` and the output buffer `E_D_FF_ANY_OUT` to the output plug `OUT`, triggering the corresponding output event (`OUT.E1`).

--

## Technical Features

- **Adapter Connection:** By using unidirectional adapters (`AI` / `AX`), this module is ideally suited for modular applications where signals are to be transmitted via adapter lines instead of loose event/data connections.

-- - **Event-driven:** Any change to one of the inputs (`EI0`, `IN1.E1`, or `G.E1`) triggers a recalculation and results in an immediate update of the output adapter `OUT`.

- **Type conformance:** Although the adapters represent abstracted channels, the internal processing is strictly designed for the data type `INT` (integer).

---

## State overview

Since this is a composite function block network (composite FB / subapp behavior), there is no classic state machine (ECC). The behavior is purely data flow and event-driven:

| Triggering event | Condition on selector `G` | Resulting behavior at output `OUT` |
| :--- | :--- | :--- |
| Event at `EI0` / `IN1.E1` / `G.E1` | `G.D1` is `FALSE` | `OUT.D1` is set to the current value of `IN0`; `OUT.E1` is triggered. |
| Event at `EI0` / `IN1.E1` / `G.E1` | `G.D1` is `TRUE` | `OUT.D1` is set to the current value of `IN1.D1`; `OUT.E1` is triggered. |

--

## Application Scenarios

- **Manual/Automatic Switching:** Reading a fixed setpoint (via `IN0` in manual mode) or an automatic setpoint dynamically provided via an adapter (`IN1`).
- **Sensor Fallback Systems:** Switching to a predefined safety value (`IN0`) if an external sensor signals an error via selector `G`.
- **Signal Multiplexing:** Structured forwarding of integer measurement values in complex, adapter-based fieldbus systems.

---

## Comparison with Similar Components

- **Standard `F_SEL`:** The standard selection component `F_SEL` has no integrated event control and does not support adapters. It operates purely at the data level. `INT_AI_AX_SEL_AI` encapsulates this functionality in an event-driven manner and directly provides the appropriate adapter interfaces.
- **Standard Multiplexer (MUX):** A MUX typically allows selection from more than two channels using an integer selection signal, while this component is optimized for binary selection (2 channels).

---

## Conclusion

The `INT_AI_AX_SEL_AI` is a robust and integration-friendly auxiliary component for IEC 61499 applications. It bridges the gap between classic IEC 61131-3 selection logic and 4diac's modern, adapter-based, and event-driven architecture.