# OFF_SPLIT_3

![AUS_SPLIT_3](./AUS_SPLIT_3.svg)

* * * * * * * * * *
## Introduction
The function block **OFF_SPLIT_3** serves as a universal distributor for incoming adapter signals of type `adapter::types::unidirectional::AUS`. It receives such a signal and forwards it unchanged to three identical output adapters. This allows control, alarm, or status information to be easily distributed across multiple subsequent blocks.

## Interface Structure
### **Event Inputs**
None – signal transmission occurs via the adapter IN.

### **Event Outputs**
None – output occurs via the adapter OUTs.

### **Data Inputs**
None – the block has no dedicated data inputs; all data is transmitted via the adapter `IN`.


### **Data Outputs**

None – the data is output via the adapters `OUT1`, `OUT2`, and `OUT3`.

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| `IN` | `adapter::types::unidirectional::AUS` | Socket (incoming) | Receives an OFF signal. |

| `OUT1` | `adapter::types::unidirectional::AUS` | Plug (outgoing) | First output of the incoming signal. |

| `OUT2` | `adapter::types::unidirectional::AUS` | Plug (outgoing) | Second output of the incoming signal. |

| `OUT3` | `adapter::types::unidirectional::AUS` | Plug (outgoing) | Third output of the incoming signal. |

## Functionality
The FB operates as a pure signal distributor. As soon as an OFF signal (consisting of an event and associated data) is active at socket `IN`, it is passed on identically to all three plugs `OUT1`, `OUT2`, and `OUT3` without delay or transformation. Each output receives the same event and the same data. No buffering, filtering, or logical processing takes place.

## Technical Features
- **Generic Type**: The function block is declared as a generic FB (`eclipse4diac::core::GenericClassName` = `'GEN_AUS_SPLIT'`). This allows it to be adapted to different OFF adapter types, provided they have the same interface structure.

- **Stateless**: The FB has no internal state diagram (ECC). Its response is purely data flow-driven and requires no initialization or reset logic.

- **License Notice**: The function block is provided under the Eclipse Public License 2.0.

## State Overview
Since **AUS_SPLIT_3** has no sequence control or explicit states, a state machine is not required. The behavior is deterministic and immediate: One input signal synchronously generates three identical output signals.

## Application Scenarios

- **Distribution of alarm signals** to multiple display or logic units.

- **Multiple use of a sensor signal** in different automation branches.

- **Splitting a control command** (e.g., "Shut down") across multiple actuators or subsystems.

- **Signal cascading** in modular 4diac applications.

## Comparison with similar function blocks

- **EVENT_SPLIT**: Distributes only events (without data). **AUS_SPLIT_3**, on the other hand, distributes complete adapter signals including all associated data.

- **DATA_SPLIT**: Distributes pure data channels and requires separate event control. The OFF splitter encapsulates the event and data together in the adapter.

- **Manual implementation**: Without this function block, each output would have to be connected to its own copy of the source adapter. **AUS_SPLIT_3** simplifies wiring and improves clarity.

## Conclusion
The **AUS_SPLIT_3** is a simple yet useful function block for multiplying OFF adapter signals. Due to its generic design and stateless nature, it is ideally suited for the modular and maintainable structuring of 4diac applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]