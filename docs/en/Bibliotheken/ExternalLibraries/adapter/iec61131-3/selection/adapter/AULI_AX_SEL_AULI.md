# AULI_AX_SEL_AULI

![AULI_AX_SEL_AULI](./AULI_AX_SEL_AULI.svg)

* * * * * * * * * *

## Introduction

The function block `AULI_AX_SEL_AULI` serves as a binary selector (multiplexer) in the 4diac framework. Based on a control signal from a selector adapter (`G`), it allows selection between two input signals from adapter inputs (`IN0` and `IN1`) and forwarding the selected signal to an output adapter (`OUT`).

The unique feature of this function block lies in the consistent use of unidirectional adapters for encapsulating events and data, resulting in a clean and modular structure within the higher-level application network.

## Interface Structure

Since this function block is entirely adapter-based, it has no direct, traditional event or data channels on its outer boundary. All communication is encapsulated within the adapters.

### **Event Inputs**

*No direct event inputs are available. Event control is implicit via the input adapters.*

### **Event Outputs**

*No direct event outputs are available. Event output is implicit via the output adapter.*

### **Data Inputs**

*No direct data inputs are available.*

### **Data Outputs**

*No direct data outputs are available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **G** (Type: `adapter::types::unidirectional::AX`):

The selector channel. The signal present here controls which of the two inputs is routed to the output.

### * **IN0** (Type: `adapter::types::unidirectional::AULI`):

The first selectable input channel. This value is passed to the output when the selector `G` is in the state `FALSE` (0).

- **IN1** (Type: `adapter::types::unidirectional::AULI`):

The second selectable input channel. This value is passed to the output when the selector `G` is in the state `TRUE` (1).

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AULI`):

The selected output channel, which carries the signal from the selected input (`IN0` or `IN1`).

## Functionality

Internally, the module is based on a network of standard function blocks from IEC 61131 and IEC 61499:

1. **Event Acquisition:** As soon as an event arrives at one of the inputs (`IN0.E1`, `IN1.E1`) or at the selector (`G.E1`), it is intercepted via edge-triggered event flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively), and the current data value (`D1`) is temporarily stored.
2. **Data Conversion & Transport:** The input data values are transferred to the central selection block via conversion blocks (`F_MOVE` with the data type `ULINT`).
3. **Selection Logic (Multiplexing):** The block `F_SEL` (Standard Selection) evaluates the state of the selector:
- If the value of `G` is equal to `FALSE`, the value of `IN0` is selected.
- If the value of `G` is equal to `TRUE`, the value of `IN1` is selected.
4. **Output:** After successful selection, the result is sent via a further conversion block (`F_MOVE_OUT`) to the output flip-flop (`E_D_FF_ANY_OUT`). This triggers the output event `OUT.E1` and assigns the selected value to `OUT.D1`.

## Technical Features

- **Data Type Specificity:** Internally, the selection operates on the data type `ULINT` (Unsigned Long Integer / 64-bit). This makes the function block particularly suitable for processing high-resolution counter values, timestamps, or large ID numbers.

## Technical Features

- **Data Type Specificity:** Internally, the selection operates on the data type `ULINT` (Unsigned Long Integer / 64-bit). This makes the function block particularly suitable for processing high-resolution counter values, timestamps, or large ID numbers.
- **Adapter Encapsulation:** By using adapters (`AULI` and `AX`), signal and event lines are bundled. This prevents "spaghetti code" in the system design.
- **Event-Driven:** The function block operates purely event-driven. No cyclic calculations are performed, which conserves resources.

## State Overview

The function block does not have its own explicit state chain (Execution Control Chart, ECC) because it is implemented as a pure network (FBNetwork). Its behavior is purely data- and event-flow-driven:

| Trigger Event | State Selector (`G.D1`) | Resulting Behavior | Output Event |
| :--- | :--- | :--- | :--- |
| Event on `G.E1`, `IN0.E1`, or `IN1.E1` | `FALSE` | Value of `IN0.D1` is copied to `OUT.D1` | `OUT.E1` |
| Event on `G.E1`, `IN0.E1`, or `IN1.E1` | `TRUE` | Value of `IN1.D1` is copied to `OUT.D1` | `OUT.E1` |

`| ] | ... ## Application Scenarios

- **Sensor Redundancy:** Switching between a primary sensor (`IN0`) and a backup sensor (`IN1`) based on a status signal (`G`).
- **Setpoint Switching:** Switching between an automatic setpoint (e.g., from a recipe control system) and a manually set user-defined setpoint.
- **Operating Mode Switching:** Routing of different data streams depending on the active system status (e.g., normal operation vs. maintenance mode).
- ## Comparison with Similar Components

Compared to the classic standard selector block `F_SEL`, `AULI_AX_SEL_AULI` offers the following advantages:
- **No manual wiring of events:** With `F_SEL`, data and event lines must be manually synchronized. Here, this happens automatically within the block through the use of adapters.
- **Increased type safety & clarity:** Connection errors in the higher-level control diagram are minimized because adapters can only be connected to matching counterparts.

## Conclusion

The `AULI_AX_SEL_AULI` is a robust, reusable, and event-driven selector block for 64-bit integer values. It is ideally suited for modern, component-based software architectures in IEC 61499, where clarity and standardized interfaces are paramount.
