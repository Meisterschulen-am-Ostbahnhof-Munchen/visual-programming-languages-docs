# Exercise_083_AX: Example for AUDI_CTUD_UDINT (Adapter-Based)
This article describes the logiBUS® exercise `Uebung_083_AX`. It is the adapter-based version of exercise 083 and demonstrates an up/down counter (`AUDI_CTUD_UDINT`) for unsigned 32-bit integers in an AX environment.
----
## Objective of the Exercise
To learn how to control a high-performance counter using an adapter and display the counter value on an ISOBUS terminal. This exercise demonstrates the use of AX adapters for the inputs (`CU`, `CD`, `R`, `LD`) and the counter value (`CV`), as well as for controlling the numeric display.
-----

## Description and Components

The subapplication `Uebung_083_AX.SUB` uses the following adapter-based function blocks:

### Function Blocks (FBs)
* **`DigitalInput_CLK_I1` to `I4`**: Input blocks of type `logiBUS::io::DI::logiBUS_IXA`. They provide an event and a Boolean signal via an AX adapter when a button is pressed.
* **`AUDI_CTUD_UDINT`**: The adapter-based up/down counter. It expects events at `CU`, `CD`, `R`, and a `AUDI` adapter at `PV`, and outputs the counter value via the `CV` adapter.
* **`DigitalOutput_Q1` & `Q2`**: Output blocks of type `logiBUS::io::DQ::logiBUS_QXA` for displaying the counter status (`QU`, `QD`).
* **`Q_NumericValue_AUDI`**: ISOBUS output module for numerical display at the terminal; receives the value via a `AUDI` adapter.
* **`AUDI_UDINT_TO_UDI`**: Conversion module that converts a `UDINT` literal (`UDINT#5`) into a `AUDI` adapter to supply the `PV` input of the counter.

-----

## Functionality

1. **Counting**: `DigitalInput_CLK_I1.OUT` (button I1) triggers `AUDI_CTUD_UDINT.CU` (counter increment). `DigitalInput_CLK_I2.OUT` (button I2) triggers `AUDI_CTUD_UDINT.CD` (counter down).

2. **Reset/Load**: `DigitalInput_CLK_I3.OUT` (button I3) triggers `AUDI_CTUD_UDINT.R` (reset). `DigitalInput_CLK_I4.IND` triggers `AUDI_UDINT_TO_UDI.REQ`, which passes the value `UDINT#5` to `AUDI_CTUD_UDINT.PV`, thus loading the counter.

3. **Display**: The counter status `QU` and `QD` controls `DigitalOutput_Q1.OUT` and `DigitalOutput_Q2.OUT`. The current counter value (`AUDI_CTUD_UDINT.CV`) is sent to `Q_NumericValue_AUDI.u32NewValue` and displayed on the ISOBUS terminal.

-----

## Implementation Notes
* **Input Types**: The `DigitalInput_CLK_I` blocks are of type `logiBUS_IE`, although `logiBUS_IXA` would be the adapter variant. The parameters `InputEvent` are redundant in an AX context and could be removed if `logiBUS_IXA` is used.
* **PV Initialization**: Directly assigning a `PV` parameter (`UINT#5`) to `AUDI_CTUD_UDINT` is not compatible with the adapter. The current solution using the converter `AUDI_UDINT_TO_UDI` is functional, but somewhat cumbersome.