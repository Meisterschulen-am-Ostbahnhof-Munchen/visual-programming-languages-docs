# ALR_SUB_2

![ALR_SUB_2](./ALR_SUB_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `ALR_SUB_2` is a generic block for performing mathematical subtractions within an IEC 61499 development environment (such as 4diac IDE). Instead of using direct data and event pins, this block is based on an adapter-driven architecture. This enables structured and clean signal encapsulation and simplifies wiring in complex control applications.

## Interface Structure

### **Event Inputs**

*This block does not have direct event inputs. Control and triggering are handled via the connected adapters.*

### **Event Outputs**

*This block does not have direct event outputs. Event forwarding is handled via the output adapter.*

### **Data Inputs**

*There are no direct data inputs.*

### **Data Outputs**

*There are no direct data outputs.*

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::ALR`):

The first input value (minuend) of the subtraction. This adapter receives both the value and the triggering event.

* **IN2** (Type: `adapter::types::unidirectional::ALR`):

The second input value (subtrahend) to be subtracted from the first value.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::ALR`):

The result of the subtraction (difference). This adapter outputs the calculated result along with the corresponding output event.

## Functionality

The module's internal logic calculates the difference between the two values provided via the sockets. The mathematical formula is:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

As soon as the values at the input adapters change or a corresponding trigger event is received at `IN1` or `IN2`, the module performs the calculation and updates the value at the output plug `OUT`, followed by an output event.

## Technical Features

* **Generic Behavior**: The module is defined as a generic type (`GEN_ALR_SUB`). It is therefore not rigidly bound to a single data type (such as only `REAL` or only `INT`), but adapts flexibly to the data types defined in the adapter `ALR`.
* **Unidirectional Adapters**: By using unidirectional adapters (`unidirectional::ALR`), the data flow is clearly directed in one direction, which increases system stability and minimizes unnecessary communication overhead.

## State Overview

Since `ALR_SUB_2` is a purely mathematical, data-flow-oriented function block, it does not have an internal state machine (ECC - Execution Control Chart). Execution is purely event- and data-driven.

## Application Scenarios

* **Control Engineering (Calculation of Control Deviation)**:

Determining the difference between a setpoint (reference input at `IN1`) and an actual value (controlled variable at `IN2`) to provide the control deviation at output `OUT` for a downstream PID controller.

* **Difference Measurements**:

Calculation of physical difference values, for example, to determine the pressure drop across a filter (pressure before the filter at `IN1` minus pressure after the filter at `IN2`).

* **Offset Correction**:

Subtracting a constant or variable correction value from a raw analog signal.

## Comparison with Similar Components

Compared to classic IEC 61131-3 subtraction blocks (such as `SUB`), which use standard data types and direct pins, the `ALR_SUB_2` offers significant advantages in program code clarity thanks to its encapsulation in adapters. Complex signal paths (data + event) are bundled in a single adapter connection.

Compared to bidirectional calculation blocks, the `ALR_SUB_2` features deterministic, non-reactive signal processing.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `ALR_SUB_2` is an efficient and flexible standard component for arithmetic calculations in modern, service-oriented control systems. By utilizing adapter technology, it supports a modular and maintainable software design according to the IEC 61499 standard.