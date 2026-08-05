# ALI_TO_AUDI
![ALI_TO_AUDI](./ALI_TO_AUDI.svg)
* * * * * * * * * *
## Introduction
The function block **ALI_TO_AUDI** is a composite block that converts an ALI adapter (LINT) into an AUDI adapter (UDINT). It serves as a unidirectional converter between two different data type adapters for the IEC 61499 profile interface. The conversion is performed using an internal block *F_LINT_TO_UDINT* from the IEC 61131 library.
## Interface Structure

The function block has no direct event or data inputs/outputs. All communication takes place via two adapter interfaces.

## **Event Inputs**

No dedicated event inputs are available. The event is received via the ALI adapter.

## **Event Outputs**

No dedicated event outputs are available. The result event is sent via the AUDI adapter.

### **Data Inputs**

No dedicated data inputs are available. The input data value is provided via the ALI adapter.

### **Data Outputs**

No dedicated data outputs are available. The converted data value is output via the AUDI adapter.

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|-----|-----------|--------------|

| ALI_IN | `adapter::types::unidirectional::ALI` | Socket (Input) | Returns the LINT value (64-bit signed) and the associated event. |

| AUDI_OUT | `adapter::types::unidirectional::AUDI` | Plug (Output) | Provides the converted UDINT value (32-bit unsigned) and the acknowledgment event. |

## Functionality

As soon as the ALI_IN adapter receives an event (E1), the associated LINT data value (D1) is read. This data value is passed to the internal function block *F_LINT_TO_UDINT*, which converts it into a UDINT value. After successful conversion, the internal function block sends an acknowledgment event (CNF), which is forwarded via the AUDI_OUT adapter (E1). Simultaneously, the converted UDINT value (OUT) is passed to the AUDI_OUT adapter (D1).

The conversion from LINT (64-bit signed) to UDINT (32-bit unsigned) is unsigned and can lead to overflows or information loss for values outside the UDINT range (0 … 4,294,967,295).

## Technical Features
- **Composite Function Block**: The function block consists of an internal network with a single conversion block.
- **Unidirectional Adapter-to-Adapter Converter**: Data flows only from ALI_IN to AUDI_OUT.
- **No State Logic**: The function block has no internal state machine; the conversion occurs deterministically with each event.

## State Overview

The function block does not have its own state machine. The state is determined solely by the internal block *F_LINT_TO_UDINT*, which performs a one-time conversion with each REQ event and immediately delivers the result.

## Application Scenarios
- **System Integration**: When one system component (e.g., sensor, drive) provides an ALI adapter (LINT), while another component expects an AUDI adapter (UDINT).
- **Protocol Adaptation**: In heterogeneous control environments where different IEC 61499 adapter profiles for integers are used.
- **Migration**: Exchange of 64-bit LINT values for 32-bit UDINT values, provided the value range limits are respected.

## Comparison with Similar Function Blocks
- **F_LINT_TO_UDINT (direct)**: This function block performs pure data conversion without an adapter. *ALI_TO_AUDI* encapsulates this function in an adapter-based interface.
- **ALI_TO_xxx/Converter**: Other adapter converters (e.g., ALI_TO_BOOL, ALI_TO_REAL) use analogous mechanisms but differ in target type and value range.

## Conclusion

The *ALI_TO_AUDI* function block is a lean composite function block for simple adapter conversion from LINT to UDINT. It utilizes an existing IEC 61131 component and extends it with a standardized IEC 61499 adapter interface. This facilitates integration into existing systems without requiring the underlying conversion logic to be reimplemented.