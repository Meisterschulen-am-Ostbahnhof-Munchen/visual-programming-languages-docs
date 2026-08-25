# AIWS_AX_SEL_AIWS

![AIWS_AX_SEL_AIWS](./AIWS_AX_SEL_AIWS.svg)

*(No image available)*

* * * * * * * * * *
The function block `AIWS_AX_SEL_AIWS` is used for binary selection between two unidirectional adapter signals of type `AIWS`. Which of the two inputs is switched to the output is controlled by a control adapter of type `AX`.

 The function block encapsulates the classic selection logic (comparable to the `SEL` standard function block from IEC 61131-3) within the event-driven environment of IEC 61499. This enables clean, modular, and transparent signal switching directly at the adapter level, eliminating the need to individually wire event and data lines in the higher-level system.

Because it is an adapter-based function block, the block itself does not have direct, classic event or data inputs and outputs on its outer casing. All communication is handled via the adapter interfaces.

*No direct event inputs available (events are received via the adapter sockets).*

*No direct event outputs available (events are sent via the adapter plug).*

*No direct data inputs available.*

*No direct data outputs available.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

#### **Sockets (Input Adapters)**

* **`G`** (Type: `adapter::types::unidirectional::AX`):

The selector adapter. The data signal it contains determines which input is activated.

* **`IN0`** (Type: `adapter::types::unidirectional::AIWS`):

The first selectable input adapter. This is passed through to the output when the selector signal is in the state `FALSE` (0).

* **`IN1`** (Type: `adapter::types::unidirectional::AIWS`):

The second selectable input adapter. This is passed through to the output when the selector signal is in the state `TRUE` (1).

#### **Plugs (Output Adapters)**

* **`OUT`** (Type: `adapter::types::unidirectional::AIWS`):

The output adapter. It outputs the data and events of the currently selected input (`IN0` or `IN1`).

## Functionality

The function block's internal network implements signal forwarding and event synchronization as follows:

1. **Event Acquisition and Buffering:**

As soon as the event `E1` arrives at one of the sockets (`G`, `IN0`, or `IN1`), the corresponding data value `D1` is temporarily stored via an internal event-driven flip-flop (`E_D_FF` for the selector and `E_D_FF_ANY` for the data).

2. **Data Conversion / Assignment:**

The data from inputs `IN0` and `IN1` are transferred to the selection block via internal assignment elements (`F_MOVE`) of type `WSTRING`.

3. **Selection Process (`F_SEL`):**

The internal function block `F_SEL` (IEC 61131-3 `SEL`) evaluates the state of the selector from the adapter `G`:

* If the signal from `G` is in the state `FALSE`, the signal from `IN0` is passed to the output.
* If the signal from `G` is in the state `TRUE`, the signal from `IN1` is passed to the output.
* If the signal from `G` is in the state `TRUE`, the signal from `IN1` is passed to the output. 4. **Output:**

The selected signal is passed via another `F_MOVE` block and an output flip-flop (`E_D_FF_ANY_OUT`) to data point `D1` of the output plug `OUT`. Simultaneously, the event `E1` is triggered at the output to inform subsequent blocks about the data update.

* **Data type `WSTRING`:** The adapter data is processed internally via `F_MOVE` blocks with the data type `WSTRING`. This means that the user data within the `AIWS` adapter is transmitted and switched as wide strings.
* **Event Decoupling:** By using flip-flops (`E_D_FF`), it is ensured that any change to the inputs or the selector results in an immediate and consistent update of the output.

The logical mapping of the output, depending on the selector `G`, is as follows:

| State of `G` (selector) | Active path | Data value to `OUT.D1` | Event to `OUT.E1` |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Value of `IN0.D1` | Triggered by events at `IN0.E1` or `G.E1` |
| `TRUE` | `IN1` | Value of `IN1.D1` | Triggered by events at `IN1.E1` or `G.E1` |

* **Switching Analog Values with Status (formatted as WSTRING):** Redundant sensor systems where, in case of a fault, the system should switch from sensor 1 (`IN0`) to a backup sensor 2 (`IN1`).
* **Dynamic Text or Recipe Selection:** Switching configuration strings, log messages, or setpoints that are routed to an HMI or control unit via adapter structures.
* **Signal Routing:** Flexible routing in modular industrial plants where data streams need to be redirected depending on the operating mode (e.g., automatic vs. manual operation).
* ## Comparison with Similar Function Blocks
* **Standard `SEL` (IEC 61131-3):** The classic `SEL` function block operates on elementary data types (e.g., `INT`, `REAL`, `STRING`) and does not have native event control or adapter support. `AIWS_AX_SEL_AIWS` extends this principle for IEC 61499 by providing direct switching for complex adapter types.
* **Multiplexer (`MUX`):** A classic multiplexer allows selection from more than two channels via an integer index. The `AIWS_AX_SEL_AIWS` is optimized for fast and resource-efficient binary selection (2 channels).

The `AIWS_AX_SEL_AIWS` is a highly specialized auxiliary module for IEC 61499 systems (such as 4diac-ide) that elegantly and deterministically switches complex data and event streams between two adapters. It significantly reduces "spaghetti code" and confusing wiring in graphical programming environments.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion