# AW_MUX_3

![AW_MUX_3](./AW_MUX_3.svg)

* * * * * * * * * *
The function block `AW_MUX_3` is a generic multiplexer (MUX) with three inputs. It selects one of the three adapter inputs based on an index parameter and forwards its value to the output. The block is used for dynamic switching between different data sources in industrial control applications.

| Name | Type | Comment |
|------|-----|------------|
| `REQ` | Event | Sets the index K and triggers the switching. |
| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of successful switching to the input specified by K. |
| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index of the input to be selected (0, 1, or 2). |

No direct data outputs are available. Output is provided via the adapter `OUT`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Name | Type | Direction | Comment |
| `IN1` | `AW` (unidirectional) | Socket | Input value 1 (selected when K = 0). |
| `IN2` | `AW` (unidirectional) | Socket | Input value 2 (selected when K = 1). |
| `IN3` | `AW` (unidirectional) | Socket | Input value 3 (selected when K = 2). |
| `OUT` | `AW` (unidirectional) | Plug | Output value – connects the internal logic to the selected input. |

## Functionality

The function block operates in an event-driven manner:

- An event at `REQ` reads the current value of the data input `K` (type UINT).
- Depending on the value of `K`, the corresponding socket input (`IN1`, `IN2`, `IN3`) is switched to the plug `OUT`.
- After a successful switchover, an event is sent to `CNF`.

Valid values for `K` are 0, 1, and 2. Values outside this range result in undefined behavior; the function block cannot select a valid input.

- **Generic Type**: The function block is declared as a generic FB (`GEN_AW_MUX`). The actual implementation can be parameterized for various data formats of the adapter `AW`.
- **Adapter-Based**: The inputs and outputs use the adapter type `adapter::types::unidirectional::AW`, which supports unidirectional data flows (e.g., analog measured values or simple structures).
- **Event-Driven Processing**: No cyclical updates – switching occurs only upon request via `REQ`.

The function block does not have an explicit state machine in its XML definition. Its behavior corresponds to a simple, event-driven selection mechanism:

- **IDLE**: Waits for a `REQ` event.
- **SELECT**: Evaluates `K` and connects the corresponding input to the output.
- **CONFIRM**: Sends `CNF` and returns to the IDLE state.
- **Switching Between Multiple Sensors**: Selects one of three analog sensors (e.g., temperature, pressure) for further processing.
- **Routing Control Signals**: Selects between different control algorithms or sources for a control signal.
- **Multiplexing in Visualizations**: If required, different display values can be switched to a display device via the index.
- **AW_MUX_2**: Two inputs, index range 0…1. `AW_MUX_3` offers an additional third input.
- **Standard MUX (e.g., E_MUX)**: Often uses simple data types (INT, REAL) instead of adapters. The adapter-based approach allows for more complex data structures and loose coupling between components.
- **AW_SELECT** (hypothetical): Can select one of several adapter inputs, but without index control (e.g., via Boolean selection). `AW_MUX_3` allows numerical, extensible selection.

The `AW_MUX_3` is a specialized, generic multiplexer for adapter-based communication in IEC 61499 systems. It enables the dynamic selection of one of three sources and is particularly suitable for flexible sensor/actuator routing in distributed automation solutions. Its simple event control and clear interface make it a robust component for standard multiplex applications.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion