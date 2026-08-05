# ALR_MUX_2
![ALR_MUX_2](./ALR_MUX_2.svg)

* * * * * * * * * *
## Introduction
The **ALR_MUX_2** is a generic multiplexer function block that allows selection between two unidirectional ALR adapter inputs and forwarding the selected data stream to a single ALR adapter output. Selection is event-driven via an integer index.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Initiates the selection of index `K` and forwards the corresponding ALR data. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirms successful processing of the `REQ` event. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| `K` | UINT | Selection index; valid values: `0` (selection of `IN1`) or `1` (selection of `IN2`). |

### **Data Outputs**

No data outputs are available. Output is exclusively via the `OUT` adapter.

### **Adapters**

| Role | Designation | Type | Description |

|--------|-------------|--------------------------------------------|--------------------------------------------|

| Socket | `IN1` | `adapter::types::unidirectional::ALR` | First ALR input (index `K=0`). |

| Socket | `IN2` | `adapter::types::unidirectional::ALR` | Second ALR input (index `K=1`). |

| Plug | `OUT` | `adapter::types::unidirectional::ALR` | Output that provides the data from the selected input. |

## Functionality

The module operates on the multiplexer principle:

1. An incoming `REQ` event triggers processing.

2. The value of `K` is evaluated:

- `K = 0`: The ALR data from `IN1` is forwarded to the `OUT` adapter.
- `K = 1`: The ALR data from `IN2` is forwarded to the `OUT` adapter.
- Other values for `K` are undefined and can lead to undefined behavior.

3. After a successful switchover, the `CNF` event is output.

Since this is a generic function block, the ALR data structures are not predefined – the exact data composition is determined by the adapter type used.

## Technical Features
- **Generic Type**: The function block is identified as `'GEN_ALR_MUX'` via the attribute `GenericClassName` and can be used in different instances with different ALR adapter bindings.
- **License**: This module is licensed under the **Eclipse Public License 2.0 (EPL-2.0)**.
- **Adapter Type**: All adapters are of type `adapter::types::unidirectional::ALR`, which implies unidirectional communication.
- **Index Limitation**: There are only two inputs (`IN1`, `IN2`); expansion to more channels is not supported.

## State Overview

This module does **not have an explicit state machine** (ECC). Its functionality is purely event-driven: Each `REQ` is followed by a `CNF`. There are no internal states that influence the process.

## Application Scenarios
- **Agricultural Control Systems**: Selection between two different ALR-based sensors (e.g., soil moisture, temperature) for controlling irrigation systems.
- **Actuator Control**: Switching between two ALR actuators (e.g., valves, motors) based on a control index.
- **Redundancy Circuit**: Switching between the primary and backup ALR paths in case of primary failure.

## Comparison with Similar Function Blocks

The standard function block repertoire includes multiplexers such as `MUX_2`, `MUX_4`, etc. However, these usually work with direct data types (BOOL, INT, etc.) and not with adapters. The **ALR_MUX_2** is specifically designed for ALR adapters and enables the structured transfer of complex data fields without additional serialization.

## Conclusion

The **ALR_MUX_2** is a specialized, generic multiplexer for unidirectional ALR adapters. It offers simple, event-driven switching between two inputs and is particularly suitable for agricultural applications where ALR data streams need to be flexibly managed. Due to its EPL 2.0 license, it can be freely used and adapted.
