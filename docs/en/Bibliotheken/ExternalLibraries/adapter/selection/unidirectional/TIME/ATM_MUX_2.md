# ATM_MUX_2

![ATM_MUX_2](./ATM_MUX_2.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_MUX_2** is a generic multiplexer for two ATM data channels. It selects one of the two input adapters (`IN1` or `IN2`) based on a numerical index (`K`) and forwards its data via the output adapter (`OUT`). This block is used for dynamic switching between two unidirectional data sources and is suitable for systems that need to switch between different ATM-like data streams.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Sets the index `K` and triggers the switchover |

The `REQ` input initiates the selection process. It takes the value from `K` and switches the corresponding input to the output.

### **Event Outputs**

| Name | Type | Comment |
|------|-----|------------|
| `CNF` | Event | Confirms the successful switchover |

After the multiplexer has completed the switchover, `CNF` is output. The selected data path is then active.

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index of the input to be selected (0 for `IN1`, 1 for `IN2`) |

The value of `K` determines which of the two input adapters is enabled. The data type `UINT` also allows larger values in principle; however, only the values 0 and 1 are used in this function block.

### **Data Outputs**

This function block does not have any independent data outputs. Data is transmitted exclusively via the adapter output `OUT`.

### **Adapter**

| Type | Name | Direction | Comment |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::ATM` | `OUT` | Plug | Output that provides the data of the selected input |
| `adapter::types::unidirectional::ATM` | `IN1` | Socket | First input (index 0) |
| `adapter::types::unidirectional::ATM` | `IN2` | Socket | Second input (index 1) |

All adapters are of the same unidirectional type, `ATM`. The plug, `OUT`, connects the module to the subsequent logic, while the sockets represent the data sources.

## Functionality

The `ATM_MUX_2` operates in an event-driven manner. A signal at the `REQ` input triggers the following steps:

1. The current value of the `K` input is adopted.
2. If `K = 0` is present, the data path from `IN1` to `OUT` is switched.
3. If `K = 1` is active, the data path from `IN2` to `OUT` is switched.
4. After a successful switchover, the event `CNF` is sent.

The actual data forwarding occurs continuously (as soon as the path is active) – the function block does not buffer data, but forwards it directly from the selected input to the output.

## Technical Features

- **Generic Function Block**: The `ATM_MUX_2` is declared as a generic function block (`GenericClassName = 'GEN_ATM_MUX'`). It can therefore be instantiated in various forms (e.g., with more than two inputs) by adjusting the generic parameters.
- **Unidirectional Adapters**: Data flows only in one direction (from input to output). Feedback or bidirectional communication is not supported.
- **No Internal State**: The device does not have a state machine with multiple states; after switching, the path remains active until a new `REQ` pulse sets a different index.
- **Indirect Data Transfer**: Data is not exchanged as simple variables, but via adapters. This allows for modular connection of similar data interfaces.

## State Overview

Since the `ATM_MUX_2` does not have an explicit ECC (Execution Control Chart), its behavior can be described as a simple state loop:

| State | Description |
|---------|--------------|
| **Ready (Idle)** | Waiting for a `REQ` event. The last configured path remains active. |
**Switching** | After receiving `REQ`, the value of `K` is read and the corresponding path is activated. |
**Confirmation** | After the switchover is complete, `CNF` is output and the function block returns to the ready state. |

The function block may be in a brief, undefined state during the switchover – typically, data is not passed on during this time.

## Application Scenarios

- **Data Source Selection**: Switching between two sensors or data streams (e.g., A/B testing of ATM interfaces).
- **Redundancy Switching**: Replacement of a defective data channel with a second channel, controlled by a fault indicator.
- **Configurable Data Paths**: In control systems, the index `K` can be dynamically set by a higher-level logic to connect different data sources depending on the operating mode.

## Comparison with Similar Function Blocks

- **ATM_MUX_N (Generic Variant)**: The present `ATM_MUX_2` is a special instance with two inputs. A generic `ATM_MUX` could define the number of inputs via a parameter `N`.
- **Simple If-else Logic**: In an IEC 61499 environment, a multiplexer could also be implemented using a combination of a Decision function block and several Select function blocks. The `ATM_MUX_2` encapsulates this logic in a single, reusable component, thus reducing network complexity.

## Conclusion

The `ATM_MUX_2` is a lean, generic multiplexer for two unidirectional ATM data streams. It features easy operation (index selection via event) and modular adapter interfaces. Due to its generic nature, it can be easily adapted to different numbers of inputs. The component is particularly suitable for applications requiring fast, event-driven channel switching without the need for additional logic on the network.
