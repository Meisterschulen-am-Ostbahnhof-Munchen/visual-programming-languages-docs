# RT_E_DELAY
* * * * * * * * * *
## Introduction
The RT_E_DELAY function block delays an event by a defined time (DT) while adhering to real-time requirements.
![RT_E_DELAY](RT_E_DELAY.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Initialization.
- **START**: Starts the delay.
- **STOP**: Stops the delay.

### **Event Outputs**
- **INITO**: Initialization acknowledged.
- **EO**: The delayed event.

### **Data Inputs**
- **QI** (BOOL): Qualifier.
- **DT** (TIME): Delay time.
- **Tmin** (TIME): Minimum time.
- **Deadline** (TIME): Deadline.
- **WCET** (TIME): Worst-case execution time.

### **Data Outputs**
- **QO** (BOOL): Status.

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | (c) 2008, 2014 ACIN, Profactor GmbH |

| License | EPL-2.0 |

| Version | 3.0 (2025-04-14, Patrick Aigner) |

| 4diac Package | eclipse4diac::rtevents |

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]