# AI_D_FF

![AI_D_FF](./AI_D_FF.svg)

* * * * * * * * * *

## Introduction

The function block **AI_D_FF** implements a data latch (D flip-flop) for the temporary storage of a data value. It serves as an adapter-encapsulated implementation of an edge-triggered D flip-flop according to IEC 61499, which, upon an event at the input, takes the incoming data value and makes it available at the output.

## Interface Structure

### **Event Inputs**

No direct event inputs.

### **Event Outputs**

No direct event outputs.

### **Data Inputs**

No direct data inputs.

### **Data Outputs**

No direct data outputs.

### **Adapter**

| Name | Direction | Type | Description |
| ------------- | ---------- | ----- | -------------- |
| **I** | Socket | `adapter::types::unidirectional::AI` | Returns the input event (E1) and the data value to be latched (D1). |
| **Q** | Plug | `adapter::types::unidirectional::AI` | After the latch is closed, outputs the result event (E1) and the stored data value (D1). |

The `AI` adapter is unidirectional, meaning that data and event flows only in one direction. Socket **I** serves as the input, and Plug **Q** as the output.

## Functionality

The internal component is a `E_D_FF_ANY` function block (IEC 61499 D flip-flop). The wiring connects:

- `I.E1` → `E_D_FF_ANY.CLK` (clock edge)
- `I.D1` → `E_D_FF_ANY.D` (data input)
- `E_D_FF_ANY.EO` → `Q.E1` (output event)
- `E_D_FF_ANY.Q` → `Q.D1` (latching data value)

**Process:**

An event at `I.E1` triggers a rising edge at the clock input of the internal flip-flop. The current value of `I.D1` is transferred and is available at `Q.D1` after processing is complete. Simultaneously, an event is output to `Q.E1`, signaling the validity of the new data value.

## Technical Features

- **Adapter Encapsulation:** The function block (FB) has no direct inputs/outputs, but only adapter interfaces. This facilitates reuse in modular architectures where multiple signals are bundled and transmitted.
- **Unidirectional Data Flow:** The adapters are designed as pure sources (plugs) or sinks (sockets), which clearly defines the signal direction.
- **Edge-Triggered:** The transfer occurs only upon an event (rising edge), not upon level changes. Therefore, the function block is suitable for clocked systems.
-

## State Overview

The internal state of the flip-flop is determined by the stored value `Q`. Two stable states exist:

| Clock (CLK) | D (Input) | Q (Output) before | Q (Output) after |
| ------------ | ------------- | --------------------- | ---------------------- |
| No event | - | Q_old | Q_old |
| Event (rising edge) | 0 | X | 0 |
| Event (rising edge) | 1 | X | 1 |

For each event at `I.E1`, the current D value is adopted, regardless of the previous Q value.

## Application Scenarios

- **Analog Value Sampling:** A sensor (e.g., temperature, pressure) periodically delivers a measured value via the `I` adapter. The function block stores this value upon a trigger event and passes it on to the subsequent logic.
- **Cable Storage in Data Paths:** In conveyor belt or pipeline structures, `AI_D_FF` can be used as a data hold to buffer values for one clock cycle.
- **Debouncing / Edge Processing:** Combined with a clock generator, the function block can be used to process incoming signals only at specific times.

## Comparison with Similar Function Blocks

- **E_D_FF** (without adapter): Offers direct event and data inputs/outputs but is less abstract. `AI_D_FF`, on the other hand, encapsulates the signals in adapters, which simplifies composition in higher hierarchies.
- **SR Flip-Flop (S/R dominant):** Stores state via set/reset, while `AI_D_FF` only takes over on clock edges and has no reset function.
- **Latch (level-controlled):** Unlike a latch, `AI_D_FF` only reacts to edges, making it better suited for synchronized systems.

## Conclusion

The **AI_D_FF** is a compact, adapter-based D flip-flop device that stores and outputs a data value on an edge-triggered basis. By using unidirectional adapters, it integrates seamlessly into modern, modular automation concepts and enables a clean separation of data and event signals. Its application is particularly suitable for clocked sampling and buffering tasks in IEC-61499 systems.
