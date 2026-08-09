# INTEGRAL

<img width="1755" height="158" alt="image" src="https://github.com/user-attachments/assets/4eac3645-d857-4c04-9bc3-7692be451a96" />
* * * * * * * * * *
## Introduction

The function block `INTEGRAL` approximates the time integral of an input signal. The integration is performed by summing partial areas that result from the product of the input value and the time elapsed since the last call. This block is useful for applications where cumulative values such as energy consumed, quantities conveyed, or distances traveled need to be determined.
![INTEGRAL](INTEGRAL.svg)
## Interface Structure

### **Event Inputs**

* **REQ**: Starts the normal execution of the integration. The data associated with this event, `IN` and `TM`, are processed.
* **RESET**: Resets the integrator. The output `OUT` is set to zero, and the overflow flag `OVERFLOW` is set to `FALSE`.

### **Event Outputs**

* **CNF**: Signals confirmation of execution. This event is triggered after both `REQ` and `RESET` and returns the current values of `OUT` and `OVERFLOW`.

### **Data Inputs**

* **IN** (`REAL`, initial value: `0.0`): The input value to be integrated.
* **TM** (`DINT`, initial value: `0`): The time elapsed since the last call in milliseconds (ms). This value must be positive for integration to occur.

### **Data Outputs**

* **OUT** (`REAL`, initial value: `0.0`): The current value of the integral. It is calculated by summing all partial integrals (`IN * TM`). The unit is `[IN] * Sekunden` because the time value `TM` is internally converted from milliseconds to seconds.
* * **OVERFLOW** (`BOOL`, initial value: `FALSE`): Indicates an overflow. If this output is `TRUE`, the value of `OUT` has exceeded the representable range of the `REAL` data type. The integration function is blocked until it is reinitialized by a `RESET` event.

### **Adapters**

This function block does not use adapters.

## Functionality

The `INTEGRAL` function block has two primary operating states, which are controlled by incoming events:

1. **Integration (`REQ`)**: Upon a `REQ` event, the algorithm `REQ` is executed. First, it checks whether a previous overflow (`OVERFLOW = FALSE`) has occurred. An overflow check is then performed: If adding the next partial integral (`IN * TM`) to the current `OUT` value would exceed the limits of the `REAL` data type (approximately ±1.0E38), `OVERFLOW` is set to `TRUE`. Otherwise, and only if the time difference `TM` is greater than 0, the partial integral is calculated, converted to seconds (`/ 1000.0`), and added to the overall integral `OUT`.

If the value of the partial integral would exceed the limits of the `REAL` data type (approximately ±1.0E38), then `OVERFLOW` is set to `TRUE`. Otherwise, and only if the time difference `TM` is greater than 0, the partial integral is calculated, converted to seconds (`/ 1000.0`), and added to the total integral `OUT`.

2. **Reset (`RESET`)**: Upon a `RESET` event, the algorithm `RESET` is executed. This resets the integral value `OUT` to `0.0` and the overflow flag `OVERFLOW` to `FALSE`.

After the execution of each algorithm, an output event `CNF` containing the current values is always generated.

## Technical Features

* **Overflow Handling**: The function block has integrated overflow detection. If a potential overflow is detected, the integration is stopped (`OVERFLOW = TRUE`) to prevent undefined behavior. A manual reset is required to resume operation.
* **Time Basis**: The integration is based on the user-specified time difference `TM` in milliseconds. The function block itself does not have an internal timer. This allows for flexible adaptation to different cycle times of the surrounding control program.
* **Initialization**: During the first initialization of the function block, `OUT = 0.0` and `OVERFLOW = FALSE` are present.

## State Overview

The function block is a Simple FB and has explicitly defined execution states (ECStates) for the two possible events:

* **State REQ**: Activated upon arrival of the `REQ` event. Executes the integration algorithm.
* **RESET State**: Activated upon arrival of the `RESET` event. Executes the reset algorithm.

Both states result in the output of the `CNF` event after their execution.

## Application Scenarios

* **Energy Measurement**: Calculation of total energy consumption from a momentary power measurement (`IN` = power in kW, `OUT` = energy in kWh).
* **Flow Measurement**: Determination of the total volume of liquid or gas delivered from a flow sensor (`IN` = flow rate in l/min, `OUT` = volume in l).
* **Velocity Integration**: Determining the distance traveled from a velocity signal (`IN` = velocity in m/s, `OUT` = distance in m).
* **Charge Calculation**: Integrating a current signal to determine the charge flow (`IN` = current in A, `OUT` = charge in Ah).

## ⚖️ Comparison with Similar Modules

Compared to simpler summation modules (e.g., `ADD`), `INTEGRAL` is distinguished by its explicit consideration of time as an integration variable. Unlike more complex control blocks with integrated timers (such as certain PID implementations), `INTEGRAL` is a pure, discrete-time integrator that expects the time difference as an input variable and is therefore clocked externally. This makes it more flexible in systems with variable or non-periodic cycle times.

## 🛠️ Related Exercises

* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)]

## Conclusion

The `INTEGRAL` function block is a fundamental and robust tool for the time-integrated processing of signals in IEC 61499 controllers. Its clear interface, integrated overflow protection, and flexible handling of the time difference make it a reliable component for a wide variety of measurement and control tasks. The need to determine and provide the elapsed time externally offers maximum flexibility, but also requires correct implementation in the surrounding application program.
