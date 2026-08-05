# AUI_D_FF_HYS
![AUI_D_FF_HYS](./AUI_D_FF_HYS.svg)

* * * * * * * * * *
## Introduction
The function block `AUI_D_FF_HYS` implements a data latch (D flip-flop) with a hysteresis function. It serves to reliably acquire an analog or digital value, suppressing small fluctuations (noise) through an adjustable hysteresis band. The block is designed for use in automation technology and complies with the IEC 61499-1 Annex A standard.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|-------|--------------------------|

| INIT | EInit | Sets the hysteresis width |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|--------------------------|

| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Data | Type | Comment |

|--------------|------|----------------------------------|

| HYSTERESIS | UINT | Hysteresis Band Width |

### **Data Outputs**

No dedicated data outputs; the latched value is provided via the `Q` adapter.

### **Adapters**

| Name | Type | Direction | Comment |

|------|--------------------------------------|----------|--------------------------|
| I | adapter::types::unidirectional::AUI | Socket | Latch Value |

| Q | adapter::types::unidirectional::AUI | Plug | Latched Value |

The adapters `I` and `Q` of type `AUI` (unidirectional) transport both data (e.g., `D1`) and associated events (e.g., `E1`).

## Functionality

The component internally contains the instance `E_D_FF_ANY_HYS` (type `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS`), which performs the actual latch with hysteresis. The signal flows are as follows:

- The event `I.E1` (from adapter `I`) is passed directly to the internal component as a clock signal (`CLK`).
- The data value `I.D1` is passed to the internal flip-flop as an input `D`.
- The hysteresis band is set via the parameter `HYSTERESIS`.
- The output of the internal component (`Q`) is routed to adapter `Q.D1`, and the output event (`EO`) is routed to `Q.E1`.
- The output of the internal component (`Q`) is routed to adapter `Q.D1`, and the output event (`EO`) is routed to adapter `Q.E1`.
- The data value `I.D1` is passed to the internal flip-flop as an input `D`.
- The output of the internal component (`Q`) is routed to adapter `EO`. - The event `INIT` is immediately passed through to `INITO` (no delay).

The hysteresis ensures that the latched value only jumps to the new input value if it differs from the currently stored value by more than the defined threshold (`HYSTERESIS`). This suppresses edge noise and unstable signal transitions.

## Technical Features
- The function block is a pure **composite function block** that delegates all logic to an internal instance.
- The hysteresis is passed as an unsigned integer (`UINT`).
- The adapters are unidirectional – data and events flow in only one direction (socket → plug).
- The function block does not contain its own state machine; the state is maintained in the internal flip-flop.

## State Overview

Since `AUI_D_FF_HYS` does not have its own ECC (Execution Control Chart), its behavior is determined solely by the internal component `E_D_FF_ANY_HYS`. A typical D flip-flop with hysteresis has two stable output states, which are switched by the applied clock signal and the hysteresis condition. A detailed state description can be found in the documentation for the internal component.

## Application Scenarios
- **Sensor Data Debouncing**: Values from analog or digital sensors are stabilized with an adjustable hysteresis.
- **Threshold Switch**: The component can be used as a Schmitt trigger if an input value only changes its output above a defined upper threshold and below a defined lower threshold (determined by the hysteresis).
- **Signal Conditioning in Process Automation**: Noisy signals are smoothed before being passed to subsequent logic components.

## Comparison with Similar Components
- **E_D_FF**: A pure D flip-flop without hysteresis. It adopts the input value on every clock edge, regardless of minimal fluctuations. `AUI_D_FF_HYS` offers improved noise immunity.
- **E_RS_BISTABLE**: A set-reset flip-flop without hysteresis and limited to binary states. `AUI_D_FF_HYS` operates with analog/integer values and allows for a dynamic threshold.
- **E_SPLIT_HYS**: A component that splits a signal with a fixed hysteresis. In contrast, the hysteresis in `AUI_D_FF_HYS` can be changed at runtime via the input `HYSTERESIS`.

## Conclusion

The `AUI_D_FF_HYS` is a useful component for stable latching of values in environments with noise or signal instability. It combines the functionality of a D flip-flop with an adjustable hysteresis threshold and can be easily integrated into modular IEC 61499 controllers using adapters.
