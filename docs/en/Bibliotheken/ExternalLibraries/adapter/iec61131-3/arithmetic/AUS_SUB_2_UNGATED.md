# AUS_SUB_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUS_SUB_2`](AUS_SUB_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AUS_SUB_2_UNGATED](./AUS_SUB_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block (FB) `AUS_SUB_2_UNGATED` is a generic block for performing arithmetic subtraction operations within 4diac-based control systems. The block uses unidirectional adapters of type `AUS` to encapsulate and transmit input and output signals. Due to its generic design (compilation class `GEN_AUS_SUB`), it can be flexibly used in various control scenarios to calculate the difference between two values.

## Interface Structure

### **Event Inputs**

This function block does not have direct, dedicated event inputs. Event control is handled entirely via the adapters used.

### **Event Outputs**

This function block does not have direct, dedicated event outputs. Event control is handled entirely via the adapters used.

### **Data Inputs**

There are no direct, basic data inputs. Data is transferred via the input adapters.

### **Data Outputs**

There are no direct, basic data outputs. The result is provided via the output adapter.

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AUS`): The first input (minuend) for subtraction calculation.
- **IN2** (Type: `adapter::types::unidirectional::AUS`): The second input (subtrahend) for subtraction calculation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AUS`): The output (difference) that provides the calculated result of the subtraction.

---

## Functionality

The primary function of `AUS_SUB_2_UNGATED` is arithmetic subtraction:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Since the function block is based on adapters, it receives the values and the corresponding trigger events via the sockets `IN1` and `IN2`. As soon as relevant data arrives via the input adapters, the mathematical operation is executed. The result of the calculation and the corresponding output event are then forwarded to the subsequent function blocks via the plug `OUT`.

Since this is a generic function block (`GEN_AUS_SUB`), the mathematical processing dynamically adapts to the data types defined in the `AUS` adapter.

---

## Technical Features

- **Generic Type (`GEN_AUS_SUB`):** The function block is not limited to a single data type (such as only `INT` or `REAL`), but supports the data types defined by the adapter structure.
- **Unidirectional Adapters:** Using the `unidirectional::AUS` type ensures a clear, one-way data and signal flow. This minimizes the complexity of signal tracing within the system.
- - **Encapsulation:** By eliminating traditional event and data pins, the visual layout in the 4diac-ide Application Editor remains extremely compact and clear.

---

## State Overview

Since this module is designed as a purely functional, stateless calculation block, it does not have a complex internal Execution Control Chart (ECC). Its execution is purely data- and event-driven, based on the interactions of the connected adapters.

---

## Application Scenarios

- **Process Value Correction:** Subtraction of zero-point offsets or calibration values from a measured sensor value.
- **Target-Actual Value Comparison:** Calculation of the control deviation ($e = w - x$) in control loops where the signals are already available as structured adapter channels.
- **Level Calculation:** Determination of differential quantities in containers or systems by subtracting the outflow from the inflow.

---

## Comparison with Similar Function Blocks

Compared to a classic IEC 61131-3 `SUB` function block, which works directly with elementary data types, the `AUS_SUB_2_UNGATED` offers the following advantages:

- **Reduced Wiring Effort:** Event and data lines do not need to be run separately, as they are bundled in the `AUS` adapter.
- **Increased Modularity:** It is ideally suited for service-oriented architectures in IEC 61499, where subsystems typically communicate via adapters.

--

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AUS_SUB_2_UNGATED` is a specialized yet flexible subtraction function block. Through the consistent use of unidirectional adapters, it promotes a clean, structured, and clear design of control programs in the 4diac IDE.
