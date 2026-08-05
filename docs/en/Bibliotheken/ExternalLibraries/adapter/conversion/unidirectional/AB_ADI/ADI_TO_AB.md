# ADI_TO_AB
![ADI_TO_AB](./ADI_TO_AB.svg)
* * * * * * * * * *
## Introduction
The function block `ADI_TO_AB` serves as a composite module for converting a 32-bit integer value (DINT) into a byte value (BYTE). It encapsulates the conversion between two unidirectional adapters: the **ADI adapter** (input) and the **AB adapter** (output). The module is used to transfer data from a DINT adapter to a BYTE adapter without requiring the user to implement the actual conversion logic.
## Interface Structure

### **Event Inputs**

The module does not have direct event inputs. Event reception is handled via the **ADI_IN socket adapter**:

| Adapter Port | Type | Description |

|--------------|------------|----------------------------------------|

| ADI_IN.E1 | Event | Starts the conversion at the input. |

### **Event Outputs**

Event output is also handled exclusively via the **AB_OUT plug adapter**:

| Adapter Port | Type | Description |

|--------------|------------|--------------------------------------|

| AB_OUT.E1 | Event | Signals that the value has been converted and is ready at the output. |

### **Data Inputs**

The data is provided via the ADI_IN adapter:

| Adapter Port | Type | Description |

|--------------|------|----------------------------------|

| ADI_IN.D1 | DINT | 32-bit integer input value. |

### **Data Outputs**

The converted data is output via the AB_OUT adapter:

| Adapter Port | Type | Description |

|--------------|------|-------------------------------|

| AB_OUT.D1 | BYTE | 8-bit byte output value. |

### **Adapters**

| Name | Direction | Adapter Type | Description |
|---------|----------|------------------------------------------|--------------------------------|

| ADI_IN | Socket | `adapter::types::unidirectional::ADI` | DINT adapter as input. |

| AB_OUT | Plug | `adapter::types::unidirectional::AB` | BYTE adapter as output. |

## Functionality

Internally, the function block uses the predefined IEC 61131-3 function block `F_DINT_TO_BYTE` to perform the actual data type conversion. The event and data flows are as follows:

1. An event at **ADI_IN.E1** triggers the conversion.

``` 2. The data value from **ADI_IN.D1** is forwarded to the input `IN` of the internal `F_DINT_TO_BYTE` function block.

3. After the conversion is complete, the internal function block generates the event **CNF**.

4. This event is output as **AB_OUT.E1**.

5. Simultaneously, the converted value is available at the output `OUT` of the internal function block and is output via **AB_OUT.D1**.

All the logic is encapsulated in a composite function block, so the user only needs to connect the adapters.

## Technical Features
- **Composite Function Block**: The function block consists of an internal network and does not have its own state machine (ECC). It performs the conversion strictly event-driven.
- **Use of IEC 61131-3 standard function blocks**: Conversion is performed using the standardized function block `F_DINT_TO_BYTE`, ensuring portability and compliance with industry standards.
- **Adapter-based input/output**: All data and events are routed via adapters – not individual ports. This simplifies integration with similar adapter interfaces in the 4diac environment.

## State Overview

Since this is a composite function block without its own state machine, there are no explicit states. The function block reacts to the incoming event, converts the value, and outputs the result. After outputting the result, it is immediately ready for another conversion.

## Application Scenarios
- **Data Protocol Adaptation**: When a sensor or controller delivers DINT values, but the connected device or communication channel expects BYTE values.
- **Adapter Mediation**: In a modular architecture that allows the exchange of adapters with different data types without having to rewrite the connection logic each time.
- **Interface Coupling**: Between components that use unidirectional adapters, e.g., in a pipeline structure.

## Comparison with Similar Components

There are numerous conversion components for direct data type conversions (e.g., `F_DINT_TO_INT`, `F_DINT_TO_WORD`). The `ADI_TO_AB` differs in that it uses complete adapters instead of individual data and event ports. This improves encapsulation and increases reusability. A similar concept exists for other data type pairs (e.g., `ADI_TO_AC` for DINT to CHAR) that follow the same design logic.

## Conclusion

The function block `ADI_TO_AB` offers a cleanly encapsulated, adapter-based conversion of DINT to BYTE values. It uses standard IEC function blocks and event-driven control, allowing for seamless integration into 4diac projects. Its adapter interfaces make it particularly suitable for modular and reusable control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
