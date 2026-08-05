# AS_MUX_2
![AS_MUX_2](./AS_MUX_2.svg)
* * * * * * * * * *
## Introduction
The AS_MUX_2 is a generic multiplexer function block that allows you to select between two input adapters (IN1 and IN2) and switch the selected adapter to the output adapter (OUT). The selection is made using an integer index variable K. This function block is typically used to dynamically switch between different signal sources or data paths without having to reconfigure the connections at runtime.
## Interface Structure
### **Event Inputs**

| Event | Data Type | With Variables | Description |

|----------|-----------|---------------|--------------|

| `REQ` | Event | `K` | Starts the input selection. The value of `K` determines which adapter is enabled. |

### **Event Outputs**

| Event | Data Type | With Variables | Description |

|----------|-----------|---------------|--------------|

| `CNF` | Event | – | Confirms that the switching is complete and the selected adapter is active. |

### **Data Inputs**

| Variable | Data Type | Description |

|----------|----------|--------------|

| `K` | UINT | Index for selection: `0` → IN1, `1` → IN2. Other values are invalid and will not result in a switch. |

### **Data Outputs**
No data outputs available.

### **Adapters**

| Type | Name | Direction | Description |

|-----------|------|-----------|--------------|

| Plug | OUT | Output | Output adapter connected to the selected input. |

| Socket (Input) | IN1 | Input | First input adapter selected for `K = 0`. |

| Socket (Input) | IN2 | Input | Second input adapter selected at `K = 1`. |

All adapters are of type **`adapter::types::unidirectional::AS`**, a unidirectional adapter that transports data in one direction.

## Functionality
The function block operates as a **1-out-of-2 multiplexer** at the adapter level.

When an event occurs at input `REQ`, the current value of `K` is evaluated:

- **K = 0**: The adapter `IN1` is internally connected to the output adapter `OUT`.
- **K = 1**: The adapter `IN2` is connected to `OUT`.
- **K ≠ 0 and ≠ 1**: No switching occurs; the previously selected adapter remains active.

After a successful switch, the event `CNF` is output. No further requests are accepted while a `REQ` event is being processed (the function block is blocked until `CNF` is output).

## Technical Features
- **Generic Function Block**: AS_MUX_2 is implemented as a generic function block (`eclipse4diac::core::GenericClassName = 'GEN_AS_MUX'`). This allows it to be instantiated with different adapter types, as long as all three adapters (IN1, IN2, OUT) are of the same type.
- **Unidirectional Adapters**: The adapters used are unidirectional, meaning data flows only in one direction – from input to output.
- **Index Range**: The input `K` is defined as `UINT`, but only the values 0 and 1 are processed meaningfully. Higher values do not result in any response.

## State Overview
The function block has a simple internal state machine:

| State | Description |

|---------|--------------|

| **IDLE** | Waiting for a `REQ` event. |

| **SELECT** | Evaluating `K` and switching the corresponding adapter (IN1 or IN2). |

| **DONE** | Sending `CNF` and returning to the IDLE state. |

While the function block is in state `SELECT`, no further `REQ` events are accepted.

## Application Scenarios
- **Sensor Switching**: Selection between two different sensors (e.g., temperature and pressure sensors), depending on requirements.
- **Signal Path Selection**: Switching between two different data sources in a controller.
- **Testing and Diagnostics**: Temporarily rerouting signals for testing purposes without changing the wiring.

## Comparison with Similar Function Blocks
- **MUX (Data Multiplexer)**: Selects between multiple values at the data level (e.g., `INT`, `REAL`). AS_MUX_2, on the other hand, operates at the adapter level and switches complete connections.
- **SEL (Selector)**: Simple case differentiation with data inputs/outputs. AS_MUX_2 uses adapters, enabling more flexible and structured connections.
- **Adapter-based multiplexers from other libraries**: Often extended to multiple channels (e.g., 4-way); AS_MUX_2 focuses on 2-way selection.

## Conclusion
AS_MUX_2 is a compact and generic component for switching between two adapters. Thanks to the adapter technology, complex signal paths can be modeled cleanly and switched dynamically at runtime. Its ease of use (one event input, one index) makes it particularly suitable for applications requiring fast and reliable source selection.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]