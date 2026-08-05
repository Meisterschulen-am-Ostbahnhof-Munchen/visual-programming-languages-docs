# AB_SPLIT_8
![AB_SPLIT_8](./AB_SPLIT_8.svg)

* * * * * * * * * *
## Introduction
The function block **AB_SPLIT_8** is used to multiply an incoming adapter signal of type `AB` into eight identical outputs. It functions as a passive splitter for unidirectional data exchange via the standardized interface `adapter::types::unidirectional::AB`. The block is designed as a generic function block and is typically used in automation technology to forward an AB signal in parallel to multiple downstream components.
## Interface Structure

### **Event Inputs**

None. The function block has no event-driven inputs; data is passed solely via the adapter interface.

### **Event Outputs**

None. No events are explicitly output.

### **Data Inputs**

No direct data inputs. All incoming information is transmitted via the socket adapter.

### **Data Outputs**

No direct data outputs. Outgoing information is provided via the plug adapters.

### **Adapters**

| Name | Type | Direction | Description |

|-------|---------------------------------------|----------|------------------------------------------------|

| `IN` | `adapter::types::unidirectional::AB` | Socket | Input adapter that receives the signal to be distributed. |

| `OUT1` | `adapter::types::unidirectional::AB` | Plug | First output adapter (identical to the input signal). |

| `OUT2` | `adapter::types::unidirectional::AB` | Plug | Second output adapter. |

OUT3` | `adapter::types::unidirectional::AB` | Plug | Third output adapter. |

OUT4` | `adapter::types::unidirectional::AB` | Plug | Fourth output adapter. |

OUT5` | `adapter::types::unidirectional::AB` | Plug | Fifth output adapter. |

OUT6` | `adapter::types::unidirectional::AB` | Plug | Sixth output adapter. |

OUT7` | `adapter::types::unidirectional::AB` | Plug | Seventh output adapter. |

OUT8` | `adapter::types::unidirectional::AB` | Plug | Eighth Output Adapter. |

## Functionality

The **AB_SPLIT_8** functions purely as a signal distributor without internal logic or state machine. The AB signal arriving via socket `IN` is forwarded identically and simultaneously to all eight plug outputs `OUT1` to `OUT8`. No buffering or delay occurs. The function block is completely passive – it reacts solely to data changes from the connected adapter and forwards them unchanged.

The distribution is independent of the internal structure of the AB adapter (e.g., data and event connections). The function block itself has no execution state and does not require sequential control.

```
## Technical Features

- **Generic Type**: The function block (FB) is declared as a generic block (`GenericClassName = 'GEN_AB_SPLIT'`), enabling flexible use in various projects.
- **No State Machine**: There is no Execution Control Chart (ECC); the FB is fully data flow controlled.
- **Adapter Type**: The adapter used, `adapter::types::unidirectional::AB`, is standardized and provides a uniform interface.
- **License**: The block is licensed under the **Eclipse Public License 2.0 (EPL-2.0)** and is designed for the **4diac IDE**.

## State Overview

The **AB_SPLIT_8** has no internal states or state machines. Signal transmission occurs without delay and without dependence on sequential logic.

## Application Scenarios
- **Distributing a single AB sensor signal** to multiple actuators or controllers.
- **Parallel connection of monitoring units** in agricultural technology (e.g., distributing an acknowledge signal).
- **Extension of control cabinet wiring** through software-based signal multiplication.
- **Test environments** where an AB signal is to be sent simultaneously to multiple analysis function blocks (FBs).

## Comparison with similar function blocks
- **`AB_SPLIT_2`, `AB_SPLIT_4`**: These function blocks distribute the signal to two or four outputs, respectively. The `AB_SPLIT_8` offers the maximum of eight outputs in a single FB.
- **`DATA_SPLIT`**: Distributes arbitrary data types (e.g., `INT`, `BOOL`). The `AB_SPLIT_8` function block is specifically designed for the `AB` adapter type and retains the complete adapter structure.
- **`EC_SPLIT`**: An event splitter that only multiplies events, but not data. In contrast, `AB_SPLIT_8` operates at the adapter level, including all data and events it contains.

## Conclusion

The **AB_SPLIT_8** function block is a simple yet effective block for multiplying a unidirectional AB adapter signal. Its generic design and passive operation make it ideal for parallelizing control and monitoring signals in automation technology. The absence of state logic ensures low runtime complexity and high reliability. This function block is a valuable addition to any 4diac library that relies on adapter communication.

## Conclusion

The **AB_SPLIT_8** function block is a simple yet effective block for multiplying a unidirectional AB adapter signal. ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 Total resistance in series & parallel circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)

]
