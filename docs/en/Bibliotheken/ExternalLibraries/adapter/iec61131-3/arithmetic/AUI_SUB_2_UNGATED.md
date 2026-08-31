# AUI_SUB_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUI_SUB_2`](AUI_SUB_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AUI_SUB_2_UNGATED](./AUI_SUB_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `AUI_SUB_2_UNGATED` is used to perform arithmetic subtraction within an IEC 61499 application. It is a generic function block (FB) specifically designed for interaction with adapter interfaces. It allows subtraction operations to be implemented modularly and in a structured manner via standardized adapter connections, instead of using discrete individual wires for data and events.

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Event control is handled internally via the connected adapters.*

### **Event Outputs**

*This function block does not have direct event outputs. Event forwarding is encapsulated via the output adapter.*

### **Data Inputs**

*There are no direct data inputs. Data is transferred via the input adapters.*

### **Data Outputs**

*There are no direct data outputs. The result is provided via the output adapter.*

### **Adapters**

#### **Sockets (Inputs)**

- **IN1** (Type: `adapter::types::unidirectional::AUI`):

First input adapter for subtraction. This represents the minuend (value from which the subtraction is made).

- **IN2** (Type: `adapter::types::unidirectional::AUI`):

Second input adapter for subtraction. This represents the subtrahend (value being subtracted).

#### **Plugs (Inputs / Outputs)**

- **OUT** (Type: `adapter::types::unidirectional::AUI`):

Output adapter that provides the result of the subtraction (the difference) for further use.

--

## Functionality

The function block performs the basic mathematical operation of subtraction on the values received via the adapters:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

As soon as a change in value is signaled at the input adapters `IN1` or `IN2` (triggered by the event-driven nature of the underlying `AUI` adapter), the function block calculates the difference and outputs the result, along with a corresponding update event, via the output adapter `OUT`.

---

## Technical Features

- **Generic Type:** The function block is based on the generic class `GEN_AUI_SUB`. This allows for flexible handling of different data types, provided they are supported by the underlying adapter type `AUI` (Analog User Interface / Unidirectional).
- **Encapsulation:** By using unidirectional adapters, signal flows and their associated trigger events are neatly bundled. This significantly simplifies application design in the 4diac IDE and reduces the number of visible connection lines.

--

## State Overview

The function block itself does not manage a complex internal state (stateless in the sense of a state machine). Its execution is purely reactive:

1. **Waiting:** The function block waits for an update event at `IN1` or `IN2`.

**Encapsulation:** 2. **Calculation:** After an event occurs, the data values are read and the subtraction is performed.

1. **Output:** The new difference value is applied to `OUT`, and the adapter's output event is triggered.

---

## Application Scenarios

- **Differential Pressure/Differential Temperature Measurement:** Calculation of the deviation between two analog sensors whose values are already available as structured adapter signals.
- **Setpoint-Actual Value Comparison:** Subtraction of an actual value from a setpoint to determine the control deviation in control loops.
- **Zero Point Compensation (Offset Calculation):** Subtraction of a static or dynamic offset value (via `IN2`) from a raw signal (via `IN1`).

- ---

## Comparison with Similar Building Blocks

Compared to a standard subtraction block (such as the classic `SUB` block from the IEC 61131-3 library), the `AUI_SUB_2_UNGATED` does not require explicit wiring of separate event and data ports (e.g., `REQ`, `IN1`, and `IN2`). All the logic for value transfer and updates is encapsulated in the `AUI` adapter. This makes the `AUI_SUB_2_UNGATED` easier to maintain and more robust against wiring errors in complex system architectures.

---

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AUI_SUB_2_UNGATED` is a highly efficient, clear, and modern function block for performing subtractions. Through the consistent use of adapters, it integrates seamlessly into service-oriented and modularized control concepts and contributes to a clean software design in the 4diac IDE.
