# AULI_ULINT_AX_SEL_AULI

![AULI_ULINT_AX_SEL_AULI](./AULI_ULINT_AX_SEL_AULI.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AULI_ULINT_AX_SEL_AULI` serves as a binary selector (selection switch) in an IEC 61499 specification. It enables event-driven selection between a value provided via an adapter (`IN0`) and a directly available standard numeric data type (`IN1` of type `ULINT`). The selection is made via a separate control adapter (`G`). The result is passed to an output adapter (`OUT`).



 ## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |

| :--- | :--- | :--- |

| `EI1` | Updates and sets the value of the direct data input `IN1`. | `IN1` |

### **Event Outputs**

*This function block does not have direct event outputs. Event forwarding occurs exclusively via the adapter interfaces (plugs/sockets).*

### **Data Inputs**

| Variable | Data Type | Description |

| :--- | :--- | :--- |

| `IN1` | `ULINT` | Selectable input value (input 1) that is passed through to the output when the selector is active. |

### **Data Outputs**

*This function block does not have direct data outputs. Data output is provided via the adapter plug `OUT`.*

### **Adapter**

| Name | Type | Direction | Description |

| :--- | :--- | :--- | :--- |

| `OUT` | `adapter::types::unidirectional::AULI` | Plug (Output) | The selected output value. |

| `IN0` | `adapter::types::unidirectional::AULI` | Socket (Input) | Selectable input value (input 0). |

| `G` | `adapter::types::unidirectional::AX` | Socket (Input) | Selector signal for controlling the selector switch. |

---

## Functionality

The module is internally based on a logic network that synchronizes the data streams of the adapters and the direct input:

1. **Input Synchronization:** The input signals from sockets `IN0` and `G`, as well as the direct data input `IN1` (triggered via `EI1`), are buffered by internal edge- and data-triggered flip-flops (`E_D_FF` and `E_D_FF_ANY`).

2. **Data Forwarding (`F_MOVE`):** The incoming values are prepared for further processing in the selector via internal `F_MOVE` function blocks.

3. **Selection Logic (`F_SEL`):** The core selection function block `F_SEL` evaluates the state of the selector `G`:

If the signal at `G` is **FALSE** (0), the value from `IN0` is forwarded to the output `OUT`.


 - If the signal at `G` is **TRUE** (1), the value of `IN1` is forwarded to the output `OUT`.

4. **Output:** As soon as a relevant input value or the selector signal changes, the selected value is output via the adapter plug `OUT`, and the corresponding event (`OUT.E1`) is triggered.

---

## Technical Features

- **Hybrid Interface:** The function block seamlessly combines the use of standardized, unidirectional adapters (`AULI`, `AX`) with classic IEC 61131 data types (`ULINT`).

- **Event-driven:** The internal use of `E_D_FF_ANY` function blocks ensures that data is only processed and forwarded when a new event actually signals the validity of the data. This conserves the system resources of the runtime environment.

---

## State Overview

The logical mapping of the output is as follows:

| Selector state (`G.D1`) | Active event at source | Output value (`OUT.D1`) |

| :--- | :--- | :--- |

| `FALSE` | Event at `IN0.E1` or `G.E1` | Corresponds to the value of `IN0.D1` |

| `TRUE` | Event on `EI1` or `G.E1` | Corresponds to the value of `IN1` |

--

## Application Scenarios

- **Signal Switching in the Field:** Switching between a value transmitted via a bus/adapter (`IN0`) and a local substitute or fixed value (`IN1`).

- **Operating Mode Selection:** Selection between an automatic process value (e.g., counter reading as `ULINT` on `IN1`) and a manually specified value via an HMI interface (via adapter `IN0`).


---

## Comparison with Similar Blocks

Compared to a standard `F_SEL` block according to IEC 61131-3, which only processes raw data without event-driven synchronization, this block offers direct integration into the event-oriented architecture of IEC 61499. It eliminates the need for users to manually create auxiliary networks for event coupling and adapter resolution.

--

## Conclusion

The `AULI_ULINT_AX_SEL_AULI` block is a specialized and robust solution for selection scenarios in modular control applications. By encapsulating the adapter and flip-flop logic, it ensures clear and easily maintainable application diagrams in the 4diac IDE.