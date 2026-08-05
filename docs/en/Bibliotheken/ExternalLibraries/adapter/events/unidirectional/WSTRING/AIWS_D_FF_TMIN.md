# AIWS_D_FF_TMIN

![AIWS_D_FF_TMIN](./AIWS_D_FF_TMIN.svg)

* * * * * * * * * *
## Introduction
The function block **AIWS_D_FF_TMIN** implements a data latch (D flip-flop) with a minimum inter-disposal time between two consecutive output events. It is accessed via adapter interfaces (type: AIWS, unidirectional) that receive a value and output it as a latched value. Control is achieved via the input adapter's event (CLK edge), with output occurring only after a configurable dead time (Tmin) has elapsed.

## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|-----|----------|

| INIT | EInit | Initialization Request (with Tmin parameter) |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|----------|

| INITO | EInit | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|----------|

| Tmin | TIME | Minimum time between two output events (inter-disposal time) |

### **Data Outputs**

No dedicated data outputs – the latched value is provided exclusively via the **Q** adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|----------|

| Socket (Input) | I | adapter::types::unidirectional::AIWS | Value to be latched |

| Plug (Output) | Q | adapter::types::unidirectional::AIWS | Latched Value |

## Functionality
The function block internally uses the block `E_D_FF_ANY_TMIN` from the IEC 61499 library. The process is as follows:

1. At **INIT**, the minimum time `Tmin` is used, and the block is initialized (`INITO` confirms the successful start).

2. Each incoming event from adapter `I.E1` is interpreted as a clock edge (CLK).

3. The data value from adapter `I.D1` is transferred to the internal flip-flop on each CLK edge.

4. The latched value is provided on the output adapter `Q.D1`.

5. However, the corresponding event `Q.E1` is only sent after the time `Tmin` has elapsed since the last EO event (inter-disposal time). This limits the output rate.

The connection in the FB network ensures that events and data are correctly forwarded between the adapter `I`, the internal FB, and the adapter `Q`.

## Technical Features

- **Adapter-Based Input/Output:** The function block uses only adapters of type `AIWS` (unidirectional) for signal processing. This allows for loose coupling and reuse of the interfaces.

- **Internal use of `E_D_FF_ANY_TMIN`:** The actual latch and timer logic is implemented by a specialized function block that already ensures a minimum time between two EO events.

- **Initialization required:** The function block must be initialized with `INIT` before its first use. This sets `Tmin`.

## State overview
The function block essentially has two operating modes:

- **Initialization phase:** After receiving `INIT`, the internal timer and the flip-flop are reset. Upon completion, `INITO` is sent.

- **Normal operation:** After initialization, the function block waits for CLK events (`I.E1`). The data value is latched at each CLK (Current Control Point). An EO (Endpoint Output) event (`Q.E1`) is only triggered if the time elapsed since the last EO is **≥ Tmin**. If this condition is not met, the EO is delayed.

A complete state machine is implemented in the internal FB (Function Block); the block described here transparently represents this.

## Application Scenarios

- **Sensor Value Acquisition with Minimum Repetition Rate:** In automation, an analog or digital measured value should be passed on to a downstream controller at defined minimum intervals to avoid overload or unwanted switching cycles.

- **Edge Debouncing:** The latch can be used to keep an input value stable while the output is debounced by `Tmin`.

- **Time-controlled data buffer:** In communication protocols where data packets must be sent with a minimal pause.

## Comparison with similar function blocks

- **Standard D flip-flop (e.g., `E_D_FF`):** A standard D flip-flop accepts the input on every CLK edge and immediately outputs an event. It lacks a time limit on the output rate.

- **`AIWS_D_FF_TMIN`:** Extends the simple D flip-flop with a configurable minimum time between output events. This makes it particularly suitable for time-critical and rate-limited applications.

- **Timer-based latch function blocks (e.g., `E_D_FF_ANY_TMIN`):** The internal function block used here is the actual implementation; `AIWS_D_FF_TMIN` encapsulates this in an adapter-based interface, thus facilitating integration into an IEC 61499 architecture.

## Conclusion
The `AIWS_D_FF_TMIN` function block combines the function of a data latch with a programmable minimum output delay. Thanks to its adapter-based interface definition, it can be flexibly deployed in distributed automation systems. It offers a simple and robust solution, particularly for applications where signal changes must occur only at specific time intervals.