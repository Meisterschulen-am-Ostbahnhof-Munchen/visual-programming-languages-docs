# AUI_CTUD
![AUI_CTUD](./AUI_CTUD.svg)
* * * * * * * * * *
## Introduction
The function block **AUI_CTUD** is an event-driven up/down counter in the adapter version. It is based on the standard function block E_CTUD and extends it with "On-Change" triggering for the output states. The counter value (CV), the preset value (PV), and the comparison results (QU, QD) are exchanged with other function blocks via the adapter interfaces. The function block is intended for use in IEC 61499 applications where loose coupling via adapters is desired.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| **CU** | Increment counter by 1 (Count Up) |
| **CD** | Decrease counter by 1 (Count Down) |

**R** | Reset counter to 0 (Reset) |

**LD** | Load counter with preset value (PV) (Load) |

### **Event Outputs**

| Event | Description |

|----------|--------------|

**CUO** | Acknowledgement of successful count-up operation |

**CDO** | Acknowledgement of successful count-down operation |

**RO** | Acknowledgement of successful reset |

**LDO** | Acknowledgement of successful load operation |

### **Data Inputs**

This function block does not have direct data inputs. The preset value (PV) is provided via a **socket adapter**:

| Adapter (Socket) | Type | Description |

|------------------|-----|--------------|

| **PV** | `adapter::types::unidirectional::AUI` | Preset value (preselection) for the counter |

### **Data Outputs**

This function block does not have direct data outputs. The results are output via **Plug Adapters**:

| Adapter (Plug) | Type | Description |

|-----|--------------|

| **QU** | `adapter::types::unidirectional::AX` | True if the current counter value is ≥ PV |

| **QD** | `adapter::types::unidirectional::AX` | True if the current counter value is ≤ 0 |

| **CV** | `adapter::types::unidirectional::AUI` | Current Counter Value (Unsigned Integer) |

### **Adapters**

This function block defines three plug adapters (QU, QD, CV) and one socket adapter (PV). The adapters are of type `adapter::types::unidirectional` and enable loose coupling between the function blocks – values are exchanged via events (e.g., `CV.E1`, `QU.E1`).

## Functionality

This function block operates as an event-driven counter with a resolution of 0 to 65535 (maximum value for an unsigned 16-bit integer). The following sequence of steps is executed:

1. An **input event** (CU, CD, R, or LD) triggers a transition from the start state to the corresponding processing state.

2. **Calculation**: In each algorithm, the internal counter (`CV.D1`) is updated, and the output adapters QU and QD are recalculated:

- **CU**: `CV.D1 := CV.D1 + 1` (only if the previous value < 65535)
- **CD**: `CV.D1 := CV.D1 - 1` (nur, wenn der Wert vorher > was 0)
- **R**: `CV.D1 := 0`
- **LD**: `CV.D1 := PV.D1`
- Subsequently, `QU.D1 := (CV.D1 >= PV.D1)` and `QD.D1 := (CV.D1 <= 0)` are set.

3. **Counter Value Output**: After each value change, the event `CV.E1` is sent to propagate the new counter value via the adapter.

**CU**: ** ... 4. **On-Change Triggering**:

- After each counting operation or after a change to the PV (event from the PV adapter), the state of QU and QD is checked.
- The internal variables `QU_OLD` and `QD_OLD` store the previous state. Only if the value has changed is the corresponding adapter event (`QU.E1` or `QD.E1`) triggered.
- This behavior prevents unnecessary event flooding with constant threshold values.

5. **Processing of PV Changes**: An incoming event on the PV adapter (`PV.E1`) results in the state `UPDATE_PV`, in which only the comparison results are recalculated (without changing the counter). The on-change check is also performed afterward.

