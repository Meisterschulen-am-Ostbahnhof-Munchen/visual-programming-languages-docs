# AUI_CTD
![AUI_CTD](./AUI_CTD.svg)
* * * * * * * * * *
## Introduction
The **AUI_CTD** is an event-driven down counter with adapter interfaces. It features **On-Change triggering**: The output signal **Q** is only updated when its logical state actually changes. This avoids unnecessary events and increases efficiency in event-driven systems.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|----------------------------------------------|

| **CD** | Count Down – reduces the counter value by 1. |

| **LD** | Load – loads the counter value **CV** with the preset value **PV**. |

### **Event Outputs**

| Event | Description |

|----------|----------------------------------------------------------|

| **CDO** | Count Down Output – output after each CD step. |

| **LDO** | Load Output – output after a successful load. |

### **Data Inputs**

The FB has no direct data inputs. Instead, values are provided via the adapter interface **PV**.

### **Data Outputs**

The FB has no direct data outputs. The current values of **CV** and **Q** are output via the respective adapter ports.

### **Adapter**

| Port | Type | Direction | Description |

|-------|------------------------------------------------|----------|------------------------------------------------------|

| **Q** | `adapter::types::unidirectional::AX` (BOOL) | Plug | Status output: `TRUE`, if **CV ≤ 0**. |

| **CV**| `adapter::types::unidirectional::AUI` (INT) | Plug | Current counter value. |

| **PV**| `adapter::types::unidirectional::AUI` (INT) | Socket | Preset value loaded into **CV** during the LD event. |

## Functionality

1. **Count Down (CD)**

Each **CD** event decrements **CV** by 1 and sets **Q** to `TRUE` if **CV ≤ 0**. **CDO** is then output.

2. **Load (LD)**

An **LD** event copies the value from **PV** to **CV**. **Q** is updated accordingly (TRUE if **CV ≤ 0**). Then, **LDO** is output.

3. **On-Change Triggering**

The function block (FB) compares the current **Q** value with the stored predecessor value **Q_OLD**. The adapter event **Q.E1** is only triggered if **Q** has changed. Otherwise, the FB returns directly to its initial state. This prevents repeated identical messages.

4. **PV Changes**

When the **PV** adapter reports (event **PV.E1**), **Q** is recalculated (using the **UPDATE** algorithm). Here too, **Q** is only output when there is a state change.

## Technical Features
- **On-Change Triggering** – Reduces event load by activating the **Q** output only when changes actually occur.
- **Adapter Interface** – Enables loose coupling and reuse in complex control structures.
- **Initial Value** – **Q_OLD** is initialized with `FALSE`, so that a change is detected on the first iteration if **CV** is already ≤ 0.

## State Overview

The process is controlled by the following ECC states:

| State | Description | Actions |

|---------------|--------------------------------------------------------------|----------------------------------|

| **START** | Waits for incoming events (CD, LD, PV.E1). | – |

| **CD** | Executes the countdown algorithm. | `CD (CV--, Q aktualisieren)`, `CV.E1`, `CDO` |

**LD** | Loads **PV** into **CV**. | `LOAD (CV:=PV; Q aktualisieren)`, `CV.E1`, `LDO` |

**UPDATE_PV** | Recalculates **Q** when **PV** changes. | `UPDATE (Q aus CV berechnen)` |

**EMIT_Q** | Saves the current **Q** value and triggers **Q.E1**. | `SAVE_Q (Q_OLD:=Q)`, `Q.E1` |

**Transitions**:

- After **CD**, **LD**, or **UPDATE_PV**, the system only switches to **EMIT_Q** if `Q.D1 ≠ Q_OLD` is present.
- If the values are equal (`Q.D1 = Q_OLD`), the system immediately returns to **START** without triggering **Q.E1**.
- From **EMIT_Q**, the system always switches back to **START**.

## Application Scenarios
- **Material Counter** in Conveyor Systems: **CD** is triggered for each part that leaves the station. As soon as **CV ≤ 0**, a replenishment request is sent.
- **Cycle Control** for Repeated Processes: The counter runs from a starting value (loaded via **LD**) to zero and then triggers an action.
- **Event-optimized systems** with many parallel counters: Thanks to on-change triggering, only relevant status changes are reported.

## Comparison with similar function blocks

| Function block | Special feature | Difference to AUI_CTD |

|----------|----------------------------------|-----------------------------------------------------|

| **E_CTD**| Standard down counter without adapters | Uses direct data inputs/outputs and no adapters. No on-change triggering. |

| **E_CTUD** | Up/down counter | Offers both counting directions, but without adapters and without on-change. |

| **AUI_CTU**| Up counter with adapters | Counts upwards, analog adapter structure, also on-change. |

The **AUI_CTD** fills the gap of a specialized down counter with more modern adapter concepts and reduced event volume.

## Conclusion

The **AUI_CTD** is a powerful down counter for IEC 61499-compliant controllers. Its combination of adapter interfaces and on-change triggering makes it particularly suitable for modular, resource-efficient automation solutions. Its behavior is deterministic and can be easily traced via the ECC. This makes it an ideal choice for applications requiring reliable and efficient counter functionality with minimized event communication.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 E_CTU Event Counter block on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)

]