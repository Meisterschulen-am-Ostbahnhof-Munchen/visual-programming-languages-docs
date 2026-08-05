# AB_MUX_5
![AB_MUX_5](./AB_MUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AB_MUX_5** implements a generic multiplexer for adapter interfaces of type `adapter::types::unidirectional::AB`. It selects one of five incoming adapter connections (IN1–IN5) and forwards it to the output adapter (OUT). The selection is made using an integer index `K`, which is evaluated on a rising edge at the event input `REQ`.
## Interface Structure
### **Event Inputs**

| Event | Comment |

|----------|-----------|

| REQ | Sets the index K and activates the forwarding to the corresponding input connection |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| CNF | Confirmation of successful index setting and output update |

### **Data Inputs**

| Variable | Type | Comment |

|----------|------|-----------|

| K | UINT | Index of the input to be selected (0 = IN1, 1 = IN2, …, 4 = IN5) |

### **Data Outputs**

*No direct data outputs are available. Output is exclusively via the adapter plugin `OUT`.*

### **Adapter**

| Direction | Adapter | Type | Comment |

| Plug | OUT | adapter::types::unidirectional::AB | Output adapter that provides the values of the selected input |

| Socket | IN1 | adapter::types::unidirectional::AB | First input (Index 0) |

| Socket | IN2 | adapter::types::unidirectional::AB | Second input (Index 1) |

| Socket | IN3 | adapter::types::unidirectional::AB | Third input (Index 2) |

| Socket | IN4 | adapter::types::unidirectional::AB | Fourth input (Index 3) |

| Socket | IN5 | adapter::types::unidirectional::AB | Fifth input (Index 4) |

## Functionality

The function block operates as a **1-out-of-5 multiplexer** at the adapter level. Upon an event at input `REQ`, the current value of `K` is evaluated. Valid values are 0 to 4. The corresponding adapter socket (IN1 at K=0, IN2 at K=1, … IN5 at K=4) is connected to the output adapter `OUT`. After the switchover, the event output `CNF` is sent.

If values outside the range 0 to 4 are applied to `K`, the behavior is undefined – typically, no input is selected, or the last valid state is retained. The function block itself does not perform range checking.

In the event of a switchover, the output `CNF` is sent. ## Technical Features

- **Adapter-based**: The function block uses the unidirectional adapter `adapter::types::unidirectional::AB`, which is designed for data exchange in one direction (here: input → output).
- **Generic Parameterization**: The function block is designed as a generic function block with the class name `GEN_AB_MUX`. This enables type checking and optimization of the runtime environment (e.g., Eclipse 4diac).
- **No Data Mapping Logic**: Data is transferred implicitly via the adapter connection; the function block itself contains no additional data inputs or outputs.
- **Copyright and License**: The function block is subject to the Eclipse Public License 2.0, which permits free use, modification, and distribution.

## State Overview
The function block does not have an explicit state machine (ECC). Its behavior is event-driven:

1. **Idle State**: No event is present. The output adapter `OUT` displays the last selected input connection.

2. **Switching Phase**: Upon a `REQ` event, the index `K` is read, the adapter connection is switched, and then `CNF` is output.

This makes the function block deterministic and allows it to operate without delays other than the internal propagation time.

## Application Scenarios
- **Signal Selection in Agricultural Engineering**: (Depending on the function block's origin) Selection between different sensor values (e.g., five different measuring points for temperature or pressure).
- **Data Selection in Automation Systems**: Switching between multiple data sources (e.g., five conveyor belts or five machine states).
- **Test and Simulation Environments**: Targeted selection of an input adapter signal for testing purposes.

## Comparison with Similar Function Blocks

| Function Block | Number of Inputs | Selection Mechanism | Differences |

-----------------|-----------------|---------------------|--------------|

| AB_MUX_5 | 5 | Index K (UINT) | This function block; pure adapter multiplexer |

| AB_MUX_2 | 2 | Index K (BOOL) | Fewer inputs, simpler selection |

| MUX (Data Type) | 2, 4, 8 … | Index (UINT) | Often designed for elementary data types (INT, REAL), not for adapters |

| SELECT | 2 | G (BOOL) | Standard function block according to IEC 61499 for binary selection of data |

The AB_MUX_5 is specifically optimized for adapter connections and offers a clear separation of event control and data path.

## Conclusion
The **AB_MUX_5** is a compact and reusable function block for adapter multiplexing. It allows the selection of one of five incoming adapter channels via a numeric index and is ideally suited for systems that need to dynamically switch between multiple identical interfaces. Thanks to its generic implementation and EPL 2.0 license, it can be used in various automation environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]