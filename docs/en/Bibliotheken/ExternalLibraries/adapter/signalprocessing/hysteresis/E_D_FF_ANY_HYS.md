# E_D_FF_ANY_HYS

![E_D_FF_ANY_HYS](./E_D_FF_ANY_HYS.svg)

* * * * * * * * * *

## Introduction

The function block `E_D_FF_ANY_HYS` is an edge-triggered D flip-flop (data latch) for numeric data types with integrated hysteresis. It serves to store (latch) an input value and make it available at the output. However, an output update and the triggering of the output event only occur with a clock signal if the change in the input value compared to the current output value reaches or exceeds the defined hysteresis threshold.

## Interface Structure

### **Event Inputs**

* **CLK**: Clock Input. Upon the occurrence of this event, the system checks whether the input value `D` has changed by at least the value of `Q` compared to the current output value `HYSTERESIS`.

### **Event Outputs**

* **EO**: Event Output. Triggered when a clock event (`CLK`) results in an actual value change and update of the output `Q`.

### **Data Inputs**

* **D** (`ANY_NUM`): The current data value to be read.

* **HYSTERESIS** (`ANY_NUM`): The hysteresis band. Specifies the minimum difference that must exist between `D` and `Q` for the output to be updated.

### **Data Outputs**

* **Q** (`ANY_NUM`): The stored (latched) value.

### **Adapters**

* *No adapters available.*

## Functionality

The function block operates internally using an Execution Control Chart (ECC) and a simple assignment algorithm:

1. **Initialization**: On first startup, the block is in state `START`. The first `CLK` event leads directly to state `SET`. The algorithm `LATCH` is executed, which writes the current value of `D` to the output `Q`. Simultaneously, the output event `EO` is sent.


The process executes the algorithm `LATCH`, which writes the current value of `D` to the output `Q`.







... 2. **Hysteresis Check for Subsequent Events**: If the function block is in state `SET`, each subsequent `CLK` event will only lead to a re-execution of `SET` (and thus to an update of `Q` and the firing of `EO`) if the following condition is met:

$$\lvert D - Q \rvert \ge \text{HYSTERESIS}$$

In the ECC condition, this is mathematically implemented using the formula `GE(SUB(MAX(D, Q), MIN(D, Q)), HYSTERESIS)`. This corresponds to the absolute difference between the input value `D` and the currently stored value `Q`. 3. If the difference is less than the value of `HYSTERESIS`, the event is ignored, the output `Q` remains unchanged, and no `EO` event is triggered.

## Technical Features

* **Generic Data Type**: By using the data type `ANY_NUM` for the inputs and outputs, the function block is highly reusable and can be interconnected with various numeric data types (e.g., `INT`, `REAL`, `LREAL`).

* **Efficient Difference Calculation**: The difference calculation using `SUB(MAX(D, Q), MIN(D, Q))` ensures that a positive absolute value is always used for comparison with the hysteresis, regardless of whether the new value is greater or less than the old value.

## Status Overview



  [ START ] --( CLK )--> [ SET (Algorithmus: LATCH, Ausgang: EO) ]
                            |
                            +--( CLK [Differenz >= HYSTERESIS] )--> (erneuter Aufruf von SET)

* **START**: Waiting state before the first clock cycle.

* **SET**: State in which the input value is accepted and output. This state is called cyclically at each valid clock cycle (taking hysteresis into account).

## Application Scenarios

* **Noise Filtering for Analog Sensor Values**: Reduction of event floods in distributed systems. If a sensor (e.g., a temperature sensor) continuously delivers slightly fluctuating values, hysteresis prevents new control events from being constantly distributed throughout the system in response to minimal changes.

* **Limit Monitoring with Deadband**: Prevention of signal bounce when transmitting process values to visualizations (HMI) or databases.

## Comparison with Similar Function Blocks

* **E_D_FF**: The standard D flip-flop typically reacts at the Boolean level or unconditionally stores values at each clock cycle. `E_D_FF_ANY_HYS` additionally filters the values using the hysteresis condition.

* **Hysteresis blocks (e.g., with Boolean output)**: Typical hysteresis blocks compare a value with fixed thresholds and output a `BOOL` signal (e.g., threshold switch). `E_D_FF_ANY_HYS`, on the other hand, outputs the numerical value itself as soon as it has changed significantly.

## Conclusion

The `E_D_FF_ANY_HYS` is an extremely useful block for data- and event-driven signal processing. It combines the memory function of a D flip-flop with intelligent noise and change filtering for numerical signals, thus significantly contributing to performance optimization and reducing the event load in IEC 61499 applications.