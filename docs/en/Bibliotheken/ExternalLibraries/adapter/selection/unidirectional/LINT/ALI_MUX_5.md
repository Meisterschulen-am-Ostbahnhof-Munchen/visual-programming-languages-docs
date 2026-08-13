# ALI_MUX_5

![ALI_MUX_5](./ALI_MUX_5.svg)

* * * * * * * * * *
## Introduction

The function block **ALI_MUX_5** implements a generic multiplexer for five ALI adapter interfaces. It selects one of the five inputs **IN1** to **IN5** based on an index value **K** (0…4) and forwards its data to the output **OUT**. The selection is triggered by the **REQ** event and acknowledged with **CNF**.
## Interface Structure

### **Event Inputs**

| Event | Description | With data input |
|----------|--------------|-----------------|
| **REQ** | Starts the selection of index **K** and transmits the values of the selected adapter input to the output | K |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Confirms successful transmission after processing **REQ** |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| **K** | UINT | Index of the input to be multiplexed (0 = IN1, 1 = IN2, …, 4 = IN5) |

### **Data Outputs**

No direct data outputs are available. The output data is provided via the **OUT** adapter.

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Plug (Output) | **OUT** | `adapter::types::unidirectional::ALI` | Enabled output that provides the data of the input selected by **K** |
Socket (Input) | **IN1** | `adapter::types::unidirectional::ALI` | First input value (K = 0) |
Socket (Input) | **IN2** | `adapter::types::unidirectional::ALI` | Second input value (K = 1) |
Socket (Input) | **IN3** | `adapter::types::unidirectional::ALI` | Third input value (K = 2) |
Socket (Input) | **IN4** | `adapter::types::unidirectional::ALI` | Fourth input value (K = 3) |
Socket (Input) | **IN5** | `adapter::types::unidirectional::ALI` | Fifth input value (K = 4) |

## Functionality

1. The function block waits for the **REQ** event.
2. Upon arrival of **REQ**, the current value of the data input **K** is read.
3. The multiplexer connects the adapter inputs **IN1** … **IN5** to the output adapter **OUT** according to the index **K**.
4. As soon as the connection is established and the data is forwarded, the **CNF** event is sent.
5. For invalid index values (e.g., K ≥ 5), the behavior is undefined; the function block assumes correct index ranges.

## Technical Features

- **Generic Type**: The function block is declared as a generic function block (GenericClassName `GEN_ALI_MUX`) and can be instantiated in projects for different ALI data types.
- **Adapter-based**: The inputs and outputs are implemented as unidirectional ALI adapters, enabling flexible coupling to other ALI-compatible components.
- **Type Hash**: A `TypeHash` attribute is present but is passed as an empty string and can be completed at runtime by the framework.
- **Package Structure**: The component uses the `adapter::selection::unidirectional` package and imports `TypeHash` from the `eclipse4diac` core.

## State Overview

The component does not have explicit state machines (no ECC states are defined). The sequence control is purely event-driven:

- **IDLE**: Waiting for **REQ**.
- **BUSY**: Upon receiving **REQ**, the adapter connection is switched and **CNF** is triggered. The FB then immediately returns to the IDLE state.

## Application Scenarios

- **Data Source Switching**: Selection between five different sensors or data sources, all connected via the ALI adapter.
- **Redundancy Management**: A system with multiple identical measuring points can switch to a common evaluation using the multiplexer.
- **Configurable Signal Paths**: In control applications where different inputs must be active depending on the operating mode.

## Comparison with Similar Function Blocks

- **ALI_MUX_2 / ALI_MUX_4**: These function blocks offer the same functionality for two or four inputs, respectively. The ALI_MUX_5 expands the selection to five channels.
- **ALI_DEMUX**: The demultiplexer distributes one input signal to multiple outputs; the ALI_MUX_5 works in the opposite way.
- **SCALE/CLAMP blocks**: These perform signal processing, while the ALI_MUX_5 offers a simple pass-through function without data manipulation.

## Change Detection

The selected output plug (`OUT`) is only written and its adapter event only sent if the incoming value differs from the value currently held on `OUT`. If the value is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The **ALI_MUX_5** is a compact, generic multiplexer for five ALI adapter channels. Its purely adapter-based communication and simple event control make it ideal for modular automation solutions with changing data sources. Its generic nature allows it to be used with various ALI data types and facilitates reuse in different projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
