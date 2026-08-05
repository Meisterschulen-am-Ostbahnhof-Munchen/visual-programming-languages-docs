# AUI_TO_AB
![AUI_TO_AB](./AUI_TO_AB.svg)
*No image available*

* * * * * * * * * *
## Introduction
The **AUI_TO_AB** function block is a composite block that converts an AUI interface (UINT) to an AB interface (BYTE). It encapsulates the conversion using the internal IEC 61131 block `F_UINT_TO_BYTE` and provides a uniform, unidirectional data flow via adapters. This block was developed for use in automation systems that need to transfer different data types between adapters.

## Interface Structure

### **Event Inputs**

| Name | Description | Data Type |

|------|---------------|----------|

| `AUI_IN.E1` | Event via the AUI adapter (socket) that triggers the conversion. | Event |

### **Event Outputs**

| Name | Description | Data Type |

|------|--------------|----------|

| `AB_OUT.E1` | Event via the AB adapter (plug) that is sent after successful conversion. | Event |

### **Data Inputs**

| Name | Description | Data Type |

|------|--------------|----------|

| `AUI_IN.D1` | UINT value that is received and converted via the AUI adapter. | UINT |

### **Data Outputs**

| Name | Description | Data Type |

|------|--------------|----------|

| `AB_OUT.D1` | Converted BYTE value output via the AB adapter. | BYTE |

### **Adapters**

| Type | Name | Direction | Comment |

|-----|------|----------|-----------|

| `adapter::types::unidirectional::AUI` | `AUI_IN` | Socket | UINT adapter input |

| `adapter::types::unidirectional::AB` | `AB_OUT` | Plug | BYTE Adapter Output |

## Functionality

This component functions as a pure signal converter:

1. An incoming event at **AUI_IN.E1** is forwarded to the internal function block `Convert` (type `F_UINT_TO_BYTE`).

2. Simultaneously, the data value **AUI_IN.D1** is passed to the input `Convert.IN`.

3. The converter transforms the UINT value into a BYTE value (data truncation to the least significant byte).

4. Upon completion, the event **AB_OUT.E1** is triggered, and the converted value is made available via **AB_OUT.D1**.

Internally, the mapping logic is implemented by a single IEC 61131 component, resulting in minimal latency and deterministic operation.

## Technical Features
- **Composite Structure**: The function block is implemented as a composite, meaning it contains an internal network with a single function block. This facilitates reuse and encapsulation.
- **Adapter Concept**: Input and output are handled exclusively via typed adapters (`AUI` and `AB`). This enables loose coupling and easy exchange of communication protocols within the application.
- **License**: The function block is licensed under the Eclipse Public License 2.0 (EPL-2.0). The source code is open and can be freely modified.
- **Dependency**: It requires the IEC 61131 function block `F_UINT_TO_BYTE`, which must be included in the package `iec61131::conversion`.

## State Overview

Since the function block does not have an internal state machine (composite without its own ECC), its state is determined solely by the internal function block `F_UINT_TO_BYTE`. This block operates in an event-driven manner and does not have a persistent state. After each event, the function block returns to its idle state.

## Application Scenarios
- **Data Conversion**: When a sensor delivers data in UINT format via an AUI adapter, but the downstream system expects a BYTE value via an AB adapter.
- **System Integration**: As an intermediary between different adapter types in heterogeneous automation networks.
- **Protocol Conversion**: In scenarios where existing libraries only support certain adapter types and type conversion is required.

## Comparison with Similar Function Blocks
- **Direct `F_UINT_TO_BYTE`**: This IEC function block is also used internally, but operates without an adapter – it requires direct data and event ports. `AUI_TO_AB` encapsulates this interface in adapter form.
- **Other Adapter Converters**: Similar function blocks exist, such as `AB_TO_AUI` or `ADI_TO_AB`, for other type combinations. They follow the same pattern and are interchangeable.

The key advantage of `AUI_TO_AB` is its complete integration into adapter-based architectures – without the application needing to know the internal conversion logic.

## Conclusion

The **AUI_TO_AB** function block is a simple yet useful composite function block for type conversion between two unidirectional adapters. Its clear structure and the use of a standardized converter make it reliable and easy to understand. It represents an elegant solution for all applications requiring clean adapter separation.
