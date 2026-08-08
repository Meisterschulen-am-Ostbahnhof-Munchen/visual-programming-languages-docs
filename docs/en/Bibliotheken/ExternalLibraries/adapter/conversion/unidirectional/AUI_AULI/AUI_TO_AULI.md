# AUI_TO_AULI
![AUI_TO_AULI](./AUI_TO_AULI.svg)

* * * * * * * * * *
## Introduction
The function block `AUI_TO_AULI` is a composite function block for converting a unidirectional AUI adapter (data type `UINT`) into a unidirectional AULI adapter (data type `ULINT`). It serves as a simple type converter between the two adapter interfaces, transparently passing on both the event signal and the data value. The function block enables seamless integration of components that use different addressing widths.
## Interface Structure

The function block does not have its own event or data inputs/outputs, but uses only adapter interfaces. The following sections describe the signals that are routed externally via the adapters used.

### **Event Inputs**

| Signal | Description |
|--------|--------------|
| (E1 via AUI_IN) | Event input of the connected AUI adapter (socket). An incoming event is forwarded directly to the AULI adapter. |

### **Event Outputs**

| Signal | Description |
|--------|--------------|
| (E1 via AULI_OUT) | Event output of the connected AULI adapter (plug). The event received from the AUI adapter is output here. |

### **Data Inputs**

| Signal | Data Type | Description |
|--------|----------|--------------|
| (D1 via AUI_IN) | `UINT` (16 bits) | Data input of the AUI adapter. The incoming value is interpreted as a 16-bit integer. |

### **Data Outputs**

| Signal | Data Type | Description |
|--------|----------|--------------|
| (D1 via AULI_OUT) | `ULINT` (64 bits) | Data output of the AULI adapter. The value received from the AUI adapter is output as a 64-bit unsigned integer. |

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AUI` | `AUI_IN` | Socket (Input) | Adapter for receiving events and data in the format `UINT`. |
| `adapter::types::unidirectional::AULI` | `AULI_OUT` | Plug (Output) | Adapter for sending events and data in the format `ULINT`. |

## Functionality

This function block forwards incoming events and data from the input adapter `AUI_IN` unchanged to the output adapter `AULI_OUT`. The data type `UINT` is implicitly converted to `ULINT` (the value remains the same; only the bit width is increased from 16 to 64 bits). The connection is established in the FB network of the composite module by directly wiring the respective event and data channels (`E1` and `D1`). No additional logic or state storage is performed.

## Technical Features
- **Implicit Type Conversion:** The conversion from `UINT` to `ULINT` is performed automatically by the 4diac IDE and does not require an explicit conversion module. The value range from 0 to 65535 (UINT) is mapped to the corresponding ULINT range.

- **Implicit Type Conversion:** - **Pass-Through Behavior:** Events and data are transmitted without delay or buffering. The output event occurs simultaneously with the input event.
- **Unidirectional Adapters:** The module supports only one direction of data flow (from the AUI input to the AULI output). Reverse communication is not supported.

## State Overview

The module does not have its own states, as it consists exclusively of direct connections. The behavior is purely combinatorial: An event at the input immediately generates an event at the output, and the data value is transmitted continuously.

## Application Scenarios
- **Systems with Mixed Address Width:** When a sensor or component delivers data in the format `UINT` (e.g., a 16-bit counter value), but a downstream controller or bus interface only accepts `ULINT` (64-bit).
- **Adapter Coupling:** Used as an intermediary between two different adapter types in a modular control architecture based on the 61499 standard.
- **Prototype Development:** Rapid integration of library blocks that use different adapter interfaces without manual conversion.

## Comparison with Similar Blocks
- **INT_TO_LINT / UINT_TO_ULINT (Direct Data Converters):** These blocks operate on pure data levels without event forwarding and require separate event processing. `AUI_TO_AULI` combines event and data conversion in a single adapter interface.
- **Adapter-Adapter Connector:** Other composite blocks that connect two similar adapters (e.g., AUI_TO_AUI) – they differ only in the absence of type conversion.
- **Explicit Multi-Channel Conversion Blocks:** More complex blocks that convert multiple signals simultaneously are overkill for simple point-to-point connections like this one.

## Conclusion

AUI_TO_AULI` is a lean, specialized composite block for converting an AUI adapter to an AULI adapter. It simplifies type conversion between 16-bit and 64-bit addressing in IEC 61499 systems by automatically converting and forwarding both event and data paths. Thanks to the implicit type conversion from `UINT` to `ULINT`, manual implementation of conversion logic is eliminated, facilitating the design of modular and reusable control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
