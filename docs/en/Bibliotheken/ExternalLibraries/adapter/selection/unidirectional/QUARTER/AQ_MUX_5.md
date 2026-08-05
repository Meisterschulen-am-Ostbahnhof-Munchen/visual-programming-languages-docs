# AQ_MUX_5
![AQ_MUX_5](./AQ_MUX_5.svg)

* * * * * * * * * *
## Introduction
The function block `AQ_MUX_5` is a generic multiplexer for analog outputs (AQ). It allows the selection of one of five analog input signals (via adapters) and routes it to a common analog output. The selection is made via the index `K`, which is inherited on a rising edge at the event input `REQ`.
## Interface Structure

### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `REQ` | Adoption of index `K` and switching of the corresponding input to the output |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| `CNF` | Confirmation that index `K` has been adopted and the output updated |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `K` | `UINT` | Index for selecting the input (0 = IN1, 1 = IN2, 2 = IN3, 3 = IN4, 4 = IN5) |

### **Data Outputs**

No separate data outputs; the selected analog value is provided via the `OUT` adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

Socket (Input) | `IN1` | `adapter::types::unidirectional::AQ` | 1st Analog Input Value |

| Socket (Input) | `IN2` | `adapter::types::unidirectional::AQ` | 2nd Analog Input Value |

| Socket (Input) | `IN3` | `adapter::types::unidirectional::AQ` | 3. Analog Input Value |

Socket (Input) | `IN4` | `adapter::types::unidirectional::AQ` | 4. Analog Input Value |

Socket (Input) | `IN5` | `adapter::types::unidirectional::AQ` | 5. Analog Input Value |

Plug (Output) | `OUT` | `adapter::types::unidirectional::AQ` | Output that provides the value of the selected input |

## Functionality
The function block operates in an event-driven manner. A valid index `K` (value range 0 to 4) is obtained through an event at input `REQ`. Immediately afterward, the analog value of the input determined by `K` (IN1 for K=0, IN2 for K=1, …, IN5 for K=4) is passed through to the output adapter `OUT`. Finally, the event `CNF` is sent to confirm the successful update. If `K` has invalid values (e.g., >4), the output remains unchanged, and `CNF` is still triggered (depending on the implementation); the specification of the specific function block defines the exact behavior.

## Technical Features

- **Generic Function Block**: The `AQ_MUX_5` is instantiated in the 4diac IDE as a generic function block (GenericClassName `'GEN_AQ_MUX'`). This allows for flexible customization of the types or parameters by the development tool.
- **Unidirectional Adapters**: Both the input and output adapters are of type `unidirectional::AQ`. This means that the data flow is strictly directional (from the socket to the plug) and no feedback occurs.
- **Real-Time Behavior**: The function block performs the multiplexing operation in a single event step, which is particularly advantageous in time-critical control systems.
- **No Dedicated Data Outputs**: All analog output information is transmitted exclusively via the adapter plug `OUT`. This enables tight coupling with subsequent adapters of the same interface.

## State Overview
The function block has at least two internal states:

1. **Waiting for REQ** – In the idle state, it waits for an event at input `REQ`.

2. **Switching and Acknowledging** – After receiving `REQ`, the index `K` is read, the corresponding input is switched to the output, and the event `CNF` is sent. The block then returns to the waiting state.

This simple state machine guarantees a fast and deterministic response.

## Application Scenarios
- **Agricultural Technology** (original application area): Selection of various analog sensor or control signals, e.g., for controlling multiple valves or switching between different measured values.
- **Industrial Automation**: Multiplexing analog signals in a control room, for example, to monitor multiple measuring points via a single analog output card.
- **Test and Simulation Environments**: Easy switching between different simulated analog values for testing purposes.

## Comparison with Similar Components
- **AQ_MUX_2 / AQ_MUX_4**: These components offer a smaller number of inputs (2 and 4, respectively). The `AQ_MUX_5` extends the flexibility to five inputs, which is often required for applications with five parallel signals.
- **AQ_MUX_5** vs. **General Multiplexers (e.g., MUX_INT)**: The component described here is specifically optimized for analog output interfaces (AQ) and uses adapters, while general multiplexers use standardized data types and events. The adapter encapsulation facilitates reuse and type safety.

## Conclusion

The `AQ_MUX_5` is a specialized, generic multiplexer for analog output applications in the 4diac framework. Its ease of use, clear event handling, and the use of unidirectional adapters make it an efficient tool for selecting one of five analog signals in real-time systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
