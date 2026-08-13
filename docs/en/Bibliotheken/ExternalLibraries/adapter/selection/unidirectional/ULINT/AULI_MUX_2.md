# AULI_MUX_2

![AULI_MUX_2](./AULI_MUX_2.svg)

* * * * * * * * * *
## Introduction

The function block **AULI_MUX_2** implements a digital multiplexer (MUX) with two inputs and one output, configured as unidirectional AULI adapters.
It is used to forward one of the two data streams present at the input to the output, depending on an index value **K**.
The block is specified as a generic function block (GenericClassName: `GEN_AULI_MUX`) and is suitable for applications requiring simple switching between two signal sources.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Sets the index **K** and triggers the selection. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirms the switchover after processing a `REQ` event. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `K` | UINT | Selection index (expected: 0 for IN1, 1 for IN2). |

### **Data Outputs**

No direct data outputs – the output value is transmitted via the adapter `OUT`.

### **Adapters**

| Name | Type (Adapter) | Direction | Comment |
|------|----------------|----------|-----------|
| `OUT` | adapter::types::unidirectional::AULI | Plug | Multiplexer output – provides the value of the selected input. |
| `IN1` | adapter::types::unidirectional::AULI | Socket | First input (selected when K = 0). |
| `IN2` | adapter::types::unidirectional::AULI | Socket | Second input (selected when K = 1). |

## Functionality

The function block operates in an event-driven manner:

1. A `REQ` event retrieves the current value of the data input **K**.
2. The block copies the data value from adapter `IN1` to adapter `OUT` if **K = 0**, or the value from `IN2` to `OUT` if **K = 1**.
3. After the transfer is complete, the `CNF` event is output.

The index **K** is only read upon a `REQ` event; a change to the index without an event has no immediate effect.

## Technical Features

- **Generic Function Block**: The function block is defined as a generic type (`GEN_AULI_MUX`), allowing it to be used in various contexts with the same adapter protocol.
- **Unidirectional Adapters**: All adapters are specified as `unidirectional::AULI` – data flows only from the socket to the plug.
- **No State Storage**: The function block does not have an internal state machine; switching occurs purely combinatorially based on the `REQ` event.
- **Minimal Latency**: Direct forwarding of the adapter data eliminates delays caused by complex processing.

## State Overview

The function block does not have an explicit state machine. It behaves like an event-driven transfer function:

- **Waiting for REQ** → Read K, forward the corresponding input, output CNF.
- System-related waiting times can occur if the connected adapters do not provide data (blocking behavior of the AULI protocol).

## Application Scenarios

- **Signal Switching**: Selection between two sensors, measured values, or control signals in automation technology.
- **Redundant Channels**: Activation of a backup input (IN2) in case of failure of the primary signal (IN1).
- **Configurable Data Sources**: Selection of different data streams by higher-level control logic (e.g., via an index from an HM panel).
- **Generic Implementation**: The function block can be used in PLC libraries as a basic building block for any AULI adapter signals.

## Comparison with Similar Function Blocks

- **`MUX_4` Function Blocks** (Quadruple Multiplexer): These require two selection lines (K=0..3) and have four input adapters. `AULI_MUX_2` is limited to two channels, but is simpler and faster.
- **`SELECT` (IEC 61131-3)**: Works with elementary data types (BOOL, INT, …), while `AULI_MUX_2` communicates via structured adapters and can therefore transmit complex data objects.
- **`MERGE` blocks**: These combine multiple inputs in parallel (e.g., logic OR), while the MUX exclusively switches a single channel.

## Change Detection

The selected output plug (`OUT`) is only written and its adapter event only sent if the incoming value differs from the value currently held on `OUT`. If the value is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AULI_MUX_2` function block represents a simple yet robust multiplexer for use in 4diac environments.

Thanks to its generic definition and event-driven interface, it is flexible and integrates seamlessly into adapter-based communication structures. It is particularly suitable for applications requiring fast and reliable switching between two signal sources.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
