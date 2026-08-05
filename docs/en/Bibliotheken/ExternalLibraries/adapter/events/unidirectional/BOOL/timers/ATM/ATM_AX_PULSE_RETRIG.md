# ATM_AX_PULSE_RETRIG
![ATM_AX_PULSE_RETRIG](./ATM_AX_PULSE_RETRIG.svg)
* * * * * * * * * *
## Introduction
The function block **ATM_AX_PULSE_RETRIG** generates a pulse of defined duration at its output. It is designed as a retriggerable version, meaning that a new start command during a running pulse resets the pulse duration. Control and parameter transfer are handled exclusively via two standardized adapter interfaces (ATM / AX), so the block does not require direct data inputs/outputs.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|--------------------------------------------|

| REQ | Event | Start command – triggers a new pulse and restarts the timer |

| R | Event | Reset – immediately terminates a running pulse |

### **Event Outputs**
None.

### **Data Inputs**
None. The pulse duration is provided via the **PT** adapter (Socket).

### **Data Outputs**
None. The pulse status (active/inactive) is output via the **Q** adapter (Plug).

### **Adapters**

| Role | Name | Type | Direction | Description |

|-------|------|-------|----------|---------|-------------------------------------------------------|

| Input | PT | ATM | Socket | Provides the desired pulse duration <small>(D1 → PT)</small> |

| Output| Q | AX | Plug | Displays the pulse state <small>(D1 = HIGH during the pulse)</small> |

## Functionality
When the function block is triggered by a **REQ** event, it starts a timer with the duration specified by the **PT** adapter (data value D1). The **Q** output (D1) is immediately set to **HIGH** and remains active for exactly this duration. If another **REQ** event arrives during an ongoing pulse, the timer is reset and the pulse duration starts again (retriggerable). A **Reset** event (**R**) terminates the pulse prematurely and sets **Q** to **LOW**.

The function block implements the internal logic using the standardized IEC 61499 function block **E_PULSE_RETRIG**, which handles all timing functions. The adapters (PT → D1 to internal timer, internal output Q → Q.D1) are connected via a hidden network.

## Technical Features
- **Retriggerable Behavior**: Each new **REQ** during an active pulse extends the pulse duration to the full value of PT.
- **Adapter-Based Interface**: The module has no direct event outputs or data ports; all communication takes place via the standardized **ATM** (parameter) and **AX** (output) adapters.
- **Reusability**: Due to the strict separation of control and parameterization, the module is particularly suitable for modular and reusable applications.

## State Overview
The module has two states:

- **Inactive** (Q.D1 = FALSE): No pulse is active, timer is not running.
- **Active** (Q.D1 = TRUE): Pulse is running; upon entry by a REQ, the timer is started with PT. Each subsequent REQ resets the timer. An R event immediately returns the device to the inactive state.

## Application Scenarios
- **Clock Generator for Signal Lights**: A continuous start signal (e.g., push button or sensor) generates a defined light pulse. The retrigger function keeps the light on continuously with a constant signal.
- **Pulse Extension in Controllers**: Short input pulses are extended to a minimum or defined duration.
- **Control of Actuators with Minimum On-Time**: Valves, motors, or relays requiring a specific on-time can be reliably controlled.

## Comparison with Similar Components

| Component | Retriggerable | Interface | Application Area |

|-------------------------|---------------|----------------------|-----------------------------------|

| **ATM_AX_PULSE_RETRIG** | Yes | Adapter (ATM/AX) | Modular Controllers with Adapter Concept |

ATM_AX_PULSE | No | Adapter (ATM/AX) | Single pulses, no retriggering |

Standard E_PULSE_RETRIG | Yes | Direct inputs/outputs | More flexible, but without adapter encapsulation |

This module stands out due to its exclusive use of adapter interfaces, which simplifies integration into existing adapter-based libraries.

## Conclusion
**ATM_AX_PULSE_RETRIG** is a compact, retriggerable pulse module characterized by its clean encapsulation using an ATM/AX adapter. It is ideally suited for use in distributed control systems based on the IEC 61499 adapter concept. Its ease of use (two events, two adapters) and proven timer behavior make it a reliable component for time-controlled outputs.