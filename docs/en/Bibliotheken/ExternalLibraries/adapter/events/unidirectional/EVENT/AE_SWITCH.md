# AE_SWITCH

![AE_SWITCH](./AE_SWITCH.svg)

* * * * * * * * * *
## Introduction

The **AE_SWITCH** function block acts as an event demultiplexer. It forwards an incoming event to one of two unidirectional event adapter outputs, depending on the value of a Boolean input `G`.
## Interface Structure

### **Event Inputs**

- **EIG** (Event): Sets the value of `G`. When this event is triggered, the corresponding data input `G` is used – no forwarding to the outputs occurs.

#### **Event Outputs**

- No independent event outputs are available. Output is exclusively via the adapters `EO0` and `EO1`.

### **Data Inputs**

| Name | Type | Comment |
|------|-------|------------------------------------------------|
| `G` | BOOL | Switch: 0 → Output via `EO0`, 1 → Output via `EO1` |

### **Data Outputs**

- No data outputs.

### **Adapters**

| Direction | Name | Type (unidirectional) | Comment |
|-----------|-------|---------------------------------------------|------------------------------------------------|
| **Socket** (Input) | `EI` | `adapter::types::unidirectional::AE` | Event input that is switched. |
| **Plug** (Output) | `EO0` | `adapter::types::unidirectional::AE` | Event output, active at `G = 0` |
| **Plug** (Output) | `EO1` | `adapter::types::unidirectional::AE` | Event output, active at `G = 1` |

## Functionality

The function block is initially in the **START** state.

1. **Setting the Switch**: An event at `EIG` inherits the current value from `G`. The block then remains in the **START** state.
2. **Forwarding the Input Event**: If an event arrives via the adapter input `EI`, the value of `G` is evaluated:
- If `G = 0` → state change to **G0**: The adapter output `EO0` is triggered with its event `E1`.
- If `G = 1` → State change to **G1**: The adapter output `EO1` is triggered by its event `E1`.
3. After the respective output is triggered, the function block automatically returns to the **START** state.

## Technical Features

- Event forwarding occurs exclusively via **unidirectional adapters** of type `AE`. This ensures a clean separation of event sources and sinks.
- The function block implements **demultiplexing** (1-to-2) at the event level: An incoming event is routed to one of two outputs depending on a Boolean condition.
- The set input `EIG` allows the switching value to be changed independently of any pending event at input `EI`.

## State Overview

| State | Description | Action on Entry |
|---------|-------------------------------------------------------------|---------------------|
| START | Wait for an event at `EI` or `EIG` | – |
| G0 | Event at `EI` with `G = 0` – forward to `EO0` | `EO0.E1` |
| G1 | Event at `EI` with `G = 1` – forward to `EO1` | `EO1.E1` |
| Event at `EI` with `G = 1` – forward to `EO1` | `EO1.E1` |
... **Transitions:**

- START → G0 : `EI.E1[NOT G]`
- START → G1 : `EI.E1[G]`
- G0 → START : `1` (immediate)
- G1 → START : `1` (immediate)
- START → START : `EIG` (only sets G, no forwarding)

## Application Scenarios

- **Event Routing** in automation systems, where a central trigger (e.g., a sensor event) controls different actuators depending on the operating mode.
- **State-Dependent Processing**: An incoming event should only be processed in a specific operating mode; the other operating mode receives a separate event.
- **Test and Diagnostic Tasks**: Switching between normal operation and test mode by setting `G`.

## Comparison with Similar Function Blocks

- **E_SWITCH** (Standard 61499): Similar functionality, but via regular event outputs. `AE_SWITCH` uses adapters, which allows for better encapsulation and reusability in components with standardized interfaces.
- **E_MUX** (Multiplexer): Combines multiple events into one output – in the opposite direction. `AE_SWITCH` demultiplexes an input event to two outputs.

## Conclusion

The `AE_SWITCH` offers a lean, adapter-based solution for conditional event forwarding. Its use of unidirectional adapters makes it ideal for modular and type-safe IEC 61499 applications. Its simple state machine makes it efficient and easy to understand.
