# AI_TO_ADI
![AI_TO_ADI](./AI_TO_ADI.svg)
* * * * * * * * * *
## Introduction
The AI_TO_ADI function block is a composite function block that converts an AI adapter (integer values, type INT) into an ADI adapter (double integer values, type DINT). It serves as a bridge between components that use different adapter interfaces.
## Interface Structure

### **Event Inputs**

The function block does not have its own event inputs. The event is provided via the incoming adapter AI_IN:

- **AI_IN.E1** (Event): Trigger for forwarding the data value and the event to the output.

### **Event Outputs**

The function block does not have its own event outputs. The event is output via the outgoing adapter ADI_OUT:

- **ADI_OUT.E1** (Event): Triggered after successful data transmission.

### **Data Inputs**

The function block (FB) does not have its own data inputs. The data is provided via the incoming adapter AI_IN:

- **AI_IN.D1** (INT): The integer value to be converted.

### **Data Outputs**

The function block (FB) does not have its own data outputs. The data is output via the outgoing adapter ADI_OUT:

- **ADI_OUT.D1** (DINT): The converted double-integer value.

### **Adapters**

| Name | Direction | Type | Description |

|---------|----------|-----------------------------|--------------------------------------|

| AI_IN | Socket | adapter::types::unidirectional::AI | Input adapter for integer values (INT) |

| ADI_OUT | Plug | adapter::types::unidirectional::ADI | Output adapter for double integer values (DINT) |

## Functionality

This function block operates as a simple forwarder: As soon as the event `E1` is present at the incoming adapter `AI_IN`, the current value of `AI_IN.D1` is read and passed unchanged to `ADI_OUT.D1`. Subsequently, the event `E1` is triggered at the outgoing adapter `ADI_OUT`. The type conversion from `INT` to `DINT` is performed automatically via the adapter binding; no explicit conversion logic is required.

## Technical Features
- **Implicit Type Conversion:** The function block (FB) performs the conversion from 16-bit integer (INT) to 32-bit double integer (DINT) without data loss, as the target data type is larger.
- **Composite Implementation:** The function block is implemented as a composite FB, meaning it contains an internal network that directly connects the two adapters. It can be used in control projects like a primitive FB.
- **Unidirectional Communication:** Both adapters are designed to be unidirectional – data flows only from input to output.
- **No Latency or Buffering:** Data forwarding is event-driven and occurs without any additional delay.
- **No Latency or Buffering:** ## State Overview

The AI_TO_ADI has no internal state machine (ECC). It behaves passively and immediately forwards every incoming event and its associated data. There are no internal states, wait times, or value storage.

## Application Scenarios
- **Adapter Bridge:** If a sensor module provides an AI adapter (INT), but a subsequent processing module expects an ADI adapter (DINT), the AI_TO_ADI can be used as an intermediary.
- **System Integration:** In heterogeneous automation systems where different data types are used for adapter interfaces, this function block enables easy adaptation without modifying the original components.
- **Prototyping:** Rapid coupling of function blocks from different libraries based on different adapter types.

## Comparison with Similar Function Blocks

| Function Block | Type Conversion | Interface | Use Case |

|-----------------|------------------|-------------------------------------|------------------------------------|

AI_TO_ADI | INT -> DINT | Adapter (Socket/Plug) | Bridge between adapter-based components |

INT_TO_DINT | INT -> DINT | Direct inputs/outputs (e.g., DI1, DO1) | Simple data conversion without adapters |

CONV_ANY_TO_ANY | Generic | Flexible inputs/outputs | Universal conversion (often more complex) |

While function blocks like `INT_TO_DINT` offer direct data conversion with their own inputs and outputs, AI_TO_ADI seamlessly integrates the conversion into an adapter-based architecture, thus facilitating the reuse of existing adapter definitions.

``` ## Conclusion

The AI_TO_ADI is a simple yet valuable function block for converting integer to double-integer adapter interfaces. Its composite structure and implicit type conversion allow it to be integrated into adapter-based control systems without additional programming logic, simplifying the integration of components with different data widths.