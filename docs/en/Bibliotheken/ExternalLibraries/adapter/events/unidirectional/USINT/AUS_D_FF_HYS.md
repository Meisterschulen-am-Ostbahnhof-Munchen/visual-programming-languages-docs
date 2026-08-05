# AUS_D_FF_HYS
![AUS_D_FF_HYS](./AUS_D_FF_HYS.svg)
* * * * * * * * * *
## Introduction
The function block `AUS_D_FF_HYS` implements a data latch (D flip-flop) with hysteresis (threshold band). It serves to receive an incoming data value on an edge-triggered basis and make it available at the output. The hysteresis ensures stable switching behavior even with noisy or fluctuating input signals. The block uses generic adapters (`AUS`) that enable unidirectional data transmission with event-driven control, making it usable with any data type.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment | With Parameter |

|----------|-------|--------------------------------|---------------|

| `INIT` | EInit | Set Hysteresis | `HYSTERESIS` |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|--------------------|

| `INITO` | EInit | Init Confirmation |

### **Data Inputs**

| Name | Type | Comment |

|--------------|-------|------------------|

| `HYSTERESIS` | USINT | Hysteresis band |

### **Data Outputs**

The FB has no direct data outputs. The latched value is provided via the adapter output `Q`.

### **Adapters**

| Name | Type | Direction | Comment |

|------|----------------------------------------------|-----------|----------------|

| `I` | `adapter::types::unidirectional::AUS` | Socket | Value to latch |

| `Q` | `adapter::types::unidirectional::AUS` | Plug | Latched value |

The adapters are unidirectional and each contains an event (`E1`) and a data value (`D1`). The input value and its acceptance event are received via `I`, and the output value and an acknowledgment event are sent via `Q`.

## Functionality

The function block encapsulates an internal block, `E_D_FF_ANY_HYS`, which implements the actual D flip-flop with hysteresis.

- **Initialization:** The hysteresis value (`HYSTERESIS`) is passed to the internal block via the event `INIT`. The initialization is acknowledged via the event `INITO`.

The FB encapsulates an internal block, `E_D_FF_ANY_HYS`, which implements the actual D flip-flop with hysteresis. - **Data Transfer:** An event on `I.E1` causes the internal component to take the current data value from `I.D1` and pass the latched value to `Q.D1`. Simultaneously, `Q.E1` is triggered.

- **Hysteresis Function:** The flip-flop output changes its state only when the input value exceeds an upper or lower threshold defined by the hysteresis value. This suppresses bounce or noise in the input signal (Schmitt trigger behavior).

The exact switching threshold depends on the data type used by the adapter (the `AUS` adapter supports any type). The hysteresis value (`USINT`) is internally scaled or interpreted to the corresponding numerical range.

## Technical Features
- **Generic Adapter:** The use of the unidirectional adapter `AUS` allows the use of a wide variety of data types (e.g., `INT`, `REAL`, `BOOL`) without requiring the function block itself to be typed. Type conversion is handled by the internal function block.
- **Hysteresis as USINT:** Hysteresis is specified as an unsigned 8-bit value. The specific interpretation (e.g., as an absolute difference or percentage) depends on the implementation and is defined in the internal function block.
- **Event Passthrough:** The INIT event is passed directly to the INITO event. This enables a simple initialization chain in the network.
- **Event Passthrough:** - **No visible state machine:** The function block (FB) does not have its own Execution Control Chart (ECC); the logic is implemented entirely by the internal FB.

## State Overview

Since the FB does not explicitly expose a state machine, its behavior is determined by the internal D flip-flop with hysteresis. This flip-flop has two stable output states:

- **State 0:** The output value corresponds to the logical "low" level (or the lower limit of the data range).
- **State 1:** The output value corresponds to the logical "high" level (or the upper limit).

State transitions occur only when the respective hysteresis thresholds are exceeded:

| Transition | Condition (Input Value) |

|----------|----------------------------------------------|

| 0 → 1 | Input exceeds upper threshold |

| 1 → 0 | Input falls below lower threshold |

The thresholds are offset by the hysteresis value relative to a mean or reference value (typically upper threshold = reference + hysteresis/2, lower threshold = reference - hysteresis/2).

## Application Scenarios
- **Sensor Debouncing:** A digital or analog sensor delivers fluctuating values (e.g., due to mechanical bouncing). The function block smooths the signal and provides a stable output.
- **Threshold Switch with Reset Delay:** Monitoring of a process value that triggers a signal when an upper limit is exceeded and is only reset when a lower limit is undershot.
- **Signal Conditioning in Building Automation:** Suppression of short interference pulses from temperature, brightness, or level sensors.
- **Hysteresis in Position Controllers:** Prevents rapid switching on and off of actuators near a setpoint limit.

## Comparison with Similar Function Blocks

| Function Block | Properties | Difference to `AUS_D_FF_HYS` |

----------|---------------|-------------------------------|

| Standard D flip-flop (`E_D_FF`) | Transfers data on clock edge, no hysteresis | No noise suppression; state changes on every edge. |

| Schmitt trigger (`E_D_FF_ANY_HYS`) | Flip-flop with hysteresis, but usually data-type specific | `AUS_D_FF_HYS` encapsulates the generic adapter and provides a uniform interface for arbitrary types. |

| SR flip-flop (`E_SR_FF`) | Set/reset function without clock | No edge-triggered data transfer; Hysteresis not directly integrated. |

## Conclusion

`AUS_D_FF_HYS` is a versatile function block for applications requiring robust, edge-triggered data acquisition with hysteresis. The use of generic adapters makes it independent of the specific data type and facilitates reuse in different contexts. Particularly in automation technology, signal processing, and sensor evaluation, it offers reliable signal conditioning through noise and bounce suppression. Initialization via `INIT` and direct event pass-through simplify integration into existing control networks.