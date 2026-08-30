# AIWS_SPLIT_7

![AIWS_SPLIT_7](./AIWS_SPLIT_7.svg)

* * * * * * * * * *

## Introduction

The function block **AIWS_SPLIT_7** is a generic component that splits a single incoming AIWS adapter (unidirectional) into seven identical outgoing AIWS adapters. It serves as a signal distributor for automation applications where a data stream or connection needs to be copied to multiple parallel paths.

## Interface Structure

### **Event Inputs**

None (the function block has no event inputs).

### **Event Outputs**

None (the function block has no event outputs).

### **Data Inputs**

None (the function block has no direct data inputs; data transmission occurs exclusively via the adapter interfaces).

### **Data Outputs**

None (the function block has no direct data outputs; data transmission occurs exclusively via the adapter interfaces).

### **Adapters**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AIWS` | **IN** | Socket (Input) | Receives the AIWS data stream to be distributed. |
| `adapter::types::unidirectional::AIWS` | **OUT1** | Plug (Output) | First identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT2** | Plug (Output) | Second identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT3** | Plug (Output) | Third identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT4** | Plug (Output) | Fourth identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT5** | Plug (Output) | Fifth identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT6** | Plug (Output) | Sixth identical output channel. |
| `adapter::types::unidirectional::AIWS` | **OUT7** | Plug (Output) | Seventh identical output channel. |

## Functionality

The function block receives a unidirectional data stream of type `AIWS` via socket **IN**. This data stream is duplicated internally without modification and simultaneously passed to all seven plugs **OUT1** through **OUT7**. Each output channel receives exactly the same data as the input. There is neither delay nor data manipulation.

## Technical Features

- **Generic Function Block** – The function block is defined as a generic component (attribute `GenericClassName` = `'GEN_AIWS_SPLIT'`), which enables type-safe reuse in different contexts.
- **Unidirectional Adapters** – All adapters used are unidirectional, meaning data flows only from the socket to the plugs.
- **No Event Control** – The function block has no internal state machine and no event inputs/outputs; distribution is purely data-driven.
- **Scalable Architecture** – Thanks to the modular adapter interface, the function block can be used in complex hierarchies of function blocks.

## State Overview

Since the function block does not have a state machine (Execution Control Chart), there are no explicit states. The output signals are always directly dependent on the input signals. The function block (FB) operates as a pure data distributor without delay or switching operations.

## Application Scenarios

- **Parallel Processing** – Distribution of a measured value or control signal to multiple independent control or monitoring paths.
- **Signal Monitoring** – The same signal is routed to different diagnostic or logic blocks.
- **Redundancy** – Provision of identical data streams for different receivers (e.g., operation, visualization, and archiving).
- **Test Environments** – A test signal can be sent to multiple simulation blocks simultaneously.

## Comparison with Similar splitters

- **AIWS_SPLIT_2, AIWS_SPLIT_4** – splitters with the same functionality but a different number of outputs (2 or 4). AIWS_SPLIT_7 offers the maximum number of outputs within this splitter family.
- **Generic 1:N Splitters** – Other IEC 61499 libraries often contain generic splitters for data types such as `ANY`. AIWS_SPLIT_7 is specifically designed for the adapter type `AIWS` and therefore requires no type conversion.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AIWS_SPLIT_7** is a simple yet powerful function block for multiplying a unidirectional AIWS data stream to seven parallel outputs. Its generic definition and purely adapter-based interface enable flexible integration into IEC 61499 applications, particularly for signal distribution and parallel processing tasks.
