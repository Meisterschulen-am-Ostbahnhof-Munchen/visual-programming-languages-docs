# AI_ADD_4

        +-------------------------+
IN1 =| [Socket]                |
   IN2 =| [Socket]         [Plug] |= OUT
IN3 =| [Socket]                |
IN4 =| [Socket]                |
        +-------------------------+

![AI_ADD_4](./AI_ADD_4.svg)

* * * * * * * * * *

## Introduction

The function block `AI_ADD_4` is a generic arithmetic block for the 4diac IDE, used to add four analog or numeric values. The unique feature of this block is the use of unidirectional adapters of type `AI` (Analog Input/Arithmetic Input) instead of traditional discrete data and event inputs. This enables a clean, modular, and clear structuring of signal flows in IEC 61499 applications.

## Interface Structure

The block does not have any traditional event- or data-based inputs and outputs at the top level. All communication is handled via adapters.

## **Event Inputs**

*No direct event inputs are available. Event control is encapsulated within the adapters.*

### **Event Outputs**

*No direct event outputs are available. Event control is encapsulated within the adapters.*

### **Data Inputs**

*No direct data inputs are available.*

### **Data Outputs**

*No direct data outputs are available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AI`): First addend for the addition operation.
- **IN2** (Type: `adapter::types::unidirectional::AI`): Second addend for the addition operation.
- **IN3** (Type: `adapter::types::unidirectional::AI`): Third addend for the addition operation.
- **IN4** (Type: `adapter::types::unidirectional::AI`): Fourth addend for the addition operation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AI`): Output adapter that provides the result of the addition (`IN1 + IN2 + IN3 + IN4`).

## Functionality

As soon as a new event is signaled at one of the input adapters (`IN1` to `IN4`) indicating that a value has changed, the function block performs the following internal addition:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

The result is immediately passed to the output adapter `OUT`, and the corresponding update event of the output adapter is triggered. Since this is a generic function block (`GEN_AI_ADD`), the actual data type (e.g., `REAL`, `INT`, `LREAL`) depends on the specific implementation and instantiation of the adapter type used.

## Technical Features

- **Generic Design:** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AI_ADD'`. This makes it highly flexible and allows it to be applied to different numeric data types, provided the adapters used support this.
- **Generic Design:** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AI_ADD'`. * **Unidirectional Adapters:** Using `unidirectional::AI` adapters drastically reduces wiring complexity in the function block diagram, as data and trigger events are bundled in a single connection.

## State Overview

The function block behaves purely reactively (event-driven):

1. **Wait State (Idle):** The function block waits for an update event at one of the sockets (`IN1` to `IN4`).
2. **Calculation:** Upon receiving an event, the current values of all four inputs are read and added together.
3. **Output:** The calculated value is written to the plug `OUT`, triggering the corresponding output event. The function block immediately returns to the wait state.

## Application Scenarios

- **Measurement Aggregation:** Summing of currents, powers, or flow rates from four different sources or sensors.
- **Average Preparation:** Combining four analog measurement values for subsequent division (e.g., for moving average calculation or redundancy checks).
- **Setpoint Offset Calculation:** Adding base setpoints, correction values, and user offsets in process engineering plants.

## Comparison with Similar Function Blocks

| Feature / Function Block | `AI_ADD_4` | Standard `ADD` (IEC 61131-3) |
| :--- | :--- | :--- |
| **Interface Type** | Adapter-based (`AI`) | Standard Data and Event Pins |
| **Number of Inputs** | Fixed (4) | Variable / Fixed (usually 2) |
| **Wiring Effort** | Very low (only 5 connections) | High (separate event and data lines) |
| **Typing** | Generic via adapter | Explicit via FB typing (e.g., `ADD_REAL`) |

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AI_ADD_4` is a highly efficient and modern function block that fully utilizes the advantages of adapter-based coupling in IEC 61499. It is ideally suited for complex control architectures where clarity in the application diagram and a clear signal structure are paramount.
