# AUS_D_FF

![AUS_D_FF](./AUS_D_FF.svg)

* * * * * * * * * *
The function block **AUS_D_FF** implements a data latch (D flip-flop) for the data type `AUS`. Upon receiving an event, it stores the incoming data value and outputs this stored value via an adapter output. Communication occurs exclusively via unidirectional adapters.
No direct event inputs. Event-driven data transfer occurs via the adapter input **I** (see section Adapters).

No direct event outputs. The output of the stored value is signaled via the adapter output **Q** (see section Adapters).

No direct data inputs. The data to be stored is provided via the adapter input **I**.

No direct data outputs. The stored value is output via the adapter output **Q**.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| **I** | Socket | `adapter::types::unidirectional::AUS` | Provides the signal to be latched (event E1 and data D1). |
| **Q** | Plug | `adapter::types::unidirectional::AUS` | Outputs the latched value (event E1 and data D1). |

The internally used module `E_D_FF_ANY` expects an event (inherited from **I.E1**) at its **CLK** input and the corresponding data value (from **I.D1**) at **D**. The output event **EO** is forwarded to **Q.E1**, and the stored data value **Q** to **Q.D1**.

## Functionality

As soon as an event arrives at the adapter input **I** (pin **E1**), the simultaneously present data value (pin **D1**) is transferred to the internal memory. After successful transfer, an event is triggered at the adapter output **Q** (pin **E1**), and the stored value is available at **Q.D1**. The stored value is retained until a new event at **I.E1** transfers a new value.

- **Adapter-based interface:** The component uses only unidirectional adapters, enabling loose coupling and flexible interconnection.
- **No dedicated event/data pins:** All input and output is handled via the **I** and **Q** adapters.
- **Internal standard flip-flop:** The actual latch functionality is provided by the IEC 61499 component `E_D_FF_ANY`, which is specified to operate on any data type template.

The component has an implicit internal state – the stored data value (`Q` output). This only changes when an event occurs at **I.E1**. There is no explicit state machine in the FBNet; The state is managed by the internal `E_D_FF_ANY`.

- **Cache Storage:** A signal (value + event) is to be cached for later processing, e.g., in a control sequence where a sensor value is only to be acquired at a specific clock cycle.
- **Data Synchronization:** An asynchronously arriving data value is latched synchronously with an event and then used in the subsequent program flow.
- **State Maintenance:** The function block remembers the last valid value until a new value is explicitly acquired.
- **SR Flip-Flop:** Sets or resets the output via separate set/reset inputs; stores only Boolean or binary states. `AUS_D_FF`, on the other hand, stores general data values of type `AUS`.
- **Toggle Flip-Flop (T-FF):** Toggles the output on every clock cycle. `AUS_D_FF` takes the current data value and outputs it unchanged.
- **MUX-based Latch:** A multiplexer could also store a value, but requires additional reset logic. `AUS_D_FF` already encapsulates this logic.

The **AUS_D_FF** is an easy-to-use latching device that uses adapters to take a stored data-event pair and pass it on. Due to its adapter interface and the use of a standardized internal flip-flop, it is suitable for modular and reusable control designs in the IEC 61499 environment.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion