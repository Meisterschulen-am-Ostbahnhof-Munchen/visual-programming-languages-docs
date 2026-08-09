# RT_E_CYCLE

* * * * * * * * * *
## Introduction

The RT_E_CYCLE function block implements periodic event generation (cycle) with real-time capabilities. It allows you to define deadlines and execution times (WCET).
![RT_E_CYCLE](RT_E_CYCLE.svg)
## Interface Structure

### **Event Inputs**

- **START**: Starts the cycle.
- **STOP**: Stops the cycle.

### **Event Outputs**

- **EO**: The cyclically generated event.

### **Data Inputs**

- **DT** (TIME): Cycle time (delay time).
- **Deadline** (TIME): Deadline for event processing.
- **WCET** (TIME): Worst-case execution time.

### **Data Outputs**

- **QO** (BOOL): Status indicator.

## Functionality

After the `START` event, the `EO` event is triggered periodically at time `DT`. The parameters `Deadline` and `WCET` are used for real-time scheduling and monitoring.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2008 ACIN |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac Package | eclipse4diac::rtevents |

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
