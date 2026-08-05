# AB_SPLIT_5
![AB_SPLIT_5](./AB_SPLIT_5.svg)

* * * * * * * * * *
## Introduction
The function block `AB_SPLIT_5` is used to distribute one unidirectional AB adapter input (socket) to five identical AB adapter outputs (plugs). It is a generic function block designed for signal distribution in automation systems.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None. Data transmission occurs exclusively via the adapter interfaces.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |

|----------|-----|-----|--------------|

**Socket** (Input) | `IN` | `adapter::types::unidirectional::AB` | Unidirectional AB adapter providing the input signal. |

**Plug** (Output) | `OUT1` | `adapter::types::unidirectional::AB` | First unidirectional AB adapter output. |

**Plug** (Output) | `OUT2` | `adapter::types::unidirectional::AB` | Second unidirectional AB adapter output. |

**Plug** (Output) | `OUT3` | `adapter::types::unidirectional::AB` | Third unidirectional AB adapter output. |

**Plug** (Output) | `OUT4` | `adapter::types::unidirectional::AB` | Fourth unidirectional AB adapter output. |

**Plug** (Output) | `OUT5` | `adapter::types::unidirectional::AB` | Fifth unidirectional AB adapter output. |

## Functionality

The module receives a unidirectional AB signal via socket `IN`. This signal is forwarded without modification to all five plugs (`OUT1` to `OUT5`). This creates five identical copies of the input signal, which can be connected in parallel to various subsequent components or systems.

Since the component has no event or data inputs, all communication takes place exclusively via the adapter interfaces. Distribution is static and without delay or buffering.

## Technical Features
- **Generic Component**: `AB_SPLIT_5` uses the generic class name `GEN_AB_SPLIT` and enables type-safe instantiation in the 4diac IDE.
- **Unidirectional**: All participating adapters are of type `unidirectional::AB`, meaning data flows only in one direction (from the socket to the plugs).
- **No State Logic**: The function block has no internal state diagram or event processing – it is purely structural and does not perform any data transformation.

## State Overview

There is no state machine. The function block operates continuously and permanently passes the received signal to all five outputs.

## Application Scenarios
- **Signal Distribution in Fieldbus Systems**: When a sensor value or control signal (as an AB adapter) needs to be sent to multiple actuators or controllers.
- **Multiplexing in Modular Machines**: Distribution of a central AB signal to different modules of a system.
- **Testing and Simulation**: Simultaneously connecting multiple monitoring or logging units to a data source.

## Comparison with Similar Function Blocks

| Function Block | Number of Outputs | Special Features |

|----------|-----------------|--------------|

| `AB_SPLIT_2` | 2 | Simple 1:2 distribution |

| `AB_SPLIT_3` | 3 | 1:3 distribution |

| `AB_SPLIT_5` | 5 | 1:5 distribution (this block) |

| `AB_SPLIT_N` (generic) | configurable | Individual number via GenericClassName |

Compared to a configurable split block, `AB_SPLIT_5` offers a fixed, yet simple and type-safe solution without additional configuration effort.

## Conclusion

AB_SPLIT_5` is a lean, specialized function block for the 1:5 distribution of unidirectional AB adapter signals. Thanks to its generic implementation and clear interface structure, it is ideally suited for the modular design of automation systems where a signal is required multiple times.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
