# AI_TO_AX
![AI_TO_AX](./AI_TO_AX.svg)
* * * * * * * * * *
## Introduction
The function block `AI_TO_AX` is a composite function block (type adapter) that converts a unidirectional interface of an INT adapter (`AI`) into a corresponding BOOL interface of an adapter (`AX`). It is used to convert analog integer signals (e.g., from sensors) into binary Boolean values, which can be used, for example, for switching signals or alarm messages.
## Interface Structure

The function block only has adapter connections (socket and plug) through which events and data flow. The following table summarizes the logical inputs/outputs resulting from the connected adapters.

### **Event Inputs**

| Label | Data Type | Description |

|-------------|----------|--------------|

| `AI_IN.E1` | EVENT | Input event that triggers the conversion. |

### **Event Outputs**

| Label | Data Type | Description |

|-------------|----------|--------------|

| `AX_OUT.E1` | EVENT | Output event that is sent after the conversion is complete. |

### **Data Inputs**

| Label | Data Type | Description |

|-------------|----------|--------------|

| `AI_IN.D1` | INT | Analog integer input value (e.g., 0…32767). |

### **Data Outputs**

| Label | Data Type | Description |

|-------------|-----------|--------------|

| `AX_OUT.D1` | BOOL | Boolean output value: `TRUE` if the input value is not equal to 0, otherwise `FALSE`. |

### **Adapter**

| Type | Name | Direction |

### **Adapter**

| Type | Name | Direction |

### **Adapter**

| Type | Name | Direction |

### **Data Outputs**

| Type | Name | Direction |

| |------------|----------|----------|

| `AI` (Input Adapter) | `AI_IN` | Socket |

| `AX` (Output Adapter) | `AX_OUT` | Plug |

## Functionality

The module internally uses the IEC 61131 comparison module `F_NE` (Not Equal). As soon as an event arrives at the event input `AI_IN.E1`, `F_NE.REQ` is triggered. This compares the INT value received via `AI_IN.D1` with the constant value `INT#0`.

- If the input value is **not equal to 0**, `F_NE.OUT` returns the value `TRUE`.
- If the input value is **equal to 0**, `F_NE.OUT` returns the value `FALSE`.

The result is passed to the data output `AX_OUT.D1`, and simultaneously the event `AX_OUT.E1` is triggered to notify downstream components.

`` If the input value is **equal to 0**, then `F_NE.OUT` returns the value `FALSE`.

`` If the input value is **equal to 0**, then `F_NE.OUT` returns the value `FALSE`.

`` ... ## Technical Features

- **Composite Block:** The `AI_TO_AX` consists of interconnected basic blocks, allowing it to be used as a reusable component in various projects.
- **Use of IEC 61131 Blocks:** The comparison logic is implemented using the standardized block `F_NE`, which supports portability and compliance with the standard.
- **No Independent State:** The block is stateless – each event pulse generates an immediate calculation without storing intermediate values.

## State Overview

The block does not have an explicit finite state machine. The internal logic is purely combinatorial: Upon the arrival of an event, the data is processed immediately and the result is output.

## Application Scenarios
- **Analog-to-Digital Conversion at the Signal Level:** An analog measured value (e.g., pressure sensor, temperature sensor) is converted into an "on/off" signal – e.g., activating a pump when a pressure threshold is exceeded.
- **Threshold Decision:** The function block can be used for simple non-zero detection, e.g., to signal the presence of a signal or an activated counter reading.
- **Adapter Coupling:** In systems that use different adapter interfaces, `AI_TO_AX` enables seamless connectivity between INT- and BOOL-based components.

## Comparison with Similar Function Blocks
- **Direct Comparison Function Blocks (e.g., F_EQ, F_GT):** These provide Boolean results for arbitrary comparisons but require two inputs and are not designed as adapter converters.
- **Custom Adapter Wrappers:** Developers could create their own encapsulation; however, the `AI_TO_AX` offers a standardized, ready-to-use solution with reduced development effort.
- **Non-Event-Driven Type Converters:** Some converters operate continuously without event triggers; the `AI_TO_AX`, on the other hand, only responds to events and is therefore better integrated into event-driven architectures.

## Conclusion

The `AI_TO_AX` is a convenient composite component that simplifies the conversion of INT adapter signals to BOOL adapter signals. It is ideal for applications where analog measurements need to be interpreted as binary states and, thanks to its event-driven processing, integrates seamlessly into IEC 61499-based automation systems.