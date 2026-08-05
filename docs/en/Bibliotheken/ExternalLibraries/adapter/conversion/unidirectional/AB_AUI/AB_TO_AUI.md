# AB_TO_AUI
![AB_TO_AUI](./AB_TO_AUI.svg)
* * * * * * * * * *
## Introduction
The function block **AB_TO_AUI** serves as an adapter converter between an AB adapter (BYTE-based) and an AUI adapter (UINT-based). It performs a unidirectional conversion from BYTE to UINT data type. The block is implemented as a composite FB and internally uses the IEC 61131-3 conversion function `F_BYTE_TO_UINT`. It is specifically designed for connecting sensors or actuators that deliver their data in BYTE format but must be processed in a UINT-based environment.
## Interface Structure

### **Event Inputs**
The FB does not have direct event inputs at the top level. Event control is handled via the connected adapters.

### **Event Outputs**
The FB has no direct event outputs at the top level. Events are passed on via the connected adapters.

### **Data Inputs**
The FB has no direct data inputs at the top level. Data is received via the connected AB adapter.

### **Data Outputs**
The FB has no direct data outputs at the top level. Data is output via the connected AUI adapter.

### **Adapters**

| Direction | Name | Adapter Type | Description |

|----------|-------|-------------------------------|-------------------------------------------------|

| Socket | AB_IN | `adapter::types::unidirectional::AB` | Input adapter for BYTE data (source adapter) |

| Plug | AUI_OUT| `adapter::types::unidirectional::AUI` | Output adapter for UINT data (destination adapter) |

**Note:** Adapters of type `AB` and `AUI` each have an event input (`E1`), an event output (`E1`), a data input (`D1` of type BYTE or UINT), and a data output (`D1` of type BYTE or UINT). See the corresponding adapter definitions for complete details.

## Functionality

The module functions as a pure converter: As soon as an event occurs at socket `AB_IN` (typically via the adapter's event input), it is forwarded to the internal function block `F_BYTE_TO_UINT`. Simultaneously, the BYTE value provided by the adapter (via the AB adapter's data input `D1`) is passed to the conversion function block. The conversion function block converts the BYTE value into an equivalent UINT value. After successful conversion, an event is triggered via the event output of the internal function block, which is then passed to plug `AUI_OUT`. The converted UINT value is transferred via the conversion function block's data output to the AUI adapter's data input.

`` The following diagram shows the internal wiring:

- Event connection: `AB_IN.E1` → `Convert.REQ` → `Convert.CNF` → `AUI_OUT.E1`
- Data connection: `AB_IN.D1` → `Convert.IN` → `Convert.OUT` → `AUI_OUT.D1`

The entire process is strictly sequential and event-driven.

## Technical Features
- **Unidirectional Operation:** The function block only supports data flow from AB (BYTE) to AUI (UINT). Reverse conversion is not possible with this function block.
- **Use of IEC 61131-3 Conversion:** The conversion is performed using the standardized function block `F_BYTE_TO_UINT` from the IEC 61131 library. This ensures reliable and portable conversion.
- **Adapter-Based Interface:** The function block is intentionally designed as an adapter converter and not as a standalone function block with direct inputs/outputs. This allows for easy integration into existing adapter-based communication structures.
- **No State Storage:** The function block is stateless, meaning it does not store intermediate values. Each conversion process is independent of previous ones.

## State Overview

The function block does not have its own state machines. Its behavior is determined by the internal function block `F_BYTE_TO_UINT` (a simple function block without states) and event chaining. Therefore, the function block is always ready to perform a conversion as soon as an event arrives at the input adapter.

## Application Scenarios
- **Sensor Connection:** A sensor delivers measured values in BYTE format (e.g., via an AB adapter), while the control system processes only UINT values. The AB_TO_AUI function block converts the values accordingly.
- **Protocol Adaptation:** In heterogeneous fieldbus systems, the function block can be used as a simple data type converter between different adapter types.
- **Testing and Simulation:** During development, this function block can be used to convert BYTE data from a test environment into UINT data for the target application.

## Comparison with Similar Function Blocks

Other adapter converters exist, such as `AB_TO_UDINT`, `BYTE_TO_WORD`, or direct converters like `F_BYTE_TO_SINT`. The `AB_TO_AUI` focuses specifically on adapter conversion while preserving the adapter structure. Unlike pure function blocks, it retains the adapter interfaces, thus enabling easy encapsulation in adapter-based architectures. Other blocks, such as the `F_BYTE_TO_UINT`, operate at the signal level and require separate interfaces.

## Conclusion

The `AB_TO_AUI` is a compact and specialized composite function block for the unidirectional conversion of BYTE to UINT data using standardized adapter interfaces. It allows for seamless integration into adapter-based systems and reduces the effort required for manual data conversion. Thanks to the use of the IEC 61131-3 conversion block, its functionality is reliable and portable. This block is particularly suitable for applications that rely on loose coupling between data sources and sinks.
