# AI_TO_AUI
![AI_TO_AUI](./AI_TO_AUI.svg)

* * * * * * * * * *
## Introduction
The function block **AI_TO_AUI** is a composite block that converts an INT adapter (AI) into a UINT adapter (AUI). It serves as an interface converter in systems that rely on unidirectional adapter communication. Internally, it uses the block `F_INT_TO_UINT` from the IEC 61131 library to convert the integer value of `AI_IN` into an unsigned integer and make it available via `AUI_OUT`.
## Interface Structure
### Event Inputs
No separate event inputs are available. Event control is handled exclusively via the adapters (`AI_IN.E1` for request, `AUI_OUT.E1` for acknowledgement).

### Event Outputs
No separate event outputs are available. Event feedback is provided via the `AUI_OUT.E1` adapter.

### Data Inputs
No separate data inputs are available. The value to be converted is received via the `AI_IN.D1` adapter (type INT).

### Data Outputs
No separate data outputs are available. The converted value is provided via the `AUI_OUT.D1` adapter (type UINT).

### Adapters

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
Socket (Input) | `AI_IN` | `adapter::types::unidirectional::AI` | INT adapter input. Returns the event `E1` and the data value `D1` (INT). |
Plug (Output) | `AUI_OUT` | `adapter::types::unidirectional::AUI` | UINT adapter output. Provides the event `E1` and the data value `D1` (UINT). |

## Functionality
The function block operates as a simple pipeline:

1. An event is received via `AI_IN.E1`.

2. This event triggers the internal conversion block `F_INT_TO_UINT` via its `REQ` input.

3. The value of `AI_IN.D1` (INT) is forwarded to `Convert.IN`.

4. After the conversion is complete, an event is sent to `AUI_OUT.E1` via `Convert.CNF`.

5. The converted value (UINT) is available at `AUI_OUT.D1`.

The module is purely causal – it reacts to an incoming event and, after conversion, outputs an outgoing event.

## Technical Features
- **Adapter-based communication**: Instead of classic input/output pins, the interfaces are implemented via adapters (`AI` and `AUI`). This enables loose coupling in modular systems.
- **Unidirectional data flow**: Both adapters are unidirectional, meaning they only transport data and events in one direction (input or output).
- **Packaging**: The module is located in the package `adapter::conversion::unidirectional`, which indicates its role as a converter between adapter types.
- **Type Conversion**: The conversion from `INT` to `UINT` is performed using the IEC 61131 function block `F_INT_TO_UINT`, which ensures value preservation for positive numbers. Negative values are converted to the corresponding UINT space (e.g., two's complement).

## State Overview
The function block does not have an explicit state machine. Internally, it only executes the following sequence: Receive event → Trigger conversion → Send event. There are no delayed responses or persistent states.

## Application Scenarios
- **Sensor Interface Adaptation**: A sensor delivers measured values as `INT` (e.g., temperature or pressure) via an AI adapter; The subsequent controller expects `UINT` via an AUI adapter.
- **System Integration**: In heterogeneous systems using different adapter types, `AI_TO_AUI` enables seamless connection of components.
- **Data Preparation**: Before further processing in a PLC that only supports unsigned values (e.g., for counters or scaling).

## Comparison with Similar Function Blocks
- **`AI_TO_AUI` vs. Direct Conversion with `F_INT_TO_UINT`**: The composite function block encapsulates the adapter interfaces and simplifies the application for the developer – individual function blocks with signal connections do not need to be wired.
- **Similar Adapter Converters**: The library may contain other modules such as `AUI_TO_AI` (reverse conversion) or converters for other data types (e.g., `REAL_TO_INT`). `AI_TO_AUI` is specifically designed for combining INT and UINT adapters.

## Conclusion
The module `AI_TO_AUI` offers a compact, reusable solution for converting an INT adapter data stream to a UINT adapter data stream. It reduces the complexity of the interconnection and ensures that the data conversion is correct and event-driven. Thanks to its adapter interfaces, it integrates seamlessly into modular, unidirectional architectures.
