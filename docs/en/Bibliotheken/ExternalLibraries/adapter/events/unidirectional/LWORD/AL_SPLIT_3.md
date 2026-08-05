# AL_SPLIT_3
![AL_SPLIT_3](./AL_SPLIT_3.svg)

* * * * * * * * * *
## Introduction
The function block **AL_SPLIT_3** is used to split an incoming unidirectional adapter signal (AL – Adapter Label) into three identical output adapters. It is designed as a generic building block and enables the multiple forwarding of an adapter-based data or event flow within an IEC 61499 application.
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

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| `adapter::types::unidirectional::AL` | IN | Socket | Input adapter that provides the signal to be distributed. |

| `adapter::types::unidirectional::AL` | OUT1 | Plug | First output adapter – identical copy of the input signal. |

| `adapter::types::unidirectional::AL` | OUT2 | Plug | Second output adapter – identical copy of the input signal. |

| `adapter::types::unidirectional::AL` | OUT3 | Plug | Third output adapter – identical copy of the input signal. |

## Functionality
The function block (FB) forwards the unidirectional adapter signal present at socket **IN** **unchanged and without delay** to the three plugs **OUT1**, **OUT2**, and **OUT3**. No logical or timing manipulation takes place – the distribution is purely structural. This behavior corresponds to passive wiring ("fan-out") at the adapter level.

## Technical Features
- **Generic Implementation:** The function block uses the generic class name `'GEN_AL_SPLIT'`, allowing it to be reused for various instances of the unidirectional AL type, as long as the specific type is defined at design time.
- **No State Logic:** There are no internal states, events, or data variables. The FB is completely passive and requires no active processing.
- **No Runtime Dependencies:** The functionality is implemented at design time by the interconnection system of the 4diac IDE.

## State Overview
The function block (FB) has **no internal state** and no state machine. It does not execute any sequential processes. The output signal is always a direct copy of the input signal.

## Application Scenarios
- **Multiple Use of an Adapter:** A unidirectional AL signal provided by a component is to be distributed to several subsequent function blocks (e.g., a sensor signal to different evaluation units).
- **Architectural Structuring:** Splitting a data stream for parallel processing or monitoring without the source component needing to know the number of sinks.
- **Testing and Diagnostic Purposes:** Connecting additional monitoring or logging blocks to an existing adapter connection.

## Comparison with Similar Function Blocks
- **Event-Based Splitters (e.g., E_SPLIT):** These split events, while AL_SPLIT_3 distributes adapter objects (complex data structures). Event splitters often require handling of event sequences.
- **Adapter Merger (e.g., AL_MERGE):** Combines multiple adapter signals into one – the opposite of the function described here.
- **Individual AL Splitters:** Generic versions also exist for other output numbers (e.g., AL_SPLIT_2, AL_SPLIT_4), differing only in the number of plugs.

## Conclusion
**AL_SPLIT_3** is a simple yet useful generic function block for duplicating a unidirectional adapter signal to three independent outputs. Due to its passive nature, it is resource-efficient and ideally suited for the flexible design of IEC 61499 applications where a signal is needed multiple times without altering the source logic.

**AL_SPLIT_3** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
