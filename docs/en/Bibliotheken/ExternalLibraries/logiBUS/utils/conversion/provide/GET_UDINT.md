# GET_UDINT

![GET_UDINT](./GET_UDINT.svg)

* * * * * * * * * *
The **GET_UDINT** function block reads the current value of a variable of type **UDINT** declared as InOut and provides it as a buffered output. Buffering ensures that the output value remains stable during a cycle, even if the source data changes later.

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Normal Execution Request |

*Associated Data:*

- **IN** (InOut variable) is read on REQ.

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Execution Confirmation |

*Associated Data:*

- **OUT** (Output Value) is provided after a successful read.
- **IN** (InOut Variable) is also associated, meaning its value can be read at the output after the event.

| Name | Type | Default Value | Comment |
|------|-----|-------------|-----------|
| IN | UDINT (InOut) | 0 | Source Variable to be Read |
| Name | Type | Default Value | Comment |
|------|-----|-------------|-----------|
| OUT | UDINT | 0 | Buffered Output Value |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapter**

None.

## Functionality

Upon an event at the **REQ** input, the function block executes the algorithm and sends an acknowledgment event to **CNF**. The algorithm copies the current value of the InOut variable **IN** to the output variable **OUT**. This freezes the value at the time of the request and makes it stably available at the output until the next request.

- **InOut Variable:** The parameter **IN** is declared as InOut. This allows direct access to the memory address of the source variable, which can be useful for communication over distributed systems (e.g., fieldbuses). However, the function block only reads the value; it does not write back.
- **No Side Effects:** The function block does not modify the InOut variable.

The function block has only one state:

- **REQ:** The algorithm is executed. After copying the value, the output **CNF** is immediately set.

There are no other states; the function block is always ready to process a request.

- **Buffering of Process Values:** In automation systems where a measured value or manipulated variable (e.g., a counter reading or speed) needs to be frozen at a specific interval before being passed on to other function blocks.
- **Decoupling of Cycles:** When an InOut variable is read by multiple function blocks and a stable value is required within a cycle.
- **Replacement for direct access:** Instead of directly reading an InOut variable, the function block (FB) provides a clear interface (event input, output) and improves system readability.
- **MUX (Multiplexer):** A MUX selects between multiple inputs, while **GET_UDINT** buffers exactly one defined value from an InOut variable.
- **GET_DINT / GET_REAL:** Analogous function blocks for other data types that implement the same principle of buffered output of InOut values.
- **Latch function blocks:** These store values and output them upon an event; **GET_UDINT**, on the other hand, overwrites the output with the current value of the source on every request.

The **GET_UDINT** function block is a simple yet useful tool for stably and event-drivenly caching the value of an InOut variable of type UDINT. It is particularly suitable for applications where access to external or shared variables should occur in controlled steps, thus contributing to clean and predictable signal processing.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
