# AUI_MUL_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUI_MUL_2`](AUI_MUL_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AUI_MUL_2_UNGATED](./AUI_MUL_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `AUI_MUL_2_UNGATED` is a generic arithmetic function block for the 4diac-ide development environment, used to perform the multiplication of two input values.

The special feature of this block lies in its adapter-based architecture. Instead of classic, individual data and event lines, this block uses unidirectional adapters (`AUI`) to transmit data and the associated control events in encapsulated form. This significantly reduces the visual complexity of control applications.

## Interface Structure

### **Event Inputs**

*No direct event inputs are available. Event control is handled entirely via the input adapters.*

### **Event Outputs**

*No direct event outputs are available. Event forwarding is handled entirely via the output adapter.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

- **`IN1` (Type: `adapter::types::unidirectional::AUI` - Socket):**

The first input adapter, providing the first multiplication factor.

- **`IN2` (Type: `adapter::types::unidirectional::AUI` - Socket):**

The second input adapter, providing the second multiplication factor.

- **`OUT` (Type: `adapter::types::unidirectional::AUI` - Plug):**

The output adapter that outputs the calculated product of the two input values along with the corresponding update event.

---

## Functionality

As soon as an event is triggered at one of the input adapters (`IN1` or `IN2`) indicating the presence of a new value, the function block reads the current values from both adapters.

The calculation is performed using the classic mathematical formula:

`OUT = IN1 * IN2`

After successful calculation, the result is passed to the output adapter `OUT`, and an output event is simultaneously triggered to inform subsequent function blocks about the presence of a new value.

---

## Technical Features

- **Generic Behavior:** The function block is linked to the value `'GEN_AUI_MUL'` via the compiler attribute `GenericClassName`. This means that the function block can operate independently of the data type (e.g., for `INT`, `REAL`, `LREAL`, etc.), depending on the specific data type defined by the connected adapters.
- **Efficient Wiring:** By encapsulating the function block in `AUI` adapters (Unidirectional Interface Adapters), the number of connections in the function plan is drastically reduced, as data and event flows are combined.

- ---

## State Overview

The function block operates purely event-driven and stateless (reactively):

1. **Standby State:** The block waits for incoming events via `IN1` or `IN2`.
2. **Calculation Phase:** An incoming event triggers the internal multiplication of the current adapter data.
3. **Output Phase:** The calculated product is applied to `OUT`, and the output event is triggered. The block immediately returns to the standby state.

--

## Application Scenarios

- **Measurement Scaling:** Multiplication of an analog sensor value (e.g., voltage) by a scaling factor to calculate the actual physical value.
- **Power Calculation:** Continuous multiplication of current (I) and voltage (U) to determine the current active power (P). * **Signal Amplification:** Application in signal processing for simple level adjustment.

---

## Comparison with Similar Components

- **Standard `MUL` component (IEC 61131-3):** A standard multiplication component requires separate pins for each data signal as well as for the execution control (`REQ`/`CNF`). `AUI_MUL_2_UNGATED` solves this more elegantly and compactly using adapter connections.
- **Multi-Input Multipliers (`MUL_3`, `MUL_4`):** While function blocks like `AUI_MUL_2_UNGATED` are fixed to two inputs, multi-input function blocks allow the multiplication of three or more factors in a single step, but are more complex.

---

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AUI_MUL_2_UNGATED` is a highly modular and modern function block for the 4diac-ide. Through the consistent use of unidirectional adapters, it promotes clean software design in distributed control systems according to IEC 61499, without sacrificing flexibility in the data types it can process.
