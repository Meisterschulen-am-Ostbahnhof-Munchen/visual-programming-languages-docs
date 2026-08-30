# ADI_D_FF_TMIN

![ADI_D_FF_TMIN](./ADI_D_FF_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **ADI_D_FF_TMIN** implements a data latch (D flip-flop) with a configurable minimum dwell time between two consecutive transfer events. It serves to save a data value at a specific event time and only update it again when a predefined time interval (Tmin) has elapsed since the last transfer.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| INIT | EInit | Initialization Request; Passes the parameter Tmin |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| Tmin | TIME | Minimum time between two events at input I.E1 |

### **Data Outputs**

No direct data outputs – the latched value is provided via the adapter output Q.

### **Adapter**

| Direction | Name | Type | Comment |
| ---------- | ------ | ----- | ----------- |
| Socket (Input) | I | adapter::types::unidirectional::ADI | Value and event to latch |
| Plug (Output) | Q | adapter::types::unidirectional::ADI | Latched Value and Associated Output Event |

## Functionality

The function block receives an event (I.E1) along with a data value (I.D1) via the adapter socket **I**. After this event, the value is transferred and output as Q.D1 at the adapter plug **Q**; simultaneously, an event is sent to Q.E1.

However, at least the time specified in **Tmin** must elapse between two consecutive transfers. As long as this minimum period has not expired, an incoming event at I.E1 is ignored (the value remains unchanged).

The INIT input sets the parameter Tmin and confirms this via INITO, without affecting the flip-flop itself.

The function block (FB) internally uses the block `iec61499::events::E_D_FF_ANY_TMIN`, which encapsulates the actual logic (a D flip-flop with time control).

## Technical Features

- **Adapter-based interface:** Instead of directly connected event and data ports, the inputs and outputs are implemented via unidirectional adapters (type `ADI`). This simplifies the reuse and separation of control and data flows.
- **Minimum time guarantee:** The Tmin time is measured from the moment of the last valid output event. If an input event occurs too early, the output remains unchanged – the old value is retained.
- **Initialization required:** The function block must first be initialized with a Tmin value via INIT before it responds to incoming adapter events.

## State Overview

The function block (FB) has implicit state logic, which is represented by the internal `E_D_FF_ANY_TMIN`:

- **Idle:** Waiting for the first valid event at I.E1 after initialization.
- **Latched:** A value has been transferred; the timer for Tmin is running. New events at I.E1 are ignored until Tmin has expired.
- **Ready:** Tmin has expired; the function block is ready for the next transfer.

The state transitions are controlled by the events at I.E1 and the internal timer. Initialization returns the function block to the idle state.

## Application Scenarios

- **Clock Decoupling in Industrial Applications:** Ensuring that data is transferred only at defined minimum intervals (e.g., for sensor queries with a fixed interval).
- **Event Debouncing:** Prevents duplicate evaluations for closely spaced events (e.g., push-button or switching signals with bounce time).
- **Data Storage in Safety-Critical Systems:** Once latched, values remain valid until the minimum time has elapsed – protecting against noise or transient disturbances.

## Comparison with Similar Function Blocks

- **Standard D Flip-Flop (without Tmin):** A simple D flip-flop, such as `E_D_FF`, immediately adopts any value upon each event. This function block extends this functionality with a time lock.
- **E_D_FF_ANY_TMIN:** This is the direct internal base function block. `ADI_D_FF_TMIN` encapsulates its functionality and offers an adapter interface instead of separate event/data ports – this increases flexibility when connecting to other adapter-based components.

## Conclusion

The `ADI_D_FF_TMIN` is a useful functional block for applications requiring reliable data acquisition with adjustable time decoupling. The use of adapters makes it particularly suitable for modular, adapter-based architectures according to IEC 61499. The minimum time enhances the overall system stability in environments with sporadic or bouncy events.
