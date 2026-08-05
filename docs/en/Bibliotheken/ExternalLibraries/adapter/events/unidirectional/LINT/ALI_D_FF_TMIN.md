# ALI_D_FF_TMIN
![ALI_D_FF_TMIN](./ALI_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_D_FF_TMIN** implements a data storage (D flip-flop) with an adapter-based input and output and a configurable minimum dwell time between output events. It serves to accept an incoming data value on a rising edge at the input and release it after a minimum time to avoid cyclical conditions or timing issues in communication.
## Interface Structure
### **Event Inputs**

| Event | Type | With Variables | Comment |
|----------|-----|----------------|------------|
| INIT | EInit | Tmin | Initialization request, sets the minimum dwell time |

### **Event Outputs**

| Event | Type | With Variables | Comment |
|----------|-----|---------------|-----------|
| INITO | EInit | – | Initialization Confirmation |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-------|-----------|
| Tmin | TIME | Minimum time between two output events (EO) |

### **Data Outputs**

No direct data outputs. The latched value is provided via the **Q-Adapter**.

### **Adapter**

| Label | Type | Direction | Comment |
### **Adapter** |-------------|-----|----------|-----------|
| I | ALI (unidirectional) | Socket (Input) | Value to be transferred |
| Q | ALI (unidirectional) | Plug (Output) | Stored value |

## Functionality
The **ALI_D_FF_TMIN** encapsulates an internal function block of type `E_D_FF_ANY_TMIN`. Its functionality:

- Upon an event at the input adapter **I.E1** (rising edge), the data value **I.D1** is transferred.
- However, the output event **EO** is only triggered if at least the time **Tmin** has elapsed since the last **EO**.
- Initialization (INIT) sets the internal timer and prepares the function block.

The function block operates asynchronously; timing is controlled via the internal function block.

## Technical Features
- The logic is completely outsourced to the internal function block `E_D_FF_ANY_TMIN`, which has its own state machine and timer.
- The **Tmin** time is set only once during INIT and remains valid for the entire lifetime.
- Adapters **I** (input) and **Q** (output) are unidirectional of type `ALI`; they transmit both events and data.
- The function block does not implement its own top-level behavior but delegates all functions.

## State Overview
Since the function block uses `E_D_FF_ANY_TMIN` internally, it implicitly has the following states:

1. **Initialized**: After INIT, ready for the first edge.

2. **Edge Received**: Value has been stored; the output will be sent after **Tmin**.

3. **Wait for Minimum Time**: No new EO (Event End) is possible until Tmin has expired.

4. **Ready**: After the waiting time has elapsed, the next EO can be triggered.

The exact state machine is located in the internal function block and is not shown here.

## Application Scenarios
- **Data Backup in Time-Controlled Bus Systems**: Buffering of values at a clock signal, which may only be passed on at defined intervals.
- **Signal Debouncing**: Prevents rapid switching on and off from resulting in numerous events at the logic level.
- **Sequential Processing with Minimum Interval**: Ensures that subsequent function blocks have sufficient processing time.

## Comparison with Similar Function Blocks

| Function Block | Difference |
|----------|-------------|
| `ALI_D_FF` (without TMIN) | No minimum time between output events, immediate forwarding on every edge. |
| `E_D_FF` (Standard-61499) | Direct event inputs and outputs, without adapters or timing. |
| `E_D_FF_ANY_TMIN` | Same functionality, but with dedicated data and event ports, not via adapters. |

The **ALI_D_FF_TMIN** extends the adapter interface with convenient encapsulation and adds timing control, which is lacking in simple flip-flops.

## Conclusion
The **ALI_D_FF_TMIN** is a useful component for applications that require delayed or timed data transmission via adapters. Its configurable minimum time between output events makes it particularly suitable for time-critical or debounced communication links. The internal implementation using a proven function block ensures robustness and reusability.
