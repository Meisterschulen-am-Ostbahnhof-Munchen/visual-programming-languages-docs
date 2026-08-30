# AR_TO_AUS

![AR_TO_AUS](./AR_TO_AUS.svg)

* * * * * * * * * *
The AR_TO_AUS function block is a composite block for converting a REAL value to a USINT value via a unidirectional adapter interface. It encapsulates the conversion process and provides a standardized connection between a REAL adapter socket and a USINT adapter plug. The function block is designed for use in automation systems that require data type conversion.

- **AR_IN.E1** (via socket `AR_IN`): Event to start the conversion of the incoming REAL value.
- **AUS_OUT.E1** (via Plug `AUS_OUT`): Event triggered after successful conversion and output of the USINT value.
- **AR_IN.D1** (via Socket `AR_IN`, Type: REAL): Input value to be converted to USINT.
- **AUS_OUT.D1** (via Plug `AUS_OUT`, Type: USINT): Converted output value.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **Socket AR_IN** (Type: `adapter::types::unidirectional::AR`): Unidirectional REAL input adapter.

## Functionality

The FB AR_TO_AUS functions as a pure data converter without its own state logic. Internally, the predefined block `F_REAL_TO_USINT` from the IEC 61131 standard library is used.

Process:

1. An incoming event at `AR_IN.E1` triggers processing.
2. The current value of `AR_IN.D1` (REAL) is passed to the input `IN` of the internal converter.
3. After the conversion is complete, the result value (USINT) is forwarded to `AUS_OUT.D1`.
4. Simultaneously, the event `AUS_OUT.E1` is triggered to activate downstream function blocks.

The entire data and event flow is unidirectional from the input to the output adapter.

- The function block is implemented as a composite and uses the function block `iec61131::conversion::F_REAL_TO_USINT` from the library `adapter::conversion::unidirectional`.
- No range check is performed; the conversion follows the rules of IEC 61131 (REAL → USINT: decimal places are truncated, values outside the range 0…255 may lead to undefined behavior).
- The function block does not have its own state machine and operates in an event-driven manner.
- The use of adapters enables loose coupling of the interfaces and facilitates reuse in different project contexts.

The function block AR_TO_AUS does not have its own state machine. The runtime behavior is entirely determined by the internal function block `F_REAL_TO_USINT`, which operates statelessly by default. Event control occurs directly from `AR_IN.E1` to `AUS_OUT.E1` without intermediate states.

- **Sensor-Actuator Coupling**: A REAL value (e.g., from an analog sensor) must be transmitted as a USINT to a binary actuator (e.g., a motor controller with an 8-bit value).
- **Interface Adaptation**: When an adapter of type `AR` (REAL) needs to be connected to an adapter of type `AUS` (USINT).
- **Data Preprocessing**: Before transferring data to systems that only accept USINT values (e.g., diagnostic or visualization components).
- **AR_TO_INT** / **AR_TO_BYTE**: Analogous structure for converting to other data types (INT, BYTE). This function block is limited to converting REAL to USINT.
- **Direct Converter Function Blocks** (e.g., `F_REAL_TO_USINT`): These do not offer adapter interfaces but require direct wiring. AR_TO_AUS encapsulates this converter and provides an ad-hoc adapter connection.
- **Bidirectional Converters**: In contrast to these, AR_TO_AUS operates strictly unidirectionally, which increases the clarity of the data flow.

The AR_TO_AUS function block offers a simple, modular solution for converting a REAL adapter to a USINT adapter. By using a standardized conversion block and encapsulating it as a composite function block, it can be easily integrated into existing 4diac projects. It is particularly suitable for scenarios requiring a clear separation of interfaces and unidirectional data transmission.

---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
