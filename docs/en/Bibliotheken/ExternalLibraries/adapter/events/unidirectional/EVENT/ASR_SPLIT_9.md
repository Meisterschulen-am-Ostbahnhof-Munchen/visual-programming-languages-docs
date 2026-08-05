# ASR_SPLIT_9

![ASR_SPLIT_9](./ASR_SPLIT_9.svg)

* * * * * * * * * *
## Introduction

The function block **ASR_SPLIT_9** is used to split a single incoming ASR adapter (Application Specific Resource) into nine separate ASR outputs. It is implemented as a generic function block (Generic FB) and allows the distribution of an ASR signal to up to nine independent receivers.

## Interface Structure

### **Event Inputs**
None available.

### **Event Outputs**
None available.

### **Data Inputs**
No separate data inputs. All data exchange takes place via the ASR adapter **IN**.

### **Data Outputs**
No separate data outputs. The data is output via the ASR adapters **OUT1** to **OUT9**.


### **Adapter**

**Socket (Input):**

| Name | Type | Direction |

|------|-----|----------|

| IN | `adapter::types::unidirectional::ASR` | Socket |

**Plugs (Outputs):**

| Name | Type | Direction |

|-------|-----|----------|

| OUT1 | `adapter::types::unidirectional::ASR` | Plug |

| OUT2 | `adapter::types::unidirectional::ASR` | Plug |

| OUT3 | `adapter::types::unidirectional::ASR` | Plug |

| OUT4 | `adapter::types::unidirectional::ASR` | Plug |

| OUT5 | `adapter::types::unidirectional::ASR` | Plug |

OUT6 | `adapter::types::unidirectional::ASR` | Plug |

OUT7 | `adapter::types::unidirectional::ASR` | Plug |

OUT8 | `adapter::types::unidirectional::ASR` | Plug |

OUT9 | `adapter::types::unidirectional::ASR` | Plug |

## Functionality

The module receives an ASR signal via the socket adapter **IN**. This signal is internally routed to all nine output adapters (**OUT1** to **OUT9**). Thus, the identical ASR signal is present at each output. No delay or buffering occurs. The module is purely passive and does not perform any data transformation.


## Functionality ## Technical Features

- **Generic Function Block:** This type is designed as a generic FB (GenericClassName `'GEN_ASR_SPLIT'`), allowing it to be parameterized with different ASR types depending on the project context.

- **Unidirectional Adapters:** All adapters used are of type `unidirectional::ASR`, ensuring a clear data flow direction from the input to the outputs.

- **No Events:** The function block has no event inputs or outputs. Data is transmitted solely via the adapter interfaces.

- **Platform-Neutral:** By using the IEC 61499-2 standard, the function block can be used in various 4diac IDE projects.

## State Overview

The function block does not have an internal state machine (ECC). It operates statically and passes the incoming signal to all outputs without any temporal or logical dependencies.


## Application Scenarios

- **Distribution of an ASR signal** to multiple parallel-operating resources or functional units.

- **Monitoring or parallel control** when multiple components require the same ASR data (e.g., one sensor value to multiple evaluation modules).

- **Simple bus-like structures** in automated control systems, without complex multicast mechanisms.

## Comparison with Similar Modules

- **ASR_SPLIT_4 / ASR_SPLIT_2:** Modules with a smaller number of outputs (4 or 2, respectively). `ASR_SPLIT_9` offers the maximum distribution across nine channels.

- **ASR_MERGE:** Combines multiple ASR signals into one, while `ASR_SPLIT_9` performs the exact opposite function.

- **Data Distributor:** Data type-oriented function blocks (e.g., `DATA_SPLIT`) tend to use simpler data types. `ASR_SPLIT_9` is specifically optimized for complex adapter structures.

## Conclusion

The **ASR_SPLIT_9** function block is a compact and efficient solution for distributing an ASR signal to nine identical outputs. Its generic nature and clear, event-free adapter coupling make it particularly suitable for modular, reusable automation systems based on IEC 61499.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]