# STRING_AIS_AX_SEL_AIS

![STRING_AIS_AX_SEL_AIS](./STRING_AIS_AX_SEL_AIS.svg)

* * * * * * * * * *
## Introduction
The function block `STRING_AIS_AX_SEL_AIS` serves as a binary selector (multiplexer) for strings (`STRING`). Based on the control signal of a gate adapter, it allows selection between a local string input and a string input fed via an adapter, and forwards the result to an output adapter. The block combines the classic selection logic of IEC 61131-3 with the event-driven, adapter-based architecture of IEC 61499.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the acquisition and processing of the local string input `IN0`.


### **Event Outputs**

*(No direct event outputs at the block level are available. Event forwarding is encapsulated via the output adapter `OUT`.)*

### **Data Inputs**
* **IN0** (STRING): Local, selectable string value.

### **Data Outputs**
*(No direct data outputs at the block level are available. Data transmission is encapsulated via the output adapter `OUT`.)*

### **Adapters**
* **Plugs (Ports / Outputs):**

* **OUT** (Type: `adapter::types::unidirectional::AIS`): The selected output adapter. Outputs the selected string value (`D1`) and signals updates via the event (`E1`).

* **Sockets (Ports / Inputs):**

* **IN1** (Type: `adapter::types::unidirectional::AIS`): Adapter-based string input. Returns the string value (`D1`) and the trigger event (`E1`).

* **G** (Type: `adapter::types::unidirectional::AX`): The selector adapter (gate). Determines, via the data signal (`D1` / Boolean) and the control event (`E1`), which input is switched to the output.


**IN1** (Type: `adapter::types::unidirectional::AX`): The selector adapter (gate). Determines, via the data signal (`D1` / Boolean) and the control event (`E1`), which input is switched to the output. ## Functionality
The module is internally based on a structured network of standard function blocks. Signal and data processing proceeds as follows:

1. When events arrive at `EI0`, `IN1.E1`, or `G.E1`, the corresponding data values (`IN0`, `IN1.D1`, and `G.D1`, respectively) are buffered and synchronized via internal flip-flops (`E_D_FF` / `E_D_FF_ANY`).

2. The internal selector `F_SEL` evaluates the control signal:

* If the selector signal `G.D1` is **FALSE** (0), the value of **IN0** (local) is selected.

* If the selector signal `G.D1` is **TRUE** (1), the value of **IN1.D1** (adapter) is selected.

3. The selected string is transferred to the output adapter `OUT.D1` via an internal move operation, and the output event `OUT.E1` is triggered simultaneously.

## Technical Features
* **Event Synchronization**: The use of edge- and event-triggered flip-flops in the internal network ensures that data changes at the asynchronous inputs are always processed consistently and without data loss ("race conditions"). * **Reduced Wiring**: By consistently using adapters (`AIS` and `AX`), the number of visible connection lines in the higher-level system diagram is minimized, significantly improving the readability of complex applications.

## State Overview
Since this is a composite function block (FBNetwork), its behavior is determined by the internal data and event flow. The following table shows the behavior for various input combinations:

| Triggering Event | State Selector (`G.D1`) | Value Forwarded to `OUT.D1` | Output Event |

| :--- | :--- | :--- | :--- |

| `EI0` | `FALSE` | Current value of `IN0` | `OUT.E1` |

| `EI0` | `TRUE` | Last known value of `IN1.D1` | `OUT.E1` |

| `IN1.E1` | `FALSE` | Last known value of `IN0` | `OUT.E1` |

| `IN1.E1` | `TRUE` | Current value of `IN1.D1` | `OUT.E1` |

| `G.E1` | `FALSE` | Current value of `IN0` | `OUT.E1` |

| `G.E1` | `TRUE` | Current value of `IN1.D1` | `OUT.E1` |


## Application Scenarios

* **Recipe and Parameter Switching**: Selection between a locally defined standard parameter set (string via `IN0`) and a parameter set dynamically loaded via a network or HMI (via adapter `IN1`).

* **HMI Text Routing**: Dynamic switching of status and error messages on a display. For example, a static operating state (`IN0`) can be displayed during normal operation, while in the event of a malfunction, the detailed error message of a subsystem (`IN1`) is displayed.

* **Switch Control in Material Flow**: Routing of barcode or RFID information (as strings) to different target stations depending on sensor thresholds (gate signal `G`).


* ## Comparison with Similar Components

* **Standard `F_SEL` (IEC 61131-3)**: The standard selection component operates purely on a data flow basis. It lacks event-based control and does not support adapters. `STRING_AIS_AX_SEL_AIS` encapsulates this basic functionality and extends it with complete event and adapter control for IEC 61499.

* **Classic Multiplexers (without adapters)**: These require separate connections for data and events for each channel. This component simplifies integration by bundling signals in the adapters `AIS` and `AX`.

## Conclusion
The `STRING_AIS_AX_SEL_AIS` is a useful auxiliary component for structured software development in the 4diac IDE. It offers a clean, event-driven way to control string data streams and ensures a tidy and maintainable application design through the use of standardized adapters.