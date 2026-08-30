# AULI_D_FF_HYS

![AULI_D_FF_HYS](./AULI_D_FF_HYS.svg)

* * * * * * * * * *

## Introduction

The function block `AULI_D_FF_HYS` implements a data latch (D flip-flop) with adjustable hysteresis. It encapsulates the logic of such a flip-flop in an adapter-based interface and allows the transmission of data and events via unidirectional adapters of type `AULI`.

## Interface Structure

### **Event Inputs**

- `INIT` (EInit): Sets the hysteresis value and initializes the function block.

## **Event Outputs**

- `INITO` (EInit): Confirms the successful initialization process (passed-through INIT).

### **Data Inputs**

- `HYSTERESIS` (ULINT): Sets the hysteresis width. The value is taken during the INIT event.

### **Data Outputs**

No direct data outputs are available; the output data is provided via the `Q` adapter.

### **Adapters**

- **Socket `I`** (Type `adapter::types::unidirectional::AULI`): Receives the value to be latched and the associated clock signal.
- **Plug `Q`** (Type `adapter::types::unidirectional::AULI`): Passes on the latched value and the output event.

## Functionality

The module internally uses the sub-module `E_D_FF_ANY_HYS`. The clock signal (`I.E1`) is fed to the CLK input and the data value (`I.D1`) to the D input of the sub-module via socket `I`. The data input `HYSTERESIS` is directly connected to the corresponding input of the sub-module. The output `Q` of the sub-module is transferred to the data output of the plug `Q` (`Q.D1`), and the event `EO` of the sub-module is mapped to the output event of the plug `Q` (`Q.E1`).

The INIT event is passed through unchanged as INITO. The actual hysteresis initialization is performed by the sub-module upon receiving INIT, adopting the current value of `HYSTERESIS`.

The hysteresis prevents the output from switching immediately in response to small fluctuations in the input signal. Only when the input value exceeds or falls below the latched value by more than the hysteresis band is a new value adopted.

## Technical Features

- The function block is defined as a pure interaction of adapters and a sub-function block (no dedicated ECC or SIFB logic).
- The use of the adapter type `AULI` (unidirectional) allows for a clear separation of data and events in a standardized interface.
- Hysteresis is set only during the INIT event; thereafter, the value remains constant for the duration of operation.
- The function block is available under the Eclipse Public License 2.0 and is defined in the IEC 61499 Annex A standard structure.

## State Overview

The function block does not have its own state machine. The entire state logic is implemented in the sub-function block `E_D_FF_ANY_HYS`, which presumably implements two states (setting the latch, checking hysteresis).

## Application Scenarios

- **Debouncing of Sensors or Switches**: A noisy digital signal is only accepted as a stable value if it exceeds the hysteresis band.
- **Signal Smoothing**: Small fluctuations in a measured value are suppressed, while significant changes are immediately passed through.
- **Data Backup in Asynchronous Systems**: The function block serves as a reliable buffer between a signal source and a subsequent processing unit.

## Comparison with Similar Function Blocks

- A simple D flip-flop (e.g., `E_D_FF`) accepts the input value on every rising edge without hysteresis. The `AULI_D_FF_HYS` extends this functionality with a configurable switching threshold.
- Compared to a Schmitt trigger IC, the focus here is on the latching behavior with added hysteresis, not on level conversion.

## Conclusion

The `AULI_D_FF_HYS` is a compact, adapter-based functional IC for reliable signal conditioning with hysteresis. By delegating the logic to a specialized sub-IC, the design remains maintainable and expandable. It is particularly suitable for applications where noise or unstable input signals need to be filtered without having to forgo a simple flip-flop.
