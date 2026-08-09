# AL_MUX_4

![AL_MUX_4](./AL_MUX_4.svg)

* * * * * * * * * *
## Introduction

The function block `AL_MUX_4` is a generic multiplexer for adapter interfaces of type `adapter::types::unidirectional::AL`. It selects one of four adapter inputs (`IN1` to `IN4`) based on an index `K` and forwards it to a single adapter output (`OUT`). The selection is triggered by an event.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `REQ` | `Event` | Sets the index `K` and starts the selection. |

### **Event Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `CNF` | `Event` | Confirmation of successful switching. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `K` | `UINT` | Index of the selected input (0…3). |

### **Data Outputs**

None.

### **Adapters**

**Plugs (Output):**

| Name | Type | Comment |
|------|-----|-----------|
| `OUT` | `adapter::types::unidirectional::AL` | Output: outputs the selected input adapter. |

**Sockets (Inputs):**

| Name | Type | Comment |
|------|-----|-----------|
| `IN1` | `adapter::types::unidirectional::AL` | Input value 1 (for `K=0`). |
| `IN2` | `adapter::types::unidirectional::AL` | Input value 2 (for `K=1`). |
| `IN3` | `adapter::types::unidirectional::AL` | Input value 3 (for `K=2`). |
| `IN4` | `adapter::types::unidirectional::AL` | Input value 4 (for `K=3`). |

## Functionality

The function block operates in an event-driven manner. When an event occurs at input `REQ`, the current value of data input `K` is evaluated. The adapter input corresponding to this index (`IN1` for `K=0`, `IN2` for `K=1`, `IN3` for `K=2`, `IN4` for `K=3`) is then switched to adapter output `OUT`. After a successful switchover, the event `CNF` is output. The function block itself has no data outputs; instead, it transmits the signals and data of the selected adapter unchanged.

## Technical Features

- The function block is designated as a generic function block with the class name `GEN_AL_MUX` and can be reused in projects.
- It exclusively uses adapter interfaces of type `adapter::types::unidirectional::AL`, meaning it is suitable for forwarding unidirectional AL signals.
- Selection is purely event-driven and without internal memory – it is a combinational switching process.
- It contains no state machines (ECCs); therefore, its behavior is deterministic and stable immediately after event processing.

## State Overview

The `AL_MUX_4` has no explicit states. Its behavior is purely functional: `REQ` is followed by the switchover and `CNF`. Between these events, it is in a neutral state, in which the output interface reflects the last selected input.

## Application Scenarios

- **Source Switching**: Selection between different measured values or control signals available as AL adapters.
- **Redundancy Switching**: Connection of multiple redundant sensors or actuators, from which the active one is selected based on an index.
- **Configurable Data Paths**: In plant control systems where the signal source must be switched at runtime (e.g., via a higher-level index `K`).
- **Source Switching**: Selection between different measured values or control signals available as AL adapters.
- **Redundancy Switching**: Connection of multiple redundant sensors or actuators, from which the active one is selected based on an index.
- **Configurable Data Paths**: In plant control systems where the signal source must be switched at runtime (e.g., via a higher-level index `K`).
## Comparison with Similar Function Blocks

- **`MUX` (Standard Data Multiplexer)**: Selects one data input from several and outputs it. The `AL_MUX_4`, on the other hand, uses adapters, meaning it passes through a complete bidirectional (or in this case, unidirectional) interface.
- **`SELECT` or `CASE` (Function Blocks)**: More process-oriented, while the `AL_MUX_4` is specifically optimized for coupling adapters in an IEC 61499 environment.
- **Adapter Bypass**: Other function blocks for adapter switching exist; the `AL_MUX_4` offers a fixed 4-to-1 structure and is generically configurable.

## Conclusion

The `AL_MUX_4` is a compact and efficient function block for selecting one of four AL adapters. Its generic nature and simple event control make it ideal for modular control applications that require flexible routing of adapter signals. Its use reduces wiring effort and increases the reusability of control logic.
