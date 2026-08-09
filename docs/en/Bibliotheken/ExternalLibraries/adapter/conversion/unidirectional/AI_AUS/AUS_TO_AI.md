# AUS_TO_AI

![AUS_TO_AI](./AUS_TO_AI.svg)

* * * * * * * * * *
## Introduction

The function block `AUS_TO_AI` is a composite block that converts a `AUS` adapter (USINT-based) into a `AI` adapter (INT-based). It serves as a unidirectional interface between system components that use different data types for analog inputs. The block encapsulates the conversion logic and facilitates the integration of components based on `USINT` adapters into environments that expect `INT` adapters.
## Interface Structure

The function block has **no direct event or data inputs or outputs**. All signal communication is handled via the two built-in adapters:

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

#### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| `AUS_IN` | Socket | `adapter::types::unidirectional::AUS` | USINT-based adapter input (source of the value to be converted) |
| `AI_OUT` | Plug | `adapter::types::unidirectional::AI` | INT-based adapter output (destination of the converted value) |

The socket `AUS_IN` receives an event signal and a USINT data value. After conversion, the plug `AI_OUT` outputs an event signal and the corresponding INT value.

## Functionality

The function block operates purely combinatorially based on an internal instance of the IEC 61131 function block `F_USINT_TO_INT`. Sequence control is implemented via the adapters' event connections:

1. **Event E1 on the OFF_IN adapter** is routed to the **REQ input** of the conversion block `Convert`.

`` 2. The conversion block converts the USINT value at its **IN** input into an INT value and signals completion with the **CNF** event.

3. The **CNF** event is passed to the **E1 input of the AI_OUT adapter**, and simultaneously, the converted INT value is output to the **D1 data output** of the AI_OUT adapter.

This creates a causal chain: An incoming event at the AUS_IN adapter triggers the conversion and results in the output of a corresponding event and the converted data value at the AI_OUT adapter.

## Technical Features

- **Pure Adapter Coupling** – The block does not have its own input/output variables but only defines adapter interfaces (socket/plug). This follows the concept of adapter-based communication in IEC 61499.
- **Unidirectional Conversion** – The direction is fixed: from USINT to INT. Reverse conversion is not supported.
- **Use of a Standard IEC 61131 Function Block** – The actual type conversion is performed by the established function block `F_USINT_TO_INT`, which is already available in many runtime environments.
- **No Internal State** – The composite function block is stateless; the conversion is triggered anew with each incoming event.

## State Overview

Since the function block does not have its own state machine, only the implicit states of the embedded `F_USINT_TO_INT` exist. In practice, the function block behaves like a **combinatorial function**: After an event is received, the output signal is available for the next execution cycle. No defined error state exists – the conversion is performed according to the IEC component specification.

## Application Scenarios

- **Migration from USINT-based hardware to INT-based controllers** – A system that originally operates with 8-bit values (USINT) can be connected via this adapter to components that expect 16-bit analog values (INT).
- **Coupling of different subsystems** – In a modular plant, a sensor adapter uses USINT, while the higher-level control unit provides INT interfaces.
- **Prototypes and test environments** – Rapid integration of components with different data types without separate conversion logic at the application level.

## Comparison with Similar Function Blocks

- **Direct Conversion Function Blocks** – Function blocks like `F_USINT_TO_INT` or `F_INT_TO_USINT` offer pure type conversion but require manual wiring of events and data. `AUS_TO_AI` encapsulates this in an adapter-to-adapter concept, simplifying integration into adapter-based architectures.
- **Other Adapter Converters** – Symmetrical function blocks like `AI_TO_AUS` (INT to USINT) or bidirectional variants are conceivable. `AUS_TO_AI` is specifically designed for the unidirectional conversion from `AUS` to `AI`.

## Conclusion

The `AUS_TO_AI` composite module offers a clean, adapter-based solution for converting a USINT value to an INT value. By encapsulating the standard `F_USINT_TO_INT` module and providing clear event/data flow control, it is ideally suited for integrating heterogeneous components into IEC 61499 systems. The module requires minimal maintenance, is stateless, and adheres to established adapter interface conventions.