## Technical Features
- **On-Change Triggering** (Change Detection): The module sends events to the output adapters only if the logical state has actually changed compared to the last iteration. This reduces the bus load and prevents infinite loops in cyclic systems.
- **Adapter-Based Communication**: All input and output values are exchanged via adapters (plug/socket), enabling flexible interconnection without fixed data connections. The counter value (CV) and the comparison results (QU, QD) are provided as plug adapters, while the preset value (PV) is supplied as a socket from external modules.
- **State Overflow Protection**: During count-up, the module checks whether the current value is less than 65535; during count-down, it checks whether it is greater than 0. This prevents overflows and underflows.
- **Two internal state variables**: `QU_OLD` and `QD_OLD` serve as shadow registers for change detection.
- **Extended ECC**: After each counting operation, the function block cycles through a sequential chain of states (e.g., CU → CHECK_QU → CHECK_QD → START) to ensure change detection.

## State Overview

| State | Description |

|----------------|--------------|

| **START** | Waiting for an input event (CU, CD, R, LD) or a PV change |

| **CU** | Increment counter and output new value via CV adapter |

| **CD** | Decrement counter and output new value via CV adapter |

| **R** | Reset counter to 0 and output new value via CV adapter |

| **LD** | Load meter with PV and output new value via CV adapter |

**UPDATE_PV** | Recalculate QU and QD after PV change (without meter change) |

**CHECK_QU** | Check if QU has changed (comparison with QU_OLD) |

**FIRE_QU** | If QU has changed: Update QU_OLD and send event to QU adapter |

**CHECK_QD** | Check if QD has changed (comparison with QD_OLD) |

**FIRE_QD** | If QD has changed: Update QD_OLD and send event to QD adapter |

The state transitions are controlled by the events and conditions `[QU.D1 <> QU_OLD]` and `[QD.D1 <> QD_OLD]`. After change detection is complete, the function block returns to the START state.

## Application Scenarios
- **Counters with External Preset**: In a system, the preset value (PV) can be dynamically set by a higher-level system or an HMI via the PV adapter. The function block then counts events and reports when the thresholds are reached or fallen below via the QU and QD adapters.
- **Direction-Dependent Counters**: By using CU and CD, a forward/reverse counter can be implemented, e.g., for position detection or inventory counting.
- **Event-Driven Limit Monitoring**: The on-change triggering of QU and QD is ideally suited for sending a discrete signal (e.g., "fill level reached") only when a state changes – similar to an edge detector.

-- **Modular Control Architecture**: Thanks to the adapter interface, the function block can be integrated into an existing IEC 61499 application without fixed data port wiring. The logical connection is established solely via the adapter runtime environment.

## Comparison with Similar Function Blocks

The standard function block **E_CTUD** (from the IEC 61499 library) also offers an up/down counter with event control, but with the following features:

| Feature | **E_CTUD** (Standard) | **AUI_CTUD** (Adapter Version) |

|-----------------------|-----------------------------------------------|-------------------------------------------------|

| Interface | Fixed event and data ports (e.g., CV as BOOL) | Loose coupling via adapter (plug/socket) |

| Output: Counter value | Data port: CV (INT/UDINT) | Adapter CV (Type AUI) |

| Limit output | Bool ports QU, QD | Adapter QU, QD (Type AX) |

| Event on change | No change detection; QU/QD are calculated with each count | On-change triggering: Event only on state change |

| Feedback on actions | No dedicated feedback events | CUO, CDO, RO, LDO as confirmation events |

The AUI_CTUD is therefore more flexible in its interconnection and reduces the event load in distributed systems. For simple applications without adapters, however, the standard E_CTUD may suffice.

## Conclusion

The **AUI_CTUD** function block represents a modern, adapter-based variant of an up/down counter. The on-change triggering of the limits and the feedback via dedicated event outputs are particularly noteworthy. The use of adapter interfaces enables loose coupling and reusability in a wide variety of control projects. Integrated overflow/underflow protection and the clean separation of counting and evaluation logic make it a robust component for industrial automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 E_CTU Event Counter component on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)

]