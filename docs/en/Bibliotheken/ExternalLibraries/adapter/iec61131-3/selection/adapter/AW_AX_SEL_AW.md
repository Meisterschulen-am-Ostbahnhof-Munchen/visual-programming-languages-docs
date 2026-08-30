# AW_AX_SEL_AW

![AW_AX_SEL_AW](./AW_AX_SEL_AW.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `AW_AX_SEL_AW` is used for binary selection between two analog or word-based input signals via a binary selector. The block is specifically designed for use with adapter-based interfaces in 4diac-ide (IEC 61499). It encapsulates the classic selection logic (`SEL`) and makes it available via unidirectional adapters for `WORD` data (`AW`) and binary control signals (`AX`).

## Interface Structure

### **Event Inputs**

There are no direct event inputs at the block level. Event processing is fully encapsulated via the adapter interfaces.

### **Event Outputs**

There are no direct event outputs at the block level. Event output is fully encapsulated via the adapter interfaces.

### **Data Inputs**

There are no direct data inputs at the block level.

### **Data Outputs**

There are no direct data outputs at the block level.

#### **Adapters**

#### **Sockets (Input Interfaces)**

- **G** (Type: `adapter::types::unidirectional::AX`):
- Selection input (selector). Determines which of the two inputs is passed through to the output.
- **IN0** (Type: `adapter::types::unidirectional::AW`):
- First selectable input channel (selected when `G` is in state `FALSE` or `0`).
- **IN1** (Type: `adapter::types::unidirectional::AW`):
- Second selectable input channel (selected when `G` is in state `TRUE` or `1`).

#### **Plugs (Output Interfaces)**

- **OUT** (Type: `adapter::types::unidirectional::AW`):
- Selected output channel carrying the value of the selected input.

## Functionality

The module is internally based on a network of standard function blocks to implement event-driven selection:

1. **Signal Buffering:** Events (`E1`) and data (`D1`) received via the adapters `IN0`, `IN1`, and `G` are buffered using D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively). This ensures that the data is consistently available as soon as an event occurs.
2. **Data Forwarding:** The data from the WORD adapters is passed to the central selection block via `F_MOVE` blocks (configured to the data type `WORD`).
3. **Selection Logic (F_SEL):** The block `F_SEL` (standard selection function) evaluates the state of the selector `G`:

- If `G.Q` = `FALSE`, the value of `IN0` is passed to the output.
- If `G.Q` = `TRUE`, the value of `IN1` is passed to the output.
1. **Output Triggering:** Any change to the inputs or the selector triggers the process via the event connections. The selected value is passed from the output buffer `E_D_FF_ANY_OUT` to the output plug `OUT`, and the corresponding output event `OUT.E1` is triggered.

## Technical Features

- **Adapter Encapsulation:** By exclusively using adapters, the cabling effort in the higher-level system is drastically reduced, as data and event lines are bundled in a single adapter channel.
- **Unidirectional Data Transmission:** The adapter types used, `AW` (Word Adapter) and `AX` (Bit/Boolean Adapter), are unidirectional, defining a clear signal flow direction.
- **Data Type:** The internal processing of analog values is fixed to the data type `WORD`.

## State Overview

Since this is a composite function block (FB) without its own state machine (ECC), its behavior is directly determined by the data and event flow of the internal components:

- **Event on G.E1:** The selector value is updated. The selection logic switches accordingly and updates the output `OUT`.
- **Event on IN0.E1 / IN1.E1:** The input data is updated. If the changed input corresponds to the channel currently selected via `G`, the new value is immediately forwarded to `OUT`, triggering the event `OUT.E1`.

## Application Scenarios

- **Setpoint Switching:** Optionally specify a setpoint (e.g., speed, pressure, temperature coded as `WORD`) from an automatic program (`IN1`) or manual operation (`IN0`).
- **Signal Routing:** Dynamic routing of data streams within modular control architectures.
- **Redundant Sensors:** Switching between a primary sensor and a backup sensor in case of signal errors.

## Comparison with Similar Function Blocks

- **Standard `F_SEL` (IEC 61131-3):** The standard selection function block works with direct elementary data types (e.g., WORD, BOOL) and does not have integrated event control for IEC 61499. `AW_AX_SEL_AW` extends this functionality with event coupling and packages it in standardized adapters.
- **Multiplexer (MUX):** A multiplexer allows selection from more than two channels using an integer index (INT). `AW_AX_SEL_AW`, on the other hand, is optimized for fast, binary selection (2 channels via BOOL/AX).

## Conclusion

The `AW_AX_SEL_AW` is a robust and reusable auxiliary module for structured programming in IEC 61499. It is ideally suited for applications that rely on a clean interface architecture using adapters and simplifies signal switching in industrial environments.
