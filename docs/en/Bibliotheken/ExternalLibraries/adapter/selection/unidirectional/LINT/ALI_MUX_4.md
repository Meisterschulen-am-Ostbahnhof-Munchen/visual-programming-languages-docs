# ALI_MUX_4
![ALI_MUX_4](./ALI_MUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **ALI_MUX_4** is a generic multiplexer for ALI adapters. Depending on an index value *K*, it selects one of four ALI inputs (IN1, IN2, IN3, IN4) and forwards its data via the ALI output OUT. The block is controlled by the REQ event and acknowledges the switching with CNF.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Accepts index K and passes the selected input through to the output. Coupled with the data input K. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirmation that the switchover according to index K has occurred. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| K | UINT | Index for selecting the active input (0 = IN1, 1 = IN2, 2 = IN3, 3 = IN4). |

### **Data Outputs**

No data outputs are available; output is exclusively via the OUT adapter.

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|----------------------------------|----------|--------------|

| IN1 | adapter::types::unidirectional::ALI | Input (Socket) | First ALI input (selected when K=0). |

IN2 | adapter::types::unidirectional::ALI | Input (Socket) | Second ALI input (selected when K=1). |

IN3 | adapter::types::unidirectional::ALI | Input (Socket) | Third ALI input (selected when K=2). |

IN4 | adapter::types::unidirectional::ALI | Input (Socket) | Fourth ALI input (selected when K=3). |

OUT | adapter::types::unidirectional::ALI | Output (Plug) | Selected ALI output that provides the data stream of the active input. |

## Functionality
The module operates as a **1-out-of-4 selector** based on ALI adapter connections. A valid cycle begins with a REQ event that takes the current value of index *K*. The corresponding ALI input (IN1 for K=0, IN2 for K=1, IN3 for K=2, IN4 for K=3) is then switched to output OUT. After successful switching, the CNF event is output. Only the index values 0 to 3 specified in the specification can be processed; values outside this range result in undefined behavior.

## Technical Features
- **Generic Structure**: The function block (FB) is implemented as a generic block (Generic FB) but can only be used with ALI adapters of type `unidirectional`.
- **No Dedicated Data Outputs**: Information is transmitted exclusively via the ALI adapter interface, not via elementary data ports.
- **Event-driven selection**: Switching occurs only upon an explicit REQ event, not continuously.
- **Type hash**: The function block contains an attribute `eclipse4diac::core::TypeHash` for runtime identification.

## State overview
The function block essentially has a single operational state. Upon a REQ event, the selection is performed and CNF is sent immediately. There is no state storage or delay; the function block can be understood functionally as a **combinational circuit with an event gate**.

## Application scenarios
- **Switching between multiple ALI data sources**, e.g., sensor data from different machine modules.
- **Channel selection in an ALI-based bus system**, where different data streams are used depending on the operating mode.
- **Test and diagnostic applications**, where different ALI signals are sequentially applied to an analysis station.

## Comparison with Similar Components
- Compared to conventional multiplexers for elementary data types (e.g., `MUX` for `INT` or `BOOL`), `ALI_MUX_4` works exclusively with the ALI adapter protocol and therefore exchanges complex, structured data.
- Unlike a simple data multiplexer, which copies the values directly, the adapter multiplexer forwards the entire connection (including event and data paths).
- An adapter demultiplexer (`ALI_DEMUX_4`) would distribute one input to multiple outputs – here, the function is exactly the opposite.

## Conclusion

`ALI_MUX_4` is a specialized, event-driven multiplexer for ALI adapters with four inputs. It is ideally suited for applications where one ALI data source needs to be selected from multiple sources. Its simple interface (one index and one control event) makes it easy to integrate, but requires adherence to the valid index range of 0–3. This component adds a basic selection function to the ALI adapter family.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]