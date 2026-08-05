# AS_TO_AUI
![AS_TO_AUI](./AS_TO_AUI.svg)

* * * * * * * * * *
## Introduction
The function block `AS_TO_AUI` is a composite function block (FB) that converts a SINT adapter input (`AS`) into a UINT adapter output (`AUI`). It encapsulates the type conversion and enables a clean, adapter-based interface between components that use different data types.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |
|-------------|-----------|--------------|
| `E1` (via `AS_IN`) | EVENT | Starts the conversion of the incoming SINT value. |

### **Event Outputs**

| Name | Data Type | Description |
|-------------|----------|--------------|
| `E1` (via `AUI_OUT`) | EVENT | Confirms the completion of the conversion and output of the UINT value. |

### **Data Inputs**

| Name | Data Type | Description |
|-------------|-----------|--------------|
| `D1` (via `AS_IN`) | SINT | The signed 8-bit value to be converted. |

### **Data Outputs**

| Label | Data Type | Description |
|-------------|----------|--------------|
| `D1` (via `AUI_OUT`) | UINT | The converted unsigned 16-bit value. |

### **Adapters**

| Label | Type | Direction | Description |
|-------------|-----|----------|--------------|
| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Input) | Provides the SINT value and the triggering event. |
| `AUI_OUT` | `adapter::types::unidirectional::AUI` | Plug (Output) | Outputs the converted UINT value and the acknowledgment event. |

## Functionality

The function block operates in an event-driven manner:

1. When the event `E1` arrives at the `AS_IN` adapter, the incoming SINT data value (`D1`) is forwarded to the internal conversion function block `F_SINT_TO_UINT`.

2. The `F_SINT_TO_UINT` function block performs the data type conversion according to IEC 61131 (SINT → UINT).

3. Once the conversion is complete, the resulting UINT value is passed to the `AUI_OUT` adapter, and the event `E1` is triggered on `AUI_OUT`.

The entire process is atomic within an event cycle: event in, data conversion, event out.

## Technical Features
- The function block internally uses the IEC 61131 conversion function `F_SINT_TO_UINT`, which is derived from the `iec61131::conversion` library.
- The adapters are designed as **unidirectional** types (AS for input, AUI for output), which clearly defines the data flow direction and avoids misunderstandings.
- There are no internal states or timing behaviors – the conversion is purely combinatorial, controlled by the event.
- The function block is licensed under the Eclipse Public License 2.0.

## State Overview

Since this is a composite function block without its own state machine, there is no internal state machine. The function block is completely event-driven and executes the conversion immediately upon each trigger.

-
## Application Scenarios
- **Connecting Different Bus Systems**: If a sensor (e.g., AS-Interface) delivers SINT values, but the controller expects UINT values, this function block can handle the translation.
- **Protocol or Adapter Compatibility**: Use in heterogeneous automation systems where different fieldbuses or components operate with different data types.
- **Data Preparation**: Preparation of SINT data for further processing that only supports UINT.

## Comparison with Similar Function Blocks
- **Direct Conversion Function Blocks** (e.g., `F_SINT_TO_UINT`): These operate at the level of individual signals without adapter encapsulation. `AS_TO_AUI` integrates the adapter interface and is therefore easier to integrate into adapter-based architectures.
- **Bidirectional Adapter Converters**: If conversion in both directions is required, a separate module (e.g., `AUI_TO_AS`) must be used. `AS_TO_AUI` is strictly unidirectional.

## Conclusion

The `AS_TO_AUI` module provides a simple, reliable, and standardized method for converting SINT adapter data to a UINT adapter format. Thanks to the use of IEC 61131 modules and unidirectional adapters, it is robust, easy to understand, and integrates well into existing 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
