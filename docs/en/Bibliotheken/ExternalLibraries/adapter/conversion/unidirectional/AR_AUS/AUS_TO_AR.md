# AUS_TO_AR
![AUS_TO_AR](./AUS_TO_AR.svg)

* * * * * * * * * *
## Introduction
The function block **AUS_TO_AR** is a composite FB for converting an AUS adapter interface (based on USINT) to an AR adapter interface (based on REAL). According to its description, it serves to convert between these two adapter types. The current implementation (version 1.0) simply passes through event and data values without performing an explicit conversion – the actual type conversion must be implemented either through the adapter definitions themselves or through subsequent extensions.
## Interface Structure
### **Event Inputs**
No separate event inputs are available. Events are transmitted exclusively via the **AUS_IN** adapter.

### **Event Outputs**
No separate event outputs are available. Events are output exclusively via the **AR_OUT** adapter.

### **Data Inputs**
No separate data inputs are available. Data is transmitted exclusively via the **OFF_IN** adapter.

### **Data Outputs**
No separate data outputs are available. Data is output exclusively via the **AR_OUT** adapter.

### **Adapters**

| Type | Name | Direction | Comment |
|---|---|---|---|
| `adapter::types::unidirectional::AUS` | OFF_IN | Socket (Input) | USINT-based adapter input |
| `adapter::types::unidirectional::AR` | AR_OUT | Plug (Output) | REAL-based adapter output |

## Functionality

This function block directly connects the event and data channels of the AUS_IN adapter to those of the AR_OUT adapter:

- **Event Forwarding**: The event arriving at socket `AUS_IN.E1` is forwarded without delay to plug `AR_OUT.E1`.
- **Data Forwarding**: The data value (type USINT) provided by socket `AUS_IN.D1` is passed directly to `AR_OUT.D1` (type REAL).

Since no type conversion or other processing is implemented in the network, the conversion from USINT to REAL is either implicitly handled by the 4diac runtime environment or must be implemented by adding a conversion function block (e.g., `CONV`) within an extension of the composite function block.

## Technical Features
- **Composite without internal logic**: The function block network consists exclusively of two direct connections; it contains no other function blocks or state machines.
- **Adapter-based interface**: Instead of individual event/data inputs and outputs, all communication is handled via standardized unidirectional adapters. This facilitates reuse in modular adapter hierarchies.
- **Incomplete implementation**: The block's name and comment suggest active conversion, which is not implemented in the current version (1.0). This can lead to runtime errors if the runtime environment does not support implicit type conversion.

## State overview

The block does not contain any state machines (ECCs). Its behavior is purely combinatorial and limited to the immediate forwarding of events and data.

## Application Scenarios
- **Replacement for legacy systems**: An existing AUS adapter interface (USINT) needs to be connected to a component that expects an AR adapter interface (REAL).
- **Placeholder during the development phase**: The function block serves as a temporary connection until actual conversion logic is implemented.
- **Test environments**: Fast coupling of two adapter types without data modification for simulations or tests.

## Comparison with similar function blocks
Typical conversion function blocks (e.g., `CONV` from the standard library) perform explicit value conversion using arithmetic or logical operations. `AUS_TO_AR`, on the other hand, delegates the conversion to the adapter level and does not perform any transformation itself. It is more of a **structural adaptation** than a true converter.

## Conclusion

The function block `AUS_TO_AR` is a simple adapter-to-adapter through-pass block. Its usefulness depends heavily on whether the target system supports automatic type conversions between USINT and REAL. If not, the function block must be extended with explicit conversion logic. It is therefore suitable as a temporary solution or as a foundation for a complete implementation.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
