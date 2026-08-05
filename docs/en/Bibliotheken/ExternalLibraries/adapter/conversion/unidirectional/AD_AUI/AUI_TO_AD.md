# AUI_TO_AD
![AUI_TO_AD](./AUI_TO_AD.svg)
* * * * * * * * * *
## Introduction
The function block **AUI_TO_AD** is a composite function block (FB) that converts an AUI adapter (UINT data type) into an AD adapter (DWORD data type). It serves as a unidirectional conversion interface within an IEC 61499-based control application. The block is implemented as an encapsulation of the standard converter `F_UINT_TO_DWORD` from the library `iec61131::conversion` and enables adapter-based data transfer.
## Interface Structure

### **Event Inputs**

| Name | Description |

|------|--------------|

| AUI_IN.E1 | Event from the AUI adapter that triggers the conversion. |

### **Event Outputs**

| Name | Description |

|------|--------------|

| AD_OUT.E1 | Event to the AD adapter that signals the availability of the converted value. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| AUI_IN.D1 | UINT | Input value from the AUI adapter that is converted to a DWORD value. |

### **Data Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| AD_OUT.D1 | DWORD | Output value that passes the converted DWORD value to the AD adapter. |

### **Adapter**

| Type | Name | Role |

|-----|------|-------|

| `adapter::types::unidirectional::AUI` | AUI_IN | Socket – Input adapter for the UINT value and the associated event. |

| `adapter::types::unidirectional::AD` | AD_OUT | Plug – Output adapter for the converted DWORD value and the confirmation event. |

## Functionality

The function block **AUI_TO_AD** operates as an encapsulation of the function block `F_UINT_TO_DWORD`. As soon as an event arrives at the event input `AUI_IN.E1`, the connected internal converter `Convert` is called. This converter reads the value from the data input `AUI_IN.D1` (type UINT) and converts it into a DWORD value. The result is provided at the data output `AD_OUT.D1`. Simultaneously, after successful conversion, an event is generated at the output `AD_OUT.E1`, which signals completion to the downstream AD adapter.

The conversion is performed according to the IEC 61131-3 standard for the function `UINT_TO_DWORD`. The value range of the UINT input (0 to 65535) is mapped to the lower 16 bits of the DWORD output; the upper 16 bits are padded with zeros.

## Technical Features
- The function block is implemented as a composite function block (FB) and does not contain its own state machines (ECCs). Its behavior is entirely determined by the integrated converter `F_UINT_TO_DWORD`.
- The connection between the adapters and the internal converter is established via event and data connections.
- The function block is designed for unidirectional data transfer – there is no reverse conversion from AD to AUI.
- The package name (`packageName`) is `adapter::conversion::unidirectional`, indicating a clear structure of the conversion adapters.

## State Overview

As a composite function block, **AUI_TO_AD** does not have its own state machine. The functional sequence is purely event-driven: An event at the input triggers the conversion, after which an event is generated at the output. There are no internal states between these events.

-
## Application Scenarios
- **Data Integration**: An AUI adapter provides a UINT value (e.g., from a sensor module) that is required in a system that processes only DWORD addresses (e.g., via an AD adapter).
- **Protocol Adaptation**: If existing components work with different data types, this function block can be used as a simple converter between the adapter interfaces.
- **Modularization**: Within a 4diac application, standardized conversion function blocks can be grouped as adapters to increase reusability.

## Comparison with Similar Function Blocks

Comparable conversion function blocks exist for other data types, e.g., `WORD_TO_DWORD`, `BYTE_TO_DWORD`, or generic `TO_DWORD` functions. The unique feature of **AUI_TO_AD** lies in the encapsulation of the adapter protocols: Instead of a direct data connection, the values are provided via adapters, enabling loose coupling between the components. Unlike a direct call to `F_UINT_TO_DWORD` in an application, this function block offers a standardized, reusable interface at the adapter level.

## Conclusion

The **AUI_TO_AD** function block provides a clean, adapter-based solution for converting UINT to DWORD values. It is easy to use, requires no custom programming, and integrates seamlessly into the 4diac environment with its event and adapter networks. The encapsulation of the standard converter ensures robust and standards-compliant functionality. This function block is particularly suitable for applications where different adapter types need to be harmonized.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
