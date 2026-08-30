# AUI_AX_SEL_AUI

Binary selection
![AUI_AX_SEL_AUI](./AUI_AX_SEL_AUI.svg)

* * * * * * * * * *

## Introduction

The function block **AUI_AX_SEL_AUI** implements a binary selection between two input values of type **AUI**. The decision as to which input is passed to the output is made via a third adapter of type **AX**, which serves as a selector. The block encapsulates the function **F_SEL** defined in IEC 61131-3 and provides it as an adapter-based component.

## Interface Structure

### **Event Inputs**

- **G.E1** (via adapter G): Triggers the selection processing as soon as an event is present at the selector adapter.

### **Event Outputs**

- **OUT.E1** (via adapter OUT): Is triggered after the selected value is present at the output.

### **Data Inputs**

- **G.D1** (via adapter G): The selecting value (e.g., BOOL or numeric) that determines whether **IN0** or **IN1** is selected.
- **IN0.D1** (via adapter IN0): First input value of type **AUI**.
- **IN1.D1** (via adapter IN1): Second input value of type **AUI**.

### **Data Outputs**

- **OUT.D1** (via adapter OUT): The selected value (type **AUI**), according to the selection logic.

### **Adapters**

- **G** (socket, type `adapter::types::unidirectional::AX`): Provides the selection signal.
- **IN0** (socket, type `adapter::types::unidirectional::AUI`): First data channel.
- **IN1** (Socket, type `adapter::types::unidirectional::AUI`): Second data channel.
- **OUT** (Plug, type `adapter::types::unidirectional::AUI`): Result channel.

## Functionality

The function block operates event-driven via the adapter interfaces. As soon as an event arrives at selector **G.E1**, the internal function block **F_SEL** is activated. **F_SEL** checks the value **G.D1**:

- If **G.D1** = `FALSE` (or 0), the value of **IN0.D1** is passed to output **OUT.D1**.
- If **G.D1** = `TRUE` (or not equal to 0), **IN1.D1** is selected.

After the selection is complete, **F_SEL.CNF** signals the event **OUT.E1** to inform the consumer of the new valid output value.

## Technical Features

- The function block is implemented as a **Composite FB** – its behavior results from the internal circuitry of a standardized **F_SEL** block (IEC 61131-3).
- Data is transmitted via adapters of type **AUI** and **AX**. These adapter types are defined as unidirectional channels whose internal data structure is not specified in detail (e.g., integer, real, or user-defined structs).
- Selection is purely combinatorial, but only after a triggering event at the selector. A simple data change without an event does not result in an output update.

## State Overview

Since this is a composite FB without its own state machine, there are no explicit states. The logic is purely event-driven:

1. **Wait for event** – as long as no **G.E1** is received, the output remains unchanged.
2. **Perform selection** – after **G.E1**, the corresponding input is selected and the output is set.
3. **Signal output** – **OUT.E1** is generated after successful selection.

## Application Scenarios

- **Switching between two measured values** (e.g., temperature from sensor A or B) based on a control signal.
- **Operating mode switching** in automation technology, where different control variables are activated depending on the mode.
- **Redundant signal sources** – if the primary channel (IN0) fails, the selector can switch to the secondary channel (IN1).

## Comparison with similar components

- **MUX (Multiplexer)**: A multiplexer selects from more than two inputs; **AUI_AX_SEL_AUI** is specialized for two inputs and uses adapters instead of individual signals.
- **F_SEL (Standard IEC 61131)**: The internal function block offers identical functionality, but without adapter encapsulation. This function block extends it with an adapter-based interface, which facilitates reuse in adapter-oriented architectures.
- **SEL (Selection)**: Similar logic, but usually defined as a pure function block without event control. Here, the selection is explicitly triggered by an event.

## Conclusion

**AUI_AX_SEL_AUI** is an adapter-based composite function block for simple binary selection between two AUI data streams. The use of `F_SEL` internally ensures robust and standards-compliant selection logic. The function block is particularly suitable for modular automation solutions where data is exchanged via unidirectional adapters.
