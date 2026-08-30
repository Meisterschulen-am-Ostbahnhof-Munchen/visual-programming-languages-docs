# AUDI_D_FF_TMIN

![AUDI_D_FF_TMIN](./AUDI_D_FF_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **AUDI_D_FF_TMIN** implements a D flip-flop (data latch) with a minimum lock time between successive output events. It serves to receive a value received via one adapter and output it via a second adapter, with the propagation of the output event being time-controlled.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|-------|-------|---------------------------------------------|
| INIT | EInit | Initializes the function block; sets the minimum time between two EO events. |

### **Event Outputs**

| Name | Type | Description |
|-------|-------|---------------------------------------------|
| INITO | EInit | Confirmation of completed initialization. |

### **Data Inputs**

| Name | Type | Description |
|------|------|----------------------------------------------------------------|
| Tmin | TIME | Minimum time that must elapse between two consecutive EO events. |

### **Data Outputs**

No direct data outputs; the latched value is provided via the **Q** adapter.

### **Adapters**

| Name | Type (unidirectional) | Role |
| ------ | ---------------------- | -------------------------------------------------- |
| I | AUDI | Input adapter: provides the value to be latched (via D1) and the latch event (via E1). |
| Q | AUDI | Output adapter: outputs the latched value (via D1) and an output event (via E1). |

## Functionality

The function block internally contains an instance of the function block `E_D_FF_ANY_TMIN`, which implements the core logic of a time-limited D flip-flop.

1. **Initialization**

An INIT event sets the minimum delay time `Tmin` (via the With association) and is passed to the internal instance. After successful initialization, INITO is output.

1. **Latch Operation**

An event at the input `I.E1` (of the adapter) is passed as a clock signal (CLK) to the internal flip-flop. Simultaneously, the value from `I.D1` (D input) is taken. The latched value appears at output `Q.D1`, and the corresponding output event appears at the adapter's event output (`Q.E1`).

1. **Minimum Wait Time**

The internal function block enforces a minimum time interval between successive `Q.E1` events. If the time defined at `Tmin` is exceeded, the next output event is only triggered after this time interval has elapsed. This prevents overloads on the output side.

## Technical Features

- **Adapter-Based Communication**

The function block uses two unidirectional AUDI adapters for input and output. This achieves loose coupling between data flow and event control.

- **Interval Control**

The minimum time between two EO events is configured via the parameter `Tmin`. The internal function block `E_D_FF_ANY_TMIN` ensures that this condition is met by delaying incoming clock events as needed.

- **No Explicit Data Outputs**

The latched value is provided exclusively via the adapter `Q`. This simplifies the connection to subsequent function blocks with the same adapter type.

## State Overview

The function block has no externally visible states, as the state logic is encapsulated within the internal function block. The internal logic cycles through at least the following internal states:

- **IDLE**: Waiting for INIT or a clock event (I.E1).
- **LATCH**: Value is being stored; waiting time is being checked.
- **OUTPUT**: Outputs Q.E1 and Q.D1 when the minimum time since the last output event has elapsed.

An INIT event resets all states.

## Application Scenarios

- **Time-Controlled Data Buffer**

Accepts measured values or control signals at fixed time intervals, e.g., to decouple a fast sensor from a slow actuator.

- **Event Filter**

Suppresses events that follow each other too quickly (application-level debouncing).

- **Synchronization**

Used as a basic building block for implementing delay elements or clock locks in IEC 61499 applications.

## Comparison with Similar Building Blocks

| Building Block | Special Feature |
--------------------- | ------------------------------------------------------------------- |
| **AUDI_D_FF** | Pure D flip-flop without a time limit between EO events. |
| **E_D_FF_ANY** | Standard D flip-flop with universal data types, but without a minimum delay. |
| **AUDI_D_FF_TMIN** | Like AUDI_D_FF, but with the additional `Tmin` parameter to control the minimum pause between output events. |

## Conclusion

The **AUDI_D_FF_TMIN** is a specialized D flip-flop component that limits the output of events and values. Its adapter interface allows it to be seamlessly integrated into unidirectional communication structures. The combination of a latch function and adjustable lock time makes it a valuable tool for event-driven real-time processing in automation systems.
