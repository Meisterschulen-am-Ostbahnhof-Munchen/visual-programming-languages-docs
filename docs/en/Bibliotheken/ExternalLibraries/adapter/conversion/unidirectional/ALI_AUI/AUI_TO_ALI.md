# AUI_TO_ALI

![AUI_TO_ALI](./AUI_TO_ALI.svg)

* * * * * * * * * *

## Introduction

The AUI_TO_ALI function block is a composite function block that converts an AUI adapter (UINT) into an ALI adapter (LINT). Internally, it uses the IEC 61131 function block F_UINT_TO_LINT for the conversion.

## Interface Structure

### **Event Inputs**

- **AUI_IN.E1** (Event via Socket AUI_IN): Starts the conversion when an event is present at the socket (via the AUI adapter).

### **Event Outputs**

- **ALI_OUT.E1** (Event via Plug ALI_OUT): Outputs the output after the conversion is complete (via the ALI adapter).


### **Data Inputs**

- **AUI_IN.D1** (Data via Socket AUI_IN): UINT value to be converted to a LINT value.

### **Data Outputs**

- **ALI_OUT.D1** (Data via Plug ALI_OUT): Converted LINT value.

### **Adapters**

- **Socket AUI_IN** (Type: adapter::types::unidirectional::AUI): Receives UINT data and the associated event.

- **Plug ALI_OUT** (Type: adapter::types::unidirectional::ALI): Sends the converted LINT data and the associated event.

## Functionality

The function block waits for an event at the input adapter AUI_IN (E1). As soon as this event arrives, the incoming UINT value (D1) is forwarded to the internal conversion block F_UINT_TO_LINT. The conversion is performed according to the IEC 61131 standard, converting the unsigned UINT value into a signed LINT value (64-bit integer). After the conversion is complete, the output event is triggered at the ALI_OUT adapter (E1), and the converted LINT value is passed to ALI_OUT.D1.

## Technical Features

- The function block (FB) is implemented as a composite type and encapsulates the conversion logic in a reusable adapter interface.

- Uses the standardized function block F_UINT_TO_LINT from the IEC 61131 library.

- License: Eclipse Public License 2.0 (EPL-2.0).

- Developed by HR Agrartechnik GmbH (Version 1.0, 2026-02-17).


## State Overview

The function block (FB) does not have its own state machine, as it passively maps the states of the internal block as a composite. The internal F_UINT_TO_LINT operates according to a simple scheme: wait for the REQ event, process the conversion, and trigger the CNF event.

## Application Scenarios

- Integration of a system that provides UINT values via an AUI adapter into a system that expects LINT values via an ALI adapter.

- Data bridge between different adapter types in a distributed controller.

- Extension of 4diac applications when type conversion between UINT and LINT is required.

## Comparison with Similar Function Blocks

Analogous adapter conversion blocks exist for other data types (e.g., UINT_TO_DINT, UINT_TO_REAL, etc.). The AUI_TO_ALI function block is specifically designed for combining the unidirectional AUI and ALI adapters, enabling a unified adapter interface without additional manual conversion.

## Conclusion

The composite function block AUI_TO_ALI offers a simple and reliable way to convert UINT data via AUI adapters to LINT data via ALI adapters. It is well-encapsulated, uses standard function blocks, and can be easily integrated into 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]