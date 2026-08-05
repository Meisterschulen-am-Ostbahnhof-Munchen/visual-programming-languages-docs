# AUDI_AX_SEL_AUDI
![AUDI_AX_SEL_AUDI](./AUDI_AX_SEL_AUDI.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_AX_SEL_AUDI** implements a binary selection between two input values. It acts as a multiplexer, switching one of the two inputs to the output depending on a selector signal. Communication occurs exclusively via unidirectional adapters that encapsulate both event and data signals. This allows for flexible and type-specific integration into existing signal paths.
## Interface Structure
### **Event Inputs**
The function block does not have dedicated event inputs. However, events are provided via the **Selector Adapter G**:

- **G.E1**: Event signal that triggers the selection logic.

### **Event Outputs**
The function block does not have dedicated event outputs. Events are output via the **Output Adapter OUT**:

- **OUT.E1**: Acknowledge signal triggered after successful completion of the selected input.

### **Data Inputs**
The FB does not have dedicated data inputs. Data values are provided via the following adapters:

- **IN0.D1** (Type: AUDI) – first selectable data value
- **IN1.D1** (Type: AUDI) – second selectable data value
- **G.D1** (Type: AX) – selector field for determining the active source

### **Data Outputs**
The FB does not have dedicated data outputs. The selected data value is output via the **Output Adapter OUT**:

- **OUT.D1** (Type: AUDI) – selected data value (corresponds to IN0.D1 or IN1.D1)

### **Adapters**

| Adapter | Direction | Type | Comment |

|---------|----------|-----|-----------|

| **IN0** | Socket (Input) | `adapter::types::unidirectional::AUDI` | First selectable input |

| **IN1** | Socket (Input) | `adapter::types::unidirectional::AUDI` | Second selectable input |

| **G** | Socket (Input) | `adapter::types::unidirectional::AX` | Selector (Event + Data) |

| **OUT** | Plug (Output) | `adapter::types::unidirectional::AUDI` | Output field with event and data |

## Functionality
The function block internally contains an instance of the IEC 61131 function block `F_SEL` (from the library `iec61131::selection`). The logic proceeds as follows:

1. **Triggering**: An event at **G.E1** (via the selector adapter) starts the processing.

2. **Data Collection**: The values received from **IN0.D1**, **IN1.D1**, and **G.D1** are forwarded to the `F_SEL` function block.

3. **Selection**: `F_SEL` checks the value of **G.D1**. Typical Semantics (depending on the data type `AX`):

- If the selector field is **False** (or 0), **IN0** is selected.
- If the selector field is **True** (or not equal to 0), **IN1** is selected.

4. **Output**: The selected signal is passed on to **OUT.D1**. Simultaneously, an event is sent to **OUT.E1** to inform downstream processing.

The internal flow is event-driven and avoids continuous read accesses, enabling efficient communication in time-controlled environments.

## Technical Features
- **Pure Adapter Communication**: All interfaces are defined as unidirectional adapters. Event and data paths are combined within a single adapter, simplifying configuration in the 4diac IDE.
- **Reuse of IEC 61131 libraries**: The selection logic is fully implemented by the standard function block `F_SEL`, which requires no additional state machines or complex algorithms.
- **Type safety**: The adapters are specialized for the user-defined types `AUDI` and `AX`. This prevents miscoupling with incompatible signals at design time.
- **No state of its own**: The function block itself is stateless – it simply forwards the signals to the internal `F_SEL`. The internal function block manages the selection logic autonomously.

## State overview
The function block **AUDI_AX_SEL_AUDI** does **not have its own state machine**. The entire selection logic is executed by the inner `F_SEL` block, which itself is a pure function block without state memory. Therefore, its behavior is **stateless**:

- After receiving an event at **G.E1**, the selection is made immediately and the result is output to **OUT.D1**.
- There are no initialization, wait, or error states; the block is always ready for a new selector request.

## Application Scenarios

This block is ideally suited for the following applications in automation technology:

- **Signal switching** between two sensors (e.g., temperature sensors, pressure transducers) depending on an operating mode or a manual switch.
- **Bypass selection** in control paths: if one channel malfunctions, the system automatically switches to a backup channel.
- **Parameter selection**: a selector field is used to choose between two fixed parameter sets (e.g., for different products).
- **Test Mode**: Switching between a real and a simulated signal for commissioning or maintenance.

The use of user-defined adapter types (`AUDI`, `AX`) allows for easy adaptation to project-specific data structures.

## Comparison with Similar Function Blocks

| Criterion | **AUDI_AX_SEL_AUDI** | Simple Boolean MUX (e.g., `F_SEL`) |

|-----------|------------------------|---------------------------------------|

| **Interface** | Pure adapters (event and data encapsulated) | Separate input/output pins |

| **Data Type** | User-defined types (`AUDI`, `AX`) | Arbitrary (configurable) |

**Selector** | Event-driven (via adapter) | Data-driven, without extra events |

**Reusability** | Higher due to type safety and encapsulation | More flexible, but loosely coupled |

**Complexity** | Medium (adapters require prior knowledge) | Low (direct pins) |

The **AUDI_AX_SEL_AUDI** offers higher integration into adapter-based architectures and is particularly suitable for modular, type-bound systems, while a pure `F_SEL` is more universal.

## Conclusion
The **AUDI_AX_SEL_AUDI** is a specialized binary selector that leverages the advantages of adapter-based communication in 4diac. By encapsulating event and data paths in a single adapter, signal wiring in the overall system is reduced and type safety is increased. Internal delegation to the proven `F_SEL` block from the IEC 61131 library ensures robust, stateless selection logic. This block is ideally suited for use in modular control projects where clear interfaces and easy reusability are paramount.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
