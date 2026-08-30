# AUS_TO_AULI

![AUS_TO_AULI](./AUS_TO_AULI.svg)

* * * * * * * * * *

## Introduction

The function block `AUS_TO_AULI` is a composite block for converting an AUS adapter (UNSIGNED SHORT INTEGER) to an AULI adapter (UNSIGNED LONG INTEGER). It enables the direct forwarding of events and data between these two unidirectional adapter types, with an implicit type conversion from USINT to ULINT.

## Interface Structure

### **Event Inputs**

- **E1** (via `AUS_IN`): Event input of the connected AUS adapter. Passed directly to the output.

### **Event Outputs**

- **E1** (via `AULI_OUT`): Event output of the AULI adapter. Corresponds to the incoming event of `AUS_IN.E1`.

### **Data Inputs**

- **D1** (via `AUS_IN`): Data input of type **USINT** (OFF adapter). The value is transferred to the output.

### **Data Outputs**

- **D1** (via `AULI_OUT`): Data output of type **ULINT** (AULI adapter). Contains the converted value of the input.

### **Adapters**

- **OFF_IN** (Socket): Input interface for an OFF adapter (data type USINT, event E1, data D1).
- **AULI_OUT** (Plug): Output interface for an AULI adapter (data type ULINT, event E1, data D1).

## Functionality

This function block directly connects the elements of the incoming OFF adapter with the corresponding elements of the outgoing AULI adapter:

- An incoming event at `AUS_IN.E1` is immediately passed on to `AULI_OUT.E1`.
- The data value `AUS_IN.D1` (USINT) is mapped to `AULI_OUT.D1` (ULINT) without any additional logic. The type conversion is implicit through the different adapter definitions; a USINT value is expanded to the corresponding ULINT value.

## Technical Features

- **Composite Function Block**: The function block does not contain its own ECC (Execution Control Chart) or state logic, but consists solely of an event and data connection.
- **Implicit Type Conversion**: The conversion from USINT to ULINT is provided by the adapter definitions in the `adapter::types::unidirectional` library. Explicit type conversion in the function block (FB) is not required.
- **Unidirectionality**: The FB only supports one direction of data flow (from AUS to AULI). Reverse conversion is not supported.

## State Overview

The function block does not have its own state machine. It operates purely event-driven and combinatorially: With each incoming event, the current data value is immediately forwarded. No internal states are stored.

## Application Scenarios

- **Adapter Integration**: If an existing module (e.g., a sensor) outputs an AUS adapter, but a subsequent module (e.g., a controller) expects an AULI adapter, this FB can be used as a conversion intermediary layer.
- **System Expansion**: Easy upgrade from USINT-based interfaces to ULINT without changing the surrounding logic.
- **Test Environments**: As a placeholder or bridge in adapter-based test structures.

## Comparison with Similar Function Blocks

- **AUS_TO_AULI vs. Generic Type Converters**: Unlike a universal converter, this function block is specifically designed for AUS/AULI adapters and requires no additional parameterization. It is more compact and faster to develop.
- **AUS_TO_AULI vs. Manual Adapter Programming**: Instead of programming an adapter-to-adapter converter yourself, this ready-made function block offers an immediately usable, tested solution.

## Conclusion

The FB `AUS_TO_AULI` is a simple yet effective composite function block for converting an AUS adapter (USINT) to an AULI adapter (ULINT). Through its direct passing of events and data, as well as implicit type conversion, it represents a clean and maintainable solution for the integration of different adapter interfaces.
