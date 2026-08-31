# ALI_ADD_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALI_ADD_2`](ALI_ADD_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALI_ADD_2_UNGATED](./ALI_ADD_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ALI_ADD_2_UNGATED` is a generic arithmetic block for performing addition (ADD) based on the IEC 61131-3 standard. It is classified as a standard arithmetic function and serves to add two input values via an adapter interface and output the result.

By using adapters, this block enables highly modular and clear wiring within the 4diac IDE.

## Interface Structure

### **Event Inputs**

*No direct event inputs are available. Control and synchronization are handled via the adapters.*

### **Event Outputs**

*No direct event outputs are available. Control and synchronization are handled via the adapters.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

- **IN1 (Socket)**: Input adapter type `adapter::types::unidirectional::ALI`. Represents the first addend of the addition.
- **IN2 (Socket)**: Input adapter type `adapter::types::unidirectional::ALI`. Represents the second addend of the addition.
- **OUT (Plug)**: Output adapter type `adapter::types::unidirectional::ALI`. Provides the mathematical result of the addition (`IN1 + IN2`).

## Functionality

The function block `ALI_ADD_2_UNGATED` performs a classic mathematical addition. As soon as the values at the input adapters `IN1` and/or `IN2` change, or a corresponding transfer event is triggered via the adapters, the block calculates the sum:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

The result is immediately available via the output adapter `OUT`. Since the block is defined as a generic type (implemented via the generic class `GEN_ALI_ADD`), it is not tied to a specific data type but can adapt to various compatible numeric data types.

## Technical Features

- **Generic Implementation**: The attribute `GenericClassName` with the value `'GEN_ALI_ADD'` allows the function block to be flexibly instantiated for different data types (e.g., INT, REAL, LREAL).
- **Adapter Coupling**: Unlike traditional function blocks that use discrete pins for data and events, this function block bundles the signals in unidirectional `ALI` adapters. This significantly reduces the number of wires in the function block diagram.

## State Overview

The function block is stateless (combinatorial behavior). It does not have an internal state machine (ECC). Any change to the inputs directly updates the output.

## Application Scenarios

- **Signal Processing**: Summing two sensor values or physical quantities that are already distributed within the application via an adapter system.
- **Setpoint Generation**: Adding a base setpoint and a correction offset.
- **Modular Plant Engineering**: Use in systems where interfaces are consistently mapped via adapters to maximize code reusability and readability.

## Comparison with Similar Components

Classic `ADD` components according to IEC 61131-3 typically have direct data inputs (`IN1`, `IN2`...) and event pins (`REQ`, `CNF`). The `ALI_ADD_2_UNGATED` differs in that it encapsulates these channels in adapters (`ALI`). This results in better encapsulation and cleaner structuring in complex 4diac applications, but requires that the connected components also support the `ALI` adapter protocol.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALI_ADD_2_UNGATED` is a specialized, highly efficient addition component for adapter-based architectures in the 4diac IDE. It combines the standard mathematical functionality of addition with the structural advantages of modern, adapter-based communication paradigms.
