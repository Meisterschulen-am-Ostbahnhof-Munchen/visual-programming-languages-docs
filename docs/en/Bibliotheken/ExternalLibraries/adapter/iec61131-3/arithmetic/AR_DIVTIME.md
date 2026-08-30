# AR_DIVTIME

![AR_DIVTIME](./AR_DIVTIME.svg)

* * * * * * * * * *

## Introduction

The function block **AR_DIVTIME** is used to divide a time value (type TIME) by a numeric value. The divisor is supplied via an adapter, allowing the block to be used flexibly in different contexts. The result is likewise output via an adapter. The block is classified as a standard arithmetic function according to IEC 61131-3.

## Interface Structure

### **Event Inputs**

- **REQ** (Event): Normal execution request. An event at REQ triggers the division. Input IN1 must be connected to the REQ event (WITH).

### **Event Outputs**

The block has no explicit event outputs in its interface list. However, the result is provided via the output adapter **OUT**, which sends an event (E1) once the calculation is complete (as shown by the internal wiring).

### **Data Inputs**

- **IN1** (TIME): Time value to be divided (dividend).

### **Data Outputs**

The block has no direct data outputs. The division result is output via the output adapter **OUT** as a data value (D1).

### **Adapters**

- **IN2** (Adapter, type `adapter::types::unidirectional::AR`): Divisor. This adapter provides both a triggering event (E1) and the data value (D1).
- **OUT** (Adapter, type `adapter::types::unidirectional::ATM`): Output for the division result (TIME). Provides both an event (E1) and data (D1).

## Functionality

The function block AR_DIVTIME encapsulates the functionality of the internal function block **F_DIVTIME** (type `iec61131::arithmetic::F_DIVTIME`).
An event at input **REQ**, or alternatively at adapter input **IN2.E1**, triggers the division. The internal function block divides **IN1** (TIME) by **IN2.D1** (numeric value) and outputs the result to **OUT.D1**.
Once the calculation is complete, an event is sent to **OUT.E1**, signaling to the downstream receiver that the result is valid.

## Technical Features

- **Adapter-based interface:** Instead of classic data inputs/outputs, adapters are used, allowing for flexible interconnection in complex networks. The adapters are defined as unidirectional and require compatible counterparts.
- **Standard compliance:** The function block meets the requirements of IEC 61131-3 (classification: standard arithmetic function).
- **Internal encapsulation:** The actual calculation is performed by the reusable function block F_DIVTIME, so AR_DIVTIME acts as a wrapper with adapter-based communication.
- **Mixed interface:** Unlike fully adapter-based blocks, AR_DIVTIME receives the dividend (IN1) as a classic data input, not via an adapter -- see `ATM_AR_DIVTIME` for the fully adapter-based variant.

## State Overview

The function block itself does not have an explicit state machine. Event-driven processing is deterministic:

- Waiting for an event at **REQ** or **IN2.E1**
- Executing the division
- Sending the result to **OUT.E1** and **OUT.D1**
- Returning to the wait state

## Application Scenarios

- Splitting a time value into equal segments, e.g., converting a total runtime into individual cycles.
- In control applications where a time parameter must be dynamically divided by a variable factor.
- As part of libraries for IEC 61131-3 compliant automatic control, especially when adapters are used to decouple the signal paths.

## Comparison with Similar Function Blocks

- **F_DIVTIME:** The direct, adapter-free function block for dividing TIME by numeric values. It offers classic event and data interfaces. AR_DIVTIME encapsulates this function block and provides the divisor via an adapter.
- **AR_MULTIME:** Multiplies instead of dividing, otherwise structurally identical (mixed interface: IN1 as a data input, IN2 as an adapter).
- **ATM_AR_DIVTIME:** The fully adapter-based variant -- here IN1 is also an adapter socket (type `ATM`) instead of a fixed data input.

## Conclusion

The **AR_DIVTIME** function block enables the division of a time value by a numeric factor via an adapter-based interface for the divisor. It combines proven IEC 61131-3 arithmetic with flexible connectivity and is particularly suitable for modular automation systems. The internal use of the F_DIVTIME function block guarantees reliable and efficient calculations.
