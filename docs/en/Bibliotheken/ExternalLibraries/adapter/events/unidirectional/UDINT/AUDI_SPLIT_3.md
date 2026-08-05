# AUDI_SPLIT_3
![AUDI_SPLIT_3](./AUDI_SPLIT_3.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_SPLIT_3** is used to multiply an incoming **AUDI** adapter signal to three separate outputs. It is designed as a generic function block (Generic FB) and is particularly suitable for architectures where a signal (e.g., a control or data stream) needs to be distributed to multiple downstream components.
## Interface Structure
### **Event Inputs**
- None

### **Event Outputs**
- None

### **Data Inputs**
- None

### **Data Outputs**
- None

### **Adapter**

| Type | Name | Description |

|-----|------|---------------|

| Socket (adapter::types::unidirectional::AUDI) | **IN** | Input adapter for receiving the AUDI signal |

| Plug (adapter::types::unidirectional::AUDI) | **OUT1** | First output adapter |

| Plug (adapter::types::unidirectional::AUDI) | **OUT2** | Second output adapter |

| Plug (adapter::types::unidirectional::AUDI) | **OUT3** | Third output adapter |

## Functionality
This module forwards the AUDI signal present at the **IN** socket unchanged to all three **OUT** plugs. No conversion, filtering, or logical processing takes place – the distribution is transparent. The use of adapters of type `unidirectional::AUDI` ensures that the signal direction (input → outputs) is clearly defined.

``` ## Technical Features

- **Generic Implementation**: The function block is implemented as a generic FB (`eclipse4diac::core::GenericClassName = 'GEN_AUDI_SPLIT'`). This allows for easy reuse in different contexts without requiring the specific AUDI type to be fully defined at development time.
- **Type Hash**: The type hash can be set at runtime if needed to enable static type checking.
- **Pure Adapter Interface**: The FB has neither event nor data inputs/outputs in the traditional sense, but communicates exclusively via adapters.

## State Overview
Since the FB has no event inputs, it does not have an explicit state machine. Signal transmission occurs continuously and asynchronously as soon as the IN adapter is connected.

## Application Scenarios
- **Signal Multiplication**: Distribution of a common control or measurement signal to different function blocks (e.g., parallel connection of several actuators or sensors).
- **Test and Simulation Environments**: Injecting a simulated audio signal into multiple independent analysis or monitoring paths.
- **Architecture Coupling**: Used in modular systems where a data stream needs to be passed to different subsystems without degrading the original signal.

## Comparison with Similar Blocks
- **AUDI_MERGE** (counterpart): A combining element that merges multiple audio inputs into one output – unlike the split block.
- **AUDI_SPLIT_2**: A splitter reduced to two outputs; this block extends this to three outputs.
- **Generic Splitters**: Many libraries contain split variants for other adapter types (e.g., `DATA_SPLIT`), but these are data-type specific.

## Conclusion

The **AUDI_SPLIT_3** is a simple yet useful function block for distributing a unidirectional AUDI adapter signal to three outputs. Its generic nature and pure adapter interface allow it to integrate seamlessly into event-driven and data-stream-oriented IEC 61499 applications. It provides a clean, maintainable solution for architectural signal distribution and reduces the need for manual signal routing.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 Total Resistance in Series & Parallel Circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)

