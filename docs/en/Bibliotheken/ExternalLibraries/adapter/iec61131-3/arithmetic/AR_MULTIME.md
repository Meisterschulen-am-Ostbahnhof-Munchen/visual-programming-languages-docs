# AR_MULTIME
![AR_MULTIME](./AR_MULTIME.svg)
* * * * * * * * * *
## Introduction
The function block **AR_MULTIME** is used to multiply a time value (type TIME) by a numeric value. The numeric factor is input via an adapter, allowing the function block to be used flexibly in various contexts. The result is also output via an adapter. The function block is classified as a standard arithmetic function according to IEC 61131-3.
## Interface Structure
### **Event Inputs**
- **REQ** (Event): Normal execution trigger. The multiplication is performed when an event occurs at REQ. The IN1 input must be connected to the REQ event (WITH).

### **Event Outputs**
The function block does not have any explicit event outputs in the interface list. The result is provided via the adapter output **OUT**, which sends an event (E1) once the calculation is complete (as can be seen from the internal wiring).

### **Data Inputs**
- **IN1** (TIME): First function input – the time value to be multiplied.

### **Data Outputs**
The function block has no direct data outputs. The multiplication result is output as a data value (D1) via the adapter output **OUT**.

### **Adapters**
- **IN2** (Adapter, type `adapter::types::unidirectional::AR`): Second function input – the numerical multiplier. This adapter provides an event (E1) for triggering the calculation as well as the data value (D1).
- **OUT** (Adapter, type `adapter::types::unidirectional::ATM`): Output for the multiplied result (TIME). Provides the event (E1) and data (D1).

## Functionality

The function block AR_MULTIME encapsulates the functionality of the internal function block **F_MULTIME** (type `iec61131::arithmetic::F_MULTIME`).

When an event occurs at the **REQ** input or, alternatively, at the adapter input **IN2.E1**, the multiplication is initiated. The internal function block multiplies **IN1** (TIME) by **IN2.D1** (numeric value) and outputs the result to **OUT.D1**.

Once the calculation is complete, an event is sent to **OUT.E1**, signaling to the subsequent receiver that the result is valid.

## Technical Features
- **Adapter-based interface:** Instead of classic data inputs/outputs, adapters are used, allowing for flexible interconnection in complex networks. The adapters are defined as unidirectional and require compatible counterparts.
- **Standard compliance:** The function block meets the requirements of IEC 61131-3 (classification: standard arithmetic function).
- **Internal Encapsulation:** The actual calculation is performed by the reusable function block F_MULTIME, so AR_MULTIME acts as a wrapper with adapter-based communication.

## State Overview

The function block itself does not have an explicit state machine. Event-driven processing is deterministic:

- Waiting for an event at **REQ** or **IN2.E1**
- Executing the multiplication
- Sending the result to **OUT.E1** and **OUT.D1**
- Returning to the wait state

## Application Scenarios
- Scaling time values by a constant or variable factor, e.g., converting seconds to milliseconds or extending delay times.
- In control applications where time parameters need to be dynamically adjusted, for example, in conjunction with PID controllers or scheduling.
- As part of libraries for IEC 61131-3 compliant automatic control, especially when adapters are used to decouple the signal paths.

## Comparison with similar function blocks
- **F_MULTIME:** The direct, adapter-free function block for multiplying TIME by numeric values. It offers classic event and data interfaces. AR_MULTIME, on the other hand, encapsulates this function block and provides the interfaces via adapters, which increases reusability in adapter-based architectures.
- **AR_MUL:** A general multiplication function block with adapters that could be designed for any numeric type. AR_MULTIME is specifically specialized for TIME values.

## Conclusion
The **AR_MULTIME** function block enables the multiplication of a time value by a numeric factor via a modern, adapter-based interface. It combines proven IEC 61131-3 arithmetic with flexible connectivity and is particularly suitable for modular automation systems that rely on standardized adapters. The internal use of the F_MULTIME function block guarantees reliable and efficient calculations.