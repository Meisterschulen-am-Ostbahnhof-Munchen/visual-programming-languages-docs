# AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED

![AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED](./AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
The function block AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED mirrors an incoming fieldbus signal value (USINT) to the output, provided the signal is recognized as valid. The input value is multiplied by a configurable scaling factor, and an offset is added. The function block is implemented as a composite block and consists of a sub-function block for scaling and an edge-triggered D flip-flop for synchronizing the validity signal. It is typically used in fieldbus signal processing to convert raw USINT values into physical quantities and pass on the data validity information.

- **INIT** (EInit): Initialization request. Passed through to the internal sub-function block.
- **INITO** (EInit): Initialization confirmation. This is handled by the internal sub-FB.
- **SCALE** (REAL): Scaling factor that is multiplied by the input value. Default value: 1.0.
- **OFFSET** (DINT): Offset value that is added to the scaled value after multiplication. Default value: 0.

No direct data outputs – output is exclusively via the adapters.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **IN** (Socket, type `adapter::types::unidirectional::AUS`): Input adapter for the raw signal. Provides USINT data via `D1` and an event via `E1`.
- **VALID** (Plug, type `adapter::types::unidirectional::AX`): Output adapter for the validity signal. Outputs a Boolean value (TRUE = valid) via `D1` and an event via `E1`.

## Functionality

1. **Initialization**: The event `INIT` is forwarded directly to the internal sub-FB `FIELDBUS_USINT_TO_SIGNAL_SCALED`. Its `INITO` is passed through to the external `INITO` output.
2. **Data Processing**: As soon as an event arrives at `IN.E1`, it triggers the execution of the internal sub-FB via its `REQ` input. The sub-FB processes the current value of `IN.D1` (USINT) using `SCALE` and `OFFSET` and calculates a scaled output value (REAL) and a validity flag (BOOL).
3. **Result Output**: After the calculation, the sub-FB generates a `CNF` event. This triggers:

- The output of the scaled value via `OUT.D1` and the event `OUT.E1`.
- The clock input (`CLK`) of the D flip-flop `E_D_FF`.
1. **Validation Signal**: The validation flag of the sub-FB is set to the data input (`D`) of the flip-flop. With each clock event, the flip-flop updates the current `D` value to its output `Q`. The event `E_D_FF.EO` then triggers the output of the validity signal via `VALID.D1` and `VALID.E1`.
2. **Interaction**: This ensures that the validity signal is updated only after scaling is complete and in a strictly timed manner with the output scaled value.

- **Composite Structure**: The function block consists of a specialized sub-function block (`FIELDBUS_USINT_TO_SIGNAL_SCALED`) for scaling and a standardized D flip-flop (`E_D_FF`) from the IEC 61499 event library.
- **Hidden Connections**: Some internal connections (e.g., for `INIT`, `SCALE`, `OFFSET`) are marked as invisible (`Visible="false"`) to improve clarity in the graphical representation.
- **Data Types**: The input value is assumed to be USINT (0…255), and the output is scaled to REAL. The offset is declared as DINT.
- **Edge-Triggered Synchronization**: The D flip-flop ensures debounced propagation of the validity signal, so it is only updated during a new processing cycle.

The function block (FB) does not have its own explicit states. The state logic is derived from the following sub-components:

- **Sub-FB `FIELDBUS_USINT_TO_SIGNAL_SCALED`**: Performs a flow-oriented calculation without state memory; it responds to each `REQ` event with a `CNF`.
- **D-Flipflop `E_D_FF`**: Has two states (Q = 0 or 1). On each positive clock cycle (CLK), Q = D is set. The state is retained until the next clock cycle.
- **Fieldbus Sensor Evaluation**: A sensor delivers a USINT value via fieldbus (e.g., 0–100% fill level or 0–255 pressure values). The function block scales this value to a physical unit (e.g., meters, bar) and outputs it along with a validity flag.
- **Signal conditioning in agricultural technology**: Agricultural machinery often requires scaled signals where the validity of the data (e.g., after a communication failure) must be explicitly indicated.
- **Initialization cascades**: The passed-through `INIT` output enables the initialization of downstream function blocks that also rely on this signal.
- **`AUS_FIELDBUS_USINT_TO_SIGNAL`** (without scaling): Provides only direct transmission of the USINT value without scaling or offset.
- **`AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` with separate validation toggle**: An alternative design could forward the validity signal asynchronously (without a flip-flop), but this could lead to potential jitter.
- **`AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` with integrated state machine**: Instead of a flip-flop, a custom state logic could manage the validity signal; however, this block uses proven standard components.

The `AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` function block offers a robust and maintainable solution for scaling USINT fieldbus signals and reliably forwarding the validity status. Its composite structure and the use of a D flip-flop ensure a clean temporal separation between data processing and output. It is particularly useful in systems with cycle-based data processing and explicit signal validity.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
