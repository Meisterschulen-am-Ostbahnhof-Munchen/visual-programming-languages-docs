# ADI_FB_CTUD
![ADI_FB_CTUD](./ADI_FB_CTUD.svg)
* * * * * * * * * *
## Introduction
The **ADI_FB_CTUD** is an up/down counting function block for integer values (DINT). It implements a forward/backward counter that is controlled via standardized **adapter interfaces**. The block encapsulates the IEC 61131-3 component `FB_CTUD_DINT` and provides its functionality via event-driven adapters.
## Interface Structure
### **Event Inputs**
The block does not have direct event inputs. Control is exclusively via the **sockets**:

- **CU (Count Up)** – Event to increment the counter value
- **CD (Count Down)** – Event to decrement the counter value
- **R (Reset)** – Event to reset the counter value to zero
- **LD (Load)** – Event to load the preset value
- **PV (Preset Value)** – Event to set the preset value (data value)

These adapters provide both an event and a data value (for AX adapters, via the data output `D1`).

### **Event Outputs**
- **CNF** – Acknowledge event, which is output after each processing of one of the input events.

### **Data Inputs**
The data values of the input adapters are processed via the connections of the internal function block `FB_CTUD_DINT`. The adapters provide the following data:

- **CU.D1** – Counting direction (Bool, 1 = Count up)
- **CD.D1** – Counting direction (Bool, 1 = Count down)

(Note: In standard CTUD-DINT, only one counting event with direction selection is typically used; here, CU/CD are treated as separate events.)

- **R.D1** – Reset signal (Bool)
- **LD.D1** – Load signal (Bool)
- **PV.D1** – Preset value (DINT)

### **Data Outputs**
The output data is provided via the plug adapters:

- **QU.D1** – Counter has incremented (Bool, after CU event)
- **QD.D1** – Counter has decremented (Bool, after CD event)
- **CV.D1** – Current count value (DINT)

### **Adapters**

The function block uses three different adapter types:

- **unidirectional::AX** – for event and Boolean data (CU, CD, R, LD as sockets; QU, QD as plugs)
- **unidirectional::ADI** – for value transfer (PV as a socket, CV as a plug)

The adapters are designed to transfer both the event and the associated data value in one operation.

## Functionality
The internal function block `FB_CTUD_DINT` implements the classic up/down counter logic:

- When an event occurs on **CU**, the counter value is incremented by 1, provided `CU.D1` = TRUE (or the event alone is considered an up pulse).
- When an event occurs on **CD**, the counter value is decremented by 1, provided `CD.D1` = TRUE.
- An event on **R** resets the counter value to 0.
- An event on **LD** loads the current counter value with the value passed via **PV**.
- After each processing step, **CNF** is output, as well as the events **QU.E1** and **QD.E1** via the corresponding adapters if the counter value has changed.

**Important:** The function block fires the output events (QU.E1, QD.E1) on *every* update (CU, CD, R, LD, PV) – not just on an actual value change. If only edge detection (on-change) is required, the use of an **AX_D_FF** as a filter is recommended.

## Technical Features
- **Adapter-based interface:** All inputs and outputs are via standardized unidirectional adapters, which increases reusability and encapsulation.
- **IEC 61131-3 Compatibility:** The internal counter complies with the standard and allows for easy migration between different control systems.
- **Always Active Events:** As described above, output events are generated with every input event – this can lead to high bus load in time-critical applications.
- **No Top-Level State Machine:** The function block (FB) does not have its own ECC; all logic is executed by the internal FB.

## State Overview

The function block does not have an explicit state machine. Processing is strictly event-driven:

1. Wait for an event at one of the sockets.

2. Process the associated data value (if available) and the internal counter state.

3. Output **CNF** and, if applicable, **QU.E1** and **QD.E1**.

4. Return to step 1.

## Application Scenarios
- **Counting pulses** in manufacturing systems (e.g., workpiece counters).
- **Position detection** with incremental encoders (counting up/down).
- **Bill of materials and inventory counting** with reset capability.
- **Event-driven controllers** in automation technology, where counter readings are exchanged via adapters.

## Comparison with similar function blocks

| Property | ADI_FB_CTUD | Standard CTUD (IEC 61131-3) |

|-------------|---------------|------------------------------|

| Interface | Adapter-based (AX/ADI) | Direct inputs/outputs (events, data) |

| Event behavior | Output on every update | Mostly edge- or value-dependent |

| Reusability | Easy due to adapter encapsulation | Dependent on the specific controller |

| Compatibility | IEC 61131-3 compliant (internal) | Direct standard implementation |

Filtering | Recommendation: AX_D_FF | Partially integrated |

The ADI_FB_CTUD offers clean, adapter-based encapsulation, but requires additional measures for on-change triggering if needed.

## Conclusion
The **ADI_FB_CTUD** is a flexible and standards-compliant up/down counter with a DINT value range, distinguished by its modern adapter interface. It is particularly suitable for modular control architectures where components communicate via standardized adapters. The always-active event output should be considered when integrating it into real-time systems.