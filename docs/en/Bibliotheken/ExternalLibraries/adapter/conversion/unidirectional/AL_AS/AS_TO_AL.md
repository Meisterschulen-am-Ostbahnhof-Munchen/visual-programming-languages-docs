# AS_TO_AL

![AS_TO_AL](./AS_TO_AL.svg)

* * * * * * * * * *
## Introduction

The function block **AS_TO_AL** is a composite block that converts a SINT adapter (AS) into an LWORD adapter (AL). It serves as a bridge between different adapter types in a unidirectional communication path. The block encapsulates the conversion logic and makes it usable for the user as a single, integrated unit.
## Interface Structure

The block has **no direct event or data interfaces** at the top level. All input and output is handled via adapters.

### **Event Inputs**

- None (Events are passed in via the AS_IN socket adapter)

### **Event Outputs**

- None (Events are output via the AL_OUT plug adapter)

### **Data Inputs**

- None (Data is provided via the AS_IN socket adapter)

### **Data Outputs**

- None (Data is provided via the AL_OUT plug adapter)

### **Adapters**

| Name | Type | Direction | Description |
|--------|----------------------------------------|----------|----------------------------------|
| AS_IN | adapter::types::unidirectional::AS | Socket | SINT adapter (input) |
| AL_OUT | adapter::types::unidirectional::AL | Plug | LWORD adapter (output) |

## Functionality

The function block internally uses the IEC 61131 conversion block **F_SINT_TO_LWORD**. As soon as an event arrives at the event output **E1** of the socket adapter **AS_IN**, it is forwarded to the input **REQ** of the conversion block. This converts the SINT data value from **AS_IN.D1** into an LWORD value and outputs it to **AL_OUT.D1**. After successful conversion, an acknowledgment event is sent to the event input **E1** of the plug adapter **AL_OUT**.

## Technical Specifications

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Standard Compliance**: Complies with IEC 61499-2.
- **Copyright**: The function block is subject to the Eclipse Public License 2.0 (Copyright 2026 HR Agrartechnik GmbH).
- **Version**: 1.0, created by Franz Höpfinger on February 17, 2026.
- **Package Structure**: Organized in the package `adapter::conversion::unidirectional`.
- **Dependencies**: Uses the function block `iec61131::conversion::F_SINT_TO_LWORD`.

## State Overview

Since this is a composite function block, it does not have its own state machine. The state logic is implemented by the integrated function block **F_SINT_TO_LWORD**, which performs a simple conversion internally without delay or error states. Execution is strictly event-driven.

## Application Scenarios

- **Adapter Conversion**: Connecting components that provide a SINT adapter with components that expect an LWORD adapter.
- **Data Adaptation**: Used in heterogeneous automation systems where different data types need to be harmonized at the adapter level.
- **Modular Reuse**: The function block can be included in libraries for unidirectional conversions.

## Comparison with Similar Function Blocks

Similar adapter conversion blocks exist for other data types (e.g., BOOL, INT, DWORD). The **AS_TO_AL** block is specifically designed for converting **SINT** (Signed Short Integer, 8-bit) to **LWORD** (Long Word, 64-bit). Unlike generic function blocks, the conversion is performed directly at the adapter level, simplifying network wiring.

## Conclusion

The **AS_TO_AL** composite block offers a compact and standards-compliant solution for converting a SINT adapter to an LWORD adapter. Encapsulating the conversion logic improves the clarity of the application network and promotes reusability. This block is particularly well-suited for modular automation projects where different data types need to be combined at the adapter level.
