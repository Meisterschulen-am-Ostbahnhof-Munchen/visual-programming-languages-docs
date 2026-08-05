# ILOCK_FB_RS_AX
## Introduction
![ILOCK_FB_RS_AX](./ILOCK_FB_RS_AX.svg)
The function block **ILOCK_FB_RS_AX** implements a bistable, reset-dominant RS latch with an AX interface for set and reset signals, as well as a bidirectional AX2 interface for chaining multiple interlock blocks in a hierarchy. The block is designed for use in safety-related and interlock-based control environments.
## Interface Structure
The block does not have separate event or data ports, but rather encapsulates all signal types via **adapters**. The following list groups the events and data received via the individual adapters.

## Event Inputs
- **SET1.E1** (via socket adapter `SET1`): Set event, triggers the latch function.
- **RESET.E1** (via socket adapter `RESET`): Reset event, triggers the reset logic.
- **ILOCK_IN.EO1** (via socket adapter `ILOCK_IN`): Event from a parent or neighboring interlock instance (bidirectional side).
- **ILOCK_OUT.EI1** (via plug adapter `ILOCK_OUT`): Event from a child interlock instance.

### Event Outputs
- **Q1.E1** (via plug adapter `Q1`): Output event after each update of the latch state.
- **ILOCK_IN.EI1** (via socket adapter `ILOCK_IN`): Event sent to the connected partner adapter of `ILOCK_IN`.
- **ILOCK_OUT.EO1** (via plug adapter `ILOCK_OUT`): Event sent to the connected partner adapter of `ILOCK_OUT`.

### Data Inputs
- **SET1.D1** (via socket adapter `SET1`): Set signal (Boolean value, TRUE sets the latch).
- **RESET.D1** (via socket adapter `RESET`): Reset signal (Boolean value, TRUE resets the latch, overrides Set).
- **ILOCK_IN.DO1** (via socket adapter `ILOCK_IN`): Interlock status from above (Boolean value, TRUE blocks the latch).
- **ILOCK_OUT.DI1** (via plug adapter `ILOCK_OUT`): Interlock status from below (Boolean value, TRUE blocks the latch).

### Data Outputs
- **Q1.D1** (via plug adapter `Q1`): Latch output state (Boolean value).
- **ILOCK_IN.DI1** (via socket adapter `ILOCK_IN`): Forwards the reset signal upwards.
- **ILOCK_OUT.DO1** (via plug adapter `ILOCK_OUT`): Forwards the reset signal downwards.

### Adapter

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| `SET1` | Unidirectional AX | Socket | Set Input |

| `RESET` | Unidirectional AX | Socket | Reset Input |

| `ILOCK_IN` | Bidirectional AX2 | Socket | Interlock Input (from top) |

| `Q1` | Unidirectional AX | Plug | Latch Output |

| `ILOCK_OUT` | Bidirectional AX2 | Plug | Interlock Output (downward) |

## Functionality

The function block executes the algorithm `REQ` upon each incoming event (via `SET1.E1`, `RESET.E1`, `ILOCK_IN.EO1`, or `ILOCK_OUT.EI1`). The internal logic calculates the new output value `Q1.D1` using the reset-dominant formula:

`Q1.D1 := (SET1.D1 OR Q1.D1) AND NOT (RESET.D1 OR ILOCK_IN.DO1 OR ILOCK_OUT.DI1);`

- If the reset signal (`RESET.D1`) or one of the interlock inputs (`ILOCK_IN.DO1` or `ILOCK_OUT.DI1`) is TRUE, the latch is immediately reset (Q = FALSE), regardless of the set signal.
- If no reset or interlock block is present, the latch is set by a set signal (`SET1.D1` = TRUE) and remains self-latching.
- The interlock signals of the AX2 interface are propagated:
- `ILOCK_IN.DI1` (upwards) = `RESET.D1 OR ILOCK_OUT.DI1`
- `ILOCK_OUT.DO1` (downwards) = `RESET.D1 OR ILOCK_IN.DO1`

This creates a cascade in which a reset signal is passed on in both directions (upwards and downwards), blocking all subordinate and superior latch components.

## Technical Features
- **Adapter-based interfaces**: Instead of individual ports, the component uses standardized AX/AX2 adapters, enabling a modular and reusable connection with other components.
- **Cascadable Interlock Chain**: Multiple ILOCK_FB_RS_AX instances can be connected in series using the bidirectional `ILOCK_IN`/`ILOCK_OUT` adapters. A reset signal is automatically propagated in both directions, blocking the entire chain.
- **Reset Dominance**: The reset signal always takes precedence over the set signal. This meets typical requirements for safety interlocks that demand a defined priority for the reset signal.
- **Continuous Event Processing**: The function block reacts to every incoming event (set, reset, up/down interlock) and immediately updates all outputs. There are no state changes in the ECC (only one state, `REQ`); the logic is purely combinational with feedback via the stored latch value.

**Reset Dominance**: ## State Overview
The component has only one state, `REQ`, in its ECC, which is always active. The internal latch state is represented by the boolean value `Q1.D1`.The state overview therefore describes the behavior of the internal memory cell:

| Current Q | SET1.D1 | RESET.D1 | Interlock active? | Next Q | Description |

|-------------|----------|----------|------------------|------------|--------------|

| FALSE | FALSE | FALSE | NO | FALSE | Latch remains reset |

| FALSE | TRUE | FALSE | NO | TRUE | Latch is set |

| FALSE | TRUE | TRUE | YES/NO | FALSE | Reset dominates |

| TRUE | FALSE | FALSE | NO | TRUE | Latch remains set (self-latching) |

| TRUE | TRUE | FALSE | NO | TRUE | Latch remains set |
| TRUE | FALSE | TRUE | YES/NO | FALSE | Reset dominates |

| TRUE | TRUE | TRUE | YES/NO | FALSE | Reset dominates |

| arbitrary | arbitrary | arbitrary | YES (ILOCK) | FALSE | Interlock blockage sets or holds latch |

## Application Scenarios
- **Machine Safety**: Interlocking drives or tools where a reset signal (e.g., emergency stop) takes precedence and also blocks adjacent modules.
- **Process Control with Hierarchy**: In a cascade of control modules, a higher-level signal can reset the subordinate blocks to their default state.
- **Redundant Interlocking**: Multiple ILOCK_FB_RS_AX instances can be arranged in a ring or line to create a distributed interlocking system without central logic.
- **Latch with External Blocking**: External conditions (e.g., sensor values or enable/disable) can block the latch via the interlock adapters without affecting the set/reset function.

## Comparison with Similar Function Blocks
- **Standard RS Latch (e.g., SR_FF)**: A typical RS latch has equal set and reset inputs. The ILOCK_FB_RS_AX is reset-dominant and additionally offers an interlock function for cascading.
- **Reset-Dominant Latch without Interlock**: A simple RS latch with reset dominance only has set/reset ports. The function block described here extends this to include bidirectional interlocking via AX2 adapters.
- **Interlock Function Blocks with Dedicated Ports**: Some libraries offer interlock function blocks with individual Boolean inputs for "InterlockFromAbove" and "InterlockFromBelow." The ILOCK_FB_RS_AX encapsulates these channels in adapters, thus simplifying the connection between instances.

## Conclusion
The **ILOCK_FB_RS_AX** is a specialized function block for interlock-based control tasks. Its reset-dominant logic ensures a defined priority for the reset signal. The use of AX/AX2 adapters enables a clean, modular structure and easy cascading of multiple function blocks. This makes it particularly suitable for hierarchical or distributed safety and locking systems in automation technology.