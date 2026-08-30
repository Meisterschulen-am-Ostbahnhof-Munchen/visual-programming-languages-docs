# AULI_D_FF_TMIN

![AULI_D_FF_TMIN](./AULI_D_FF_TMIN.svg)

* * * * * * * * * *

## Introduction

The function block **AULI_D_FF_TMIN** implements a data latch (D flip-flop) with an adjustable minimum delay time between successive event outputs. It serves as a memory element for asynchronous event/data interfaces and ensures that a defined time interval elapses after a data transfer before another event is triggered. The block operates exclusively via adapter interfaces of type `AULI` (unidirectional) and is therefore particularly suitable for modular and distributed control architectures.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|--------|------------------------------------------------|
| INIT | EInit | Initialization request; synchronized with `Tmin` |

### **Event Outputs**

| Name | Type | Comment |
|-------|--------|-----------------------------------------------|
| INITO | EInit | Initialization confirmation |

### **Data Inputs**

| Name | Type | Comment |
|-------|-------|--------------------------------------------------------|
| Tmin | TIME | Minimum time between two event outputs (EO) at the output adapter |

### **Data Outputs**

None

### **Adapters**

| Name | Role | Type | Comment |
| ------ | ----------- | ---------- | -------------------------------------------- |
| I | Socket | AULI | Input: value to latch (event E1, data D1) |
| Q | Plug | AULI | Output: latching value (event E1, data D1) |

## Functionality

This function block encapsulates an internal `E_D_FF_ANY_TMIN` function block from the IEC 61499 library. It operates as an edge-triggered D flip-flop with the following sequence:

1. **Initialization** – An event at the `INIT` input resets the internal state and assigns the parameter `Tmin`. The output `INITO` acknowledges the initialization.
2. **Event-driven data transfer** –

- An event at the adapter input `I.E1` (as a clock signal) transfers the current data value `I.D1` to the internal flip-flop.
- Simultaneously, the minimum time `Tmin` is started.
- After `Tmin` has elapsed, an event is triggered at the adapter output `Q.E1`, and the transferred data value `Q.D1` is output.
1. **Lockout time** – While `Tmin` is still active, a subsequent input event is ignored or buffered (depending on the internal implementation). Only after the specified time has elapsed can the next value be processed.

## Technical Features

- **Unidirectional Adapters** – The function block exclusively uses the standardized adapter type `AULI` for events and data, enabling easy integration with other AULI-compatible function blocks.
- **Minimum Time (`Tmin`)** – Enforces a minimum pause between two consecutive output events. This prevents data loss or overloads in downstream components with limited processing speed.
- **No Dedicated Data Outputs** – Output data is provided exclusively via the plugin adapter `Q`, increasing modularity.

## State Overview

The internal function block `E_D_FF_ANY_TMIN` can be simplified to three states:

- **IDLE** – Waiting for a clock event at input `I.E1`.
- **LATCHED** – Data has been transferred and the `Tmin` timer is running. No further transfer is possible.
- **OUTPUT** – `Tmin` has expired; the output event is triggered and the block returns to the IDLE state.

Initialization (`INIT`) resets the function block to the IDLE state.

## Application Scenarios

- **Data synchronization** in time-critical control loops where a sensor value may only be sampled at a minimum interval.
- **Buffering** of asynchronous events to smooth out peak loads in the data stream.
- **Cascading** of flip-flops with different minimum times to implement time-staggered signal processing.
- **Interface between fast and slow components** (e.g., between fast logic and a slow actuator).

## Comparison with similar components

- **E_D_FF** – Simple D flip-flop without timing; takes data immediately on every clock edge. The `AULI_D_FF_TMIN` extends this with an adjustable minimum time.
- **E_D_FF_TMIN** – Same internal core, but with direct event/data interfaces instead of adapters. The adapter version `AULI_D_FF_TMIN` is designed for systems that rely on standardized, reusable interfaces.
- **E_D_FF_ANY_TMIN** (directly used) – Offers the same functionality but is designed for arbitrary data types. `AULI_D_FF_TMIN` is specifically tailored for the AULI adapter.

## Conclusion

The `AULI_D_FF_TMIN` is a specialized D flip-flop device for event/data adapter interfaces. Its integrated minimum time (`Tmin`) ensures reliable and predictable data transfer in time-critical environments. Its modular design and compliance with IEC 61499 Annex A make it a robust component for industrial control applications.
