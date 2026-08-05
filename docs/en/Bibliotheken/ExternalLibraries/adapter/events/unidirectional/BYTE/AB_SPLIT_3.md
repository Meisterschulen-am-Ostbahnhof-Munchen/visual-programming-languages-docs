# AB_SPLIT_3
![AB_SPLIT_3](./AB_SPLIT_3.svg)
* * * * * * * * * *
## Introduction
The function block **AB_SPLIT_3** is used to split an incoming unidirectional data/signal adapter (type `AB`) into three identical output adapters. It is implemented as a generic function block and represents a simple 1-to-3 distribution without additional logic or delay.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| `adapter::types::unidirectional::AB` | `IN` | Socket (Input) | Receives a unidirectional AB-type adapter. |

| `adapter::types::unidirectional::AB` | `OUT1` | Plug (Output) | First output of the incoming signal. |

| `adapter::types::unidirectional::AB` | `OUT2` | Plug (Output) | Second output of the incoming signal. |

| `adapter::types::unidirectional::AB` | `OUT3` | Plug (Output) | Third output of the incoming signal. |

## Functionality

The module forwards the unidirectional adapter connected to socket `IN` **without manipulation** to the three plugs `OUT1`, `OUT2`, and `OUT3` in parallel. No buffering, processing, or timing control takes place. The module functions purely as a **splitter** (distributor) for adapter-based signals.

Since the adapter `AB` is unidirectional, data transmission occurs exclusively in one direction (from the socket to the plugs). The three outputs are independent of each other and always provide the current state of the input.

```
## Technical Features

- **Generic Block**: The function block is marked as generic by the attribute `eclipse4diac::core::GenericClassName` (`'GEN_AB_SPLIT'`). This means the actual adapter type can be specified at runtime or during instantiation, as long as it has the basic structure of a unidirectional AB adapter.
- **Unidirectionality**: Both the input and output adapters are of type `unidirectional::AB`. Reverse communication is not supported.
- **No State Maintenance**: The block has no internal state machine or memory. The routing is passive and continuous.
- **Copyright**: The block was released by HR Agrartechnik GmbH under the Eclipse Public License 2.0.

## State Overview

The function block has **no explicit state machine**. The behavior is purely data-flow oriented: As soon as the input adapter provides data, it is immediately propagated to all outputs. No state monitoring or control is required.

## Application Scenarios
- **Signal Distribution in Automation Technology**: Splitting a sensor signal (e.g., temperature, pressure) to multiple processing units.
- **Parallelization of Control Sequences**: Providing the same adapter stream to different function blocks that operate independently.
- **Prototyping and Testing**: Using a simulated adapter to supply multiple system components simultaneously.

## Comparison with Similar Function Blocks

| Function Block | Behavior | Special Feature |

|----------|------------|--------------|

| `SPLIT_2` | 1-to-2 Distribution | Analog function block with two outputs. |

| `AB_SPLIT_3` | 1-to-3 Distribution | This block. |

| `AB_JOIN` | Combining Multiple Adapters | Counterpart to the splitter. |

While `SPLIT_2` offers only two outputs, `AB_SPLIT_3` covers the need for triple distribution. No additional logic functions such as filtering or delay are implemented.

## Conclusion

The **AB_SPLIT_3** is a simple yet useful generic splitter block for unidirectional adapters. It enables clean structuring of automation applications by splitting an incoming signal path into three parallel paths. Thanks to its generic nature, it can be used with any AB adapter type and integrates seamlessly into the IEC 61499-2 compliant 4diac development environment.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
