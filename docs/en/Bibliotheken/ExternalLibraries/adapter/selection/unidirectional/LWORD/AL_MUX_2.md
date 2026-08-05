# AL_MUX_2
![AL_MUX_2](./AL_MUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **AL_MUX_2** is a generic multiplexer for unidirectional AL (Action-Link) adapter interfaces. It selects one of two incoming adapters (`IN1` or `IN2`) based on an integer index `K` and forwards its data via the output adapter `OUT`. The switchover occurs synchronously with the event `REQ`. The block is implemented as a generic type (`GEN_AL_MUX`) and can therefore be used for various AL adapter implementations.

## Interface Structure

### Event Inputs

| Event | Comment |
|----------|-----------|
| `REQ` | Starts the switch or forwarding according to the current index `K`. |

### Event Outputs

| Event | Comment |
|----------|-----------|
| `CNF` | Confirms successful processing of the `REQ` event. |

### Data Inputs

| Data | Type | Comment |
|-------|------|-----------|
| `K` | UINT | Index for selecting the input (0 = `IN1`, 1 = `IN2`). |

### Data Outputs

No dedicated data outputs; output data is provided via the `OUT` adapter.

### Adapters

| Adapter | Direction | Type | Comment |
|---------|----------|-----|-----------|
| `OUT` | Plug | `adapter::types::unidirectional::AL` | Output adapter (provides the data of the selected input). |
| `IN1` | Socket | `adapter::types::unidirectional::AL` | First input adapter – active for `K = 0`. |
| `IN2` | Socket | `adapter::types::unidirectional::AL` | Second input adapter – active for `K = 1`. |

## Functionality

1. The device expects two unidirectional AL adapters at sockets `IN1` and `IN2`, which can continuously transmit data.

# Functionality 2. The event `REQ` evaluates the current value of index `K`:
- If `K = 0`, the connection is switched from `IN1` to `OUT`.
- If `K = 1`, the connection is switched from `IN2` to `OUT`.
- For other values of `K`, the behavior is undefined (typically, the last valid state is retained, or no connection is established).

3. After a successful switchover, the event `CNF` is sent.

The function block operates **synchronously**: A new `REQ` event immediately triggers a re-evaluation of `K` and the corresponding switchover.

## Technical Features
- **Generic Function Block**: The type `AL_MUX_2` is marked as generic (`eclipse4diac::core::GenericClassName = 'GEN_AL_MUX'`). This allows it to be used in various forms for different AL adapter types – the specific adapter type is only determined during instantiation.
- **Unidirectional AL Adapters**: The adapters used are of type `adapter::types::unidirectional::AL`. These transmit data only in one direction (from the socket to the plug). Bidirectional communication or acknowledgment mechanisms are not supported.
- **No State Machine**: The function block does not have an explicit ECC (Execution Control Chart) – its functionality is limited to a simple, immediate switching of the data flow upon arrival of `REQ`.

## State Overview

Since the function block has no internal states of its own, its behavior can be described as **combinatory** with a trigger:

- **Idle**: Waiting for `REQ`.
- **Switching**: Upon arrival of `REQ`, `K` is read and the corresponding connection is activated. Afterward, `CNF` is sent, and the function block returns to the idle state.

A detailed state machine is not provided by the manufacturer.

## Application Scenarios
- **Selection of an AL signal path**: In control systems where two different AL sources (e.g., sensor data, position values) are available and one of them needs to be passed on to the subsequent logic depending on the operating mode.
- **Switching between redundant paths**: If a primary AL signal fails, a switch to a backup signal can be made via an index.
- **Configurable signal sources**: External control (e.g., from a higher-level function block) allows dynamic selection between two AL inputs.

## Comparison with Similar Components
- **AL_MUX_2 vs. MUX_2 (Standard Data Types)**: While classic multiplexers (e.g., `MUX_2` for `INT`, `REAL`, `BOOL`) forward individual data values, `AL_MUX_2` operates at the adapter level. It passes through not just a single value, but the entire adapter interface (multiple signals).
- **AL_MUX_2 vs. AL_MUX_4**: A multiplexer with four inputs may exist as an extension, but then requires a larger index range (e.g., `K = 0..3`).
- **AL_MUX_2 vs. generic `GEN_AL_MUX`**: The present function block is a concrete instance of the generic pattern with two inputs. Other instances could be, for example, `AL_MUX_4` or `AL_MUX_8`.

## Conclusion

The **AL_MUX_2** is a simple yet flexible multiplexer for unidirectional AL adapters. Its generic nature allows its use in many applications where switching between two adapter signals is required. The clean separation of event and data paths, as well as the acknowledgment via `CNF`, make it a reliable function block in IEC 61499-based automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
