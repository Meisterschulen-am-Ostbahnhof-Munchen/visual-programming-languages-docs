# AB_MUX_4
![AB_MUX_4](./AB_MUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **AB_MUX_4** is a generic multiplexer for four adapter inputs of type `adapter::types::unidirectional::AB`. Based on the index value `K` (0 to 3), it selects one of the four inputs (`IN1` … `IN4`) and forwards its signal to the output `OUT`. The block is implemented as a generic FB (GenericClassName: `GEN_AB_MUX`) and can therefore be used in various contexts, provided the adapter interface is compatible.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Sets the index K and triggers the multiplexer action. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation that the index K has been adopted and the selection updated. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0 … 3) for selecting the active input. |

### **Data Outputs**
No dedicated data outputs. The output is provided via the adapter output `OUT`.

### **Adapter**

| Type | Name | Direction | Comment |

|-----|------|----------|-----------|

| adapter::types::unidirectional::AB | OUT | Plug | Output reflecting the selected input. |

| adapter::types::unidirectional::AB | IN1 | Socket | First input (Index 0) |

| adapter::types::unidirectional::AB | IN2 | Socket | Second input (Index 1) |

| adapter::types::unidirectional::AB | IN3 | Socket | Third input (Index 2) |

| adapter::types::unidirectional::AB | IN4 | Socket | Fourth input (Index 3) |

## Functionality
The `AB_MUX_4` operates purely event-driven. As soon as a `REQ` event arrives, the index specified by `K` is evaluated. If `K` is less than 4, the corresponding input adapter (`IN1` for K=0, `IN2` for K=1, `IN3` for K=2, `IN4` for K=3) is switched to the output adapter `OUT`. The confirmation event `CNF` is then output. The values of the adapter signals (e.g., AB – usually an analog or binary value) are copied unchanged from the source to the sink.

## Technical Features
- **Generic Function Block**: The XML declares `eclipse4diac::core::GenericClassName` as `'GEN_AB_MUX'`. This allows the function block to be used as a template in the IDE and adapted to different configurations (e.g., number of inputs).
- **Adapter-Based Interface**: Data is not transferred via simple variables, but via adapters (`adapter::types::unidirectional::AB`). This enables the exchange of complex data structures or bus protocols.
- **Error Handling**: The index `K` should be in the range 0…3. A value outside this range can lead to undefined behavior. The current implementation does not define a default behavior for invalid indices.
- **Copyright**: This function block was developed by HR Agrartechnik GmbH (Eclipse Public License 2.0).

## State Overview
This function block does not have an explicit state machine (ECC). After each `REQ`, it immediately executes the multiplexer function and sends `CNF`. There is no internal state other than the current connection, which is determined by K.

## Application Scenarios
- **Sensor Switching**: Selection of one of four analog sensors (e.g., temperature, pressure) for further processing.
- **Signal Routing**: Switching between different communication channels defined via the `AB` adapter.
- **Test and Diagnostic Modules**: In test benches, this function block can be used to connect different devices under test to a common measuring instrument in succession.

## Comparison with Similar Components
- **AB_MUX_2**: A simpler, two-input multiplexer that only processes indices 0 and 1.
- **AB_MUX_8**: An advanced eight-input multiplexer. The `AB_MUX_4` falls in between, offering a good compromise between flexibility and resource consumption.
- **Demultiplexer (AB_DMUX)**: Distributes a signal to multiple outputs; the `AB_MUX_4` operates in the opposite direction.

## Conclusion
The `AB_MUX_4` is a compact, generic multiplexer component for the `unidirectional::AB` adapter interface. Due to its generic nature and simple event control, it is ideally suited for building modular automation solutions with a limited number of selectable signal sources.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]