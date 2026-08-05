# ASR_AX_SWITCH
![ASR_AX_SWITCH](./ASR_AX_SWITCH.svg)
* * * * * * * * * *
## Introduction
The function block **ASR_AX_SWITCH** serves as a demultiplexer for asynchronous set/reset events (ASR). It forwards an incoming SET or RESET event, based on the state of a binary control input **G**, to either one of two outputs (**EO0** or **EO1**). This block enables demand-based distribution of control signals in automation applications.
## Interface Structure

### **Event Inputs**

The function block does not have traditional event inputs via *EventInputs* – events are received via the **Socket Adapter `EI`** of type `ASR`. This adapter provides the two events `SET` and `RESET`.

### **Event Outputs**

The event outputs are provided via the **plug adapters `EO0`** and **`EO1`** (both type `ASR`). Each of these adapters has the outputs `SET` and `RESET`:

| Adapter | Event | Description |

|---------|----------|--------------|

| `EO0.SET` | SET | Triggered when a `EI.SET` event occurs and `G.D1 == 0` |

| `EO0.RESET` | RESET | Triggered when a `EI.RESET` event occurs and `G.D1 == 0` |

| `EO1.SET` | SET | Triggered when a `EI.SET` event occurs and `G.D1 == 1` |

| `EO1.RESET` | RESET | Triggered when a `EI.RESET` event occurs and `G.D1 == 1` |

### **Data Inputs**

The FB has no separate data inputs. The control variable **G** is obtained via the **Socket Adapter `G`** of type `AX` – the logical signal is present at the data output `D1` of the adapter.

### **Data Outputs**

There are no explicit data outputs. Control information is transmitted exclusively via the event outputs of the ASR adapters.

### **Adapters**

| Name | Direction | Type | Description |

|------|----------|-----|--------------|

| `EI` | Socket (Input) | `adapter::types::unidirectional::ASR` | Receives the SET/RESET events to be distributed |

| `G` | Socket (Input) | `adapter::types::unidirectional::AX` | Provides the binary toggle signal via `D1` (0 → Channel 0, 1 → Channel 1) |

| `EO0` | Plug (Output) | `adapter::types::unidirectional::ASR` | Output for Channel 0 (with `G.D1 = 0`) |

| `EO1` | Plug (Output) | `adapter::types::unidirectional::ASR` | Output for Channel 1 (with `G.D1 = 1`) |

## Functionality

The function block operates in an event-driven manner. After startup, it is in the **START** state and waits for incoming events via the `EI` adapter:

- **`EI.SET`** and **`EI.RESET`** are only processed if a valid binary value is simultaneously present at `G.D1` via the `G` adapter.
- The condition for the transition is:
- `EI.SET[NOT G.D1]` → **G0_SET** → Output `EO0.SET`
- `EI.SET[G.D1]` → **G1_SET** → Output `EO1.SET`
- `EI.RESET[NOT G.D1]` → **G0_RESET** → Output `EO0.RESET`
- `EI.RESET[G.D1]` → **G1_RESET** → Output `EO1.RESET`
- After the initial event is triggered, the function block immediately returns to the **START** state (unconditional transition with `1`).
- Additionally, there is a transition from **START** to **START** at **`G.E1`** – this allows for asynchronous updating of the control signal without immediate event propagation (serves, for example, for synchronization or initialization).

Processing is deterministic without intermediate event storage.

## Technical Features
- **Adapter-based communication**: The function block uses only adapters (sockets/plugs) for event and data exchange – this enables flexible integration within the 4diac IDE.
- **No state storage**: The selection of the target channel is purely combinatorial at the time of the incoming event. No internal state is maintained.
- **Full synchronicity**: After each output event, the function block returns to its initial state – events cannot be stacked.
- **Embedded license**: The code is released under the Eclipse Public License 2.0.

## Status Overview

| Status | Description | Action |

|---------|--------------|--------|

| **START** | Waiting for incoming SET/RESET event | – |

| **G0_SET** | Receive `EI.SET` at `G.D1=0` | Output `EO0.SET` |

| **G1_SET** | Receive `EI.SET` at `G.D1=1` | Output `EO1.SET` |

| **G0_RESET** | Receive `EI.RESET` at `G.D1=0` | Output `EO0.RESET` |

| **G1_RESET** | Receive `EI.RESET` at `G.D1=1` | Output `EO1.RESET` |

State transitions follow the ECC scheme: A condition leads from START to the action state, and from there, without further conditions, immediately back to START.

## Application Scenarios
- **Channel Switching**: In a modular controller, a central set/reset command should be forwarded to different actuators (e.g., valves, motors) depending on the operating mode.
- **Safety Logic**: Depending on an enable signal (`G`), resets are only routed to the active channel.
- **Redundancy Control**: The signal `G` selects between the main and backup channels.
- **Sequential Processes**: Multiple processing stations are controlled sequentially by switching `G`.

## Comparison with Similar Function Blocks

| Property | ASR_AX_SWITCH | Simple event multiplexer (e.g., SELECT) |

|-------------|----------------|----------------------------------------------|

| Event Type | SET/RESET (ASR Adapter) | Any single event |

| Control | Binary via AX adapter (with `D1`) | Boolean data input |

| Output Type | Two ASR adapters | Depending on the type, single or multiple events |
| Stateful | No (no storage) | Mostly stateless |

| Adapter interface | Yes | Often directly via event/data ports |

The ASR_AX_SWITCH is specifically optimized for asynchronous set/reset signals and integrates seamlessly into the ASR adapter world of the 4diac library. Compared to generic multiplexers, there is no need to manually extract the adapter events.

## Conclusion

The **ASR_AX_SWITCH** is a compact, efficient demultiplexer for the directed routing of ASR control events. Thanks to its adapter-based interface and clear decision logic, it is ideally suited for modular automation projects where a single control signal needs to be selectively routed to different paths. The simple state machine guarantees fast, deterministic response times without side effects.

**ASR_AX_SWITCH** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]