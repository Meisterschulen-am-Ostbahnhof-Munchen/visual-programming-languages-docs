# ATM_AX_TON

![ATM_AX_TON](./ATM_AX_TON.svg)

* * * * * * * * * *
## Introduction

The **ATM_AX_TON** is a function block for on-delay. It implements standard timer functionality according to IEC 61499-2, which is controlled via an adapter interface (AX/AT). The block allows a timer to be started via an input adapter and the output state and confirmation of completion to be provided via an output adapter.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| EIPT | Event | Sets the lead time (non-triggering) |

### **Event Outputs**

The function block does not have its own event outputs. Acknowledgments and state changes are communicated via the **Q** adapter (E1).

### **Data Inputs**

The function block (FB) has no explicit data inputs. All input data is provided via the adapter interfaces.

### **Data Outputs**

The FB has no explicit data outputs. Output data is provided via the **Q** adapter (D1).

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Socket | IN | adapter::types::unidirectional::AX | Timer input (AX adapter) – provides the Boolean input signal and the start pulse |
| Socket | PT | adapter::types::unidirectional::ATM | Lead time (AT adapter) – provides the delay time |
| Plug | Q | adapter::types::unidirectional::AX | Timer output (AX adapter) – outputs the timer status and confirmation |

## Functionality

The **ATM_AX_TON** encapsulates a standard on-delay timer (E_TON) from the IEC 61499 library. Detailed functionality:

1. **Starting the timer:**

The input adapter **IN** provides the start pulse (REQ) via its event **E1** and the Boolean value **IN** via its data signal **D1**. When **IN.D1** becomes TRUE, the timer starts.

2. **Delay time:**

The desired delay time is provided via the adapter **PT** (via **PT.D1**). Once the timer is running, the output **Q.D1** is set to TRUE after this delay time has elapsed.

3. **Output Signal and Acknowledgement:**

The output adapter **Q** outputs the current timer state via **Q.D1** (TRUE when the delay time has elapsed, FALSE when the input goes to FALSE). The event **Q.E1** is sent after each state change (CNF of the internal E_TON).

4. **Setting the Lead Time Without Triggering:**

According to the specification, the event input **EIPT** is used to set the lead time **PT** without starting the timer. However, in this FBNetwork, this input is not connected internally – it is available for external use if an application requires a time preset.

5. **Fallback:**

If **IN** goes to FALSE, the timer is immediately reset and **Q.D1** becomes FALSE (without delay).

## Technical Features

- **Adapter-Based Interface:** The function block uses only adapters (AX and ATM) for communication, not traditional input/output grooves. This enables flexible encapsulation and reuse in complex systems.
- **Unidirectional Adapters:** The adapters used are unidirectional (AX for Boolean values and ATM for time values). The function block expects the adapters to be correctly integrated into the higher-level hierarchy.
- **Unconnected Event Input EIPT:** The **EIPT** input is defined but not connected to the internal E_TON. This could indicate a planned extension or external use by the user. In the current version, it has no direct function within the function block network.
- **Authors and Version:** The function block was originally developed by Franz Höpfinger (HR Agrartechnik GmbH) and later revised by Patrick Aigner (version 3.0, April 2025). It is available under the Eclipse Public License 2.0.

## State Overview

The FB itself does not manage its own state machine – the state logic resides in the integrated **E_TON**. Nevertheless, its behavior can be described as follows:

| Input IN State | Behavior | Output Q.D1 |
|-------------------------|-----------|--------------|
| FALSE → TRUE (rising edge) | Timer starts; after the timer expires, Q becomes TRUE | FALSE (until the timer expires) → TRUE |
| TRUE (while the timer is running) | Timer continues running | FALSE |
| TRUE → FALSE (falling edge) | Timer is immediately reset | TRUE → FALSE |
| TRUE (after the timer expires) | Output remains TRUE as long as IN is TRUE | TRUE |
| FALSE (any) | Output remains FALSE | FALSE |

## Application Scenarios

- **Machine Control:** Delaying the activation of drives or valves to prevent multiple components from starting simultaneously.
- **Signal Conditioning:** Debouncing switching signals by only considering a short pulse as valid after a defined time.
- **Process Automation:** Initiating subsequent steps only after a waiting period (e.g., in conveyor belts or dosing systems).
- **Adapter Integration:** Use in systems already based on the AX/AT adapter protocol without additional data lines.

## Comparison with Similar Function Blocks

| Function Block | Type | Special Feature |
|----------|-----|--------------|
| **E_TON** (IEC 61499) | Standard On-Delay | Classic input/output interface; direct event and data ports |
| **ATM_AX_TON** | Adapter-based | Encapsulates E_TON and provides an AX/AT adapter; additional EIPT input (not connected) |
**E_TOF** | Off-Delay | Delay on power-off (opposite behavior) |
**E_CTU** | Up-counter | Counts events, not a timer |

The **ATM_AX_TON** differs in its pure adapter interface and the lack of direct data coupling. It is particularly suitable for modular, hierarchically structured controllers.

## Conclusion

The **ATM_AX_TON** is a ready-made on-delay timer with a modern, adapter-based interface. It simplifies the integration of time delays into larger systems that already use the AX/AT concept. The unconnected **EIPT** input offers potential for future expansions or customer-specific adaptations. Overall, the module is robust, well-documented, and available under an open-source license.

The **ATM_AX_TON** is a ready-to-use on-delay timer with a modern, adapter-based interface. It simplifies the integration of time delays into larger systems that already use the AX/AT concept. The unconnected **EIPT** input offers potential for future expansions or customer-specific adaptations. Overall, the module is robust, well-documented, and available under an open-source license.

The **ATM_AX_TON** is a ready-to-use, adapter-based interface. ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)
