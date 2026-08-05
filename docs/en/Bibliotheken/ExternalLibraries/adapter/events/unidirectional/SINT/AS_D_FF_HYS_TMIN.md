# AS_D_FF_HYS_TMIN

![AS_D_FF_HYS_TMIN](./AS_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Introduction
The function block **AS_D_FF_HYS_TMIN** implements a data-triggered flip-flop (D flip-flop) with hysteresis and a minimal time delay between successive events. It serves for stable, debounced signal transmission in time-critical control sequences. The block uses adapters for unidirectional communication, with an input signal received via socket **I** and the latching output signal provided via plug **Q**.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|-------|----------------------------------------------|

| INIT | EInit | Initialization request; sets hysteresis and minimum time |


### **Event Outputs**

| Name | Type | Comment |

|-------|-------|---------------------------------------------|

| INITO | EInit | Confirmation of completed initialization |

### **Data Inputs**

| Name | Type | Comment |

|------------|------|--------------------------------------------------|

| HYSTERESIS | SINT | Hysteresis band (integer value, e.g., 8 bits) |

| Tmin | TIME | Minimum time between two events (e.g., for debouncing) |

### **Data Outputs**

No direct data outputs – the output signal is provided via the **Q** adapter.

### **Adapters**

| Type | Name | Direction | Comment |

|-----|-------------|----------|---------------------------------------|

| AS | I (Socket) | Input | Unidirectional adapter for the signal to be latched (e.g., data + event line) |

| AS | Q (Plug) | Output | Unidirectional adapter for the latching output signal |

## Functionality
The function block operates internally with a predefined function block **E_D_FF_ANY_HYS_TMIN**. Upon the **INIT** event, the parameters **HYSTERESIS** and **Tmin** are transferred. The incoming event (via the **I** adapter, line **E1**) triggers the flip-flop clock, while the corresponding data value (via **I.D1**) is transferred. Output **Q.D1** is updated only if:

- the new data value differs from the currently stored value by at least the **hysteresis**, and

- at least the time **Tmin** has elapsed since the last event.

The output event (via **Q.E1**) signals a valid update. The module thus suppresses noise and prevents excessively rapid edge transitions.

## Technical Features
- **Adapter-Based Input/Output** – Signal transmission via adapters **I** and **Q** enables easy integration into complex adapter networks and increases reusability.

- **Hysteresis** – Prevents oscillations with fluctuating or noisy input signals by only registering significant changes.

- **Minimum Event Time (Tmin)** – Enforces a minimum pause between two triggers; serves as an additional debouncing mechanism.

- **Internal use of a proven flip-flop component** – The implementation delegates the core logic to **E_D_FF_ANY_HYS_TMIN**, which is designed for generic data types.

## State Overview
The component does not have any explicit, externally visible states. Internally, the flip-flop maintains a stored value (last valid output) that is only updated when the hysteresis and timing conditions are met. After initialization (INIT/INITO), the stored value is undefined until the first valid signal arrives.

## Application Scenarios

- **Debouncing of sensor signals** – e.g., limit switches or proximity sensors with mechanical bouncing.

- **Frequency limiting** – Preventing excessively fast switching operations in downstream actuators or communication interfaces.

- **Hysteresis-based threshold detection** – e.g., temperature or pressure control with a reset band.

- **Signal transmission in time-critical, interference-prone environments** (e.g., agricultural machinery controls).

## Comparison with similar components

- **Simple D flip-flop (e.g., E_D_FF)** – without hysteresis or time delay; accepts every clock signal without filtering.

- **Schmitt trigger component** – also with hysteresis, but usually without asynchronous event control and without an adjustable minimum time.

- **Delay component (e.g., E_DELAY)** – only delays the signal, but has no hysteresis or latch function.

**AS_D_FF_HYS_TMIN** combines latch function, hysteresis, and timing in a single component and is therefore specifically optimized for robust, time-controlled signal processing.


## Conclusion

The **AS_D_FF_HYS_TMIN** is a specialized function block for industrial controllers that require reliable, noise-insensitive signal transmission with adjustable dead time. The combination of a D flip-flop, hysteresis, and minimum time makes it a valuable tool for automation solutions, especially in environments with high levels of interference or tight timing requirements.