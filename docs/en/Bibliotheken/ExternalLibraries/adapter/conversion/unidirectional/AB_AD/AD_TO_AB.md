# AD_TO_AB

![AD_TO_AB](./AD_TO_AB.svg)

* * * * * * * * * *
## Introduction
The **AD_TO_AB** function block is a composite module for the unidirectional conversion of a 32-bit DWORD adapter (AD) to an 8-bit BYTE adapter (AB). It serves as a bridge between components designed for different data widths and encapsulates the necessary type conversion according to IEC 61131-3.

## Interface Structure
### **Event Inputs**
The module has no directly visible event inputs. Event control is handled via the **AD_IN** adapter.

#### **Event Outputs**
The module has no directly visible event outputs. Event feedback is provided via the **AB_OUT** adapter.


### **Data Inputs**
This function block has no directly visible data inputs. The DWORD value is provided via the **AD_IN** adapter.

### **Data Outputs**
This function block has no directly visible data outputs. The BYTE value is output via the **AB_OUT** adapter.

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| **AD_IN** | `adapter::types::unidirectional::AD` | Socket (Input) | Accepts a DWORD (32-bit) and an associated event (here `E1`). |

| **AB_OUT** | `adapter::types::unidirectional::AB` | Plug (Output) | Outputs a converted byte (8-bit) and an acknowledgment event (here `E1`). |

Both adapters are unidirectional. The exact signature of the adapters (number of event and data channels) corresponds to the types defined in the 4diac library.

## Functionality
The function block operates purely event-driven and encapsulates the conversion using the internal base function block **F_DWORD_TO_BYTE** from the IEC 61131-1 library.

1. An incoming event at **AD_IN.E1** triggers the call to the internal conversion function block via its input `REQ`.

2. The value from **AD_IN.D1** (DWORD) is forwarded to the converter's data input `IN`.

3. After the conversion is complete, the converter signals the readiness of the result with `CNF`.

4. This event is passed to **AB_OUT.E1**, and the converted BYTE value (from `OUT`) is output to **AB_OUT.D1**.

The conversion is performed according to IEC 61131-3: The least significant 8 bits of the incoming DWORD are interpreted as a BYTE.

## Technical Features

- The module is implemented as a composite, meaning it does not contain its own state machine but delegates all logic to the internal base module.

- Neither buffering nor error handling is implemented; data transfer occurs directly synchronously with the event.

- This module is designed for use in systems that require a clear separation between adapters for different data widths.

## State Overview
Since this is a pure composite module without its own state machine, there is no explicit state machine. Its behavior is entirely determined by the internal **F_DWORD_TO_BYTE** module, which has a simple wait state (IDLE) and a processing state.

## Application Scenarios

- **Connecting Sensors/Actuators**: A sensor delivers 32-bit raw data via an AD adapter, which, after conversion to an 8-bit value, is passed on to a downstream BYTE adapter.

- **Protocol Conversion**: In a communication chain, a DWORD interface is mapped to a BYTE interface, e.g., when integrating older fieldbus devices.

- **Data Width Reduction**: Targeted extraction of the least significant byte from a DWORD for subsequent processing steps.

## Comparison with Similar Function Blocks

| Function Block | Conversion | Direction | Adapter Type |

|----------|---------------|-----------|------------|

| AD_TO_AB | DWORD → BYTE | Unidirectional | AD ↔ AB |

| AD_TO_AW | DWORD → WORD | Unidirectional | AD ↔ AW |

| AW_TO_AB | WORD → BYTE | Unidirectional | AW ↔ AB |

The **AD_TO_AB** function differs in its specific target data width and the use of the corresponding adapters. It is specifically designed for systems that use standard unidirectional adapters.

## Conclusion
The composite block **AD_TO_AB** offers a simple, event-driven way to convert a DWORD adapter to a BYTE adapter. It cleanly encapsulates the type conversion and can be integrated into existing 4diac networks without its own state logic. Reusing the standardized **F_DWORD_TO_BYTE** block guarantees correct behavior according to IEC 61131-3.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]