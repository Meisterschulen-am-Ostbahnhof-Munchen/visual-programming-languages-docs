# AULI_TO_AD

![AULI_TO_AD](./AULI_TO_AD.svg)

* * * * * * * * * *

## Introduction

The **AULI_TO_AD** function block is a composite function block that converts a unidirectional adapter of type **AULI** (ULINT) to a unidirectional adapter of type **AD** (DWORD). It serves as a bridge between components that provide data in ULINT format and those that expect a DWORD format. The conversion is performed using the IEC 61131 function `F_ULINT_TO_DWORD`.

## Interface Structure

The function block does not have its own event or data inputs/outputs, but communicates exclusively via two adapters:

### **Event Inputs**

| Adapter | Event | Description |
|-----------|----------|----------------------------------|
| `AULI_IN` | `E1` | Starts the conversion |

### **Event Outputs**

| Adapter | Event | Description |
|-----------|----------|----------------------------------|
| `AD_OUT` | `E1` | Signals conversion complete |

### **Data Inputs**

| Adapter | Variable | Data Type | Description |
|-----------|----------|----------|----------------------------------|
| `AULI_IN` | `D1` | ULINT | Input value for conversion |

### **Data Outputs**

| Adapter | Variable | Data Type | Description |
|-----------|----------|----------|----------------------------------|
| `AD_OUT` | `D1` | DWORD | Converted Output Value |

### **Adapter**

| Name | Direction | Type | Description |
|------------|----------|------------------------------------------|------------|----------------------------|
| `AULI_IN` | Socket | `adapter::types::unidirectional::AULI` | Input Adapter (ULINT) |
| `AD_OUT` | Plug | `adapter::types::unidirectional::AD` | Output Adapter (DWORD) |

## Functionality

This function block internally connects socket `AULI_IN` to function block `F_ULINT_TO_DWORD` and its output to plug `AD_OUT`. The sequence is controlled via events:

1. An incoming event at `AULI_IN.E1` activates the input of the conversion function.
2. The data value `AULI_IN.D1` (ULINT) is passed to the input `IN` of the function.
3. After the conversion, the result (DWORD) is provided at output `OUT`.
4. Simultaneously, an event is output to `AD_OUT.E1` to inform the connected function block about the new data.

The entire process is event-driven and occurs without any delay or state storage.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Composite Structure**: The function block is implemented as a network consisting of a single function block (`F_ULINT_TO_DWORD`). All connections are hard-wired.
- **Package Import**: The conversion function used comes from the package `iec61131::conversion`. The function block is organized in the package `adapter::conversion::unidirectional`.
- **No State Storage**: The function block is purely combinatorial – each input event immediately generates an output event with the converted value.
- **Type Safety**: The adapter interfaces are strictly defined as ULINT or DWORD, so incorrect connections are detected during development.

## State Overview

Since this is a composite block without its own algorithms, there is no explicit state machine. The overall state is derived solely from the internal state of the function block used, `F_ULINT_TO_DWORD`, which returns to its idle state after each execution cycle. During normal operation, the block cycles between:

- **Waiting**: Waiting for an event at `AULI_IN.E1`.
- **Converting**: Briefly executing `F_ULINT_TO_DWORD`.
- **Output**: Sending the result and the event to `AD_OUT.E1`.

## Application Scenarios

- **Data Adaptation in Agricultural Engineering**: Conversion of ULINT values (e.g., from sensors or control units) into the DWORD format required by downstream components.
- **Adapter-Based Communication**: Use in modules that are connected exclusively via adapter interfaces, without direct input/output pins.
- **System Integration**: If one existing system provides ULINT data, but another only accepts DWORD adapters, this module serves as a simple converter.

## Comparison with Similar Modules

| Module | Description |
----------------- | ------------------------------------------------------------------------------ |
| `F_ULINT_TO_DWORD` | Simple conversion function, but without adapter integration. |
| `AULI_TO_AD` | Same functionality, but as a composite block with adapter interfaces. |
| Other adapter converters | Blocks exist for related types (e.g., LINT, DINT) that operate on the same principle. |

The key difference lies in the interface type: While the pure function uses direct data and event pins, `AULI_TO_AD` encapsulates the conversion in an adapter-based solution.

## Conclusion

The `AULI_TO_AD` function block offers a clean, standardized way to convert ULINT data into the DWORD format of an AD adapter via an AULI adapter. Thanks to its composite nature, it is easy to use, requires no custom programming, and integrates seamlessly into an adapter-oriented architecture. It is particularly useful in environments where components communicate via defined adapter interfaces.
