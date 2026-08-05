# AUDI_D_FF_HYS
![AUDI_D_FF_HYS](./AUDI_D_FF_HYS.svg)
* * * * * * * * * *
## Introduction
The function block `AUDI_D_FF_HYS` implements a data-triggered flip-flop (D-latch) with a hysteresis function. It serves to accept an incoming data value upon an event, with the hysteresis enabling switching behavior with a defined deadband. The block encapsulates the logic of the internal block `E_D_FF_ANY_HYS` and provides the interfaces via two unidirectional adapters of type `AUDI`.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment | With Variable |

|----------|-------|-----------------|--------------|

| `INIT` | EInit | Set Hysteresis | `HYSTERESIS` |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|--------------------|

| `INITO` | EInit | Init Confirmation |

### **Data Inputs**

| Variable | Type | Comment |

|---------------|-------|------------------|

| `HYSTERESIS` | UDINT | Hysteresis band |

### **Data Outputs**

No direct data outputs – output data is provided via the `Q` adapter.

### **Adapters**

| Role | Name | Type (Adapter) | Comment |

|---------|------|-----------------------------|--------------------|

| Plug | `Q` | `adapter::types::unidirectional::AUDI` | Latched value |

| Socket | `I` | `adapter::types::unidirectional::AUDI` | Value to latch |

The adapter `AUDI` contains one event channel and one data channel:

- `I.E1` – Event that triggers the latch operation
- `I.D1` – Data value to be latched
- `Q.E1` – Confirmation event after successful latch
- `Q.D1` – The latched (and hysteresis-affected) data value

## Functionality
The module operates as a wrapper around the internal module `E_D_FF_ANY_HYS`. During the initialization event `INIT`, the hysteresis value (passed to `HYSTERESIS`) is transferred; The `INITO` event confirms initialization.

During operation, the current data value from `I.D1` is taken at each event on the adapter input `I.E1` and processed with the configured hysteresis. The result is output via the adapter output `Q.D1`, accompanied by an event `Q.E1`.

The hysteresis prevents constant switching with small signal changes: The output only changes its state when the input value leaves the hysteresis range.

## Technical Features
- The function block uses the generic implementation `E_D_FF_ANY_HYS` (from the library `logiBUS::signalprocessing::hysteresis`).
- The hysteresis is specified as `UDINT` (unsigned double integer) – the value range is therefore 0…4294967295.
- All input/output is handled exclusively via unidirectional adapters (`AUDI`), which promotes clear separation and reusability in complex networks.
- The INIT event is passed directly to `INITO` without intermediate processing – however, the hysteresis setting is configured before `INITO` (according to the data connection).

## State Overview
Since the FB is a pure function block network (no dedicated ECC), the state is determined by the internal block `E_D_FF_ANY_HYS`. Simplified:

- **Reset**: Output `Q.D1` is 0 or a defined initial value.
- **Set**: The output is set to 1 when the upper hysteresis threshold is exceeded.
- **Hold**: The output remains unchanged for values within the hysteresis range.
- **Reset**: The output is reset when the lower hysteresis threshold is undershot.

## Application Scenarios
- **Sensor Signal Debouncing**: Prevents chatter in mechanical switches or proximity sensors.
- **Threshold Switch with Feedback Suppression**: E.g., temperature control with adjustable deadband.
- **Digital Input Buffering**: Adopts a stable value upon a defined event (e.g., clock edge).

## Comparison with Similar Components
- **Standard D Flip-Flop (without hysteresis)**: Responds instantly to any change – no noise or bounce suppression.
- **RS Flip-Flop with hysteresis (e.g., `RS_FF_HYS`)**: Controls via separate set/reset events, while `AUDI_D_FF_HYS` uses a single data/event input.
- **Schmitt Trigger Component**: Functionally similar, but usually without latch/store behavior – here, the value is latched at an event and held until the next event.

## Conclusion

`AUDI_D_FF_HYS` combines the properties of a data-triggered flip-flop with adjustable hysteresis. By being encapsulated as an adapter module, it can be easily integrated into modular automation networks and offers a robust solution for signal processing with debouncing or threshold logic.