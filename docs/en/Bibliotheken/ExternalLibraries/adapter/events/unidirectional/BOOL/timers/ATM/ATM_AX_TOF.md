# ATM_AX_TOF

![ATM_AX_TOF](./ATM_AX_TOF.svg)

* * * * * * * * * *
## Introduction

The function block `ATM_AX_TOF` implements off-delay timing with a modular adapter interface based on the types `AX` and `ATM`. It is typically used to keep an output active for a defined period after an input signal is lost. The block is classified as a standard timer function block according to IEC 61499-2 and is implemented internally with the function block `E_TOF`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|-----------|
| R | Event | Resets the timer |

### **Event Outputs**

No direct event outputs are available. The output is provided via the `Q` adapter.

### **Data Inputs**

No direct data inputs are available. Data is provided via the `IN` and `PT` adapters.

### **Data Outputs**

No direct data outputs are available. The output is provided via the `Q` adapter.

### **Adapters**

| Name | Direction | Type | Description |
|------|----------|------|--------------|
| IN | Socket | AX | Input adapter: Provides the Boolean trigger signal (D1: BOOL) and an event (E1) to trigger the timer function |
| PT | Socket | ATM | Time adapter: Provides the delay time (D1: TIME) |
| Q | Plug | AX | Output adapter: Provides the Boolean output signal (D1: BOOL) and an acknowledgment event (E1) |

## Functionality

The `ATM_AX_TOF` operates on the principle of an **off-delay**:

1. **Normal operation:** As long as the input `IN.D1` (BOOL) has the value `TRUE`, the output `Q.D1` is immediately `TRUE` (without delay).
2. **Shutdown Delay:** When `IN.D1` changes from `TRUE` to `FALSE`, `Q.D1` remains at `TRUE` for the time specified in `PT.D1` (TIME). After this time has elapsed, `Q.D1` changes to `FALSE`.
3. **Reset:** An event at input `R` immediately resets the internal timer. `Q.D1` immediately becomes `FALSE`, regardless of the current state of `IN.D1` or the remaining time.

The trigger is the event `IN.E1` – a new value at `IN.D1` is only applied after an event. An event on `Q.E1` confirms every state change of `Q.D1`.

## Technical Features

- **Adapter-Based Interface:** The use of the universal adapters `AX` and `ATM` enables flexible connection to addressing or other modules without fixed wiring.
- **Internal Implementation:** The function block uses the standard FB `E_TOF` from the IEC 61499 library, ensuring robust and tested timer logic.
- **Reset Function:** The reset input `R` allows for immediate cancellation of the delay, e.g., for controlling safety functions.
- **Compatibility:** Developed for the 4diac IDE and based on the Eclipse Public License 2.0.

## State Overview

The function block goes through the following operating states:

| State | Conditions | Q.D1 | Description |
|-----------------|-----------------------------------|-------|---------------|
| **Idle** | IN.D1 = FALSE, timer is not running | FALSE | Idle state after expiration or reset |
| **Active** | IN.D1 = TRUE | TRUE | Input active, output immediately TRUE |
| **Timing** | IN.D1 changes from TRUE to FALSE, timer active | TRUE | Delay phase: Output remains TRUE for the duration of the delay phase |
| **Resetting** | Event R during Timing or Active | FALSE | Timer is stopped immediately, output goes to FALSE |

## Application Scenarios

- **Fan Run-On:** After a motor is switched off, the fan continues to run for an adjustable time to dissipate residual heat.
- **Signal Debouncing:** Short interruptions in a sensor signal are bridged by the delay.
- **Lighting Control:** Lights remain on for a defined run-on time after leaving a room.
- **Safety Shutdowns:** Reset via R enables immediate shutdown in emergencies.

## Comparison with Similar Function Blocks

| Property | ATM_AX_TOF | E_TOF (Standard) |
|-------------------------|------------------------------------------|--------------------------------------|
| Interface | Adapter (AX/ATM) | Direct Events/Data |
| Reset Function | Yes (Event R) | Yes (Event R) |
| Triggering | Event-driven via adapter event | Event-driven via REQ |
| Flexibility | Increased through adapter coupling | Simpler, but more rigid |
| Application Area | Modular automation systems | Basic function in IEC 61499 editors |

## Conclusion

The `ATM_AX_TOF` offers a reliable and flexible turn-off delay for modular automation projects. Thanks to the adapter interface, it can be easily integrated into various system landscapes and extends the functionality of the standard timer `E_TOF` by adding a reset option and loose coupling via AX/AT adapters. It is ideal for applications requiring a delayed shutdown with optional immediate reset.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
