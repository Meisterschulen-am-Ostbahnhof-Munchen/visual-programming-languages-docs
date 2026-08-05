# ADI_TO_AULI
![ADI_TO_AULI](./ADI_TO_AULI.svg)

* * * * * * * * * *
## Introduction
The **ADI_TO_AULI** function block is a composite function block (FB) according to IEC 61499. It converts a DINT value (signed 32-bit integer) received via an ADI adapter (input interface) into a ULINT value (unsigned 64-bit integer) output via an AULI adapter (output interface). Internally, the standardized conversion block `F_DINT_TO_ULINT` from the IEC 61131 library is used. This function block simplifies the integration of adapters and type conversion in automation solutions.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|-------------|-----|--------------|

| ADI_IN.E1 | Event (implicit) | Trigger for conversion; provided by the ADI adapter. |

### **Event Outputs**

| Name | Type | Description |

|-------------|-----|--------------|

| AULI_OUT.E1 | Event (implicit) | Signals completion of conversion; passed to the AULI adapter. |

### **Data Inputs**

| Name | Type | Description |

|-------------|-------|--------------|

| ADI_IN.D1 | DINT | Input value to be converted to ULINT. |

### **Data Outputs**

| Name | Type | Description |

|-------------|--------|-------------|

| AULI_OUT.D1 | ULINT | Converted output value (unsigned). |

### **Adapter**

| Name | Type (Interface) | Direction | Description |

|-----------|-----------------------|-----------|--------------|

| ADI_IN | ADI (Socket) | Input | Receives the DINT value via a unidirectional ADI adapter. |

| AULI_OUT | AULI (Plug) | Output | Provides the converted ULINT value via a unidirectional AULI adapter. |

## Functionality
The function block waits for an event at the input adapter `ADI_IN.E1`. As soon as this event arrives, the current data value `ADI_IN.D1` (type DINT) is passed to the internal conversion function block `F_DINT_TO_ULINT`. After successful conversion, the result (type ULINT) is forwarded to the output `AULI_OUT.D1`, and an event is triggered at the output `AULI_OUT.E1`. The entire logic is purely combinational – there are no delays or states other than the signal processing of the internal module.

## Technical Features
- **Adapter-Based Interface:** The module uses only adapter plugs and sockets for input and output. This allows for clean encapsulation and reuse in modular control architectures.
- **Unidirectional Adapters:** Both the ADI and AULI adapters are declared as unidirectional and transmit only in one direction (input or output).
- **Internal Conversion:** The function block `F_DINT_TO_ULINT`, responsible for the actual conversion, is taken from the package `iec61131::conversion` and provides a standardized, sequence-invariant function.
- **Namespace:** The composite function block belongs to the package `adapter::conversion::unidirectional`, which clearly indicates its role as an adapter wrapper.

## State Overview
As a composite function block, `ADI_TO_AULI` does not have its own state machine. Its behavior is entirely determined by the internal linking of event and data flows between the socket `ADI_IN`, the conversion function block, and the plug `AULI_OUT`. The state logic of the internal function block `F_DINT_TO_ULINT` is transparent to its operation.

## Application Scenarios
- **Transition between control systems:** When a system with DINT signals (e.g., PLC data) needs to communicate with another system that expects ULINT values (e.g., visualization or long-term archiving with 64-bit timestamps).
- **Adapter bridge:** In a modular automation environment where adapters for different data types are defined, this function block serves as a simple "translation link" between ADI and AULI interfaces.
- **Prototypes or migration:** Rapid integration of components with different integer representations without application-specific conversion logic.

## Comparison with similar function blocks
- **Separate `F_DINT_TO_ULINT`:** The internal function block used here is directly responsible for the pure type conversion but requires separate event and data connections. `ADI_TO_AULI` encapsulates these connections and the adapter interface in a single block.
- **Other Adapter Wrappers:** Similar composite blocks exist for other type conversions (e.g., `ADI_TO_AUDI`, `ASI_TO_AULI`), which are structured according to the same pattern. They differ only in the data types involved.
- **Direct Type Conversion Without Adapters:** Some systems offer conversion functions as pure function blocks without an adapter layer. The present block is specifically designed for use with adapters.

## Conclusion
The `ADI_TO_AULI` block is a compact, adapter-based wrapper for converting DINT to ULINT values. By cleanly separating adapter and conversion logic, it increases the reusability and readability of control programs. It is particularly suitable for modular automation solutions that rely on unidirectional adapters and require standardized type conversion.
