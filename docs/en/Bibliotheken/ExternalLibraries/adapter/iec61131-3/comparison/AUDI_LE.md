# AUDI_LE
![AUDI_LE](./AUDI_LE.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_LE** performs a less-than-equal-to comparison of two values. It is built as a composite function block based on the standardized comparison block `F_LE` from the IEC 61131 classification. Communication with the environment occurs exclusively via adapter interfaces, allowing the block to be integrated modularly into event-driven processes.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |

|-------------|-----------|--------------|

| `IN1.E1` | EVENT | Event input of adapter IN1 – triggers processing of the first value. |

| `IN2.E1` | EVENT | Event input of adapter IN2 – triggers processing of the second value. |

*Note: Both events must be received for a comparison to take place (logical AND operation in the internal network).*

### **Event Outputs**

| Label | Data Type | Description |

|-------------|-----------|--------------|

| `OUT.E1` | EVENT | Event output of adapter OUT – is activated as soon as the comparison result is available. |

### **Data Inputs**

| Label | Data Type | Description |

|-------------|----------|--------------|

| `IN1.D1` | ANY | First value to be compared (via adapter IN1). |

| `IN2.D1` | ANY | Second value to be compared (via adapter IN2). |

### **Data Outputs**

| Label | Data Type | Description |

|-------------|-----------|--------------|

| `OUT.D1` | BOOL | Comparison result: `TRUE` if `IN1 ≤ IN2`; otherwise `FALSE`. |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| `IN1` | `adapter::types::unidirectional::AUDI` | Socket (Input) | Capture the first value (event + data). |

| `IN2` | `adapter::types::unidirectional::AUDI` | Socket (Input) | Capture the second value (event + data). |

| `OUT` | `adapter::types::unidirectional::AX` | Plug (Output) | Output the comparison result (event + data). |

## Functionality

1. The function block (FB) expects one event and one data value at each of its two input adapters (`IN1` and `IN2`).

2. Internally, the two events are combined (via an implicit AND condition in the network), and the embedded function block `F_LE` is started with the data values.

3. `F_LE` performs the comparison `IN1 ≤ IN2` and places the result (Boolean value) at its data output.

4. As soon as the result is available, the event at the output adapter `OUT` is triggered, and the result value is made available via `OUT.D1`.

## Technical Features
- **Adapter-Based Interfaces:** The function block (FB) does not have traditional individual ports but uses standardized unidirectional adapters. This facilitates reuse and integration into complex communication structures.
- **Composite Structure:** All logic is implemented via an internal FB (`F_LE`). This makes the function block easy to understand and extend.
- **Event Synchronization:** Both input events must arrive before processing starts. This ensures that current value pairs are always compared.

## State Overview

The FB does not have its own directed state machine, as it operates purely combinatorially. The internal `F_LE` is also stateless. The only relevant logic is the AND operation of the events – after receiving both events, the result is output once.

## Application Scenarios
- **Limit Monitoring:** Check whether a measured value exceeds a threshold.
- **Enabling Logic:** Activate an action only if the current requirement is less than or equal to a maximum allowable value.
- **Comparison Chains:** Combine multiple `AUDI_LE` function blocks to implement complex conditions (e.g., `x ≤ y ≤ z`).

## Comparison with Similar Function Blocks

| FB | Function | Difference to AUDI_LE |

|----|----------|------------------------|

| `AUDI_LT` | Less than (`<`) | Not including equality. |

| `AUDI_EQ` | Equality (`=`) | Checks for exact matches only. |

| `AUDI_GE` | Greater Than or Equal To (`≥`) | Reverse comparison direction. |

| `AUDI_AND` | Logical AND | Works with Boolean values, not numerical comparisons. |

## Conclusion

`AUDI_LE` is a specialized comparison block that, thanks to its adapter interfaces, is particularly well-suited for modular, event-driven automation solutions. It offers clear, standardized logic for the "less than or equal to" condition and, due to its composite structure, can be easily integrated into custom applications.