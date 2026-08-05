# AI_SPLIT_9
![AI_SPLIT_9](./AI_SPLIT_9.svg)
* * * * * * * * * *
## Introduction
The function block **AI_SPLIT_9** is a generic component that distributes a single analog input signal (adapter type `AI`) to nine identical outputs (OUT1 to OUT9). It serves as a signal distributor, allowing an AI signal to be used multiple times in a control application without having to link the source multiple times.
## Interface Structure
### **Event Inputs**
No event inputs available.

### **Event Outputs**
No event outputs available.

### **Data Inputs**
No data inputs available.

### **Data Outputs**
No data outputs available.

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|

Input (Socket) | `IN` | `adapter::types::unidirectional::AI` | Single analog input distributed to all outputs. |

Output (Plug) | `OUT1` | `adapter::types::unidirectional::AI` | First outgoing AI channel. |

Output (Plug) | `OUT2` | `adapter::types::unidirectional::AI` | Second outgoing AI channel. |

Output (Plug) | `OUT3` | `adapter::types::unidirectional::AI` | Third outgoing AI channel. |

Output (Plug) | `OUT4` | `adapter::types::unidirectional::AI` | Fourth outgoing AI channel. |

Output (Plug) | `OUT5` | `adapter::types::unidirectional::AI` | Fifth outgoing AI channel. |

Output (Plug) | `OUT6` | `adapter::types::unidirectional::AI` | Sixth outgoing AI channel. |

Output (Plug) | `OUT7` | `adapter::types::unidirectional::AI` | Seventh outgoing AI channel. |

Output (Plug) | `OUT8` | `adapter::types::unidirectional::AI` | Eighth outgoing AI channel. |

Output (Plug) | `OUT9` | `adapter::types::unidirectional::AI` | Ninth outgoing AI channel. |

## Functionality
The module operates as a pure signal distributor: The AI value present at adapter socket `IN` is passed on unchanged and simultaneously to all nine adapter plugs `OUT1` … `OUT9`. No signal processing, scaling, or other manipulation takes place. The distribution is continuous and without internal state behavior – the output follows the input without delay.

## Functionality ## Technical Features
- **Generic Block:** The function block is typed as `GEN_AI_SPLIT` and utilizes the generics mechanisms of Eclipse 4diac (`GenericClassName`, `TypeHash`). This allows for flexible use in type hierarchies and libraries.
- **Adapter-Based Interface:** Instead of individual data ports, adapters are used that provide an encapsulated, reusable interface for analog inputs (`AI`). This simplifies the interconnection concept in 4diac applications.
- **Zero Latency:** Since there is no internal logic or processes, signal transmission is instantaneous.

## State Overview

The block does not have an internal state machine (no ECC). It operates purely on a data flow basis: The input value is continuously passed through to the outputs.

## Application Scenarios
- **Signal Multiplication:** A single analog sensor (e.g., temperature, pressure) is to be evaluated in parallel across multiple function blocks.
- **Redundant Processing:** An AI signal is routed to multiple independent paths to enable failover or plausibility checks.
- **Modular Distribution:** In a large control application, an analog input signal is routed to various modules (e.g., control, monitoring, visualization).

## Comparison with Similar Components
- **AI_SPLIT_2 / AI_SPLIT_4 / …**: Analog components with 2 or 4 outputs, respectively. `AI_SPLIT_9` extends the concept to nine outputs and is therefore suitable for applications with many receivers.
- **AI_MERGE**: Combines multiple AI inputs into a single output – the opposite operation.
- **Direct Adapter Linking**: In 4diac, a single adapter port can theoretically be connected multiple times, but the explicit splitting with this function block is more documented and clearly structured.

## Conclusion
The **AI_SPLIT_9** is a simple yet useful function block for signal multiplication of analog inputs in IEC 61499 applications. Its generic structure and adapter interface allow it to integrate seamlessly into the 4diac ecosystem and facilitate the structured routing of signals. Its use is recommended wherever an AI signal needs to be simultaneously passed to multiple processing units.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]