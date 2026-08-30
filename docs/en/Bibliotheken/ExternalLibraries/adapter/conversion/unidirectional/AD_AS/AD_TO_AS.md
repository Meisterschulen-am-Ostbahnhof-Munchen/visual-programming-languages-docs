# AD_TO_AS

![AD_TO_AS](./AD_TO_AS.svg)

* * * * * * * * * *

## Introduction

The **AD_TO_AS** function block is a composite block for converting a DWORD adapter (type `AD`) into a SINT adapter (type `AS`). It enables data conversion between different adapter standards within the 4diac IDE and is provided in version 1.0.
The internal conversion is performed via the IEC 61131 block `F_DWORD_TO_SINT`.

## Interface Structure

### **Event Inputs**

No direct event inputs.

The block receives events exclusively via the adapter socket **AD_IN** (event port E1 of the AD adapter).

### **Event Outputs**

No direct event outputs.

The function block sends events exclusively via the adapter plug **AS_OUT** (event port E1 of the AS adapter).

### **Data Inputs**

No direct data inputs.

The function block receives data exclusively via the adapter socket **AD_IN** (data port D1 of the AD adapter, data type **DWORD**).

### **Data Outputs**

No direct data outputs.

The function block sends data exclusively via the adapter plug **AS_OUT** (data port D1 of the AS adapter, data type **SINT**).

### **Adapter**

- **Socket AD_IN**:

Type: `adapter::types::unidirectional::AD`

Description: Receives a DWORD value and an associated event.

- **Plug AS_OUT**:

Type: `adapter::types::unidirectional::AS`

Description: Sends a SINT value and an associated event.

## Functionality

The function block operates in an event-driven manner:

1. An event at socket **AD_IN.E1** triggers processing.
2. The internal block `Convert` (type `F_DWORD_TO_SINT`) is started. It receives the DWORD value from **AD_IN.D1** at its input `IN` and performs the conversion to a SINT value.
3. After the conversion is complete, `Convert` signals an event via its output `CNF`.
4. This event is forwarded to the plug **AS_OUT.E1**, and simultaneously the converted SINT value from `Convert.OUT` is passed to **AS_OUT.D1**.

This establishes a complete, unidirectional coupling between the AD and AS adapters.

## Technical Features

- **Bit-reinterpretation**, value-preserving only if the source value fits the narrower destination width (otherwise the upper bits are silently dropped).

- **Value Range Loss**: Converting DWORD (32-bit, unsigned) to SINT (8-bit, signed) can result in data loss. Only the lower 8 bits of the DWORD are used; the SINT value range is between -128 and +127.
- **Library Used**: The function block uses the IEC 61131 conversion function `F_DWORD_TO_SINT`, which is defined in the package group `iec61131::conversion`.
- **Unidirectional Data Flow**: The function block only allows data flow in one direction (from AD to AS) and has no feedback.

## State Overview

Since this is a composite function block, there is no explicit internal state machine. The process can be described as a simple state sequence as follows:

- **WAIT**: The function block waits for an event at socket AD_IN.
- **CONVERT**: After receiving the event, the conversion `F_DWORD_TO_SINT` is performed.
- **SEND**: After the conversion is complete, the output event is sent to plug AS_OUT, and the data value is passed on.

This returns the function block to the **WAIT** state.

## Application Scenarios

- **Data Conversion Between Different Adapter Types**: If a sending module provides a DWORD value (e.g., a 32-bit counter reading) via an AD adapter, but the receiver expects a SINT value via an AS adapter, this module is used for mediation.
- **Event-Driven Signal Conditioning**: In control applications where events must be transmitted asynchronously between adapters, `AD_TO_AS` serves as a bridge for type conversion.

## Comparison with Similar Modules

- **AD_TO_INT / AD_TO_BYTE**: Analog conversion modules that convert DWORD values to other integer types (e.g., INT, BYTE).
- **AD_TO_INT / AD_TO_BYTE**: Analog conversion modules that convert DWORD values to other integer types (e.g., INT, BYTE). - **Direct Type Conversion**: Unlike using a simple `F_DWORD_TO_SINT` as an embedded function block, `AD_TO_AS` offers complete adapter encapsulation, allowing the interfaces to be integrated into a 4diac system without additional connection logic.

## Conclusion

The **AD_TO_AS** function block provides a compact and standardized solution for converting DWORD to SINT data in an event-driven adapter environment. By utilizing the IEC 61131 library function and its clear, event-based execution, it is reliable and easily integrated into existing control projects. The unidirectional structure limits its application to a simple data flow, which is sufficient for many use cases.

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
