Here is the documentation for exercise `Uebung_006a3_sub_AX` based on the provided data.

# Exercise_006a3_sub_AX: Subapplication Type

* * * * * * * * * *

## Introduction
This function block is a subapplication (SubAppType) that implements logic for the mutual control of two outputs. The block uses adapter technology (`AX`) to process signals. The goal is to toggle the state of two outputs (`Links` and `Rechts`) based on an input signal, with these outputs always having opposite states (complementary).

## Function Blocks Used

Specific adapter blocks are used in this subapplication to implement the switching logic and signal distribution.


### Sub-Blocks: Exercise_006a3_sub_AX
- **Type**: SubAppType
- **Internal Function Blocks Used**:

- **AX_SWITCH**: `adapter::events::unidirectional::AX_SWITCH`

- **Description**: Serves as an input switch that converts or passes through adapter signals to events.

- **Adapter Input**: `G` (Connected to the external adapter `IN`).

- **Event Output**: `EO1` (Connected to `AX_T_FF.CLK`).


- **AX_T_FF**: `adapter::events::unidirectional::AX_T_FF`

- **Description**: A toggle flip-flop (T flip-flop) for adapter structures. It changes its output state with each input pulse.

- **Event Input**: `CLK` (Comes from `AX_SWITCH.EO1`).

- **Adapter Output**: `Q` (Goes to `AX_SPLIT_2.IN`).

- **AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2`

- **Description**: A splitter IC that splits an incoming adapter signal into two outputs.


**Event Input**: `CLK` (Comes from `AX_SWITCH.EO1`).

**Adapter Output**: `Q` (Goes to `AX_SPLIT_2.IN`).

**AX_SPLIT_2**: `adapter::events::unidirectional::AX_SPLIT_2`

**Description**: A splitter IC that splits an incoming adapter signal into two outputs. - **Adapter Input**: `IN` (Comes from `AX_T_FF.Q`).

- **Adapter Output 1**: `OUT1` (Goes directly to the external adapter `Rechts`).

- **Adapter Output 2**: `OUT2` (Goes to `AX_NOT.IN`).

- **AX_NOT**: `adapter::booleanOperators::AX_NOT`

- **Description**: A logic NOT gate (inverter) for adapter signals.

- **Adapter Input**: `IN` (Comes from `AX_SPLIT_2.OUT2`).

- **Adapter Output**: `OUT` (Connects to the external adapter `Links`).

- **Functionality**:

The component receives a signal via the adapter socket `IN`. This signal triggers the toggle flip-flop `AX_T_FF` via `AX_SWITCH`. The flip-flop then changes its state. The state signal is split by `AX_SPLIT_2`: One path leads directly to the output `Rechts`, while the other path is inverted by `AX_NOT` and leads to the output `Links`. Therefore, `Links` and `Rechts` always behave inversely to each other.

## Program Flow and Connections

The flow within the subapplication is purely event- and signal-driven via the adapter connections:

1. **Input Signal**: The external signal arrives at socket `IN`.

2. **Triggering**: `AX_SWITCH` detects the signal at input `G` and fires an event at output `EO1`.

3. **State Change**: This event serves as the clock signal (`CLK`) for `AX_T_FF`, which then toggles its internal state `Q`.

4. **Signal Distribution**: The signal from `Q` is passed on to the splitter `AX_SPLIT_2`.

* **Path A (Right)**: The output `OUT1` of the splitter forwards the signal directly to the plug `Rechts`.

* **Path B (Left)**: The output `OUT2` of the splitter forwards the signal to the inverter `AX_NOT`. The inverted signal is then output to the plug `Links`.

**Interfaces:**

* `IN` (Socket): Input for the control signal.

* `Rechts` (Plug): Output corresponding to the current state of the flip-flop.

* `Links` (Plug): Output corresponding to the inverted state of the flip-flop.

## Summary
The subapplication `Uebung_006a3_sub_AX` provides a module that converts an input pulse into two alternating output signals. The use of adapter ICs (`AX`) simplifies the wiring, as data and events can be transmitted in encapsulated form. The integrated inversion (`AX_NOT`) ensures that the outputs `Links` and `Rechts` never have the same logical state.