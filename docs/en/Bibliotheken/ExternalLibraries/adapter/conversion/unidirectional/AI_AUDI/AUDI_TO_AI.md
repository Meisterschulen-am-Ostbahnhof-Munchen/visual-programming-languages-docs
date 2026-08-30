# AUDI_TO_AI

![AUDI_TO_AI](./AUDI_TO_AI.svg)

* * * * * * * * * *

## Introduction

The composite function block `AUDI_TO_AI` converts a unidirectional AUDI adapter (data type `UDINT`) into a unidirectional AI adapter (data type `INT`). It encapsulates the conversion logic and enables easy integration into adapter-based communication structures according to IEC 61499.

## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. Event control is handled via socket `AUDI_IN` of type `adapter::types::unidirectional::AUDI`. This adapter provides an event input, `E1`, which triggers the conversion.

### **Event Outputs**

The function block (FB) has no direct event outputs. Event output is provided via the plug `AI_OUT` of type `adapter::types::unidirectional::AI`. This adapter provides an event output, `E1`, which signals the completion of the conversion.

### **Data Inputs**

No direct data inputs. The socket `AUDI_IN` provides the value to be converted, `UDINT`, via its data input `D1`.

### **Data Outputs**

No direct data outputs. Plug `AI_OUT` outputs the converted `INT` value via its data output `D1`.

### **Adapters**

- **Socket `AUDI_IN`**: Type `adapter::types::unidirectional::AUDI` – receives a unidirectional data value of type `UDINT` and an associated event.
- **Plug `AI_OUT`**: Type `adapter::types::unidirectional::AI` – sends a unidirectional data value of type `INT` and an associated event.

## Functionality

The function block is implemented as a composite block. Internally, socket `AUDI_IN` is connected to the standard conversion block `iec61131::conversion::F_UDINT_TO_INT`, whose output is in turn linked to plug `AI_OUT`.

When an event is received via the adapter input `AUDI_IN.E1`, the corresponding data value `AUDI_IN.D1` is passed to the conversion block. After successful conversion of `UDINT` to `INT`, the event `Convert.CNF` is generated and output via `AI_OUT.E1`. Simultaneously, the converted value is available at `AI_OUT.D1`.

...

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- Uses a standardized IEC 61131 conversion block that can be implemented platform-independently.
- The conversion from `UDINT` (32 unsigned bits) to `INT` (16 signed bits) is potentially lossy. Depending on the implementation of the conversion block, an overflow or limit may occur if the value range is exceeded.
- The use of unidirectional adapters ensures a clean data flow and facilitates integration into modular systems.
- The function block does not have its own state machine; all logic is executed event-driven via the internal wiring.

## State Overview

The function block does not have an internal state machine. Its functionality arises solely from the causal chaining of event and data connections. There is only one active state in which an incoming event-data combination is processed and the output is generated.

## Application Scenarios

- Connecting a sensor that delivers measured values as `UDINT` to a control system that expects `INT` values (e.g., a PLC with 16-bit analog inputs).
- Integration into PROFINET or EtherCAT applications where adapters are required for type conversion between different data formats.
- Reusable encapsulation of the conversion in an adapter-based library for industrial automation solutions.

## Comparison with Similar Function Blocks

- A direct conversion function block like `F_UDINT_TO_INT` requires separate event and data connections and is not designed for direct use in adapter interfaces.
- `AUDI_TO_AI` encapsulates the entire adapter conversion, thus simplifying reuse in architectures based on unidirectional adapters.
- Analogous function blocks for other data types (e.g., `REAL_TO_INT` or `DINT_TO_INT`) follow the same design pattern and can be implemented using the same scheme.

## Conclusion

The composite function block `AUDI_TO_AI` provides a clean and reusable solution for lossy conversion of `UDINT` values to `INT` values using unidirectional adapters. It simplifies integration into IEC 61499 systems that rely on adapter communication and encapsulates the conversion logic in a single, clearly defined function block.
