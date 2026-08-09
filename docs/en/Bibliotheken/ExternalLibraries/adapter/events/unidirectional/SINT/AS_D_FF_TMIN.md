# AS_D_FF_TMIN

![AS_D_FF_TMIN](./AS_D_FF_TMIN.svg)

* * * * * * * * * *
The function block **AS_D_FF_TMIN** implements a data-locking D flip-flop that takes over a data value supplied via an adapter upon the arrival of an event and outputs it via another adapter. Its special feature is a configurable minimum time (`Tmin`) between two consecutive take-over events. This suppresses excessively rapid event sequences, which can be used, for example, for debouncing or to enforce process constraints.

| Event | Type | Comment |
|----------|-------|-------------------------------------------|
| INIT | EInit | Initialization Request (reads `Tmin`) |
| Event | Type | Comment |
|----------|-------|-------------------------------------|
| INITO | EInit | Initialization Confirmation |
| Name | Type | Comment |
|------|------|---------------------------------------------------------------|
| Tmin | TIME | Minimum time between two consecutive CLK events |

This block has no explicit data outputs; output is exclusively via the **Q** adapter.

### **Daten‑Ausgänge**

### **Daten‑Eingänge**

### **Ereignis‑Ausgänge**

### **Ereignis‑Eingänge**

## Interface Structure

## Introduction

### **Adapters**

| Direction | Adapter | Type | Comment |
| Socket | I | adapter::types::unidirectional::AS | Input data (D1) and clock (E1) |
| Plug | Q | adapter::types::unidirectional::AS | Output data (D1) and event (E1) |

The adapters of type `AS` each provide one event input/output (E1) and one data input/output (D1).

## Functionality

After successful initialization (INIT with a valid `Tmin`), the block operates like a clocked D flip-flop with a time filter:

* An event at the adapter input **I.E1** is interpreted as a clock signal (CLK).
* The data value **I.D1** is adopted upon the arrival of I.E1, **provided the time interval to the last CLK event is at least `Tmin`**. Otherwise, the event is ignored.
* If the adoption is successful, the stored value is output at data output **Q.D1**, and an event **Q.E1** is triggered.

Time filtering is implemented by the internally used block `E_D_FF_ANY_TMIN`, which delays or discards the clock event if the minimum time is not met.

- **Adapter-based I/O**: Data and events are not exchanged as separate variables, but via unidirectional adapters (`AS`). This allows for modular connection with other blocks.
- **Parameterizable Minimum Time**: The time `Tmin` is set for initialization and cannot be changed during operation (another INIT call is required).
- **Event Suppression**: Clock events that occur too close together are silently ignored – no error message is generated.

The block does not have explicit state machines in the sense of a statechart. However, its behavior can be described in two phases:

1. **Initialization Phase**: After the INIT event, `Tmin` is set internally. Only then is the block ready to process CLK events.
2. **Operation Phase**: The block waits for CLK events. When one arrives, it checks whether the time lock (since the last CLK) has expired. If so, the data value is taken and output. If no, the event is discarded.
- **Digital Signal Debouncing**: A sensor delivers fast, bouncing signals; the minimum pulse width is set using `Tmin`.
- **Clock Synchronization in Time-Critical Systems**: Prevents data transfers faster than a predefined system clock threshold.
- **Rate Limiting for Communication Interfaces**: A new value is only accepted every `Tmin` seconds (e.g., for bus accesses).

| Function Block | Time Filtering | Additional Features |
|------------------|-----------------------------------|-------------------------------------------|
| AS_D_FF | No (immediate transfer) | Simple D flip-flop without time limit |
| AS_D_FF_TMIN (this one) | Yes, configurable via `Tmin` | Suppresses excessively fast clock sequences |
| AS_D_FF_TMAX | Yes, maximum time between clock cycles | Enforces regular takeovers |

The **AS_D_FF_TMIN** function block extends a simple D flip-flop by adding an adjustable minimum time between two takeover events. Thanks to its adapter interface and the clear separation of initialization and operation, it is particularly suitable for industrial control systems and discrete-time processing applications where excessively fast switching must be avoided.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion