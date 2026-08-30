# AUI_EQ

![AUI_EQ](./AUI_EQ.svg)

* * * * * * * * * *

## Introduction

The AUI_EQ function block performs an equality comparison between two analog values. It is classified as a standard comparison function according to IEC 61131-3 and uses adapters for type-safe communication with the environment. The result is output as a Boolean value, which is `true` if and only if both input values are equal.

## Interface Structure

### **Event Inputs**

- **IN1.E1** – Trigger for the comparison (sent when the first value is updated).
- **IN2.E1** – Alternative trigger for the comparison (sent when the second value is updated).

Both events are associated with the same internal processing event; the comparison is triggered when either event occurs.

### **Event Outputs**

- **OUT.E1** – Confirmation that the comparison is complete and the result is available at the data output.

### **Data Inputs**

- **IN1.D1** – First analog value to be compared.
- **IN2.D1** – Second analog value to be compared.

### **Data Outputs**

- **OUT.D1** – Comparison result: `true` if `IN1.D1 == IN2.D1`, otherwise `false`.

### **Adapters**

- **IN1** (Socket) – Adapter type `adapter::types::unidirectional::AUI`, encapsulates the first input value and the associated event.
- **IN2** (Socket) – Adapter of type `adapter::types::unidirectional::AUI`, encapsulates the second input value and the associated event.
- **OUT** (Plug) – Adapter of type `adapter::types::unidirectional::AX`, encapsulates the result and the output event.

The adapters enable loose coupling between the function block and its environment, simplifying reuse in different applications.

## Functionality

AUI_EQ delegates the actual comparison logic to the internal function block `F_EQ` (type `iec61131::comparison::F_EQ`). As soon as an event arrives at one of the input adapters (IN1 or IN2), the calculation is started. The internal `F_EQ` compares the two passed values and returns the Boolean result. After the calculation is complete, the result is output via the output adapter OUT, and a corresponding event is sent.

The function block is event-driven – it reacts to input events and does not require its own cyclic call.

## Technical Features

- The function block uses only adapters for communication, which offers high flexibility when connecting to various data sources and sinks.
- Internally, it is based on the standard function block `F_EQ` from the IEC 61131 library, which provides a robust and tested comparison function.
- The input events are logically ORed: Each of the two events triggers a recalculation. This simplifies control, as only the currently updated signal needs to be sent.
- The function block has been further developed in several versions and was last updated in 2025.

## State Overview

AUI_EQ does not have an explicit state machine. Its behavior is entirely determined by the event processing of the internal `F_EQ`. Upon the arrival of an event, the function block performs a calculation and sends the result – there are no waiting or blocking states.

## Application Scenarios

- **Equality Monitoring**: Checking whether two sensor readings (e.g., temperature, pressure) have the same value.
- **Alarming**: Triggering an alarm if two redundant measurements differ (logical negation of the output).
- **Control**: Switching actuators when a setpoint matches an actual value.
- **Plausibility Check**: Comparing analog values from different sources for error detection.

## Comparison with Similar Function Blocks

In addition to `AUI_EQ`, the IEC 61131 library contains other comparison blocks such as `AUI_GT` (greater than), `AUI_LT` (less than), and `AUI_NE` (not equal to). These share the same adapter interface but differ in their comparison operation. `AUI_EQ` is specifically optimized for equality testing and does not offer any other comparison logic. For more comprehensive comparisons (e.g., greater than or equal to), combinations with logic blocks are required.

## Conclusion

The AUI_EQ function block implements a simple and reliable equality check for analog values. The use of adapters makes it highly adaptable to various automation environments. Its event-driven operation and the internal use of a standardized comparison module ensure consistent and high-performance execution. AUI_EQ is therefore a fundamental building block for monitoring and control tasks where value equality must be determined.
