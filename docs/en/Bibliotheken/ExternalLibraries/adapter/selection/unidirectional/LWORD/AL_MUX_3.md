# AL_MUX_3
![AL_MUX_3](./AL_MUX_3.svg)
* * * * * * * * * *
## Introduction
The **AL_MUX_3** is a generic multiplexer (signal switch) for AL data adapters. Depending on the index **K**, it selects one of three inputs (IN1, IN2, IN3) and forwards its data to the output **OUT**. The module operates in an event-driven manner: A **REQ** event triggers the selection, and the result is acknowledged via **CNF**.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Requests the selection of the input determined by **K**. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirms selection (no data transfer) |

### **Data Inputs**

| Variable | Type | Description |

|----------|------|--------------------------------------------|

| K | UINT | Index of the input to be selected (0/1/2) |

### **Data Outputs**

– No direct data outputs are available. Data is only transmitted via the **OUT** adapter.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|---------------------------------------|----------------------------------------|

| Plug | OUT | adapter::types::unidirectional::AL | Output that passes on the selected input |

Socket | IN1 | adapter::types::unidirectional::AL | Input 1 (passes through when K = 0) |

Socket | IN2 | adapter::types::unidirectional::AL | Input 2 (passes through when K = 1) |

Socket | IN3 | adapter::types::unidirectional::AL | Input 3 (passes through when K = 2) |

## Functionality
The function block waits for a **REQ** event. Upon its arrival, the value of **K** (0, 1, or 2) is evaluated. The corresponding input adapter (IN1 when K = 0, IN2 when K = 1, IN3 when K = 2) is switched to the output adapter **OUT**. The data from the selected input is then available at the output. After the switchover is complete, a **CNF** event is output. For invalid values of K (e.g., > 2), the output remains unchanged or no valid signal is passed on (depending on the implementation environment).

## Technical Features
- The function block is declared as a **generic function block** ("GEN_AL_MUX"), meaning it can be reused in different contexts.
- The interfaces are implemented exclusively as **adapters** of type `adapter::types::unidirectional::AL`. This allows for flexible coupling with other AL-compatible function blocks.
- No custom values are cached – selection is purely logical via the index.
- The maximum number of inputs is fixed at three, but can be extended by derived variants.

## State Overview
Since the function block does not have an explicit state machine (IEC 61499 basis), it can be considered **stateless**. The response to **REQ** is deterministic without internal branching. The only relevant state is waiting for the next event after successful **CNF** confirmation.

## Application Scenarios
- **Signal Switching**: Selection of a sensor signal from three sources (e.g., temperature, pressure, level) for processing by a subsequent function block.
- **Operating Mode Switching**: A controller can select between different algorithms or parameter settings.
- **Redundancy**: Fallback to a second or third data path if a primary signal fails.

## Comparison with Similar Function Blocks
- **AL_MUX** (Standard 2-Input Multiplexer): Offers only two channels; the AL_MUX_3 extends this to three.
- **MUX_ANY**: A data-type-independent multiplexer (e.g., for `ANY` types) typically works with simple data variables and not with adapters. The AL_MUX_3 is specifically designed for the **AL** adapter type.
- **SELECT**: A similar function block (e.g., from the IEC 61499-2 Standard Library) often operates using event-driven Boolean conditions. The AL_MUX_3 uses a numeric index.

## Conclusion
The **AL_MUX_3** is a simple yet useful multiplexer function block for adapter-based AL data. It is particularly suitable for scenarios where one data source needs to be dynamically selected from several similar data sources. Its clear event-driven operation and generic nature make it easy to integrate into automation solutions based on IEC 61499 and the 4diac framework.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]