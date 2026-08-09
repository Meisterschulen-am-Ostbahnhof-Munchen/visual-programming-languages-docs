# AD_DWORD_AX_SEL_AD

                     +-----------------------------+
|     AD_DWORD_AX_SEL_AD      |
|                             |
         [AX] G ====>| S                         P |====> OUT [AD]
[AD] IN0 ====>| S                           |
|                             |
(Event) EI1 --->| EI1                         |
(DWORD) IN1 ---->| IN1                         |
                     +-----------------------------+

![AD_DWORD_AX_SEL_AD](./AD_DWORD_AX_SEL_AD.svg)

* S = Socket / P = Plug
* * * * * * * * * *
The function block `AD_DWORD_AX_SEL_AD` is a composite function block for IEC 61499 systems. It is used for the binary selection of `DWORD` values. The block enables event-driven switching between a value fed in via an adapter (`IN0`) and a data value directly connected to the block (`IN1`). The selection signal and the selected output value are also transmitted via standardized adapters.

* **EI1**: Triggers the update and transfer of the directly connected data input `IN1`.
* *No direct event outputs.* (Event output is encapsulated via the adapter plug `OUT`).
* **IN1** (DWORD): Directly available, selectable input variable.
* *No direct data outputs.* (Data output is encapsulated via the adapter plug `OUT`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AD`): Outputs the selected `DWORD` value (`D1`) and the corresponding update event (`E1`).
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): Selector input. Controls, via a Boolean signal, which of the two inputs (`IN0` or `IN1`) is connected to the output `OUT`.

---

## Functionality

The component uses a combination of flip-flops (`E_D_FF_ANY` and `E_D_FF`) for state storage and the standard selector component `F_SEL`.

1. **Value Storage**: As soon as an event arrives at `IN0.E1`, `G.E1`, or the direct input `EI1`, the internal flip-flops store the current data values from `IN0.D1`, `G.D1`, and `IN1`, respectively.
2. **Switching (Selection)**:
* If the adapter's selection signal is `G` (value `G.D1`) **`FALSE`**, the value of **`IN0`** (via the internal function block `F_MOVE_IN0`) is passed to the selector.
* If the adapter's selection signal is `G` (value `G.D1`) **`TRUE`**, the value of **`IN1`** (via the internal function block `F_MOVE_IN1`) is selected.
3. **Output**: The selected value is passed to the output adapter `OUT`, and the event `OUT.E1` signals the successful update of the output.

---

* **Asynchronous Processing**: The internal data flip-flops buffer signal states until a logical evaluation takes place. This ensures reliable processing even with events occurring at different times.
* **Hybrid Interface**: The component combines the classic event/data-based IEC 61499 modeling (input `IN1` / `EI1`) with the more modern, adapter-based modeling (`IN0`, `G`, `OUT`). This facilitates integration into existing, mixed architectures.

---

The following table shows the output behavior depending on the selection signal `G`:

| Selector State (`G.D1`) | Selected Input | Output Value (`OUT.D1`) | Triggering Event |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Value of `IN0.D1` | `IN0.E1` or `G.E1` |
| `TRUE` | `IN1` | Value of `IN1` | `EI1` or `G.E1` |

---

* **Manual/Automatic Switching**: Selection between a manually specified DWORD value (e.g., via an HMI on `IN1`) and an automatic value from the process control (via adapter `IN0`).
* **Recipe and Parameter Control**: Dynamic switching of configuration or threshold values in DWORD format during operation.
* **Modular Signal Routing**: Reduction of wiring effort in complex control applications by encapsulating data and event lines in adapters.
* ---
* **`F_SEL` (IEC 61131-3)**: The standard selection component lacks event handling and adapter support. `AD_DWORD_AX_SEL_AD` extends this basic functionality with event handling and encapsulation via adapters.
* **Standard Multiplexers**: Often require numerous individual event and data lines for each channel. This component reduces the "spaghetti design" in the 4diac application window by using standardized adapter interfaces.

--

The `AD_DWORD_AX_SEL_AD` is a robust and flexible auxiliary component for structured signal processing. It is ideally suited for applications where clarity and the consistent use of adapters to reduce connection complexity are paramount.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion