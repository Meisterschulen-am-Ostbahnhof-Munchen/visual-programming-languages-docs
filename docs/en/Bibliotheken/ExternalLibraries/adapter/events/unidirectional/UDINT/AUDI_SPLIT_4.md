# AUDI_SPLIT_4
![AUDI_SPLIT_4](./AUDI_SPLIT_4.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_SPLIT_4** is used to distribute an incoming unidirectional **AUDI** adapter signal to four identical outputs. It functions as a simple signal distributor (fan-out) for the generic adapter type **AUDI**. The block is implemented as a generic function block (Generic FB) and can be adapted to different adapter types via the class `GEN_AUDI_SPLIT`.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| **Socket** | `IN` | `adapter::types::unidirectional::AUDI` | Input adapter that provides the signal to be distributed. |

| **Plug** | `OUT1` | `adapter::types::unidirectional::AUDI` | First output, identical to the input signal. |

| **Plug** | `OUT2` | `adapter::types::unidirectional::AUDI` | Second output, identical to the input signal. |

| **Plug** | `OUT3` | `adapter::types::unidirectional::AUDI` | Third output, identical to the input signal. |

**Plug** | `OUT4` | `adapter::types::unidirectional::AUDI` | Fourth output, identical to the input signal. |

## Functionality

The module operates **eventlessly** and **continuously**:

As soon as socket `IN` is connected to an AUDI adapter, the data or signals transmitted via this adapter are forwarded unchanged to all four output adapters (`OUT1` to `OUT4`). No processing or conversion of the data takes place – the module functions solely as a passive distributor (splitter). Since no events or state changes are involved, the distribution occurs implicitly through the connection structure.

```
## Technical Features

- **Generic Function Block**: The function block is declared as a generic type with the class name `'GEN_AUDI_SPLIT'`. This allows the specific adapter type (e.g., a specialized AUDI subtype) to be adapted at design time or through code generation.
- **Unidirectional Adapters**: All adapters used (`AUDI`) are unidirectional, meaning data flows only from the socket to the plugs.
- **No Event Control**: The function block has no event inputs or outputs. Signal distribution is data flow-driven and requires no explicit triggering.
- **Scalability**: The function block is specifically designed for 4 outputs. Variants exist for other numbers (e.g., `AUDI_SPLIT_2`, `AUDI_SPLIT_3`).

## State Overview

This function block does **not have a state machine (ECC)**, as it does not process events or store an internal state. Its function is purely combinatorial: The outputs continuously reflect the input.

## Application Scenarios
- **Signal Distribution in Control Systems**: An audio signal provided by a sensor or higher-level system is to be passed on in parallel to multiple consumers (actuators, visualizations, logic units).
- **Test and Simulation Environments**: A single test signal is split across multiple parallel test paths.
- **Prototypical Adapter Coupling**: When multiple downstream blocks require the same input signal without the need for logical replication.

## Comparison with Similar Function Blocks

| Function Block | Function | Special Feature |

|----------|----------|--------------|

| `AUDI_SPLIT_2` | Distributes an audio signal to two outputs. | Similar principle, but with two outputs. |

AUDI_SPLIT_4` | Distributes an audio signal to four outputs. | This is a simple 1:4 splitter. |

AUDI_MERGE` | Combines multiple audio inputs into one output. | Inverted splitter (1:1 mapping, but reversed). |

Generic splitters | Can be applied to other adapters via type parameters. | Offer more flexibility than hardwired versions. |

## Conclusion

The `AUDI_SPLIT_4` is a simple yet useful function block for multiplying a unidirectional audio adapter signal to four parallel outputs. Its generic nature allows for adaptation to various adapter types, and its eventless operation makes it particularly suitable for pure data distribution tasks without additional control logic. The component contributes to the structuring and reusability of signals in complex automation solutions.
