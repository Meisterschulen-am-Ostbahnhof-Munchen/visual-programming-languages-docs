# AUDI_SPLIT_6

![AUDI_SPLIT_6](./AUDI_SPLIT_6.svg)

* * * * * * * * * *

## Introduction

The function block **AUDI_SPLIT_6** serves as a generic splitter for a unidirectional AUDI adapter. It receives an incoming adapter data stream via a socket and forwards it unchanged to six separate output adapters (plugs). The block is designed generically, so the specific adapter type can be configured via the attribute `GenericClassName`.

## Interface Structure

### **Event Inputs**
None.

### **Event Outputs**
None.

### **Data Inputs**
None.

### **Data Outputs**
None.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

Socket | **IN** | `adapter::types::unidirectional::AUDI` | Incoming adapter for the data stream to be distributed. |

Plug | **OUT1** | `adapter::types::unidirectional::AUDI` | First output adapter (copy of the input). |

Plug | **OUT2** | `adapter::types::unidirectional::AUDI` | Second output adapter. |

Plug | **OUT3** | `adapter::types::unidirectional::AUDI` | Third output adapter. |

Plug | **OUT4** | `adapter::types::unidirectional::AUDI` | Fourth output adapter. |

Plug | **OUT5** | `adapter::types::unidirectional::AUDI` | Fifth output adapter. |

Plug | **OUT6** | `adapter::types::unidirectional::AUDI` | Sixth output adapter. |

## Functionality

This function block acts as a pure distributor without any data processing. The data stream arriving via the **IN** socket is forwarded unchanged and in parallel to all six output adapters (OUT1–OUT6). Distribution occurs continuously as soon as the input adapter provides data. Since the function block is generic, it can be adapted to a specific adapter type (e.g., a custom derived type) by setting the attribute `eclipse4diac::core::GenericClassName`.

## Technical Features

- **Generic Design:** The function block uses the 4diac generic mechanisms (`GenericClassName`). This allows the adapter type to be set at runtime or during instantiation without recompiling the function block.

- **Unidirectional:** Both the input and output adapters are unidirectional. No feedback from the outputs to the input is provided.

- **No Event Control:** The function block has no event interface and no ECC. Data transmission is purely data-driven (as soon as data is present at the IN socket).

- **No Internal State:** No state change occurs; the function block is stateless.

## State Overview

No state machine (ECC) exists. The function block does not execute any sequential processes.

## Application Scenarios

- **Data Distribution:** An audio data stream provided by a sensor or another function block is to be sent to several subsequent components simultaneously, e.g., to a visualization, a logging component, and control logic.

- **Parallel Processing:** When the same data stream needs to be processed in parallel in different path segments, e.g., filtering, conditioning, and storage.

- **Generic Use:** Thanks to its configurable type assignment, the function block (FB) can be used in various projects with different adapter definitions without having to modify the source code.

## Comparison with Similar Function Blocks

Other split function blocks exist (e.g., `AUDI_SPLIT_2`, `AUDI_SPLIT_4`) that differ only in the number of outputs. With six outputs, `AUDI_SPLIT_6` offers a higher distribution density. Unlike pure data splitters for basic data types, this FB works exclusively with AUDI adapters and supports unidirectional coupling.

## Conclusion

`AUDI_SPLIT_6` is a simple yet flexible function block for multiplying adapter connections in a 4diac environment. Its generic nature and lean implementation without event overhead make it ideal for scenarios where an incoming data stream needs to be distributed to multiple independent receivers.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]