# AI_ADD_2

![AI_ADD_2](./AI_ADD_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block (FB) **AI_ADD_2** is a generic block for performing the arithmetic addition of two analog input values. It is based on the concept of generic function blocks (`GEN_AI_ADD`) and uses adapter interfaces instead of classic, loosely coupled data and event connections. This enables structured, clear, and modular signal processing within 4diac-ide-based control applications.

## Interface Structure

### **Event Inputs**

*There are no direct event inputs. Event control is encapsulated via the adapters used.*

### **Event Outputs**

*There are no direct event outputs. Event control is encapsulated via the adapters used.*

### **Data Inputs**

*There are no direct data inputs.*

### **Data Outputs**

*There are no direct data outputs.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN1** (Type: `adapter::types::unidirectional::AI`): The first addend of the addition operation. Both the value and the corresponding update event are received via this adapter.
* **IN2** (Type: `adapter::types::unidirectional::AI`): The second addend of the addition operation.

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AI`): The result of the addition ($OUT = IN1 + IN2$). This adapter passes the result and the corresponding update event to subsequent function blocks.

## Functionality

The function block **AI_ADD_2** functions as a mathematical adder. As soon as a new event is signaled at one of the input adapters (`IN1` or `IN2`) indicating that the input data has been updated, the function block performs the addition:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

The calculated result is immediately passed to the output adapter `OUT`, and the corresponding update event is triggered to inform subsequent program parts of the new value.

Since this is a generic function block (`GEN_AI_ADD`), the underlying data type (e.g., `REAL`, `INT`, `LREAL`) is flexible and determined by the configuration of the connected adapters.

## Technical Features

* **Generic Type (`GEN_AI_ADD`):** The function block is not tied to a specific data type, which increases its reusability for different analog signal ranges.
* **Unidirectional Adapters:** Using the `adapter::types::unidirectional::AI` type drastically reduces wiring complexity in the 4diac-ide, as values and events are bundled in a single connection.
* * **Clean Encapsulation:** No loose event and data lines on the surface of the function block.

## State Overview

The function block operates in an event-driven and stateless manner. No internal state is maintained (as with a memory element). Each incoming event at the inputs immediately triggers recalculation and output at output `OUT`.

## Application Scenarios

* **Sensor Data Aggregation:** Adding two flow rates (e.g., main flow and bypass flow) to obtain a total flow rate.
* **Setpoint Offsetting:** Adding a fixed or dynamic offset (e.g., calibration value) to an analog input signal.
* **Signal Mixing:** Simple mathematical combination of two analog control signals in process automation.

## Comparison with Similar Function Blocks

Compared to the standard IEC 61131-3 add block (`ADD`), which uses classic data pins (e.g., `IN1`, `IN2` of type `ANY_NUM`) and explicit control events (`REQ` / `CNF`), **AI_ADD_2** offers a significantly cleaner visual representation. Encapsulation within adapters eliminates the need to manually draw separate event lines, minimizing the risk of errors during application development.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The **AI_ADD_2** is a modern, highly efficient function block for the 4diac-ide. It combines the fundamental mathematical function of addition with the structural advantages of IEC 61499 adapters. This makes it the ideal choice for modular control architectures.