# ASR_SPLIT_2

![ASR_SPLIT_2](./ASR_SPLIT_2.svg)

* * * * * * * * * *
## Introduction

The function block **ASR_SPLIT_2** splits an incoming unidirectional ASR (Application Service Request) adapter into two identical output adapters. It is designed as a generic function block and allows an ASR signal to be forwarded to two separate consumers or subsequent function blocks without changing the logic.
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

| Type | Direction | Name | Description |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::ASR` | Input (Socket) | **IN** | Incoming ASR signal |
| `adapter::types::unidirectional::ASR` | Output (Plug) | **OUT1** | First outgoing ASR path |
| `adapter::types::unidirectional::ASR` | Output (Plug) | **OUT2** | Second outgoing ASR path |

## Functionality

This module passes the ASR signal received via socket **IN** unchanged to both plugs **OUT1** and **OUT2**. No processing, filtering, or delay occurs – the signal is passively split into two paths. Each output provides the exact same information as the input.

## Technical Features

- The function block is implemented as a **Generic Function Block (FB)**. The actual type instance is determined at runtime by configuring the generic class attribute (`eclipse4diac::core::GenericClassName = 'GEN_ASR_SPLIT'`).
- No event or data inputs/outputs are used – all communication takes place exclusively via the adapter interfaces.
- The outputs are independent of each other; an error or blockage at one output does not affect the other.

## State Overview

The function block does not have its own state diagram, as it operates purely passively. Its behavior corresponds to a static branch.

## Application Scenarios

- **Parallelization of Service Requests:** An ASR (e.g., a service request) should be sent to two independent components, e.g., to a logging component and simultaneously to an execution service.
- **Redundancy:** Distribution of a signal across two redundant paths to increase fault tolerance.
- **Adapter Bridge:** Used in systems where an ASR connection needs to be split across two adapter points without copying the logic.

## Comparison with Similar Components

- **ASR_MERGE_2** (hypothetical): Combines two ASR inputs into one output (e.g., using priority or a logical OR operation). The **ASR_SPLIT_2** does the opposite.
- **SPLIT_1_to_N** (generic split components): A general splitter that operates with a configurable number of outputs. The **ASR_SPLIT_2** is a specialized version with two fixed outputs.

## Conclusion

The **ASR_SPLIT_2** is a simple yet useful generic component for multiplying ASR signals. Thanks to its platform-independent adapters and purely passive operation, it is suitable for all scenarios where a service signal needs to be distributed across multiple paths. Integration requires no configuration and has no side effects on the transmitted data.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
