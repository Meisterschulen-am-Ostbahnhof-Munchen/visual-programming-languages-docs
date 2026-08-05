# ADI_MUX_2
![ADI_MUX_2](./ADI_MUX_2.svg)
* * * * * * * * * *
## Introduction
The function block **ADI_MUX_2** is a generic multiplexer for ADI (Agricultural Data Interface) adapters. It allows selection between two ADI inputs (IN1 and IN2) and routes the selected input to the output OUT. Selection is made via the index K, which is set by an event.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Sets the index K and triggers the multiplexer action. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirms successful indexing and selection. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Selection Index (0 → IN1, 1 → IN2) |

### **Data Outputs**

No direct data outputs. Output is via the **OUT** adapter.

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Plug (Output) | OUT | `adapter::types::unidirectional::ADI` | Output: Returns the data of the selected input. |

| Socket (Input) | IN1 | `adapter::types::unidirectional::ADI` | First input (K = 0). |

Socket (Input) | IN2 | `adapter::types::unidirectional::ADI` | Second input (K = 1). |

## Functionality
1. The function block waits for a **REQ** event.

2. Upon arrival of **REQ**, the value of the data input **K** is read.

3. Depending on **K**, either **IN1** (K = 0) or **IN2** (K = 1) is made visible externally via the **OUT** adapter.

4. After successful selection, the confirmation event **CNF** is sent.

The selection is purely event-driven; any change to **K** requires another **REQ** event to take effect.

## Technical Features
- **Generic Function Block**: The FB is declared as a generic block (`GEN_ADI_MUX`) and can be used for various ADI data types (e.g., by adapting the ADI adapter definition).
- **Adapter-Based Interface**: Communication occurs exclusively via ADI adapters (unidirectional). No direct data variables are used at the outputs.
- **Simple Logic**: No internal state machine – the action is triggered directly by the event.

## State Overview
The FB does not have an explicit state machine. The workflow can be described as follows:

1. **Waiting** for **REQ**.

2. **Processing**: Reading **K** and switching the corresponding input.

3. **Acknowledge**: Sending **CNF**.

4. Returning to the wait state.

## Application Scenarios
- **Sensor Switching**: Selection between two ADI-compliant sensors (e.g., temperature/pressure) in an agricultural control system.
- **Redundancy**: Switching to a backup ADI input in case of primary signal failure.
- **Mode Selection**: A different data stream is used depending on the operating mode (e.g., manual/automatic).

## Comparison with Similar Function Blocks
- **ADI_MUX_2** is limited to exactly two inputs.
- For more inputs, corresponding variants (e.g., ADI_MUX_4, ADI_MUX_8) would be conceivable, which would extend the index **K** accordingly.
- Unlike a general multiplexer for standard data types (e.g., INT, REAL), this function block works exclusively with ADI adapters and is therefore integrated into ADI-based system architectures.

## Conclusion

The **ADI_MUX_2** is a compact, event-driven multiplexer for ADI adapters. It is ideally suited for applications requiring dynamic switching between two ADI data sources. Thanks to its generic design, it can be used in a wide variety of ADI contexts without requiring any modifications to its internal logic.