# ALR_DIV_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALR_DIV_2`](ALR_DIV_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALR_DIV_2_UNGATED](./ALR_DIV_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ALR_DIV_2_UNGATED` is a generic function block (Generic FB) for performing arithmetic divisions. It is defined in the package `adapter::iec61131::arithmetic` and is based on the generic class `GEN_ALR_DIV`.

Unlike classic arithmetic function blocks that work with direct data and event inputs, this block uses adapters of type `ALR` (unidirectional). This enables significantly simplified and structured wiring within 4diac applications, as signals and their associated control flows are bundled in adapters.

## Interface Structure

### Event Inputs

*This block has no direct event inputs. Control and triggering are implicit via the connected adapters.*

### Event Outputs

*This block has no direct event outputs.*

### Data Inputs

*This block has no direct data inputs.*

### Data Outputs

*This block has no direct data outputs.*

### **Adapters**

| Type | Name | Adapter Type | Description |
| :--- | :--- | :--- | :--- |
| **Socket (Input)** | `IN1` | `adapter::types::unidirectional::ALR` | First Operand of Division (Dividend) |
| **Socket (Input)** | `IN2` | `adapter::types::unidirectional::ALR` | Second operand of the division (divisor) |
| **Plug (output)** | `OUT` | `adapter::types::unidirectional::ALR` | Result of the division (quotient) |

## Functionality

The function block `ALR_DIV_2_UNGATED` performs a mathematical division of the values provided via the adapters. The calculation follows the formula:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Since this is a generic function block, the exact data type of the mathematical operation is determined at runtime or during instantiation by the specific data type used by the underlying `ALR` adapter. Data transmission is unidirectional, from the sockets (`IN1` and `IN2`) to the plug (`OUT`).

## Technical Features

- **Generic Block:** The property `GenericClassName = "GEN_ALR_DIV"` allows the block to be used flexibly for various data types, provided they are supported by the adapter type.
- **Adapter Coupling:** Using adapters instead of individual pins minimizes the graphical wiring effort in the 4diac IDE and improves clarity in the application editor.
- **Division by Zero:** During implementation and use, ensure that the value on the adapter `IN2` is not zero to avoid runtime errors or undefined system behavior.

## State Overview

This module does not have a complex internal state diagram (ECC). It operates as a purely functional processing module that calculates the result when values change at the input adapters (`IN1` or `IN2`) and forwards it via the output adapter (`OUT`).

## Application Scenarios

- **Signal Scaling:** Division of analog measured values by constant factors for unit conversion within an adapter-based signal processing chain.
- **Averaging and Ratio Control:** Calculation of ratios (e.g., air-fuel ratio) in control systems where signal paths are implemented modularly via adapters.
- **Standardization:** Use in complex control architectures to reduce the number of interconnects.

## Comparison with Similar Function Blocks

Compared to the standard IEC 61131-3 compact component `DIV`, the `ALR_DIV_2_UNGATED` has no direct data pins (unlike `IN1`, `IN2`, and `ANY_NUM`). While the standard `DIV` component is optimized for simple, point-to-point calculations, the `ALR_DIV_2_UNGATED` is primarily suited for service-oriented architectures and applications that consistently rely on loose coupling via adapter structures.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALR_DIV_2_UNGATED` is a specialized yet flexible division component for the 4diac IDE. It is ideally suited for demanding projects that value clean encapsulation of data flows using the unidirectional `ALR` adapter.
