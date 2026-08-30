# AIS_SPLIT_2

![AIS_SPLIT_2](./AIS_SPLIT_2.svg)

* * * * * * * * * *
## Introduction

The function block **AIS_SPLIT_2** is a generic adapter module that splits an incoming unidirectional AIS adapter (Application Interface Socket) into two identical outgoing AIS adapters. It serves as a passive splitter without its own logic or event processing.
## Interface Structure

### **Event Inputs**

Not present.

### **Event Outputs**

Not present.

### **Data Inputs**

Not present.

### **Data Outputs**

Not present.

### **Adapter**

- **IN** (Socket): Type `adapter::types::unidirectional::AIS` – Input interface for the adapter to be distributed.
- **OUT1** (Plug): Type `adapter::types::unidirectional::AIS` – first output, receives all data/events from IN.
- **OUT2** (Plug): Type `adapter::types::unidirectional::AIS` – second output, receives identical data/events as OUT1.

## Functionality

The function block forwards the adapter connected to socket **IN** unchanged and without delay to both plugs **OUT1** and **OUT2**. All events and data defined via the AIS adapter are copied to both outputs in parallel. The function block itself has no processing logic, states, or timing behavior.

## Technical Features

- **Generic Parameterization**: The specific AIS adapter type is only defined during project configuration via the attribute `eclipse4diac::core::GenericClassName` (default value: `'GEN_AIS_SPLIT'`). This allows the function block to be reused for different AIS variants.
- **No Eigenstates**: Since there is no ECC state machine or data/event inputs/outputs, the function block is purely passive and behaves like a "wiring aid."
- **Unidirectional**: The adapters are declared as unidirectional – a data flow direction from IN to OUT1/OUT2 is implicit.

## State Overview

The AIS_SPLIT_2 does not have its own state machine. The operating state is determined exclusively by the connected AIS adapters.

## Application Scenarios

- **Parallel Processing**: An AIS signal is to be processed simultaneously by two subsequent function blocks (e.g., visualization and control).
- **Monitoring**: Branching off an AIS signal to a monitoring instance without affecting the original signal.
- **Generic Splitting**: Used in libraries where the exact AIS structure is only defined at runtime or configuration time.

## Comparison with Similar Function Blocks

- **AIS_SPLIT_4**: Offers four outputs instead of two; otherwise, identical functionality.
- **Event/Data Splitter**: Other splitters work with simple events or data (e.g., F_SPLIT), while AIS_SPLIT_2 splits complete adapter interfaces.
- **AIS_MERGE**: The counterpart that combines two AIS inputs into one output.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AIS_SPLIT_2 is a minimalist, generically applicable adapter splitter that enables the flexible branching of AIS interfaces in 4diac projects. By configuring it via the GenericClassName attribute, it can be used for different AIS types without modifying the source code.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
