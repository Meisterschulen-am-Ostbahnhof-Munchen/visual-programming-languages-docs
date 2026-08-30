# AUI_TO_AI

![AUI_TO_AI](./AUI_TO_AI.svg)

* * * * * * * * * *

## Introduction

Composite function block (FB) for converting an AUI (UINT) adapter into an AI (INT) adapter. It encapsulates the conversion using the function block `F_UINT_TO_INT` and provides a standardized adapter interface.

## Interface Structure

### **Event Inputs**

No direct event inputs at the FB level. The event is received via the **AUI_IN socket** (event `E1`).

### **Event Outputs**

No direct event outputs at the FB level. The event is output via the **AI_OUT plug** (event `E1`).

### **Data Inputs**

No direct data inputs at the FB level. The UINT value is provided via the **Socket AUI_IN** (data point `D1`).

### **Data Outputs**

No direct data outputs at the FB level. The INT value is output via the **Plug AI_OUT** (data point `D1`).

### **Adapters**

- **Socket AUI_IN** (Type: `adapter::types::unidirectional::AUI`) – Receives UINT data and an event.
- **Plug AI_OUT** (Type: `adapter::types::unidirectional::AI`) – Sends INT data and an event.

## Functionality

This function block connects the AUI adapter socket to a conversion function block of type `F_UINT_TO_INT` via an FBNetwork:

1. The event `E1` of the AUI_IN adapter triggers the conversion function block at the **REQ** input.
2. The conversion function block reads the UINT value from the data point `AUI_IN.D1` and converts it to INT.
3. After the conversion, the function block sends an acknowledgment event via **CNF**, which triggers the event `E1` of the AI_OUT adapter.
4. The event `E1` of the AI_OUT adapter.
5. The conversion function block reads the UINT value from the data point `AUI_IN.D1` and converts it to INT. 4. The converted INT value is passed to the AI adapter via the data point `AI_OUT.D1`.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- Composite function block without its own state logic (no ECC).
- Uses the standard function block `iec61131::conversion::F_UINT_TO_INT` for type conversion.
- Contains license information according to the Eclipse Public License 2.0.

## State Overview

The function block does not have an internal state machine. Control is achieved solely through event chaining in the FBNetwork.

## Application Scenarios

- Integration of a component that provides an AUI adapter (UINT) into a system that expects an AI adapter (INT).
- Encapsulation of the conversion to facilitate reuse and maintain a clear network structure.

## Comparison with Similar Function Blocks

- **AUI_TO_AI** converts UINT to INT.
- An analogous function block **AI_TO_AUI** would provide the reverse conversion (INT to UINT).
- Unlike direct type conversion function blocks (such as `F_UINT_TO_INT`), this function block operates at the adapter level and integrates seamlessly into IEC 61499 adapter concepts.

## Conclusion

The **AUI_TO_AI** function block offers a simple and encapsulated solution for converting AUI adapters to AI adapters. It facilitates interoperability between components with different data types and contributes to a clean, modular system architecture.
