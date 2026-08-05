# ALR_MUX_3
![ALR_MUX_3](./ALR_MUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_MUX_3** is a generic multiplexer for ALR adapter connections. Based on an index value `K`, it selects one of three ALR inputs (`IN1`, `IN2`, `IN3`) and forwards its data to the output `OUT`. The block is controlled by the event `REQ` and acknowledges processing with `CNF`.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| `REQ` | Event | Starts the selection of index `K` and updates the output `OUT`. |

### **Event Outputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| `CNF` | Event | Confirms successful index selection. |

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `K` | `UINT` | Index for selecting the active input (values 0, 1, or 2). |

### **Data Outputs**

*No direct data outputs available.*

Output is exclusively via the adapter `OUT`.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| **Plug** | `OUT` | `adapter::types::unidirectional::ALR` | Multiplexer output – contains the data of the selected input. |

| **Socket** | `IN1` | `adapter::types::unidirectional::ALR` | First input (selected at `K = 0`). |

| **Socket** | `IN2` | `adapter::types::unidirectional::ALR` | Second input (selected at `K = 1`). |

| **Socket** | `IN3` | `adapter::types::unidirectional::ALR` | Third input (selected at `K = 2`). |

## Functionality
The function block operates strictly event-driven:

1. A pulse at the event input `REQ` triggers processing.

2. The current value of the data input `K` is evaluated.

3. Depending on `K`, the corresponding adapter socket (`IN1`, `IN2`, or `IN3`) is switched to the output plug `OUT`.

4. After successful switching, the event `CNF` is output.

If an invalid index value (e.g., greater than 2) is applied, the behavior is unspecified—in practice, a safe error state should be avoided.

## Technical Features
- **Generic Type**: The function block (FB) is implemented as a generic class block (`GenericClassName = 'GEN_ALR_MUX'`), which allows its internal structure to be adapted to various ALR adapter variants.
- **ALR Adapter**: All inputs and outputs are implemented as unidirectional ALR adapters. This encapsulates complex data structures or signals in a standardized interface.
- **No Data Outputs**: Output is provided solely via the adapter plug, simplifying integration into existing component networks.

## State Overview
The FB does not contain any explicit state machines in its XML. The behavior is defined purely by event control:

- **Waiting** for `REQ`
- After `REQ`: Evaluate `K`, switch the corresponding input
- Output `CNF`

A detailed state machine is provided by the generic framework when compiling the FB instance.

## Application Scenarios
- **Source Switching**: In a controller, three different ALR data sources (e.g., sensors, calculations) can be selected via an index.
- **Modular Configuration**: The function block is suitable for switching between different operating modes during operation.
- **Test and Simulation Environments**: For importing various test data into an ALR-based system.

## Comparison with Similar Function Blocks
- **ALR_MUX_3**: Specifically designed for two inputs (channels 0 and 1) – here, all three inputs are used.
- **General Multiplexer Function Blocks** (e.g., `MUX` from IEC 61499 standard libraries): These usually work with scalar data types (BOOL, INT) and not with adapters. The **ALR_MUX_3** is optimized for the ALR adapter interface.
- Unlike an analog switch or data distributor, the focus is on event-driven transmission of complete ALR packets.

## Conclusion

The **ALR_MUX_3** is a compact, generic multiplexer for the ALR adapter interface. It enables flexible switching between three data sources based on an index value. Thanks to its adapter-based input/output and generic typing, it can be easily integrated and extended into IEC 61499 projects.
