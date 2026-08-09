# AX_TO_AULI

![AX_TO_AULI](./AX_TO_AULI.svg)

* * * * * * * * * *
## Introduction

The function block **AX_TO_AULI** is a composite block for converting a BOOL adapter signal (type `AX`) into a ULINT adapter signal (type `AULI`).
It encapsulates the type-safe conversion of a binary value into an unsigned 64-bit integer, thus enabling the easy integration of BOOL interfaces into ULINT-based control logic.

The function block is provided in the package `adapter::conversion::unidirectional` and is based on the standardized conversion function block `F_BOOL_TO_ULINT` from the IEC 61131 library.

## Interface Structure

### **Event Inputs**

No dedicated event inputs.

Event control is handled via the connected adapters (see section **Adapters**).

### **Event Outputs**

No dedicated event outputs.

Result events are provided via the output adapter (see section **Adapters**).

### **Data Inputs**

No dedicated data inputs.

The data to be converted is received via the input adapter (see section **Adapters**).

### **Data Outputs**

No dedicated data outputs.

The converted result is provided via the output adapter (see section **Adapters**).

No dedicated data outputs.

The converted result is provided via the output adapter (see section **Adapters**).

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket | `AX_IN` | `adapter::types::unidirectional::AX` | BOOL adapter input. Provides input data via the event `E1` and the date `D1` (BOOL value). |
| Plug | `AULI_OUT` | `adapter::types::unidirectional::AULI` | ULINT adapter output. Outputs the conversion result via the event `E1` and the date `D1` (ULINT value).

## Functionality

The function block contains an internal network consisting of a single instance of the conversion function block `F_BOOL_TO_ULINT`.

The connections are as follows:

1. **Event Handling**:
- The event `AX_IN.E1` (from the input adapter) is passed to the event input `Convert.REQ` and starts the conversion.
- After the conversion is complete, the event `Convert.CNF` is passed to the event output `AULI_OUT.E1` to finally update the output adapter.
2. **Data Flow**:
- The Boolean value of `AX_IN.D1` is mirrored to the data input `Convert.IN`.
- The converted ULINT value of `Convert.OUT` is transferred to `AULI_OUT.D1`.

Thus, on each rising edge of the input event, the current BOOL value is converted to a ULINT value (BOOL → 0 → 0 ULINT, BOOL → 1 → 1 ULINT) and made available via the output adapter.

## Technical Specifications

- **License**: The source code is licensed under the Eclipse Public License 2.0 (EPL-2.0).
- **Author**: Developed by **Franz Höpfinger** for **HR Agrartechnik GmbH** (Version 1.0, dated 2026-02-17).
- **Package Structure**: The module is organized in the package `adapter::conversion::unidirectional`.
- **Dependencies**: It imports the module `iec61131::conversion::F_BOOL_TO_ULINT`.
- **Type Safety**: The use of adapters ensures strict type checking at design time.

## State Overview

The composite module does not have its own state machine.

The entire sequence control is implemented by the internal module `F_BOOL_TO_ULINT`, which implements a simple event-driven state machine:

- In its idle state, it waits for a `REQ` event.
- Upon arrival of the event, the conversion is performed and the output is immediately confirmed with `CNF`.

## Application Scenarios

- **Integration of binary sensors** into controllers that expect ULINT values (e.g., counter registers, addressing logic).
- **Adapter bridging** in heterogeneous systems where a BOOL adapter (e.g., from a switch) needs to be adapted to a ULINT adapter (e.g., a profile/parameter interface).
- **Type-safe conversion** in composite function blocks to standardize the handling of different data types in an application.

## Comparison with Similar Function Blocks

- **F_BOOL_TO_ULINT**: The underlying basic function block – it offers pure conversion without adapter encapsulation.
- **AX_TO_UDINT**, **AX_TO_DINT**: Analogously structured composite function blocks for other target data types (UDINT, DINT).
- **Direct Type Conversion**: Numerous standard conversion function blocks exist in the IEC 61131 environment; this one specializes in the adapter interface.

## Conclusion

The **AX_TO_AULI** function block is a compact, type-safe, and easily reusable solution for converting a BOOL adapter to a ULINT adapter.

It simplifies the hierarchical structuring of applications and enables a clear separation between data sources and sinks. Thanks to its EPL 2.0 licensing, it can be freely integrated into custom projects.
