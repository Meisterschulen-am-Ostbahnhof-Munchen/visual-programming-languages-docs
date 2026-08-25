# ATM_AX_TP

![ATM_AX_TP](./ATM_AX_TP.svg)

* * * * * * * * * *
## Introduction

The **ATM_AX_TP** is a special timer function block that generates a time-limited pulse from an input signal. It implements the functionality of a **non-retriggerable pulse shaper**. The block is controlled via an AX adapter and outputs the result via another AX adapter; the pulse duration is specified via a separate ATM adapter. The adapter interfaces make it particularly easy to integrate into modular automation systems.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|------------------------------|
| R | Event | Resets the timer |

### **Event Outputs**

No dedicated event outputs – the pulse output is provided via the **Q** adapter (see Adapter section).

### **Data Inputs**

No direct data inputs. The input values (IN and PT) are provided via the corresponding adapter sockets.

### **Data Outputs**

No direct data outputs. The output value (Q) is provided via the **Q** adapter.

### **Adapters**

| Name | Type | Direction | Description |
|-------------|--------|----------|--------------------------------------------------|
| **Q** | AX | Plug | Output: Provides the pulse signal |
| **IN** | AX | Socket | Input: Receives the triggering signal |
| **PT** | ATM | Socket | Input: Provides the pulse duration (pulse time) |

**Note:** The adapters are of type *adapter::types::unidirectional::AX* (or *ATM*) and transmit an event along with a data value.

## Functionality

The **ATM_AX_TP** operates based on the standardized IEC 61499 function block **E_TP**, which is instantiated within the network.

- **Triggering:** A rising edge at input **IN** (event IN.E1 and data value IN.D1 = TRUE) starts the timing.
- **Pulse Generation:** The output **Q** is immediately set to TRUE and remains active for the duration **PT**. After this time has elapsed, Q returns to FALSE.
- **Non-Retriggerable:** During an ongoing pulse, a subsequent rising edge from IN is ignored – the pulse continues at its original length.
- **Reset:** An event at input **R** immediately ends the current pulse (Q = FALSE) and resets the timer. A new pulse can then be started.

Internal wiring:

IN.E1 → E_TP.REQ`
IN.D1 → E_TP.IN`
PT.D1 → E_TP.PT`
E_TP.CNF → Q.E1` (Event output at pulse end)
E_TP.Q   → Q.D1` (Output data value)
R       → E_TP.R`

## Technical Features

- **Adapter-based connection:** Unlike a direct E_TP, ATM_AX_TP operates exclusively via adapters (AX and ATM). This allows for loose coupling in distributed systems and simplifies the exchange of signal types.
- **Compatibility:** This function block is optimized for use with the Eclipse 4diac framework (recognizable by the package attribute `adapter::events::unidirectional::timers`).
- **Versioning:** Multiple versions document the evolution (reset function, package changes).
- **License:** Eclipse Public License 2.0 – the source code may be used, modified, and distributed.

## State Overview

This function block does not have any explicit state machines at the top level – the state logic is implemented entirely by the internal **E_TP**. This state cycles through the following states:

- **IDLE** – waiting for the rising edge of IN
- **ACTIVE** – pulse is running (Q = TRUE, timer is running)
- **RESET** – returned to IDLE by event R (pulse terminates prematurely)

After the timer expires, E_TP automatically switches from ACTIVE to IDLE.

## Application Scenarios

- **Control of momentary actuators:** Valves, lights, signal transmitters that should only be switched on for a specific duration.
- **Debouncing / Pulse shaping:** An incoming signal (e.g., push button) is converted into a precisely defined pulse.
- **Modular automation:** Thanks to the adapter interfaces, the function block is suitable for use in distributed systems where signals are exchanged between different components.

## Comparison with similar function blocks

| Function block | Properties | Difference from ATM_AX_TP |
-----------------|-------------------------------------------------------------------------------|------|
| **E_TP** (Standard) | Direct event/data connections, no adapter. | ATM_AX_TP encapsulates E_TP and provides adapters. |
| **E_R_TRIG** | Edge detection without pulse extension. | Generates only a very short pulse, no time control. |
| **E_CYCLE** | Cyclic timer, repeats pulses. | Single pulse. |

## Conclusion

The **ATM_AX_TP** is a useful function block for generating a non-retriggerable pulse with adjustable duration. Its special feature lies in the adapter-based interface, which enables flexible and loose coupling in IEC 61499 systems. The embedded standard timer E_TP ensures robust and proven functionality. A practical function block for all applications where a defined time window needs to be triggered by an external signal.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
