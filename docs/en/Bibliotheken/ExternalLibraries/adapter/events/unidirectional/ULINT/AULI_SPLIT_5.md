# AULI_SPLIT_5
![AULI_SPLIT_5](./AULI_SPLIT_5.svg)

* * * * * * * * * *
## Introduction
The function block **AULI_SPLIT_5** serves as a generic splitter for the unidirectional AULI adapter type. It generates five identical output signals from a single incoming AULI signal, which can then be distributed to separate devices. The block is implemented as a generic FB and is parameterized for the Eclipse 4diac Core Framework using the attributes `GenericClassName` and `TypeHash`.
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

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket | `IN` | `adapter::types::unidirectional::AULI` | Incoming AULI adapter (source) |

| Plug | `OUT1` | `adapter::types::unidirectional::AULI` | First outgoing AULI adapter |

| Plug | `OUT2` | `adapter::types::unidirectional::AULI` | Second outgoing AULI adapter |

| Plug | `OUT3` | `adapter::types::unidirectional::AULI` | Third outgoing AULI adapter |

| Plug | `OUT4` | `adapter::types::unidirectional::AULI` | Fourth outgoing AULI adapter |

| Plug | `OUT5` | `adapter::types::unidirectional::AULI` | Fifth outgoing AULI adapter |

The interface consists solely of one socket and five plugs of the same type. All adapters are unidirectional.

## Functionality

The FB forwards the AULI signal arriving at socket `IN` to all five plugs (`OUT1` … `OUT5`) without delay or processing. A simple **1:5 replication** takes place. The function block has no logic, no states, and no internal buffer. Data is passed passively: As soon as the source adapter sends data, it is replicated to all outputs.

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GenericClassName = 'GEN_AULI_SPLIT'`). The specific type used is only resolved at runtime by the Eclipse 4diac Core Framework.
- **Unidirectional Adapters**: All adapters use the type `adapter::types::unidirectional::AULI`, which allows data flow in only one direction, from the source to the destinations.
- **No Conditions or Filters**: The input signal is distributed to all outputs without quality control, conversion, or synchronization.
- **Compatibility**: The function block (FB) is designed for use in IEC 61499-2 compliant systems and requires the import of the packages `eclipse4diac::core::GenericClassName` and `eclipse4diac::core::TypeHash`.

## State Overview

The FB has **no internal state machine**. There are no states, no transitions, and no actions. Its functionality is limited to passive signal distribution.

## Application Scenarios
- **Signal Distribution**: A sensor value or a control signal (e.g., an AULI-based data source) must be sent to multiple parallel processing units or actuators.
- **Test Environments**: In simulation or test systems, the same input signal can be applied simultaneously to multiple analysis blocks or log functions.
- **Redundant Outputs**: When multiple subsystems require the same value, but cascaded chaining is not desired.

## Comparison with Similar Components

| Component | Type | Outputs | Special Feature |

|----------|-----|----------|--------------|

| `AULI_SPLIT_5` | Generic splitter | 5 | Specific to AULI adapters |

| `SPLIT_2` (non-standardized) | Generic splitter | 2 | Mostly for data types such as INT or BOOL |

| `F_SPLIT` (from IEC 61499 libraries) | Functional splitter | Variable | Based on ECC and events |

The `AULI_SPLIT_5`, unlike event-based splitters, is **eventless** and purely adapter-based. It is therefore particularly suitable for use in data flow systems without a clock signal.

## Conclusion

The `AULI_SPLIT_5` is a minimalist yet useful function block for multiplying a unidirectional AULI signal to five outputs. Its generic nature allows for flexible parameterization within the Eclipse 4diac framework. Due to the absence of a state machine and its simple pass-through functionality, it is extremely resource-efficient and suitable for high-speed data distribution.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
