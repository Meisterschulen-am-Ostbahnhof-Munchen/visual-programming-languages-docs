# AX_TO_AW
No image available.
![AX_TO_AW](./AX_TO_AW.svg)

* * * * * * * * * *
## Introduction
The function block `AX_TO_AW` is a composite function block (FB) for converting a unidirectional BOOL adapter (type `AX`) into a unidirectional WORD adapter (type `AW`). It acts as an interface converter, forwarding an incoming event and a BOOL data value directly to the output adapter, with the BOOL value being implicitly converted into a WORD.
## Interface Structure
### **Event Inputs**
The function block does not have separate event inputs. The event is provided via the socket adapter `AX_IN` (type `AX`) (internal event `E1`).

### **Event Outputs**
The function block does not have separate event outputs. The event is output via the plug adapter `AW_OUT` (type `AW`) (internal event `E1`).

### **Data Inputs**
The function block does not have separate data inputs. The input data (BOOL) is provided via the socket adapter `AX_IN` (data point `D1`, type `BOOL`).

#
## ### **Data Outputs**

This function block does not have separate data outputs. The output data (WORD) is provided via the plug adapter `AW_OUT` (data point `D1`, type `WORD`).

### **Adapter**

| Direction | Label | Type | Comment |

|----------|-------------|-----|-----------|

| **Socket** | `AX_IN` | `adapter::types::unidirectional::AX` | BOOL adapter input (consisting of event `E1` and data `D1:BOOL`) |

| **Plug** | `AW_OUT` | `adapter::types::unidirectional::AW` | WORD adapter output (consisting of event `E1` and data `D1:WORD`) |

## Functionality
This component forwards the event (`E1`) received from socket `AX_IN` directly to plug `AW_OUT` (`E1`). Simultaneously, the incoming BOOL value (`AX_IN.D1`) is passed to the WORD output (`AW_OUT.D1`) without further processing. An implicit type conversion takes place from `BOOL` to `WORD` (typical mapping: `FALSE` → 0, `TRUE` → 1). No logic, delay, or state change occurs – the function block (FB) functions purely as a pass-through.

## Technical Features
- **Composite FB:** The function block does not have its own state machine (ECC) but consists solely of wiring the included adapter interfaces.
- **Type Conversion:** The conversion from `BOOL` to `WORD` occurs automatically via the data connection between the adapters. No explicit conversion logic is implemented.
- **Performance:** Direct coupling eliminates the need for additional processing steps, ensuring minimal latency.
- **Reusability:** This function block can be used in projects that require connecting adapters of different types without needing separate conversion logic.

## State Overview
Since this is a composite function block without its own ECC, there are no explicit states. The function block behaves like a simple signal forwarder and has no behavioral model of its own.

## Application Scenarios
- **Connecting a BOOL-based sensor** to a control system that expects WORD interfaces (e.g., digital inputs as bitmasks).
- **Adapter layer** in libraries where components with different adapter types need to be combined without modifying the source function blocks.
- **Prototypical development** for the rapid integration of BOOL and WORD adapters prior to later optimization.

## Comparison with Similar Blocks
- **AW_TO_AX (theoretical):** This would be the inverse conversion from WORD to BOOL – requiring a reduction of the value range (e.g., only bit 0 is evaluated).
- **TYPCONV Blocks:** IEC 61499 libraries typically offer explicit type converters (e.g., `BOOL_TO_WORD`), but these operate as standard function blocks with event and data inputs, not as adapter converters.
- **Direct Adapter Coupling:** Without `AX_TO_AW`, the adapter types would have to be identical, or a separate conversion would be required at the network layer.

## Conclusion
The function block `AX_TO_AW` is a simple yet useful converter that enables coupling between BOOL and WORD adapters. Thanks to the direct pass-through of events and data with minimal overhead, it is ideally suited for interface adaptations in distributed automation systems. Its composite structure makes it transparent, easy to understand, and simple to integrate into existing projects.
