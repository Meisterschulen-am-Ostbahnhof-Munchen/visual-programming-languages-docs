# AULI_SUB_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AULI_SUB_2`](AULI_SUB_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AULI_SUB_2_UNGATED](./AULI_SUB_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `AULI_SUB_2_UNGATED` is a generic function block (Generic FB) designed to perform arithmetic subtraction (`OUT = IN1 - IN2`). Instead of traditional data and event pins, this block uses adapter interfaces of type `unidirectional::AULI`. This enables structured and modularized signal transmission in IEC 61499 applications.

## Interface Structure

### **Event Inputs**

*No direct event inputs are available. Event control is handled entirely via the adapters.*

### **Event Outputs**

*No direct event outputs are available. Event control is handled entirely via the adapters.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AULI`):
- Description: The first input (minuend) for subtraction.
- **IN2** (Type: `adapter::types::unidirectional::AULI`):
- Description: The second input (subtrahend) for subtraction.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AULI`):
- Description: The output (difference) of arithmetic subtraction.

---

## Functionality

As soon as values and their corresponding events arrive via the input adapters `IN1` and `IN2`, the function block executes the mathematical operation `OUT = IN1 - IN2`.

Since this is a generic function block (`GEN_AULI_SUB`), the specific data type processing can be determined by the data types defined in the adapter (e.g., integers or floating-point numbers). The result, along with the corresponding trigger event, is forwarded via the output adapter `OUT`.

` ... ---

## Technical Features

- **Generic Block:** The attribute `GenericClassName` with the value `'GEN_AULI_SUB'` allows the block to be used flexibly for various data types, provided the adapters used support this.
- **Unidirectional Adapters:** Using the type `AULI` ensures a clear separation of signal flow directions (unidirectional) and drastically reduces the wiring effort in the 4diac editor.

--

## State Overview

The block behaves purely combinatorially or event-driven:

1. **Waiting for Input:** The block remains in idle state until an event is signaled at one of the input adapters (`IN1` or `IN2`).

**Unidirectional Adapters:** 2. **Calculation:** Subtraction is performed upon signal change/event.

1. **Output:** The result is immediately transferred to the plug `OUT`, triggering the output event.

---

## Application Scenarios

- **Target-Actual Value Comparison:** Calculation of control deviations in process engineering (e.g., `Regeldifferenz = Sollwert - Istwert`).
- **Offset Compensation:** Subtraction of zero-point errors or offsets from analog sensor values.
- **Cascaded Calculations:** Mathematical calculations in modular plant control systems where measured values are transported in a structured manner via adapters.

---

## Comparison with Similar Function Blocks

Compared to a standard subtraction function block (e.g., `SUB` from the IEC 61131-3 standard library), `AULI_SUB_2_UNGATED` offers the following advantages:

- **Reduced Complexity:** Instead of separate lines for event (REQ/CNF) and data (IN1, IN2, OUT), the `AULI` adapters bundle all relevant information into a single connection.
- **Modularity:** The design is ideally suited for service-oriented architectures in distributed systems.

--

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AULI_SUB_2_UNGATED` is a robust and reusable function block for subtraction. Through the consistent use of adapters, it promotes a clean, well-organized, and maintainable application design in the 4diac IDE.
