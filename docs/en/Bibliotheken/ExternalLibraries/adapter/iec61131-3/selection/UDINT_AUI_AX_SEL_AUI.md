# UDINT_AUI_AX_SEL_AUI
![UDINT_AUI_AX_SEL_AUI](./UDINT_AUI_AX_SEL_AUI.svg)
* * * * * * * * * *
## Introduction
The function block `UDINT_AUI_AX_SEL_AUI` implements a binary selection between two input signals. The selection is controlled via an external selector (adapter `G`), and the selected signal is provided via an output adapter (`OUT`). The input values can be updated separately via two events.
## Interface Structure
### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `EI0` | Sets the value of `IN0` |

| `EI1` | Sets the value of `IN1` |

### **Event Outputs**
No dedicated event outputs. Output is provided via the adapter `OUT` (see Adapter section).

### **Data Inputs**

| Name | Type | Comment |

|------|-------------------|-------------------------------|

| `IN0`| `ANY_ELEMENTARY` | First selectable value |

| `IN1`| `UINT` | Second selectable value |

### **Data Outputs**
No dedicated data outputs. The selected value is output via the adapter `OUT` (see section Adapters).

### **Adapters**

| Adapter | Type | Direction | Comment |

|---------|--------------------------------------|----------|------------------------------|

| `G` | `adapter::types::unidirectional::AX` | Socket (Input) | Receives the binary selector signal and the trigger event |

| `OUT` | `adapter::types::unidirectional::AUI`| Plug (Output) | Outputs the selected signal and an acknowledgment event |

**Adapter Details:**

- **Socket `G`**: Provides an event output (`E1`) and a data output (`D1`). `G.E1` triggers the selection, and `G.D1` serves as the selector (0 → select `IN0`, ≠0 → select `IN1`).
- **Plug `OUT`**: Has an event input (`E1`) and a data input (`D1`). After the selection is complete, the function block (FB) sends an event to `OUT.E1` and sets the selected value to `OUT.D1`.

## Functionality

1. **Value Update** – The events `EI0` and `EI1` set the data inputs `IN0` and `IN1`, respectively. A call to `EI0` updates `IN0`, and `EI1` updates `IN1`.

2. **Selection Trigger** – An event at socket `G.E1` starts the selection operation. This event originates from an external source that specifies the selection time.

3. **Internal Processing** – The internal block `F_SEL` (type `iec61131::selection::F_SEL`) evaluates the binary signal `G.D1`:

- If `G.D1 = 0` is present, `IN0` is selected.
- Otherwise, `IN1` is selected.

4. **Output** – The result is passed to `OUT.D1`. Simultaneously, an event is sent to `OUT.E1` to trigger the processing of downstream blocks.

## Technical Features
- **Adapter-Based Input/Output** – The interface to other function blocks is exclusively via adapters (`G`, `OUT`), enabling modular and service-oriented communication.
- **Mixed Data Types** – While `IN0` is generally defined as `ANY_ELEMENTARY`, `IN1` is fixed to `UINT`. The output follows the type of the selected signal, thus avoiding implicit type conversion.
- **Separation of Value Update and Selection** – Setting the input values and the actual selection process are decoupled by separate events. This allows for flexible timing control.

## State Overview
The function block does not have an explicit state machine. Its behavior is event-driven:

- After each `EI0` or `EI1` event, the updated values are available.
- A `G.E1` event immediately triggers the selection and output of the signal.
- There is no implicit initialization – the inputs must be set before the first selection.

## Application Scenarios
- **Sensor Switching** – Selection between two analog or digital sensors in a controller, e.g., switching between a short-range and a long-range sensor.
- **Parameter Management** – Provision of a fixed (UINT) value or a dynamically specified value (ANY_ELEMENTARY) for configuration purposes.
- **Resource-Saving Redundancy** – In safety-critical systems, a choice can be made between a primary and a backup signal.

## Comparison with Similar Components
- **Standard `F_SEL`** – This simple selector works with direct inputs/outputs without an adapter. `UDINT_AUI_AX_SEL_AUI` encapsulates the logic in an adapter-based interface and supports separate input updates.
- **`MUX` Function Blocks** – A multiplexer selects from more than two channels. The component described here is limited to two inputs, which is sufficient for binary decisions.
- **`SWITCH` Function Blocks** – These often have additional switching states. The component presented here is optimized for simple, fast binary selection.

## Conclusion

UDINT_AUI_AX_SEL_AUI` is a specialized function block for the binary selection of two signals. The combination of adapter-based connectivity, separate value updates, and external triggering makes it particularly suitable for modular automation projects where flexible and time-decoupled signal switching is required. Despite the mixed data types, the functionality remains clear and easy to use.
