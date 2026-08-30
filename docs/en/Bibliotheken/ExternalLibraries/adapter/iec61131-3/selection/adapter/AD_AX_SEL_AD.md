# AD_AX_SEL_AD

![AD_AX_SEL_AD](./AD_AX_SEL_AD.svg)

* * * * * * * * * *
The function block `AD_AX_SEL_AD` performs binary selection between two input signals provided via adapter structures. Based on the state of a selection signal (G), either the value of input `IN0` or input `IN1` is passed to output `OUT`. Internally, the block is implemented as a composite function block and utilizes standardized IEC 61499 and IEC 61131 mechanisms to ensure event-driven, type-safe signal propagation.

The interfaces of this function block are implemented entirely via adapters, enabling modular and clear wiring within the application network.

*This function block does not have direct event inputs on the housing. Event control is implicit via the adapters.*

*This function block does not have direct event outputs on the housing. Event forwarding is implicit via the adapters.*

*This component has no direct data inputs on its housing.*

*This component has no direct data outputs on its housing.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **Sockets (Input Adapters):**
- `IN0` (Type: `adapter::types::unidirectional::AD`): First selectable input channel (selected when `G` is in the state `FALSE`).
- `IN1` (Type: `adapter::types::unidirectional::AD`): Second selectable input channel (selected when `G` is in state `TRUE`).
- `G` (Type: `adapter::types::unidirectional::AX`): Selector signal for controlling the selection.
- **Plugs (Output Adapters):**
- `OUT` (Type: `adapter::types::unidirectional::AD`): The selected output channel that carries the value of the selected input.

- ## Functionality

The module encapsulates an internal network of control and conversion modules:

1. **Signal Buffering and Acquisition:** As soon as data changes on the adapters `IN0`, `IN1`, or `G`, the corresponding adapter event `E1` triggers the internal flip-flops (`E_D_FF` or `E_D_FF_ANY`).
2. **Data Forwarding:** The data values (`D1`) of inputs `IN0` and `IN1` are read via internal data converters (`F_MOVE` of type `DWORD`) and made available to the selection block `F_SEL`.
3. **Selection Logic (`F_SEL`):**

- If the signal `FALSE` is present at selector `G`, the block switches the signal from `IN0` to the output.
- - If the signal `TRUE` is present at selector `G`, the function block switches the signal from `IN1` to the output.
1. **Output Synchronization:** The selected value is passed via another function block `F_MOVE` to an output flip-flop (`E_D_FF_ANY_OUT`). This flip-flop generates the output event `E1` at output adapter `OUT` and places the selected value at `D1`.

- **Adapter Encapsulation:** The use of unidirectional adapters (`AD` and `AX`) simplifies signal routing and avoids loose data and event lines.
- **Type Independence via DWORD:** The internal data paths use the `DWORD` data type to represent the adapter data, enabling flexible transmission of different data formats.
- **Near-Real-Time Response:** Every edge or value change at the input or selector adapters immediately results in an output update.

As a composite function block, this module does not have its own Execution Control Chart (ECC). The behavior is purely data- and event-driven through the internal interaction of the standard function blocks (FBs):

- **Event on `IN0` or `IN1`:** Updates the respective internal value buffer. If the affected input is currently active, the new value is immediately output to `OUT`.
- **Event on `G`:** Switches the active channel and outputs the value of the newly selected channel to `OUT`.
- **Sensor Redundancy:** Switches between a primary sensor (`IN0`) and a redundant backup sensor (`IN1`) in case of signal loss or malfunction.
- **Setpoint Switching:** Switching between manual and automatic setpoint operation in industrial processes.
- **Signal Multiplexing:** Structured forwarding of control data in modular systems.
- **Standard `F_SEL`:** The classic `F_SEL` function block according to IEC 61131-3 operates directly on elementary data types and requires manual wiring of trigger events. `AD_AX_SEL_AD` encapsulates this logic and makes it directly available for adapter-based architectures.
- **Multiplexer (MUX):** A classic MUX allows selection from more than two channels using an integer value. `AD_AX_SEL_AD` is optimized for simple binary decisions (either/or) and thus saves processing resources.

The `AD_AX_SEL_AD` is a robust and efficient auxiliary module for event-driven signal switching. Thanks to the consistent use of adapters, it integrates perfectly into modern, service-oriented control architectures within 4diac.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
