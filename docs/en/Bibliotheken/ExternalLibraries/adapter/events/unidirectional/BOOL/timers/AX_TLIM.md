# AX_TLIM
![AX_TLIM](./AX_TLIM.svg)

* * * * * * * * * *
## Introduction
The **AX_TLIM** function block is a time-limiting timer according to IEC 61499-2. It monitors a Boolean input signal provided via a unidirectional **AX adapter**. As long as the signal is active (TRUE), the output remains active – but only for a predefined time. If the activation duration exceeds the limit, the output is reset (timeout). A separate event input allows the time limit to be preset without triggering a new execution.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|-------|--------|--------------------------------------------------------------|
| `EIPT` | Event | Resets the time limit `PT` (does not trigger execution) |

### **Event Outputs**

This function block does not have direct event outputs. Instead, the output event and value are provided via the **adapter `Q`** (see the Adapters section).

### **Data Inputs**

| Name | Type | Description |
|------|--------|-------------------------------------------|
| `PT` | `TIME` | Time limit (Preset Time) for the timer |

### **Data Outputs**

Direct data outputs are not available. The current timer status is output via the **adapter `Q`**.

### **Adapter**

| Name | Type | Direction | Description |
|------|-----------|----------|----------------------------------------------------------------------------|
| `IN` | `AX` | Socket | Input adapter: receives (via event `E1` and date `D1`) the Boolean value to be monitored |
| `Q` | `AX` | Plug | Output adapter: sends (via event `E1` and date `D1`) the timer state (`TRUE` = active, `FALSE` = inactive or timeout) |

> Note: The adapter type `AX` is a unidirectional standard adapter consisting of an event (`E1`) and a Boolean date (`D1`).

## Functionality

1. **Initial State** – The output variable `Q.D1` is `FALSE`; the timer is not running.

> Note: The adapter type `AX` is a standard unidirectional adapter consisting of an event (`E1`) and a Boolean date (`D1`).


1. **Initial State** – The output variable `Q.D1` is `FALSE`; the timer is not running.

2. **Activation** – As soon as the input adapter `IN` delivers an event (`E1`) with the date `TRUE`, `Q.D1` is immediately set to `TRUE`, and an internal timer is started.

3. **Time Monitoring** – The timer counts the time that `IN.D1` remains on `TRUE`. The timer uses the value last set via `EIPT`, `PT`.

- *Case A:* If `IN.D1` becomes `FALSE` before `PT` expires, then `Q.D1` is immediately set to `FALSE`.
- *Case B:* If `IN.D1` remains on `TRUE` longer than `PT`, then after `PT` expires, `Q.D1` is set to `FALSE` (timeout).

*Case B:* If `IN.D1` remains on `TRUE` for longer than `PT` expires, then `Q.D1` is set to `FALSE` (timeout). 4. **Event Output** – Every change to `Q.D1` is signaled via the output adapter `Q.E1`.

5. **Default** – The event `EIPT` resets the time limit `PT` without affecting the current timer execution. Only the next activation of the timer (by `IN.E1` with `TRUE`) uses the new value.

## Technical Features
- The function block is implemented as a **composite FB**; internally, it uses the standard FB `E_TLIM` (from `iec61499::events::timers`). The underlying logic is identical, but the interface is provided via unidirectional **AX adapters**.
- The use of an adapter socket (`IN`) and an adapter plug (`Q`) enables a clean separation of event and data communication and simplifies integration with other function blocks using compatible adapters.
- The timer is triggered **on an edge**: Only a rising edge on `IN.D1` starts a new timer cycle. A subsequent event on `IN.E1` with `TRUE` during a running timer does not reset the timer (unless the value briefly goes to `FALSE` and then back to `TRUE`).

## State Overview

The function block cycles through the following logical states (not explicitly represented as a state machine in the XML):

| State | Condition `IN.D1` | Output `Q.D1` | Timer running | Description |
-----------------|-------------------|----------------|-------------|-------------------------------------------------------------|
| **Inactive** | `FALSE` | `FALSE` | no | Waiting for activation |
| **Active** | `TRUE` | `TRUE` | yes | Timer counting, output active |
| **Timeout** | `TRUE` | `FALSE` | no | Timeout, timer expired, output inactive |
| **Return** | `FALSE` | `FALSE` | no | Input reverts before timeout, output immediately inactive |

A switch from **Active** to **Timeout** occurs when the remaining timer time reaches zero. A switch from **Active** to **Revert** occurs when `IN.D1` changes to `FALSE` before the timer expires.

## Application Scenarios
- **Actuator Monitoring** – e.g., checking whether a valve remains open longer than permitted.
- **Safety Functions** – Switching off a signal after a maximum activation time.
- **Time-Based Plausibility Check** – Detection of a stuck sensor that continuously reports `TRUE`.
- **Control of blinking or pulse sequences** – the timer can be used as a simple monostable multivibrator with a timeout.

## Comparison with similar function blocks

| Function block | Description | Difference to AX_TLIM |
|-----------|-------------------------------------------------------------------------------|---------------------------------------------------------------------|
| `E_TLIM` | Standard timer (IEC 61499-2), direct event and data interfaces | AX_TLIM encapsulates `E_TLIM` and provides an adapter-based interface (`AX`) that is easier to integrate into certain architectures. |
| `E_DELAY` | Delay function block (response delay, fallback delay) | `E_DELAY`Delays signal changes, while AX_TLIM enforces a maximum activation duration. |
| `E_SR` | Set-Reset Flip-Flop | AX_TLIM does not reset the output as long as the input is active (except via timeout). `E_SR` responds to separate set/reset events. |

## Conclusion

The **AX_TLIM** function block offers a compact, adapter-based solution for time-limited monitoring of Boolean signals. By encapsulating the standard `E_TLIM` and using unidirectional AX adapters, it can be flexibly integrated into IEC 61499 systems, especially when communication paths need to be encapsulated via adapters. Its operation is intuitive: As long as the input is active, the output remains active – for a maximum of the configurable time `PT`. This makes the component ideal for safety and monitoring tasks in automation technology.
