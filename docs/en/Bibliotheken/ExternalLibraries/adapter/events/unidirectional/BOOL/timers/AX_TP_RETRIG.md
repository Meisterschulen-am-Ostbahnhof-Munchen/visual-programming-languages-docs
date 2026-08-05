# AX_TP_RETRIG
![AX_TP_RETRIG](./AX_TP_RETRIG.svg)
* * * * * * * * * *
## Introduction
The **AX_TP_RETRIG** function block is a standardized timer function block (pulse) in a retriggerable configuration. It generates a pulse of duration **PT** on the adapter output **Q** as soon as the input signal **IN** receives a rising edge (event REQ). The pulse is restarted (retriggered) with each new REQ event. A reset via the event input **R** advances the pulse duration **PT** and resets the timer.
The function block is designed for use in IEC 61499-based automation systems and utilizes the AX adapter interface for efficient, unidirectional signal transmission.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| **R** | Reset – Sets the pulse time **PT** and immediately terminates a running pulse. |

### **Event Outputs**

No dedicated event outputs – output is provided via the **Q** adapter (event **E1**).

### **Data Inputs**

| Name | Type | Description |

|------|-------|--------------|

| **PT** | TIME | Pulse duration (pulse time). |

### **Data Outputs**

No dedicated data outputs – pulse status is output via the **Q** adapter (data value **D1**).

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| **IN** | `adapter::types::unidirectional::AX` | Socket | Input – Receives the start signal (event **E1**) and the logical value (**D1**). A rising edge on **E1** triggers the pulse. |

| **Q** | `adapter::types::unidirectional::AX` | Plug | Output – Outputs the pulse: As long as the pulse is active, **D1** = `TRUE`, otherwise it is FALSE. The event **E1** is sent with every state change. |

## Functionality

1. **Initial State** – **Q.D1** is `FALSE`, no pulse is active.

2. **Start** – Upon an event **IN.E1** (a rising edge interpreted as REQ), the function block initiates a pulse of duration **PT**. **Q.D1** is immediately set to `TRUE`, and the event **Q.E1** is sent.

3. **Retrigger** – While the pulse is still active, another **IN.E1** resets the timer, and the pulse restarts for the full duration **PT**. **Q.D1** remains `TRUE` for the entire duration of the pulse.

4. **Pulse End** – After **PT** has elapsed (without a new trigger), **Q.D1** is reset to `FALSE`, and **Q.E1** is sent again.

5. **Reset** – The **R** event immediately terminates a running pulse and sets **Q.D1** to `FALSE`. Simultaneously, **PT** is prepended with the current value at input **PT** (this can be used for a new pulse duration).

## Technical Features
- **Retriggerability** – Unlike simple timer blocks, a running pulse is not interrupted by a new start pulse, but rather extended (timer restart).
- **Adapter Interface** – Instead of individual event/data ports, the AX adapter interface is used, which enables a standardized, unidirectional connection. This simplifies integration in adapter-based architectures.
- **License** – The block is released under the **Eclipse Public License 2.0** (see copyright information).
- **Implementation** – Internally, the IEC 61499 standard function block **E_TP_RETRIG** is used, which is integrated via the network.

## State Overview

The function block goes through the following states (based on the internal timer function block):

| State | Description |

|---------|--------------|

| **IDLE** | No pulse active; **Q.D1** = `FALSE`. |

| **RUNNING** | Pulse active; **Q.D1** = `TRUE`. The timer runs for the duration **PT**. Upon retriggering, the timer is reset (remains in the RUNNING state). |

| **TIMEOUT** | Pulse terminated; transition back to IDLE. |

Note: The reset (event **R**) always immediately returns to the IDLE state.

## Application Scenarios
- **Control of output signals with fixed pulse duration** – e.g., controlling a relay that is switched for a defined time.
- **Clock generator with retriggering** – If a new start signal arrives during a pulse, the pulse duration should be extended (e.g., for a manual push button that is pressed for a longer time).
- **Safety interlocks** – An alarm or action should remain active for a minimum duration, even if the triggering state disappears briefly.
- **Time-controlled enables** – e.g., a machine movement that is executed for the duration **PT** after a start signal, but restarts upon a new start pulse.

## Comparison with similar function blocks

| Function block | Property |

|----------|-------------|

| **AX_TP_RETRIG** | Retriggerable pulse timer with AX adapter. |

**E_TP** (Standard IEC 61499) | Simple pulse timer, non-retriggerable – restarting during the pulse is ignored. |

**E_TP_RETRIG** | Retriggerable version without adapter (pure event/data interface). |

**E_DELAY** (Delay) | Delays a signal by a fixed time, but does not generate a pulse of fixed duration. |

The **AX_TP_RETRIG** combines retrigger functionality with a compact adapter interface and is therefore particularly suitable for modular, adapter-based systems.

## Conclusion

The **AX_TP_RETRIG** is a flexible and standardized timer function block for IEC 61499 applications. Its retrigger capability makes it ideal for situations where a pulse needs to be extended during repeated start commands. The use of the AX adapter interface simplifies integration with other adapter-based components and promotes a clean, modular system architecture. Thanks to the clear separation of event and data flows and adherence to the standard, the module is suitable for reliable use in industrial control systems.