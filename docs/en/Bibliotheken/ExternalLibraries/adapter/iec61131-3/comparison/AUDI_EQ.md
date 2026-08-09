# AUDI_EQ

![AUDI_EQ](./AUDI_EQ.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_EQ** compares two analog values for equality. It is implemented as a composite function block (FB) and uses adapters to communicate with the environment. The result is a Boolean value, which is output via another adapter. The function block complies with the IEC 61131-3 classification "Standard comparison function".
## Interface Structure

The FB has only adapter interfaces. No direct event or data inputs/outputs are defined. The actual inputs/outputs are implemented via the adapter types.

## **Event Inputs**

- **IN1.E1** (via adapter `IN1`): Event input of the first value to be compared.
- **IN2.E1** (via adapter `IN2`): Event input of the second value to be compared.

### **Event Outputs**

- **OUT.E1** (via adapter `OUT`): Event output – activated once the comparison is complete and the result is valid.

### **Data Inputs**

- **IN1.D1** (via adapter `IN1`): First comparison value (analog).
- **IN2.D1** (via adapter `IN2`): Second comparison value (analog).

### **Data Outputs**

- **OUT.D1** (via adapter `OUT`): Boolean result of the comparison (`TRUE` if both values are equal, otherwise `FALSE`).

### **Adapters**

| Adapter | Direction | Type | Short Description |
|---------|----------|-----|------------------|
| `IN1` | Socket | `adapter::types::unidirectional::AUDI` | Returns the first analog value including event. |
| `IN2` | Socket | `adapter::types::unidirectional::AUDI` | Returns the second analog value including event. |
| `OUT` | Plug | `adapter::types::unidirectional::AX` | Outputs the comparison result (Boolean) with an event. |

## Functionality

The function block **AUDI_EQ** internally contains a pre-existing function block `iec61131::comparison::F_EQ` for simple equality checking.

- As soon as an event arrives at one of the two input adapters (`IN1` or `IN2`), the internal function block `F_EQ` is called.
- The current data values from `IN1.D1` and `IN2.D1` are passed to `F_EQ`.
- The internal function block compares both values and returns a Boolean result.
- After processing is complete, the internal function block (FB) outputs an event that is forwarded via the output adapter `OUT`.
- Simultaneously, the comparison result is made available at the data output `OUT.D1`.

The function block operates purely **combinatorially** – it does not store any states and executes the comparison logic anew with each activation.

## Technical Features

- **Composite FB**: The function block is implemented as a network of sub-FBs, enabling a modular and reusable structure.
- **Adapter-Based Interface**: The use of the unidirectional adapters `AUDI` and `AX` allows for flexible encapsulation of event and data channels. The adapters define the actual inputs and outputs.
- **Standard Component**: The internal FB `F_EQ` is part of the IEC 61131-3 library and guarantees platform-independent comparison logic.
- **No State Machine**: The function block does not have an internal state diagram but delegates the logic entirely to the embedded FB.

## State Overview

The FB **AUDI_EQ** has **no independent states**. The internal logic is purely event-driven and results directly in the output. Therefore, a state overview is not available.

## Application Scenarios

- **Monitoring Process Variables**: Checking two analog values (e.g., pressure sensors, temperature sensors) for equality.
- **Redundancy Check**: Comparing two independently measured values to detect sensor failures.
- **Signal Matching**: In control systems where it must be ensured that two input signals have the same value before an action is triggered.

## Comparison with Similar Function Blocks

- **`F_EQ` (directly used)** – The internal function block `F_EQ` offers the same comparison logic, but without adapters. It requires explicit event and data inputs.
- **`F_NE` (inequality)** – Performs an inequality comparison; structurally similar, but the result is inverted.
- **`AUDI_GT` (greater than)** – Analogous structure with adapters, but a different comparison operator.

The **AUDI_EQ** differs in its pre-built adapter interface, which enables easy integration into existing adapter networks. It is specifically designed for applications that require standardized input/output via unidirectional adapters.

## Conclusion

The **AUDI_EQ** is an easy-to-use, composite function block for equality comparisons with two analog values. Its adapter-based interface allows for seamless integration into modular control systems. The internal use of standardized IEC function blocks ensures reliable functionality defined according to IEC 61131-3. This function block is particularly suitable for applications requiring a clear separation of event and data flows via adapters.
