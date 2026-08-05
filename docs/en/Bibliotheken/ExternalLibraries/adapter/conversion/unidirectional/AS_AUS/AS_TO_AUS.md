# AS_TO_AUS
![AS_TO_AUS](./AS_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The function block **AS_TO_AUS** is a composite block that connects an AS adapter (type `adapter::types::unidirectional::AS`) to an AUS adapter (type `adapter::types::unidirectional::AUS`) and converts the data values contained within from `SINT` (signed 8-bit) to `USINT` (unsigned 8-bit). The conversion is performed by the embedded standard function block `F_SINT_TO_USINT` from the IEC 61131 library. This function block enables simple, adapter-based data type conversion in industrial control applications.

## Interface Structure

### **Event Inputs**

No direct event inputs. Event control is handled exclusively via the `AS_IN` adapter (socket).

### **Event Outputs**

No direct event outputs. Event transmission is handled exclusively via the `AUS_OUT` adapter (plug).

### **Data Inputs**

No direct data inputs. Data acquisition is handled exclusively via the `AS_IN` adapter.

### **Data Outputs**

No direct data outputs. Data output is handled exclusively via the `AUS_OUT` adapter.

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Input) | Receives a SINT value and an event (E1). |

| `AUS_OUT` | `adapter::types::unidirectional::AUS` | Plug (Output) | Outputs the converted USINT value and an event (E1). |

## Functionality

The function block operates as a pure data flow converter:

1. An external event at socket `AS_IN.E1` triggers the conversion.

2. Simultaneously, the corresponding data value `AS_IN.D1` (SINT) is passed to the input `IN` of the internal block `F_SINT_TO_USINT`.

3. The conversion block converts the SINT value to the corresponding USINT value and places it at its output `OUT`.

4. The converter's completion event (`CNF`) triggers the event `AUS_OUT.E1` and passes the converted value to `AUS_OUT.D1`.

5. The output adapter makes the result available to the calling environment.

## Technical Features
- **Composite Block**: The function block (FB) does not contain its own state logic but combines the existing standard converter with the predefined adapter interfaces.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional – data and events flow in only one direction.
- **Type Conversion**: The conversion from SINT to USINT is lossless, as the value range of USINT (0…255) completely covers the positive part of SINT (−128…127). However, negative SINT values are interpreted as follows: e.g., −1 becomes 255 (two's complement). This behavior corresponds to the IEC 61131 function `SINT_TO_USINT`.

## State Overview

The FB does not have an internal state machine (ECC). The entire sequence control is implemented through event chaining in the network.

## Application Scenarios
- **Sensor Integration**: A sensor delivers a SINT value (e.g., temperature as a signed value), but the subsequent module expects USINT (e.g., for displays or logic with unsigned types).
- **System Coupling**: Between different control components that communicate via adapters, a signed representation must be converted to an unsigned representation.
- **Protocol Adaptation**: In fieldbus or OPC UA connections where the data formats are predefined.

## Comparison with Similar Function Blocks
- **F_SINT_TO_USINT**: This standard function block performs pure type conversion without an adapter. This function block encapsulates it in an adapter interface so that it can be directly integrated into adapter-based architectures.
- **Other Converters** (e.g., `F_INT_TO_DINT`): These work analogously, but for different data types. The advantage of `AS_TO_AUS` lies in its specific adapter adaptation for the AS and AUS types.

## Conclusion

The function block `AS_TO_AUS` is a practical tool for type conversion in adapter-based 4diac applications. It simplifies the integration of components that use different signed and unsigned 8-bit data types and enables a clean separation of the adapter interfaces. Thanks to the use of the established IEC converter, the functionality is reliable and standards-compliant.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
