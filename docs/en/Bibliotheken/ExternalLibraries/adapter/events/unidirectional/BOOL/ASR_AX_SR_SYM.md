# ASR_AX_SR_SYM
![ASR_AX_SR_SYM](./ASR_AX_SR_SYM.svg)
* * * * * * * * * *
## Introduction
The function block **ASR_AX_SR_SYM** implements an event-driven, bistable flip-flop (SR flip-flop) with symmetric start behavior. It is implemented as a Basic FB according to IEC 61499-1 (Annex A) and operates exclusively via adapter interfaces – without direct event or data inputs. The block is suitable for applications where the initial state is determined by the first arriving event and neither input has priority.
## Interface Structure

### Event Inputs

The FB has no direct event inputs. All events are received via the **socket adapter `S_R`** (type `adapter::types::unidirectional::ASR`). This adapter provides the following event inputs:

- `S_R.SET` – Set event
- `S_R.RESET` – Reset event

### Event Outputs
The FB has no direct event outputs. Outgoing events are sent via the **plug adapter `Q`** (type `adapter::types::unidirectional::AX`). This adapter provides the following event output:

- `Q.E1` – Output event, triggered by a state change

### Data Inputs
No direct data inputs.

### Data Outputs
The output value is provided via the plug adapter `Q`:

- `Q.D1` (BOOL) – current state of the flip-flop (`TRUE` = set, `FALSE` = reset)

### Adapter

| Name | Type | Direction | Description |

|-------------|----------------------------------------|----------|-------------------------------------|

| `S_R` | `adapter::types::unidirectional::ASR` | Socket | Set/Reset Events (Input) |

| `Q` | `adapter::types::unidirectional::AX` | Plug | State Output (Event + Data) |

## Functionality

After initialization, the module starts in the **START** state. In this state, it waits for the first arriving event at `S_R.SET` or `S_R.RESET`. Depending on which event arrives first, it switches to the **SET** or **RESET** state:

- **SET State**:

The data output `Q.D1` is set to `TRUE`, and the event `Q.E1` is triggered.

Upon a subsequent `S_R.RESET` event, the module transitions to the RESET state.

` ... - **RESET State**:

The data output `Q.D1` is set to `FALSE`, triggering the event `Q.E1`.

Upon a subsequent event, `S_R.SET`, the transition to the SET state occurs.

After the first transition, the function block remains in one of the two stable states until the complementary event occurs. There is no precedence between SET and RESET – the first event at startup determines the initial state.

## Technical Features
- **Symmetrical Startup Behavior**: Unlike typical SR flip-flops, neither input has priority. The initial state is determined by the first event.
- **Pure Adapter Interface**: Both events and data are exchanged via IEC 61499 adapters, not via direct input/output ports. This simplifies reuse in complex, adapter-based systems.
- **No explicit event I/O**: The function block (FB) does not have its own event inputs/outputs and instead uses the integrated event ports of the adapters.
- **Compact ST implementation**: The two algorithms `SET` and `RESET` simply set the data output and trigger the output event.

## State Overview

*(Note: A graphical state diagram can be extracted from the ECC XML, but is not embedded here as an image.)*

| State | Description | Action | Output |

|---------|-----------------------------------|-----------------------|-------------------------------------------------|

| START | Initial wait state | – | No output |

| SET | Stored state "set" | `Q.D1 := TRUE` | Triggering `Q.E1` |

| RESET | Saved state "reset" | `Q.D1 := FALSE` | Triggering `Q.E1` |

**Transitions:**

- START → SET: when `S_R.SET` arrives
- START → RESET: when `S_R.RESET` arrives
- SET → RESET: when `S_R.RESET` arrives (after the first set)
- RESET → SET: when `S_R.SET` arrives (after the first reset)

## Application Scenarios
- **Binary State Memory**: Storing an on/off state controlled by two separate events (e.g., "Start" and "Stop").
- **Controlling Actuators with Set and Reset Inputs**: Used in controllers where an output needs to be set and reset symmetrically without prioritization.
- **First-Event Initialization**: Systems where the start state is not predefined but determined by the first command (set or reset).

## Comparison with Similar Function Blocks
- **Standard SR Flip-Flop (e.g., `SR` classic)**: Often, one input is dominant (e.g., reset takes precedence). The `ASR_AX_SR_SYM` treats both inputs equally – at startup, the first event determines the state.
- **RS Flip-Flop with Prioritized Set**: Other implementations prioritize the set input.

This function block is characterized by its symmetrical handling of both events and its exclusive adapter interface, making it flexible for use in adapter-based libraries.

## Conclusion

The `ASR_AX_SR_SYM` function block offers a reliable, event-driven SR flip-flop with symmetric start behavior. Its adapter interfaces allow for seamless integration into IEC 61499 systems, making it particularly suitable for applications requiring equal set/reset control without precedence. Its simple state logic and small number of algorithms make it efficient and easy to understand.
