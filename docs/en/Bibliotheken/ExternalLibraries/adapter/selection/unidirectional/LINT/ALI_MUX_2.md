# ALI_MUX_2
![ALI_MUX_2](./ALI_MUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_MUX_2** is a generic multiplexer for two ALI adapter signals. Depending on an index value `K`, it selects one of the two inputs (`IN1` or `IN2`) and forwards its value via the output adapter `OUT`. The block operates in an event-driven manner and acknowledges each selection operation with a confirmation event.
## Interface Structure
### **Event Inputs**

| Event | Comment |
|----------|-----------|
| `REQ` | Sets the index `K` and triggers the multiplexer logic. |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| `CNF` | Confirmation that the multiplexer provides the selected value via `OUT`. |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-------|-----------|
| `K` | UINT | Index for selecting the input (0 → `IN1`, 1 → `IN2`). |

### **Data Outputs**
No standalone data outputs; output is via the adapter `OUT`.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|---------------------------------------------------|----------------------------------------------|
| Plug | `OUT`| `adapter::types::unidirectional::ALI` | Output signal (corresponds to the selected input) |
| Socket | `IN1`| `adapter::types::unidirectional::ALI` | First input (index 0) |
| Socket | `IN2`| `adapter::types::unidirectional::ALI` | Second Input (Index 1) |

## Functionality

1. The function block waits for an event at input `REQ`.

2. Upon arrival of `REQ`, the current value of data input `K` is evaluated.

3. If `K = 0` is present, the current value of adapter `IN1` is transferred to output adapter `OUT`.

`` If `K = 1` is , the value of `IN2` is transferred to `OUT`.

For other values of `K` (e.g., >1), the behavior is undefined – the function block cannot make a valid selection.

4. After successful transfer, an event is sent at output `CNF`.

5. The function block remains idle until the next `REQ`.

## Technical Features
- **Generic Function Block**: The function block is generic and can be used for any ALI adapter type instance (generic class name `GEN_ALI_MUX`).
- **Type Hash**: The function block supports the type hash identification of the Eclipse 4diac Core environment for optimized runtime management.
- **Unidirectional Adapters**: All adapters used are of type `adapter::types::unidirectional::ALI`, meaning data flows in only one direction (from the socket to the plug).
- **No Internal State**: The function block does not have an explicit state machine; the logic is executed based on the current `K` value for each `REQ`.

## State Overview
The function block implicitly has two main states:

| State | Description |
|---------|---------------|
| IDLE | Waiting for a `REQ` event. Outputs: no action. |
| MUX | During processing: Evaluate `K`, transfer the corresponding input to `OUT`, and send `CNF`. Then return to IDLE. |

An effective state machine is not explicitly defined in the XML, as the logic operates purely combinatorially with event triggering.

## Application Scenarios
- **Sensor Switching**: Selection between two analog or digital sensors (e.g., temperature sensors 1 and 2) in an automation application.
- **Signal Routing**: Forwarding different control signals to a common destination, depending on the operating mode.
- **Redundancy Switching**: Switching to a backup input if the primary signal fails.

## Comparison with Similar Function Blocks
- **Standard MUX (e.g., IEC FB of type MUX)**: These typically work with simple data types (BOOL, INT, REAL) and output via a data output. The **ALI_MUX_2**, on the other hand, uses only adapter interfaces, enabling loose coupling and reusability in adapter-based architectures.
- **Generic Multiplexers**: Comparable function blocks for general-purpose ALI adapters often exist with a fixed number of channels. **ALI_MUX_2** is specified for two channels, but thanks to its generic nature, it can easily be extended to other channel numbers (e.g., through variants like ALI_MUX_4).
- **Difference from Dedicated Logic Function Blocks**: The FB does not implement any additional logic (e.g., hysteresis, filters) – it is a pure, event-driven switch.

## Conclusion

The **ALI_MUX_2** is a simple yet effective multiplexer for ALI adapter signals. Its generic design and purely adapter-based interface make it ideal for modular automation projects where switching between two sources is required. The clear state logic and confirmation via `CNF` allow for reliable integration into higher-level control processes.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
