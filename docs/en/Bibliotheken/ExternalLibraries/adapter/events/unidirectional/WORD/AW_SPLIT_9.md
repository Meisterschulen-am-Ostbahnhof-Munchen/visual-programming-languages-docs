# AW_SPLIT_9

![AW_SPLIT_9](./AW_SPLIT_9.svg)

* * * * * * * * * *

## Introduction

The function block `AW_SPLIT_9` serves as a generic distributor for one incoming adapter of type `AW` to nine identically configured output adapters. It enables the multiple use of a single adapter signal without duplicating the original data source. The designation "SPLIT 1 AW into 9 AW" describes the core function: One AW input is distributed to nine AW outputs.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Type | Name | Direction | Description |

|------|------|----------|-------------|

| `adapter::types::unidirectional::AW` | `IN` | Socket (Input) | Incoming AW adapter that is distributed to all outputs. |

| `adapter::types::unidirectional::AW` | `OUT1` | Plug (Output) | First outgoing AW adapter. |

| `adapter::types::unidirectional::AW` | `OUT2` | Plug (Output) | Second outgoing AW adapter. |

| `adapter::types::unidirectional::AW` | `OUT3` | Plug (Output) | Third outgoing AW adapter. |

`adapter::types::unidirectional::AW` | `OUT4` | Plug (Output) | Fourth outgoing AW adapter. |

`adapter::types::unidirectional::AW` | `OUT5` | Plug (Output) | Fifth outgoing AW adapter. |

`adapter::types::unidirectional::AW` | `OUT6` | Plug (Output) | Sixth outgoing AW adapter. |

`adapter::types::unidirectional::AW` | `OUT7` | Plug (Output) | Seventh outgoing AW adapter. |

| `adapter::types::unidirectional::AW` | `OUT8` | Plug (Output) | Eighth outgoing AW adapter. |

| `adapter::types::unidirectional::AW` | `OUT9` | Plug (Output) | Ninth outgoing AW adapter. |

## Functionality

The component has no processing logic whatsoever (no ECC, no algorithms). It functions purely as a wiring aid: The AW signal present at socket `IN` is structurally forwarded to all nine plug adapters `OUT1` to `OUT9`. In the IEC 61499 model, this means that all connections to the outputs receive the same signal present at the input. No timing or data manipulation takes place.

## Technical Features

- **Generic Function Block**: The function block is declared as a generic class (`GEN_AW_SPLIT`). This allows reuse with different AW adapter types, provided the basic structure (unidirectional AW adapter) is maintained.

- **No Events or Data**: All communication occurs exclusively via adapter interfaces. This simplifies handling in purely adapter-based architectures.

- **No State Logic**: The function block has no inherent behavior; it is a purely "passive" element for signal copying.

## State Overview

The function block does not have its own state machine, as no events or algorithms are defined. Its behavior is purely structural: As long as the input adapter is connected, all outputs are always active – no state change occurs.

## Application Scenarios

- **Signal Fan**: A central output signal (e.g., a control command or sensor value) must be distributed to several downstream components.

- **Redundant Connections**: In safety-critical systems, the same output signal can be sent to multiple parallel evaluation units.

- **Wiring Simplification**: The function block replaces manual star wiring in the application and improves the clarity of the function diagram.

## Comparison with Similar Function Blocks

- **AW_SPLIT_N**: A generic split function block with a variable number of outputs (e.g., `AW_SPLIT_4`, `AW_SPLIT_16`). `AW_SPLIT_9` is a special implementation for exactly nine outputs.

- **Data Split Blocks**: Blocks that split data inputs (e.g., `INT`, `REAL`). `AW_SPLIT_9` operates exclusively at the adapter level and not at individual data points.

- **Multiplexers (MUX)**: A multiplexer selects one of several inputs, while this block distributes one input to many outputs (fan-out).

## Conclusion

The `AW_SPLIT_9` is a simple yet useful generic function block for splitting a unidirectional AW adapter signal into nine parallel outputs. Its structure is minimalist and purely passive, making it a reliable tool in adapter-oriented control architectures. It requires neither events nor data and can be integrated into existing applications without side effects.