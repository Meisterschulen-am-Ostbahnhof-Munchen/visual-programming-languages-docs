# AULI_TO_ALI

![AULI_TO_ALI](./AULI_TO_ALI.svg)

* * * * * * * * * *

## Introduction

The **AULI_TO_ALI** function block is a composite module that performs an adapter conversion from **AULI** (ULINT adapter) to **ALI** (LINT adapter). It converts an unsigned 64-bit integer value (ULINT) into a signed 64-bit integer value (LINT) and forwards it via the corresponding adapter interfaces.

## Interface Structure

### **Event Inputs**

Events are received via the incoming adapter **AULI_IN**:

- `E1` – Starts the conversion of the incoming ULINT value.

### **Event Outputs**

Events are sent via the outgoing adapter **ALI_OUT**:

- `E1` – Acknowledges the completed conversion and indicates that the LINT value is present at the output.

### **Data Inputs**

Data is provided via the incoming adapter **AULI_IN**:

- `D1` (Data type: ULINT) – The unsigned 64-bit value to be converted.

### **Data Outputs**

Data is output via the outgoing adapter **ALI_OUT**:

- `D1` (Data type: LINT) – The converted signed 64-bit value.

### **Adapters**

- **AULI_IN** (Socket) – Unidirectional adapter of type `adapter::types::unidirectional::AULI` for receiving ULINT values and associated events.
- **ALI_OUT** (Plug) – Unidirectional adapter of type `adapter::types::unidirectional::ALI` for outputting LINT values and associated events.

## Functionality

The module internally uses the IEC 61131 conversion module `F_ULINT_TO_LINT`. As soon as the event `E1` arrives at the **AULI_IN** adapter, the ULINT value present at `D1` is read and passed to the converter. After conversion, the resulting LINT value is passed to the **ALI_OUT** adapter, and simultaneously, the event `E1` is sent to its output. The data and event flows are strictly synchronized: Conversion only occurs on demand via the event `E1`.

## Technical Features

- **Adapter-Based Encapsulation**: The function block completely encapsulates the conversion logic behind standardized unidirectional adapters (AULI/ALI), allowing for easy integration into existing adapter-based data flows.
- **Composite Structure**: Because it is a composite function block, no separate state machine is required; the logic is implemented by linking the sub-function block `F_ULINT_TO_LINT`.
- **Type Safety**: The conversion from ULINT to LINT preserves the value range as long as the ULINT value is not greater than `LINT#9223372036854775807` (maximum LINT). Exceeding this limit results in undefined behavior (no error handling in the function block).

## State Overview

The function block does not have its own state machine. It reacts event-driven:

- **Waiting for event `E1`**: No activity.
- **During Conversion**: The internal function block `F_ULINT_TO_LINT` is executed (the duration depends on the clock cycle).
- **Output to `CNF`**: The event `E1` is sent at the output.

## Application Scenarios

- **Data type conversion in control systems** when a sensor or source delivers ULINT values, but the subsequent system expects LINT values (signed).
- **Adapter bridge** between components that communicate exclusively via AULI or ALI adapters, e.g., in modular automation architectures.
- **Integration into cross-device data flows** without changing the actual application logic.

## Comparison with similar components

Similar adapter conversions exist for other data types, e.g., `UINT_TO_INT` or `UDINT_TO_DINT`. The **AULI_TO_ALI** module specializes in 64-bit integers (ULINT/LINT) and uses the same adapter interface (unidirectional), allowing it to be seamlessly integrated into existing adapter circuits.

## Conclusion

The **AULI_TO_ALI** module is a simple yet effective solution for converting ULINT to LINT values using standardized adapters. It simplifies the integration of different data types into unidirectional communication paths and is particularly well-suited for modular IEC 61499 applications.
