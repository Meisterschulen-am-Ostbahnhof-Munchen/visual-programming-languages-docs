# ATM_AX_TP_RETRIG
![ATM_AX_TP_RETRIG](./ATM_AX_TP_RETRIG.svg)

* * * * * * * * * *
## Introduction
The `ATM_AX_TP_RETRIG` is a retriggerable pulse timer function block. It generates a pulse of defined duration at the output when the input switches to TRUE. During the pulse's execution, additional triggers can restart the timer (retrigger function). A reset input immediately terminates the pulse. The block uses standardized adapters for input and output, enabling flexible integration into modular control systems.
## Interface Structure
### **Event Inputs**
- **R** (Event) – Reset: Resets the timer and terminates the current pulse.

## **Event Outputs**
- **Q.E1** (Event) – Output Event: Triggered via adapter Q when the pulse state changes (start or end).

### **Data Inputs**
- **IN.D1** (BOOL) – Trigger Input: On a rising edge and a TRUE value, the timer starts.
- **PT.D1** (TIME) – Pulse Duration: Specifies the time for which output Q is set to TRUE after a trigger.

### **Data Outputs**
- **Q.D1** (BOOL) – Pulse Output: Displays TRUE during the pulse duration, otherwise FALSE.

### **Adapters**
- **IN** (Socket, Type AX) – Input Adapter: Couples the trigger event (E1) and the Boolean trigger value (D1).
- **PT** (Socket, Type ATM) – Time Adapter: Returns the pulse duration as a TIME value (D1).
- **Q** (Plug, Type AX) – Output Adapter: Provides the pulse state (D1) and an event on state change (E1).

## Functionality
The function block internally uses the standard function block `E_TP_RETRIG`. An event at the input **IN** (rising edge of IN.E1) starts the timer, provided **IN.D1** = TRUE. The output **Q.D1** is set to TRUE for the time specified in **PT.D1**. During this time, a subsequent trigger (repeated IN.E1 with IN.D1 = TRUE) triggers a retrigger: The timer is reset, and the pulse starts again. An event at the reset input **R** immediately ends the pulse, and **Q.D1** becomes FALSE. After the pulse duration has elapsed without a further trigger, **Q.D1** automatically returns to FALSE.

## Technical Features
- **Retriggerable**: Multiple triggers during a running pulse restart the timer without extending the pulse duration.
- **Adapter-based interface**: The IN, PT, and Q adapters ensure a clean separation of event and data communication.
- **Internal standard module**: The actual timer logic is executed by the IEC 61499-compliant `E_TP_RETRIG` module.
- **Unidirectional adapters**: Both the AX and ATM adapters are unidirectional, clearly defining the data flow direction.

## State overview
The module has two main states:

| State | Q.D1 | Description |

|----------|-------|-------------------------------------------------------------------|

| **IDLE** | FALSE | Idle state, no pulse active. |

| **TIMING** | TRUE | Pulse running, timer counts down the duration PT. |

**Transitions:**

- IDLE → TIMING: Trigger (IN.E1 with IN.D1 = TRUE)
- TIMING → TIMING (Retrigger): A subsequent trigger restarts the timer.
- TIMING → IDLE: Timer expires or Reset (R)
- IDLE → IDLE: Reset has no effect

## Application Scenarios
- **Pulse Control for Actuators**: Control of valves, lamps, or motors that are activated for a defined time upon receiving a start signal.
- **Safety Applications**: Retriggerable pulses allow for a renewed request during an ongoing action, e.g., for button retriggering.
- **Modular Automation Systems**: Use in combination with other adapter-based components for standardized communication via AX/ATM interfaces.

## Comparison with Similar Function Blocks
- *E_TP (non-retriggerable)*: Ignores a subsequent trigger during the running pulse; once started, the pulse always runs its full course.
- *E_TP_RETRIG (Standard)*: Same timer logic, but without an adapter interface – connected directly via event and data inputs.
- *TON / TOF*: Other timer types; TON delays power-on, TOF delays power-off – neither generates pulses.

## Conclusion
The `ATM_AX_TP_RETRIG` combines the proven retriggerable pulse function with an adapter-based interface. By using standardized AX and ATM adapters, it is particularly well-suited for modular and reusable control solutions. The retrigger feature offers flexibility in applications where a pulse needs to be restarted upon request.
