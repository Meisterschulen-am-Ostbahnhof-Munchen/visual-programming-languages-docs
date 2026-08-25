# ASR_SPLIT_3

![ASR_SPLIT_3](./ASR_SPLIT_3.svg)

* * * * * * * * * *
## Introduction

The function block `ASR_SPLIT_3` is used to distribute an incoming ASR (Application-Specific Resource) adapter to three identical outgoing ASR adapters. It is designed as a generic block and enables simple signal distribution within an adapter-based communication structure.
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
|-------------|----------|------|--------------------------------------|
| Socket | Input | IN | Incoming ASR signal adapter. |
| Plug | Output | OUT1 | First outgoing ASR signal adapter. |
| Plug | Output | OUT2 | Second outgoing ASR signal adapter. |
| Plug | Output | OUT3 | Third outgoing ASR signal adapter. |

All adapters are of type `adapter::types::unidirectional::ASR`.
...
## Functionality

This function block forwards all signals and events arriving via socket `IN` from the ASR adapter unchanged to the three plug channels `OUT1`, `OUT2`, and `OUT3`. No logical processing or buffering takes place – the distribution is passive and instantaneous. The function block acts as a simple splitter for ASR connections.

## Technical Features

- The function block is generic (attribute `eclipse4diac::core::GenericClassName` = `'GEN_ASR_SPLIT'`), allowing it to be reused for different instances of the ASR type.
- No Execution Control Chart (ECC) is required, as the forwarding occurs directly through the adapter coupling.

- All three outputs are separately addressable, allowing different target modules to be connected independently.

## State Overview

Since the module does not process events and operates without a state, there is no state diagram. Its functionality is limited to passive signal pass-through.

## Application Scenarios

- **Distributing control signals** to multiple parallel components in an automation system, e.g., to three drives or sensors.
- **Splitting ASR communication** across different subsystems that expect the same adapter interface.
- **Test and debugging setups** where a signal needs to be forwarded to multiple monitoring points simultaneously.

## Comparison with Similar Modules

- `ASR_SPLIT_2` splits an ASR signal across two outputs; `ASR_SPLIT_3` extends this functionality to three outputs.
- `ASR_MERGE` (if present) combines multiple ASR signals, while `ASR_SPLIT_3` separates them.
- Unlike generic data splitters, this component operates directly at the adapter level and requires no additional data type conversions.

## Conclusion

The `ASR_SPLIT_3` is a simple yet effective component for duplicating an ASR signal to three identical outputs. It is particularly well-suited for modular structures where a central signal is needed multiple times. Its generic design increases reusability and reduces configuration effort.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
