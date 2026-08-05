# AW_MUX_2
![AW_MUX_2](./AW_MUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **AW_MUX_2** is a generic multiplexer for two adapter inputs. Based on an index value (`K`), it selects one of the two adapters (`IN1`, `IN2`) and forwards it to the output adapter (`OUT`). The block operates in an event-driven manner and is suitable for switching between two unidirectional adapter connections of type "AW".
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| `REQ` | Event | Sets the index `K` and triggers the switching of the selected input to the output. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `CNF` | Event | Confirms the successful execution of the switch according to the current index `K`. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `K` | UINT | Index for selecting the input: `0` → `IN1`, `1` → `IN2`. |

### **Data Outputs**

None.

### **Adapters**

| Name | Direction | Type | Comment |

|------|----------|-----|-----------|

| `IN1` | Socket (Input) | `adapter::types::unidirectional::AW` | First adapter input, active at `K = 0`. |

| `IN2` | Socket (Input) | `adapter::types::unidirectional::AW` | Second adapter input, active at `K = 1`. |

| `OUT` | Plug (Output) | `adapter::types::unidirectional::AW` | Output adapter that passes on the selected input. |

## Functionality

The function block performs the following steps on each event at `REQ`:

1. Evaluate the current index value `K`.

2. Connect the corresponding socket adapter (`IN1` for `K = 0` or `IN2` for `K = 1`) to the plug `OUT`.

- If `K` has values other than 0 or 1, no input is passed through (no action is taken).

3. Send the confirmation event `CNF`.

The adapter type `AW` is defined as unidirectional, so data transmission only occurs in one direction (from the socket to the plug).

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GenericClassName = 'GEN_AW_MUX'`). It can be used in various contexts with the underlying adapter type `AW`.
- **No State Machine**: The function block has no explicit state logic – switching occurs purely event-driven and instantaneously.
- **Adapter-Oriented**: Instead of individual data points, entire adapter connections are switched, making the function block ideal for modular, adapter-based architectures.

## State Overview

The function block does not have an internal state machine. Its functionality is limited to the direct response to the `REQ` event. Therefore, no defined states exist except for the implicit **idle state** (waiting for `REQ`).

## Application Scenarios
- **Sensor Switching**: Selection between two sensors (e.g., temperature from two different sensors) via an index.
- **Configuration Switching**: Switching between two different data sources (e.g., two parameter sets) via adapter multiplexing.
- **Test and Diagnostics**: Selective switching between test or normal operation to a common output interface.

## Comparison with Similar Function Blocks

| Function Block | Feature |

|----------|---------|

| `MUX` (Standard-4diac) | Switches individual data values (e.g., INT, REAL) based on an index. |

| `AW_MUX_2` | Switches complete adapter connections (type `AW`). Suitable for adapter-based communication, e.g., B. in OPC UA or service interfaces. |

| `SELECT` | Selects between two Boolean inputs; here, adapter selection is done using an integer index. |

The `AW_MUX_2` fills the gap between pure data multiplexers and full protocol switchers.

## Conclusion

The **AW_MUX_2** is a simple yet powerful function block for adapter switching in the 4diac IDE. By using the generic adapter type `AW` and index-based selection, it is suitable for flexible switching in modular automation solutions. The absence of a state machine makes it resource-efficient and easy to use, while the clear event-based control ensures reliable synchronization.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
