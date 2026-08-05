# AL_SPLIT_5

![AL_SPLIT_5](./AL_SPLIT_5.svg)

* * * * * * * * * *

## Introduction

The function block **AL_SPLIT_5** serves as a generic splitter for a unidirectional adapter of type `AL`. It splits an incoming signal (via the `IN` socket) into five separate outputs (`OUT1` to `OUT5`). The block is marked as generic, which allows the specific adapter type to be defined when using it.

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

| Type | Direction | Name | Description |

|----------|----------|------|-------------------------------------|

| Socket | Input | IN | Unidirectional `AL` adapter input |

| Plug | Output | OUT1 | First output (unidirectional `AL`) |

| Plug | Output | OUT2 | Second output (unidirectional `AL`) |

| Plug | Output | OUT3 | Third output (unidirectional `AL`) |

| Plug | Output | OUT4 | Fourth output (unidirectional `AL`) |

| Plug | Output | OUT5 | Fifth output (unidirectional `AL`) |

## Functionality

The function block receives a signal of type `AL` via socket `IN` and forwards it unchanged to all five plugs `OUT1` to `OUT5`. No data processing or event handling takes place; the distribution occurs purely at the adapter level. This allows multiple downstream components to be supplied with the same adapter signal in parallel.

The function block is designed as a generic function block (`GEN_AL_SPLIT`). The specific adapter type `AL` can be defined via an attribute during instantiation.

## Technical Features

- **No Events or Data**: The function block has only adapter interfaces, no event or data ports.

- **Generic Design**: The type of the `AL` adapter is configurable (generic class), allowing different implementations of the same adapter type to be used.

- **Pure Signal Distribution**: This is a pure 1:5 distribution without any logic, delay, or transformation.

## State Overview

The function block does not have an internal state machine, as it does not process any events. It behaves statically and permanently passes the input signal to all outputs.

## Application Scenarios

- **Signal Distribution**: If several components require the same adapter signal of a `AL` type, e.g., For example, to send a sensor value to different control logics.

- **Test and debugging environments**: An incoming adapter signal can be passed on to multiple monitor or logging blocks simultaneously.

- **Redundancy**: The signal can be distributed to parallel processing paths.

## Comparison with similar blocks

Other splitter blocks exist in the 4diac ecosystem, such as `SPLIT` for event or data flows. The advantage of `AL_SPLIT_5` lies in its exclusive adapter interface. While a `SPLIT` block separates events or data, this block operates directly at the adapter level and requires no conversion between events and data. Similar function blocks with a different number of outputs (e.g., `AL_SPLIT_2`, `AL_SPLIT_3`) are conceivable, but are not included in this generic form by default.

## Conclusion

The **AL_SPLIT_5** is a simple yet useful generic function block for duplicating a unidirectional adapter signal to five outputs. Due to its pure adapter interface and lack of event/data logic, it is particularly suitable for applications that need to distribute a signal to multiple receivers without processing. The generic design increases flexibility for reuse in different projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]