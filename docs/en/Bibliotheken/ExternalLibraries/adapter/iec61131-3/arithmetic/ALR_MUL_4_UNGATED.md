# ALR_MUL_4_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALR_MUL_4`](ALR_MUL_4.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALR_MUL_4_UNGATED](./ALR_MUL_4_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `ALR_MUL_4_UNGATED` performs an arithmetic multiplication of four input values. It is a generic function block (FB) for the 4diac IDE, based on the IEC 61499 standard. Signal transmission and processing are handled via special unidirectional analog adapters, enabling clean encapsulation of the data streams.

## Interface Structure

### **Event Inputs**

*No direct event inputs are defined for this function block, as control and updates are handled via adapters.*

### **Event Outputs**

*No direct event outputs are defined for this function block.*

### **Data Inputs**

*No direct data inputs are defined for this function block.*

### **Data Outputs**

*No direct data outputs are defined for this function block.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::ALR`): First input value (multiplicand 1) for multiplication.
- **IN2** (Type: `adapter::types::unidirectional::ALR`): Second input value (multiplicand 2) for multiplication.
- **IN3** (Type: `adapter::types::unidirectional::ALR`): Third input value (multiplicand 3) for multiplication.
- **IN4** (Type: `adapter::types::unidirectional::ALR`): Fourth input value (multiplicand 4) for multiplication.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::ALR`): Output for the calculated product of the four input values.

## Functionality

The `ALR_MUL_4_UNGATED` module multiplies the analog values provided by the four input adapters (`IN1` to `IN4`). The mathematical result is output via the `OUT` output adapter.

The underlying calculation formula is:

$$ OUT = IN1 × IN2 × IN3 × IN4 $$

Since this is a generic function block that uses the class `GEN_ALR_MUL`, the implementation is flexible with respect to the data types used in the adapter (e.g., `REAL` or `LREAL`).

## Technical Features

- **Generic Function Block**: The attribute `GenericClassName` with the value `GEN_ALR_MUL` allows the function block to adapt flexibly to the specific data type implementation of the adapter used at runtime or during compilation.
- **Encapsulation via Adapter**: The use of the unidirectional adapter `ALR` (`adapter::types::unidirectional::ALR`) ensures that data values and any associated status or trigger events are bundled compactly in a single connection. This significantly reduces the wiring effort in the function block diagram.

## State Overview

The function block has no internal state behavior (no state machine/ECC) and operates purely in a data flow-oriented manner. As soon as the values at the input adapters change or a corresponding update event is triggered via the adapters, the multiplication is performed and the result is provided at the output `OUT`.

## Application Scenarios

- **Physical Calculations**: Calculation of more complex quantities that represent the product of several variables (e.g., power, energy calculations, or volumetric flow rates taking correction factors into account).
- **Cascaded Scaling**: Applying multiple scaling or correction factors to an analog input signal in a single step.
- **Signal Processing**: Preprocessing sensor values in control systems before the data is passed on to visualizations or actuators.

## Comparison with Similar Function Blocks

- **Standard MUL Function Blocks (IEC 61131-3)**: Classic multiplication function blocks typically work directly with standard data types (e.g., `REAL`) and require separate event connections (`REQ`/`CNF`). `ALR_MUL_4_UNGATED` simplifies this through the use of adapters.
- **ALR_MUL_2 / ALR_MUL_3**: These function blocks are designed for multiplying only two or three values. The `ALR_MUL_4_UNGATED` function block eliminates the need for additional intermediate steps and block cascades when four multiplicands are required, thus improving the performance and clarity of the control program.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALR_MUL_4_UNGATED` function block is a practical auxiliary block for mathematical signal processing in 4diac. By consistently utilizing the adapter concept, it significantly reduces the number of connecting lines in the application diagram while simultaneously offering the flexibility of a generic function block.
