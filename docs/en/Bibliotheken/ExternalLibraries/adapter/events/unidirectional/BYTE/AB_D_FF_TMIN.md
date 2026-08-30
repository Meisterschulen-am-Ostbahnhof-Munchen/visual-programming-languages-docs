# AB_D_FF_TMIN

![AB_D_FF_TMIN](./AB_D_FF_TMIN.svg)

* * * * * * * * * *

## Introduction

The **AB_D_FF_TMIN** is an adapter-based function block (FB) according to IEC 61499 that implements the functionality of a data latch (D flip-flop) with a minimum time condition between successive output events. It serves to transfer a digital data value from an adapter socket (input) to an adapter plug (output), ensuring that the output events (EO) do not occur faster than permitted by a configured time parameter `Tmin`. The block abstracts the pure D flip-flop logic by using an internal flip-flop block and encapsulates data and events in adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|--------|--------|-------------------------------------|
| `INIT` | EInit | Initialization Request (sets the minimum time) |

### **Event Outputs**

| Name | Type | Comment |
|---------|--------|-------------------------------------|
| `INITO` | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |
|--------|------|------------------------------------------------|
| `Tmin` | TIME | Minimum time between two output events (EO) |

### **Data Outputs**

No direct data outputs; Data output is handled via the adapter plug `Q`.

### **Adapter**

| Direction | Name | Type | Comment |
| ---------- | ------ | ---------------------------------- | ------------------------------------------------------------- |
| Socket | `I` | adapter::types::unidirectional::AB | Input adapter: returns event `E1` and data value `D1` (the value to be latched) |
| Plug | `Q` | adapter::types::unidirectional::AB | Output adapter: outputs the latched data value `D1` and the event `E1` |

*Note:* The adapter `unidirectional::AB` defines an event `E1` and a data value `D1` (typically a Boolean or any generic type). The exact type definition of the adapter is outside this function block.

## Functionality

The function block works internally with the function block `E_D_FF_ANY_TMIN` (type `iec61499::events::E_D_FF_ANY_TMIN`), which implements the core logic of the D flip-flop with a minimal hold time between output events. The functionality is structured as follows:

1. **Initialization:**

An event at `INIT` passes the parameter `Tmin` (minimum time) to the inner function block. The function block acknowledges this with `INITO`.

1. **Data Acquisition and Transmission:**

- An event `E1` occurs at socket `I`, which carries the data value `D1` (the signal to be latched).

- This event is forwarded as `CLK` to the inner flip-flop, which simultaneously receives the data value `D1` from `I.D1`.

- The inner flip-flop stores the value `D1` and outputs it at its output `Q`.
- The latched value is passed out via plug `Q.D1`, and at the same time, the output event `EO` of the inner flip-flop is triggered.
- This `EO` is forwarded to `Q.E1`, so that the receiving adapter is informed of the update.

` 3. **Time Control:**

The internal function block `E_D_FF_ANY_TMIN` ensures that after an output event `EO`, no further output events can be generated for the duration of `Tmin` – regardless of how quickly input events arrive. If the time between two `E1` inputs exceeds the `Tmin` threshold, the value is immediately adopted; otherwise, it is blocked until the minimum time has elapsed.

## Technical Features

- **Adapter-Based Interface:**

Instead of individual event/data ports, the function block uses adapters that transport events and data as an encapsulated unit. This increases reusability and reduces the number of external connections.

- **Minimum Output Time (Tmin):**

The setting `Tmin` prevents output events from being triggered too quickly, which is useful in time-critical control systems (e.g., for debouncing or maintaining processing cycles).

- **Internal Use of a Specialized Function Block:**

The function block delegates the actual flip-flop logic to the system-internal function block `E_D_FF_ANY_TMIN`, which is responsible for correct timing. This keeps the external function block lean and error-free.

- **Typed Adapter:**

The adapter type `adapter::types::unidirectional::AB` is defined as unidirectional: data and events flow only in one direction (from the socket to the plug). This makes the function block strictly upward compatible.

## State Overview

The function block does not have an explicit visible state machine; The state is determined by the internal flip-flop and the timing:

- **State 0 (initial / not latched):** After INIT or a reset (not explicitly implemented), the state is undefined. The value `Q.D1` is only set after the first valid `E1` event at the socket.
- **State 1 (latched and active):** The internal flip-flop has a data value stored. After an output event, a lock state is maintained for the duration `Tmin`, during which incoming `E1` events are ignored or delayed. After the minimum time has elapsed, the function block is ready for the next takeover.
- **State 1 (latched and active):** (No SFC or ECC is defined in the XML; the state logic is entirely contained within the internal function block.)

## Application Scenarios

- **Signal Debouncing:**

If a sensor or button generates multiple rapid pulses (bounce), the function block (FB) can prevent multiple values from being passed on in quick succession by setting `Tmin` to, for example, 20 ms.

- **Cyclic Data Passing with Minimum Interval:**

In a distributed control system, a measured value should only be sent to a higher-level component at certain minimum intervals. The FB acts as a buffer that limits the update rate.

- **Reliable Transfer in Time-Critical Systems:**

When transferring a value from a fast to a slower clock range, the FB can be set to a suitable `Tmin`.Prevent data loss or noise.

## Comparison with similar components

| Component | Properties |
| ------------------- | ------------------------------------------------------------------------------- |
| **AB_D_FF** | Pure D flip-flop without a minimum output time – events are passed on immediately. |
| **E_D_FF_ANY** | Standard event data flip-flop without a time limit, but with discrete ports (no adapters). |
| **AB_D_FF_TMIN** | Combines adapter encapsulation with a configurable minimum time between output events. |
| **R_TRIG / F_TRIG** | Detects rising/falling edges – no functionality for latching a data value. |

The **AB_D_FF_TMIN** stands out due to the integration of timing control into adapter-based D flip-flop logic and is therefore particularly suitable for applications requiring both data latching and temporal decoupling.

## Conclusion

The **AB_D_FF_TMIN** is a compact, adapter-based function block that extends the basic functionality of a D flip-flop by adding the ability to maintain a minimal waiting time between output events. The encapsulated adapter interface and the internal use of a specialized flip-flop component ensure high reusability and a clear separation of logic and timing control. This component is particularly well-suited for industrial control applications where signal processing with temporal constraints is required.
