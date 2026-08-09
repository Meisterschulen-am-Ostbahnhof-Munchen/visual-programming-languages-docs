# ALI_D_FF_HYS

![ALI_D_FF_HYS](./ALI_D_FF_HYS.svg)

* * * * * * * * * *
## Introduction

The **ALI_D_FF_HYS** function block implements a data latch (D flip-flop) with a hysteresis function. It serves for the stable and debounced transmission of a binary signal: An incoming data signal is received and output on a rising clock edge, with configurable hysteresis preventing small signal changes (noise) from causing unwanted output changes. The component is specifically designed for use with the unidirectional **ALI** adapter structure in IEC 61499 environments.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|-----------|--------|-------------------------------------------|
| `INIT` | EInit | Sets the hysteresis value for the switching threshold. |

### **Event Outputs**

| Event | Type | Comment |
|-----------|--------|------------------------------------------|
| `INITO` | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Variable | Type | Comment |
|---------------|------|-----------------------------------------------|
| `HYSTERESIS` | LINT | Hysteresis bandwidth (e.g., as an integer) |

### **Data Outputs**

No direct data outputs – output is via the adapter `Q`.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|--------------------------------------------|-----------------------------|
| Socket | `I` | `adapter::types::unidirectional::ALI` | Input value (data + clock) |
| Plug | `Q` | `adapter::types::unidirectional::ALI` | Output value (latched value) |

The adapter `I` provides two signals:

- **`I.E1`** – Clock signal (event)
- **`I.D1`** – Data input (e.g., BOOL or numeric)

The adapter `Q` provides the latched value as **`Q.D1`**.

## Functionality

The function block works internally with another function block **E_D_FF_ANY_HYS** (from the library `logiBUS::signalprocessing::hysteresis`), which implements the core logic. Overview of how it works:

1. **Initialization**

When the event `INIT` arrives, the value of `HYSTERESIS` is passed to the inner component, and the event is immediately acknowledged as `INITO`.

2. **Data Processing**

The event and data connections are directly connected between the adapters and the internal module:

- `I.E1` → **CLK** (Clock signal)
- `I.D1` → **D** (Input data)
- **Q** → `Q.D1` (Lagged output signal)
3. **Hysteresis Behavior**

At each clock cycle (`CLK`), the current data value `D` is evaluated. If `D` lies within the hysteresis band around the current output value `Q`, the output remains unchanged. If `D` exceeds the upper or lower threshold, the new value is adopted. This suppresses interference and ensures a clean, debounced signal.

## Technical Features

- **Pure Adapter Communication**: The function block uses only unidirectional adapters (`ALI`) for event and data transmission. This makes it easy to integrate into modular, adapter-based architectures.
- **Indirect Hysteresis Implementation**: Hysteresis is not implemented directly in the function block body, but rather through the internal block `E_D_FF_ANY_HYS`. This allows for flexible reuse of the logic.
- **Immediate INIT Acknowledgement**: The `INIT` event is acknowledged immediately via a direct connection (`INIT → INITO`) without waiting for the hysteresis logic.
- **Hysteresis Parameter Type**: `HYSTERESIS` is defined as `LINT`, thus allowing large integer values.

## State Overview

The function block itself has no visible states, as all state logic is encapsulated within the internal function block. Behavior of the D flip-flop with hysteresis:

- **Idle State**: Output values remain stable as long as no clock signal is applied.
- **Clock Edge (Rising)**:
- If D > Q + HYSTERESIS → Q = D (Set)
- If D < Q - HYSTERESIS → Q = D (Reset)
- Otherwise → Q remains unchanged (hysteresis range)

## Application Scenarios

Typical applications for this function block include:

- **Debouncing of switch signals** in automation technology (e.g., limit switches, proximity sensors).
- **Signal conditioning in harsh environments** (agricultural technology, mechanical engineering) – the hysteresis prevents oscillations caused by vibrations or noise.
- **Basic building block for more complex logic** with adapter-based data transmission, e.g., as an input stage of a state machine.

## Comparison with Similar Function Blocks

| Function Block | Feature |
|------------------------|------------------------------------------------------|
| **ALI_D_FF** (without hysteresis) | Simple D flip-flop without noise suppression |
**ALI_D_FF_HYS** (this one) | D flip-flop with configurable hysteresis for noise filtering |
Schmitt trigger function block | Similar function, but often with fixed thresholds |
**E_D_FF_ANY_HYS** | Internal logic, generic type (no adapter format) |

The advantage of **ALI_D_FF_HYS** lies in its direct adapter connection, enabling seamless integration into existing IEC 61499 adapter networks.

## Conclusion

The **ALI_D_FF_HYS** function block offers a proven combination of a D flip-flop and adjustable hysteresis, packaged in a standards-compliant IEC 61499 adapter interface. It is particularly suitable for applications where signals must be processed reliably under real-world conditions (noise, bounce). The clear separation of initialization and data processing, as well as the use of a proven sub-component, makes it robust, maintainable and flexible in its application.
