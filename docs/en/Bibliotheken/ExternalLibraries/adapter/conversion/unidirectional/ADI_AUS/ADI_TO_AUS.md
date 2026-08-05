# ADI_TO_AUS
![ADI_TO_AUS](./ADI_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The ADI_TO_AUS function block acts as an adapter converter from a DINT adapter (ADI) to a USINT adapter (AUS). It converts a DINT value to a USINT value and enables the seamless integration of components with different data types in the 4diac IDE.
## Interface Structure
### **Event Inputs**
- **E1** (via ADI_IN): This event triggers the conversion.

### **Event Outputs**
- **E1** (via AUS_OUT): Signals the completion of the conversion and the availability of the output value.

### **Data Inputs**
- **D1** (via ADI_IN): The DINT value to be converted.

#
## ### **Data Outputs**
- **D1** (via AUS_OUT): USINT value, the result of the conversion.

### **Adapters**
- **ADI_IN**: Socket (input) of type `adapter::types::unidirectional::ADI`. Provides DINT data and events.
- **AUS_OUT**: Plug (output) of type `adapter::types::unidirectional::AUS`. Receives USINT data and events for further processing.

## Functionality
The function block is implemented as a composite FB. Upon an event at event input E1 (via ADI_IN), the corresponding DINT value is read from data input D1 and passed to the internal conversion block `F_DINT_TO_USINT`. This function block converts the value according to the IEC 61131 standard (e.g., by limiting it to the USINT range 0–255 or by type conversion). The result is output via data output D1, and an event at output E1 (via AUS_OUT) signals the availability of the new value.

## Technical Features
- The function block uses an IEC 61131-compliant conversion block for type conversion from DINT to USINT.
- It is a composite function block (nested block) that maps the logic in a network of a single Convert function block.
- Communication takes place exclusively via adapter interfaces, which enables modular encapsulation.
- During conversion, values outside the USINT range (0–255) can be truncated or limited to the maximum or minimum value (depending on the conversion block used).

## State Overview
Since the function block does not have its own state machine, its behavior is purely event-driven: It reacts to every incoming event with an immediate conversion and output. There are no internal states or delays.

## Application Scenarios
- Connecting a sensor that delivers DINT values to a controller that expects USINT.
- Integrating adapter-based components with different data types into a 4diac application.
- Migrating existing systems where data formats need to be adapted.

## Comparison with Similar Function Blocks
- A direct conversion function block like `F_DINT_TO_USINT` performs the same conversion but operates on standard inputs/outputs. The ADI_TO_AUS encapsulates the logic in adapter interfaces and is therefore specifically designed for adapter-based communication paths.
- This function block differs from other adapter converters due to the specific type combination DINT↔USINT.

## Conclusion

The ADI_TO_AUS is a practical building block for the seamless integration of DINT and USINT adapters in the 4diac IDE. Its simple, event-driven functionality and encapsulation as a composite function block make it flexible and easily maintainable. It is particularly suitable for projects that require a clear separation between adapter interfaces and conversion logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
