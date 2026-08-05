# UDINT_AUDI_EQ

![UDINT_AUDI_EQ](./UDINT_AUDI_EQ.svg)

* * * * * * * * * *
## Introduction

The function block `UDINT_AUDI_EQ` performs a comparison of two values for equality. The first value is provided via the data input `IN1`, and the second value is received via an adapter socket (`IN2`). The result of the comparison (true if both values are equal) is output via an adapter plug (`OUT`). The block triggers the comparison operation as soon as an event occurs at the input `REQ` or at the adapter socket `IN2`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|-------------------|

| REQ | Event | Service Request |

### **Event Outputs**

No direct event outputs. The result event is provided via the adapter plugin `OUT`.

### **Data Inputs**

| Name | Type | Comment |

|------|------------------|------------------|

| IN1 | ANY_ELEMENTARY | Input value 1 |

### **Data Outputs**

No direct data outputs. The result is provided as data via the adapter plugin `OUT`.

### **Adapters**

| Name | Type | Direction | Comment |

|------|--------------------------------------------------------|----------|------------------------------------------------|

| IN2 | adapter::types::unidirectional::AUDI | Socket | Input value 2 |

| OUT | adapter::types::unidirectional::AX | Plug | value 1 = value2 = true |

- **IN2** (Socket): This adapter passes the second comparison value (both event and date) to the function block from an external source. The event `IN2.E1` triggers the comparison, and the date `IN2.D1` contains the value.

- **OUT** (Plug): This adapter outputs the comparison result. The event `OUT.E1` signals completion, and the date `OUT.D1` contains the result (of type BOOL).

## Functionality

This function block performs an equality comparison. Internally, it uses the standard function block `F_EQ` (`iec61131::comparison::F_EQ`).

1. **Trigger**: The comparison is started as soon as an event arrives at input `REQ` or at adapter socket `IN2.E1`.

2. **Operation**: The event triggers the internal function block `F_EQ`, which compares the values at `IN1` and `IN2.D1`.

3. **Result**: After the comparison is complete, `F_EQ` sends an event to its output `CNF`. This event is forwarded to the adapter plug `OUT.E1`. Simultaneously, the comparison result (BOOL) from `F_EQ.OUT` is transferred to the data output `OUT.D1`.

The function block operates asynchronously: As soon as a corresponding event occurs, the comparison is performed and the result is output via the plug.

## Technical Features

- **Adapter-Based Input/Output**: Both the second input value and the result are communicated via adapter interfaces, enabling flexible integration with other components or systems.

- **Generic Data Type**: `IN1` is declared as `ANY_ELEMENTARY`, allowing the function block to work with various elementary data types (e.g., INT, REAL, BOOL). The adapter `IN2` must provide the same data type.

- **Internal Standard Function Block**: The comparison function is implemented using the standardized IEC 61131 function block `F_EQ`, ensuring correctness and reusability.

- **No State Machines**: The function block is purely functional and does not have its own state model – the logic is implemented exclusively via the internal FB network.

## State Overview

The function block has no explicit states or a state diagram. Its behavior is determined solely by the event and data flows in the internal network. Each incoming event is processed immediately.

## Application Scenarios

- **Measurement Value Comparison**: A sensor value (`IN1`) is compared to a reference value provided by another system via an adapter connection.

- **Threshold Feedback**: The function block can be used in control applications to check whether a process value has reached a setpoint and to pass the result as a Boolean signal to downstream logic.

- **Distributed Systems**: Thanks to the adapters, the function block is suitable for use in systems that require loose coupling between components, e.g., in manufacturing automation or building control.


## Comparison with Similar Components

- **Standard Comparison Components** (e.g., `F_EQ`, `F_NE`, `F_GT`): These have direct data inputs and outputs. The `UDINT_AUDI_EQ`, on the other hand, uses adapters for the second input and output. This increases flexibility for modular and networked architectures.

- **Adapter-Based Components**: Unlike simple comparison components with fixed interfaces, this component allows for dynamic connection of the second comparison value via a socket, which is advantageous in hierarchical or reusable components.

## Conclusion

The `UDINT_AUDI_EQ` is a versatile function block for comparing two values for equality. The use of input and output adapters enables decoupled communication, which offers particular advantages in complex automation systems or distributed environments. The module is easy to integrate and relies on proven standard functions for comparison logic.