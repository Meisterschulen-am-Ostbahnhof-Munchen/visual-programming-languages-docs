# AW_SPLIT_4

![AW_SPLIT_4](./AW_SPLIT_4.svg)

* * * * * * * * * *

## Introduction

The function block `AW_SPLIT_4` distributes an incoming AW adapter (unidirectional) to four identical AW output adapters. The block is designed generically and can be used with different AW types.

## Interface Structure

### **Event Inputs**
None.

### **Event Outputs**
None.

### **Data Inputs**
None (data transmission occurs exclusively via the adapter socket).

### **Data Outputs**
None (output occurs exclusively via the adapter plugs).

### **Adapters**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| `adapter::types::unidirectional::AW` | `IN` | Socket | Input for the AW data stream to be distributed |

| `adapter::types::unidirectional::AW` | `OUT1` | Plug | First output (copy of the input) |

| `adapter::types::unidirectional::AW` | `OUT2` | Plug | Second output |

| `adapter::types::unidirectional::AW` | `OUT3` | Plug | Third output |

| `adapter::types::unidirectional::AW` | `OUT4` | Plug | Fourth Output |

## Functionality

This function block acts as a passive distributor: Every value (or data packet) arriving via socket `IN` is forwarded unchanged to all four plugs `OUT1` to `OUT4`. No processing, buffering, or time synchronization takes place. The entire data flow is uneventful and purely adapter-based.

## Technical Features

- **Generic Function Block**: The function block is declared with the generic name `GEN_AW_SPLIT`. This allows for late binding to specific AW adapter types (e.g., `AT_AW`, `CT_AW`, etc.) at compile or configuration time.

- **Unidirectional Communication**: The adapters used are of type `unidirectional::AW`, meaning data flows only in one direction. There are no return channels or acknowledgments.

- **No Dynamics**: The function block (FB) has no events, states, or time-dependent logic. It is purely combinatorial.

## State Overview

Not applicable – the FB does not contain a state machine (ECC) and operates entirely in a data-driven manner.

## Application Scenarios

- Distribution of a single sensor or actuator signal path across multiple parallel evaluations.

- Preparation of a data source for different consumers in a control application.

- Generation of test or simulation points by multiplying an AW data stream.

## Comparison with similar function blocks

Unlike data- or event-based split function blocks (e.g., `SPLIT`, `F_SPLIT`), `AW_SPLIT_4` operates exclusively at the adapter level. The advantage lies in its loose coupling and reusability across different AW types. The disadvantage: Only AW data can be distributed, not events or general values.

## Conclusion

The `AW_SPLIT_4` function block is a simple, generic distributor for unidirectional AW adapters. It is ideally suited to split a single AW signal into up to four outputs and, thanks to its generic nature, integrates flexibly into various IEC 61499 applications.