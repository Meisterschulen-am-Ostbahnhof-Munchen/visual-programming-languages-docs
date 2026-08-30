# ALI_AX_SEL_ALI

![ALI_AX_SEL_ALI](./ALI_AX_SEL_ALI.svg)

*[Image of the function block]*

* * * * * * * * * *

## Introduction

The function block `ALI_AX_SEL_ALI` is a binary selection block designed for use with unidirectional adapters. It allows you to select between two input signals based on a selector signal and then output the selected signal. This block encapsulates the standard selection logic and adapts it to an event-driven adapter interface.

## Interface Structure

Because it is an adapter-based function block, it does not have direct, traditional event or data inputs at the top level. All communication is handled via adapters.

### **Event Inputs**

*No direct event inputs available (control is via the adapters).*

### **Event Outputs**

*No direct event outputs available (control is via the adapters).*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Interfaces)**

- **G** (`adapter::types::unidirectional::AX`): The selector adapter (gate). It controls which of the two inputs is routed to the output.
- **IN0** (`adapter::types::unidirectional::ALI`): The first selectable input adapter (selected by default for `G = FALSE`).
- **IN1** (`adapter::types::unidirectional::ALI`): The second selectable input adapter (selected at `G = TRUE`).

#### **Plugs (Output Interfaces)**

- **OUT** (`adapter::types::unidirectional::ALI`): The output adapter that provides the selected signal and the corresponding event.

---

## Functionality

The function block operates as a multiplexer for the adapter signals:

1. **Event Detection**: As soon as an event (`IN0`, `IN1`) is received by one of the input adapters (`G`) or the selector adapter (`G`), it is intercepted via internal edge-triggered flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively).
2. **Data Buffering**: The data from the inputs (`IN0.D1` and `IN1.D1`) are passed via internal `F_MOVE` function blocks (configured to the data type `LINT`) to the central selection function block `F_SEL`.
3. **Selection**: The function block `F_SEL` evaluates the state of the selector `G.D1`:

- If `G.D1` is set to `FALSE`, the value of `IN0` is selected.
- If `G.D1` is set to `TRUE`, the value of `IN1` is selected.
1. **Output**: The selected value is passed to the flip-flop `E_D_FF_ANY_OUT`. This updates the output data point `OUT.D1` and simultaneously triggers the output event `OUT.E1`.

---

## Technical Features

- **Data Type Specificity**: The internal shift blocks (`F_MOVE`) are fixed to the data type `LINT` (Long Integer). This means that the data transmitted via the `ALI` adapter is interpreted and processed as `LINT`.
- **Event Decoupling**: The use of flip-flops (`E_D_FF`) ensures that data changes at the inputs arrive at the output consistently and synchronously with the corresponding events.

---

## State Overview

The function block does not have its own state hierarchy (no ECC) because it is implemented as a composite network function block (FB). Its behavior is purely data- and event-flow-driven:

| State Selector (`G.D1`) | Trigger Event | Action / Result |
| :--- | :--- | :--- |
| `FALSE` | Event on `IN0.E1`, `IN1.E1`, or `G.E1` | The value of `IN0.D1` is passed to `OUT.D1`; `OUT.E1` is triggered. |
| `TRUE` | Event on `IN0.E1`, `IN1.E1`, or `G.E1` | The value of `IN1.D1` is passed to `OUT.D1`; `OUT.E1` is triggered. |

` | | ... ---

## Application Scenarios

- **Setpoint Switching**: Selection between an automatic setpoint (e.g., calculated by a controller) and a manually specified setpoint in an industrial plant.
- **Sensor Redundancy**: Switching between two redundant sensors (e.g., in case of failure or for calibration) that provide their data via standardized adapter interfaces.
- **Recipe-Controlled Path Selection**: Dynamic selection of process parameters based on a binary control signal in the sequence program.

--

## Comparison with Similar Function Blocks

- **F_SEL (Standard IEC 61131-3)**: The standard selection effect block works directly with elementary data types and requires explicit event connections. `ALI_AX_SEL_ALI` encapsulates this component and extends it with direct support for the more structured and cleaner use of unidirectional adapters (`ALI`/`AX`).
- **Classic Multiplexers (MUX)**: While a MUX can often handle multiple channels (e.g., 4, 8), this component is strictly optimized for binary selection (2 channels) but offers streamlined adapter integration.

---

## Conclusion

The `ALI_AX_SEL_ALI` is a specialized auxiliary component that simplifies signal and event routing in complex 4diac systems. By encapsulating the adapter logic, it significantly improves the clarity of the application network by eliminating the need for manually unpacking and repackaging adapter signals.
