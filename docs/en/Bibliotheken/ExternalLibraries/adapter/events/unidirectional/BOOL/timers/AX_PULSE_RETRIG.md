# AX_PULSE_RETRIG
![AX_PULSE_RETRIG](./AX_PULSE_RETRIG.svg)

* * * * * * * * * *
## Introduction
The **AX_PULSE_RETRIG** function block is a retriggerable pulse shaper with an AX adapter interface. It generates a pulse with a predefined duration (PT) at its output. A restart command within the pulse duration resets the timer and extends the pulse. This block is typically used to generate precisely timed, extendable output signals in automation systems.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| **REQ** | EVENT | Service request to start or restart the timer (connected to PT) |
| **R** | EVENT | Reset Timer (End Pulse Immediately) |

### **Event Outputs**

This function block does not have direct event outputs. Output signals are provided via the Q adapter.

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| **PT** | TIME | Pulse Duration (Pulse Time) |

### **Data Outputs**

This function block does not have direct data outputs. Output data is provided via the Q adapter.

### **Adapter**

| Name | Type | Description |
|------|-----|---------------|
| **Q** | `adapter::types::unidirectional::AX` | Adapter interface that outputs the pulse status (event and data) |

## Functionality
- The function block internally encapsulates the standard function block `E_PULSE_RETRIG` (according to IEC 61499).
- A **REQ** event starts the timer: Output Q (via adapter) becomes active and the pulse begins.
- If another **REQ** event occurs during the pulse duration, the timer is reset and the pulse duration starts again (retrigger function).
- An **R** event immediately interrupts the pulse – output Q becomes inactive.
- Adapter Q transmits the current pulse state as an event (via `Q.E1`) and as a data value (via `Q.D1`).

## Technical Features
- Uses the standardized `E_PULSE_RETRIG` function block as an internal implementation.
- Output is exclusively via an AX adapter, which provides both an event signal (upon state change) and the binary pulse state (type BOOL).
- A subsequent trigger restarts the timing – ideal for pushbuttons with a delay or pulse-width modulated signals.
- The pulse duration PT can be changed during propagation, but this change only takes effect upon the next REQ.

## State Overview

This function block maps the states of the internal `E_PULSE_RETRIG`:

| State | Description |
|---------|--------------|
| **IDLE** | No pulse active; output Q = FALSE |
| **PULSE** | Pulse running; output Q = TRUE; timer running. A REQ event returns to PULSE with a new timer start. |

- Transition IDLE → PULSE via REQ.
- Transition PULSE → IDLE by expiration of the PT time or by Reset R.

## Application Scenarios
- **Extendable Switch-On Pulses**: If a sensor triggers multiple times within the pulse duration, the output should remain permanently active (e.g., for level monitoring).
- **Clock Generator with Retriggerable Pulse Width**: Control of valves or lamps that are switched on again for a fixed time upon repeated request.
- **Safety Functions**: Monitoring of machines where a renewed start command resets the downtime.

## Comparison with Similar Function Blocks

| Function Block | Property |
|----------|-------------|
| **E_PULSE** | Simple pulse without retrigger – one-time timer start, no restart upon subsequent request. |
| **AX_PULSE_RETRIG** | Retriggerable version with AX adapter (event + data). |
**TON / TOF** | Delay blocks (turn-on delay / turn-off delay) – no pulse shaper. |

The AX_PULSE_RETRIG thus offers the flexibility of a retriggerable pulse with a standardized adapter interface for easy integration into larger function block networks.

## Conclusion

The **AX_PULSE_RETRIG** is a compact, high-performance function block for generating retriggerable pulses. Thanks to the AX adapter interface, it can be seamlessly integrated with other function blocks and is particularly suitable for applications where an output signal needs to be extended for repeated requests. The use of the established `E_PULSE_RETRIG` function block ensures standards-compliant and reliable timing behavior.
