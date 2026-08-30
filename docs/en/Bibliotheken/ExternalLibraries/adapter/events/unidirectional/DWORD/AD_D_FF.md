# AD_D_FF

![AD_D_FF](./AD_D_FF.svg)

* * * * * * * * * *
The function block **AD_D_FF** implements a **data latch (D flip-flop)**. It receives a data value upon an incoming event and holds this value until the next data transfer. The interface is defined exclusively via standardized **adapters**, which allows for flexible wiring in complex automation systems.

No direct event inputs. The function block uses only the **input adapter `I`**, which provides the clock signal via its internal event channel.

No direct event outputs. The FB uses only the **output adapter `Q`**, which signals via its internal event channel that a new data value is available.

No direct data inputs. The value to be latched is provided via the **data channel of the input adapter `I`**.

No direct data outputs. The latched value is provided via the **data channel of the output adapter `Q`**.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| `I` (Socket) | Input | `adapter::types::unidirectional::AD` | Provides the clock signal (E1) and the data value to be stored (D1). |
| `Q` (Plug) | Output | `adapter::types::unidirectional::AD` | Outputs the stored data value after the clock event (E1 as acknowledgment, D1 as data). |

The adapters of type `unidirectional::AD` each define one event channel (`E1`) and one data channel (`D1`). The exact data types are defined by the adapter definition (usually `ANY`).

The adapters of type `unidirectional::AD` define one event channel (`E1`) and one data channel (`D1`). The exact data types are defined by the adapter definition (usually `ANY`).

## Functionality

The function block (FB) internally uses the elementary block `E_D_FF_ANY` (from the IEC 61499 standard library). Its behavior is as follows:

1. **Upon each event at the clock input (CLK)**, the current data value at input `D` is transferred to output `Q`. This transfer is triggered by an edge (rising edge of the event).
2. Output `Q` remains unchanged until a new clock event arrives.

The connection in the FB network:

- The event `I.E1` is connected to `CLK`.
- The date `I.D1` is linked to `D`.
- The event output `EO` of the internal function block is forwarded to `Q.E1`.
- The data output `Q` of the internal function block is forwarded to `Q.D1`.

Thus, with each event at the input adapter, the incoming data value is received and immediately output via the output adapter. The value is retained until the next event.

- **Pure Adapter Interface:** The function block does not have traditional event/data ports but communicates exclusively via adapters. This enables its use in systems with standardized connections (e.g., via specific fieldbus adapter profiles).
- **Type Transparency:** Since the adapters are generic (`ANY`), the function block (FB) can work with different data types – provided that both the input and output adapters use the same data type.
- **No Internal State Machine:** The FB implements the flip-flop behavior through the pure data/event wiring of the internal `E_D_FF_ANY`. It does not have its own state machine.

The FB does not have an explicit state machine. The internal block `E_D_FF_ANY` internally stores the saved value (state). However, from the perspective of event processing, the FB is stateless: Every event at the input immediately triggers an output.

- **Signal Buffering:** A data value should be "frozen" upon a specific event and made available for subsequent processing steps.
- **Standardized data coupling:** In architectures that rely on adapter interfaces (e.g., in agricultural machinery), the function block can be used as a universal latch component.
- **RS flip-flop (AD_RS_FF):** Stores two states (Set/Reset) and requires two event/data channels. The AD_D_FF operates with only one clock signal and one data point – simpler and more deterministic.
- **E_D_FF_ANY (direct):** Offers the same functionality, but with classic event/data ports instead of adapters. The AD_D_FF encapsulates this logic in an adapter interface, which facilitates reuse in adapter-based environments.
- **Toggle FF (AD_T_FF)** or **JK FF:** More complex flip-flops with multiple inputs; the AD_D_FF is the simplest form of a data-controlled memory.

The **AD_D_FF** is a lightweight, adapter-based D flip-flop device for the 4diac IDE. It takes a data value on each clock event and outputs it. Thanks to its simple adapter interfaces, it integrates seamlessly into architectures that rely on standardized connections. Its straightforward functionality makes it the ideal choice for data buffering and synchronization tasks without the need for additional logic.

The **AD_D_FF** is a lightweight, adapter-based D flip-flop device for the 4diac IDE. ---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
