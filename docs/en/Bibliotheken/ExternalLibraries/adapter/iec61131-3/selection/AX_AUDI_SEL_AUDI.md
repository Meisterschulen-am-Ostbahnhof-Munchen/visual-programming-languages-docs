# AX_AUDI_SEL_AUDI
![AX_AUDI_SEL_AUDI](./AX_AUDI_SEL_AUDI.svg)

* * * * * * * * * *
## Introduction
The function block `AX_AUDI_SEL_AUDI` implements a binary selection between two input values. It is controlled by two events, each of which can take one of the two data inputs. The actual selection is performed via a connected **Adapter G** (type `AX`), which provides the selection value. The selected result is passed to the environment via the **Adapter OUT** (type `AUDI`). The block encapsulates the logic of the IEC 61131 standard block `F_SEL` in an adapter-based form.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `EI0` | Event | Sets the value of `IN0` (passes it on to internal processing) |

| `EI1` | Event | Sets the value of `IN1` (passes it on to internal processing) |

### **Event Outputs**
Event output is exclusively via the `OUT` adapter. Once the selection is complete, the event `E1` is sent via the `OUT` adapter.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `IN0` | UDINT | First selectable value |

| `IN1` | UDINT | Second selectable value |

### **Data Outputs**
The output value is provided exclusively via the adapter `OUT` as data element `D1`.

### **Adapters**

| Name | Type | Role |

|------|-----|-------|

| `G` | `adapter::types::unidirectional::AX` | Returns the selection control value (event `E1` + data `D1`) |

| `OUT` | `adapter::types::unidirectional::AUDI` | Outputs the selected result as event `E1` and data `D1` |

## Functionality

1. **Providing Input Values** – The current values from `IN0` and `IN1`, respectively, are transferred to the function block via the event inputs `EI0` and `EI1`.

`` 2. **Trigger Selection** – The external adapter `G` sends a selection signal via its event `E1`.

3. **Internal Selection** – The event `E1` and the data input `G.D1` (as a selection criterion) are forwarded to the internal function block `F_SEL`. `F_SEL` selects according to IEC 61131 logic: If `G.D1` = FALSE (0), `IN0` is output; if `G.D1` = TRUE (not equal to 0), `IN1` is output. 4. **Output Result** – The confirming event (`CNF`) from `F_SEL` is passed to the adapter `OUT.E1`. Simultaneously, the output value `F_SEL.OUT` is transferred to `OUT.D1`.

## Technical Features
- The data width of the inputs and outputs is **UDINT** (unsigned double integer, 32 bits).
- Selection is **event-driven** – the selection is only triggered by an event at the adapter `G`.
- The function block does not automatically buffer the input values; it only accepts them upon the corresponding events (`EI0`, `EI1`).
- The adapters are based on the **unidirectional** protocol (one data and one event connection each).
- The actual selection logic is implemented by the standardized IEC block `F_SEL`, ensuring high compatibility and predictability.

## State Overview
The function block does not have its own state machine. Its behavior is entirely determined by the internal sub-block `F_SEL`, which implements the IEC standard logic.

- **Init** – After power-up, no values are applied; `OUT.D1` contains no defined value until a selection cycle has been completed.

`` - **Operating Phase** – When `EI0`/`EI1` occurs, the input values are set. When `G.E1` occurs, the selection is performed and the result is signaled via `OUT.E1`.

There are no other internal states.

## Application Scenarios
- **Adapter-Oriented Signal Switching** – In a modular automation system, `AX_AUDI_SEL_AUDI` can be used to switch between two sensor values or setpoints, controlled by a higher-level selector adapter.
- **Source Selection in Data Paths** – If two data sources with different update rates are available, this function block can select the current one.
- **Parameterizable Decision Logic** – The selection value (G.D1) can originate from an external calculation or a state machine, enabling flexible switching.

## Comparison with Similar Function Blocks
- **F_SEL (direct)** – By default, `F_SEL` would be used as a function block without an adapter. `AX_AUDI_SEL_AUDI` encapsulates it in an adapter-based interface, which simplifies connection to other adapter types (e.g., from the `AX` or `AUDI` families).
- **MUX Function Blocks** – Classic multiplexers (e.g., `MUX2`) offer a larger number of inputs, while this function block is specialized for exactly two inputs and a unidirectional adapter interface.
- **Adapter-based converters** – Other adapter blocks convert or scale values; this block does not perform an arithmetic operation, but only selects.

## Conclusion
AX_AUDI_SEL_AUDI` is a compact, event-driven selection block that embeds IEC selection logic in an adapter-based environment. Due to the clear separation of data inputs, control adapter, and output adapter, it is particularly suitable for modular, reusable automation solutions within the 4diac IDE environment. The limitation to two inputs and the use of standard types guarantee easy integration and predictable runtime behavior.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
