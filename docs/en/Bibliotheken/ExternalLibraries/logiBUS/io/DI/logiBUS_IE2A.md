# logiBUS_IE2A
![logiBUS_IE2A](./logiBUS_IE2A.svg)

* * * * * * * * * *
## Introduction
The function block `logiBUS_IE2A` is a composite block (FB) for processing events at digital inputs of the logiBUS system. It extends the functionality of the underlying block `logiBUS_IE2` by adding a dedicated adapter output for event messages and allows the transfer of parameters such as long press times or multi-click counters. The block serves as a standardized interface between the logiBUS hardware and a higher-level control logic.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|-------|-------------------------------------------|

| INIT | EInit | Service Initialization |

| REQ | Event | Service Request |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|-----------------------------------|

| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment | Initial Value |

|------------|----------------------------------|-----------------------------------------------------------------------|------------------------|

| QI | BOOL | Event Input Qualifier | – |

| PARAMS | STRING | Service Parameter | – |

| Input | `logiBUS::io::DI::logiBUS_DI_S` | Digital input identification (e.g., Input_I1..I8) | `logiBUS_DI::Invalid` |

InputEvent | `logiBUS::io::DI::logiBUS_DI_Events_S` | Event identification (Down, Up, Single-Click, Double-Click, etc.) | `logiBUS_DI_Events::Invalid` |

arg | UINT | Event data: Long press time or number of multiple clicks (depending on the event) | 65535 |

### **Data Outputs**

| Name | Type | Comment |

|--------|--------|---------------------------------------|

| QO | BOOL | Event output qualifier |

| STATUS | STRING | Service status |

### **Adapters**

| Name | Type | Description |

|------|------------------------------------------------------|--------------------------------------------------|

| IN | `adapter::types::unidirectional::AE` | Unidirectional adapter output for events (E1) |

## Functionality

The `logiBUS_IE2A` is a purely structural block that encapsulates the logic of the internal block `logiBUS_IE2`.

- Upon the arrival of an **INIT** event, the data inputs `QI`, `PARAMS`, `Input`, `InputEvent`, and `arg` are forwarded to the internal function block, where initialization is performed. After successful processing, an acknowledgment containing the output data `QO` and `STATUS` is returned via the **INITO** output.
- A **REQ** event triggers a new request (e.g., for another measurement) without resetting the parameters.
- The actual event messages of the digital input are routed by the internal function block (FB) to the adapter output **IN.E1** via its outputs `IND` and `CNF`. This allows the higher-level application to react to incoming events without needing to know the internal details of the function block.

The data flows are hard-coded in the internal network and conform to the protocol of `logiBUS_IE2`.

## Technical Features
- **Composite Structure**: The function block does not contain its own state machine, but delegates all logic to the internal FB `logiBUS_IE2`.
- **Predefined Initial Values**: The inputs `Input` and `InputEvent` are pre-assigned to `Invalid`, and `arg` to `65535`. This prevents misconfigurations as long as the parameters are not explicitly set.
- **Adapter Output**: Event output is provided via a unidirectional adapter (`AE`), which enables loose coupling to the calling application.
- **Type Imports**: The function block uses specific type definitions from the packages `logiBUS::io::DI` and `logiBUS::io::DI::logiBUS_DI_Events`, ensuring consistent use within the logiBUS ecosystem.

## State Overview

The `logiBUS_IE2A` does not have its own state machine (no ECC). The internal function block `logiBUS_IE2` implements the necessary states for event detection and output. From the perspective of the composite function block, only the cyclic processes INIT → INITO and REQ → (event output via adapter) are relevant.

## Application Scenarios
- **Button and Switch Evaluation**: Detection of single and multiple clicks as well as long presses on the digital inputs of a logiBUS module.
- **Configurable Event Detection**: The `arg` input allows for dynamic definition of thresholds for long press times or the number of multiple clicks.
- **Integration into Higher-Level Controllers**: The adapter output enables seamless integration with automation systems that communicate via adapter interfaces.

## Comparison with Similar Function Blocks
- **`logiBUS_IE2`**: This function block is used within `logiBUS_IE2A`. It offers the same functionality, but without the dedicated adapter output and without the aggregation of parameters in a composite structure.
- **`logiBUS_IE2S`** (if present): Another function block in the same family, which may differ in additional status outputs or other event selection.
- The **`logiBUS_IE2A`** is characterized by its simple configuration and standardized adapter interface, which facilitates reuse in different projects.

## Conclusion

The `logiBUS_IE2A` is a pre-configured composite module for event-based processing of logiBUS digital inputs. It combines the proven logic of the `logiBUS_IE2` with an adapter output and configurable event data. Thanks to its clear interface and predefined initial values, it is particularly suitable for modular and standardized automation solutions where rapid integration and ease of use are paramount.
