# AI_TO_AL
![AI_TO_AL](./AI_TO_AL.svg)

* * * * * * * * * *
## Introduction
The composite function block **AI_TO_AL** converts an INT value provided via the unidirectional AI adapter (type `adapter::types::unidirectional::AI`) into an LWORD value output via the unidirectional AL adapter (type `adapter::types::unidirectional::AL`). The block encapsulates the conversion logic, thus enabling a clean separation between INT- and LWORD-based adapter interfaces.
## Interface Structure

### **Event Inputs**
No standalone event inputs on the block. Event control is handled exclusively via the integrated socket `AI_IN`, which provides the event `E1` as a trigger for the conversion.

### **Event Outputs**
No independent event outputs on the block. The result of the internal conversion is output via the plug `AL_OUT` as event `E1`.

### **Data Inputs**
No independent data inputs on the block. The INT value to be converted is read into the block via the socket `AI_IN` (data point `D1`).

### **Data Outputs**
No independent data outputs on the block. The converted LWORD value is output via the plug `AL_OUT` (data point `D1`).

### **Adapter**

| Label | Type | Direction | Comment |
|-------------|-----|-----------|-----------|
| `AI_IN` | `adapter::types::unidirectional::AI` | Socket (Input) | INT Adapter Input |
| `AL_OUT` | `adapter::types::unidirectional::AL` | Plug (Output) | LWORD Adapter Output |

## Functionality

1. An incoming event `E1` at the adapter `AI_IN` activates the data conversion.

2. The internal function block `F_INT_TO_LWORD` (from the library `iec61131::conversion`) is triggered via its event input `REQ` and converts the INT value present at `IN` into an LWORD value.

3. After the conversion is complete, the function block signals this via the event output `CNF`.

4. This event is forwarded to the adapter `AL_OUT` as event `E1` and simultaneously outputs the converted LWORD value via `D1`.

This event is forwarded to the adapter `AL_OUT` as event `E1` and simultaneously outputs the converted LWORD value via `D1`.

... The data paths are:

- `AI_IN.D1` → `Convert.IN`
- `Convert.OUT` → `AL_OUT.D1`

The event paths are:

- `AI_IN.E1` → `Convert.REQ`
- `Convert.CNF` → `AL_OUT.E1`

## Technical Features
- **Composite Block:** The `AI_TO_AL` is implemented as a composite and does not contain its own algorithmic logic. It delegates the conversion entirely to the defined function block `F_INT_TO_LWORD`.
- **Standard Conversion:** The conversion function used is part of the IEC 61131 library and ensures standards-compliant type conversion from INT (16-bit) to LWORD (64-bit).
- **Adapter-Based:** The function block operates exclusively via the specified adapter interfaces and can therefore be seamlessly integrated into an adapter-based architecture.
- **License and Version:** The function block is licensed under the Eclipse Public License 2.0 (EPL-2.0) and was released in version 1.0 by HR Agrartechnik GmbH.
- **Date of Creation:** February 17, 2026, Author: Franz Höpfinger.

## State Overview

As a composite function block, `AI_TO_AL` does not have its own internal state machine. The entire state logic is controlled by the integrated function block `F_INT_TO_LWORD`, which executes a simple request-acknowledgment sequence (REQ/CNF). The function block is therefore purely data flow-driven and does not have persistent states.

## Application Scenarios
- **Bus Coupling:** When a sensor or actuator delivers an INT value via an AI adapter, but the downstream system expects an LWORD value via an AL adapter (e.g., when connected to a fieldbus with 64-bit data types).
- **Protocol Adaptation:** In heterogeneous automation systems where different adapter types (AI and AL) need to be interconnected.
- **Data Preparation:** Before further processing of INT data in a controller that internally uses LWORD.

## Comparison with Similar Components
- **Other Conversion Adapters:** Similar composite components exist for other data type pairs, such as `WORD_TO_DWORD`, `BYTE_TO_WORD`, or `DINT_TO_LWORD`. The `AI_TO_AL` is specifically designed for the INT → LWORD combination.
- **Direct Conversion:** Alternatively, conversion could be performed directly with `F_INT_TO_LWORD` without adapter encapsulation. The advantage of `AI_TO_AL` lies in its standardized adapter interface, which facilitates exchange and reusability in adapter-based networks.

## Conclusion

The `AI_TO_AL` function block is a simple yet valuable adapter converter that bridges the gap between INT- and LWORD-based adapter interfaces. By encapsulating the conversion logic within a single composite block, the application logic remains clear and reusability is increased. It is particularly well-suited for use in modular automation systems based on unidirectional adapter communication.
