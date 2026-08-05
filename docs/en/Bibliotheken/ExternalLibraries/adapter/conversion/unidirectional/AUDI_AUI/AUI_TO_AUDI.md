# AUI_TO_AUDI

![AUI_TO_AUDI](./AUI_TO_AUDI.svg)

* * * * * * * * * *
## Introduction
The **AUI_TO_AUDI** function block is a composite function block that converts an AUI adapter (UINT) into an AUDI adapter (UDINT). It serves to transfer data and events from one adapter type to another, where the underlying data types differ (UINT → UDINT). The conversion is performed by simply passing the signals through, without any additional logic.

## Interface Structure
### **Event Inputs**

No dedicated event inputs: The function block has no direct event inputs. Events are received via the connected socket adapter **AUI_IN**.

#### **Event Outputs**

No dedicated event outputs: The function block has no direct event outputs. Events are sent via the connected plug adapter **AUDI_OUT**.

### **Data Inputs**
No dedicated data inputs: This function block has no direct data inputs. Data is received via the connected socket adapter **AUI_IN**.

### **Data Outputs**
No dedicated data outputs: This function block has no direct data outputs. Data is sent via the connected plug adapter **AUDI_OUT**.

### **Adapters**

| Name | Type | Direction | Comment |

|------|-----|----------|-----------|

| AUI_IN | `adapter::types::unidirectional::AUI` | Socket (Input) | Receives UINT data and associated event |

| AUDI_OUT | `adapter::types::unidirectional::AUDI` | Plug (Output) | Sends UINT data and associated event |


## Functionality

The function block internally connects the interfaces of the incoming AUI adapter with those of the outgoing AUDI adapter:

- **Event Connection**: The event `E1` of the AUI adapter is directly forwarded to the event `E1` of the AUDI adapter.

- **Data Connection**: The data value `D1` of the AUI adapter (type UINT) is directly transferred to the data value `D1` of the AUDI adapter (type UDINT). This involves an implicit type conversion from UINT (16 bits) to UDINT (32 bits).

The function block does not perform any logic or conversion of its own; it simply acts as a pass-through for adapters with different data types.


## Technical Features

- **Unidirectional Adapters**: Both the input and output adapters are unidirectional, meaning data and events flow only in one direction (from the socket to the plug).

- **Composite FB**: The function block is implemented as a composite function block (FB) that maps the adapter connections in the FBNetwork.

- **Implicit Type Conversion**: The conversion from UINT to UDINT occurs automatically within the data connection, based on the IEC 61499 data type rules.

- **Package Structure**: The function block belongs to the package `adapter::conversion::unidirectional`.

## State Overview
The function block does not have its own states or state machines. Its behavior results solely from the forwarding connection of the adapter interfaces.


## Application Scenarios

- **Adapter Adaptation**: If a system uses an AUI adapter (UINT) but expects an AUDI adapter (UDINT), this function block can be used as an intermediary converter.

- **Signal Forwarding**: Used in hierarchical systems where a unidirectional data flow from a smaller to a larger data type needs to be mapped.

- **Prototypical Integration**: Rapid coupling of components with different adapter types without additional logic.

## Comparison with Similar Function Blocks

- **AUI_TO_AUDI** performs pure type conversion without further processing.

- Similar function blocks like `AUDI_TO_AUI` would map the reverse direction (UDINT → UINT), possibly with data overflow handling.

- Other adapter converters (e.g., `BOOL_TO_BYTE`) follow the same pattern but differ in the data types used and the direction.


## Conclusion

The **AUI_TO_AUDI** block is a simple yet useful composite function block for converting a UINT-based AUI adapter to a UDINT-based AUDI adapter. It is particularly suitable for situations requiring unidirectional signal forwarding with implicit data type conversion, without the need for custom processing logic. Thanks to its clear structure, it can be easily integrated into existing 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]