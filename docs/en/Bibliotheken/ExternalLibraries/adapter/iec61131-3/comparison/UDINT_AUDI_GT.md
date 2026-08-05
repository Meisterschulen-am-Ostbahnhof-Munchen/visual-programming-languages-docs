# UDINT_AUDI_GT
![UDINT_AUDI_GT](./UDINT_AUDI_GT.svg)
* * * * * * * * * *
## Introduction
The function block **UDINT_AUDI_GT** compares two values and outputs the result, indicating whether the first value is greater than the second. It is specifically designed for use with **adapter interfaces**, which enable flexible coupling with various data sources and sinks. The block encapsulates the IEC 61131-3 comparison block `F_GT` and extends it with adapter-based input and output.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|-----------|

| REQ | Event | Service Request – triggers the comparison |

### **Event Outputs**

This function block does not have its own event outputs. The result event is provided via the **Out Adapter** (OUT) (see Adapter).

### **Data Inputs**

| Name | Type | Comment |

|------|----------------|---------------|

| IN1 | ANY_ELEMENTARY | First comparison value (greater than ?) |

### **Data Outputs**

This function block does not have its own data outputs. The comparison result is output via the **Out Adapter** (OUT) (see Adapter).

### **Adapter**

| Name | Type | Direction | Comment |

|------|----------|----------|-----------|

| IN2 | `adapter::types::unidirectional::AUDI` | Socket | Second comparison value (input) |

| OUT | `adapter::types::unidirectional::AX` | Plug | Result output: `IN1 > IN2` |

The adapter `AUDI` provides the second value (`D1`) and a corresponding event (`E1`).

The adapter `AX` expects the result (`D1`) and an event (`E1`) for forwarding.

## Functionality

1. An **event** at input `REQ` or an **event via socket IN2** (E1) triggers the processing. 2. The internal comparison module `F_GT` compares the data value of `IN1` with the data value of `IN2` (via the socket).

3. The result (TRUE/FALSE) is output via the data port `OUT.D1` of plug `OUT`.

4. Simultaneously, a **confirmation event** is generated at plug `OUT.E1`, signaling that the result is valid.

The internal logic is hard-coded in the FB network:

- `IN1` → `F_GT.IN1`
- `IN2.D1` → `F_GT.IN2`
- `F_GT.OUT` → `OUT.D1`
- Events: `REQ` or `IN2.E1` → `F_GT.REQ`; `F_GT.CNF` → `OUT.E1`

## Technical Features
- **Adapter-Based Communication**: The module uses standardized unidirectional adapters (`AUDI` and `AX`) that enable loose coupling between the connected components.
- **Flexible Data Types**: `IN1` is of type `ANY_ELEMENTARY`, therefore various elementary data types (BOOL, INT, UDINT, REAL, etc.) can be used. Internal comparison is type-safe via `F_GT`.
- **Two Triggering Options**: The comparison can be initiated via the event input `REQ` or via the event from socket `IN2`.
- **No Stateful Logic**: The function block operates purely combinatorially after each event.

## State Overview
The function block does not have an explicit state machine. Its behavior is purely event-driven and functional: The comparison is performed once for each incoming event (REQ or IN2.E1), and the result is output via the OUT adapter.

## Application Scenarios
- **Comparison in Heterogeneous Control Systems**: Use in systems where different data sources (e.g., sensors, bus couplers) are connected via adapters.
- **Limit Value Monitoring**: Checks whether a measured value (IN1) exceeds a setpoint (IN2).
- **Output Control**: Linking the result to actuators via the OUT adapter, e.g., to activate an alarm or a control variable.
- **Modular Composition**: Integration into complex adapter chains where the comparison function serves as an intermediate block.

## Comparison with Similar Blocks
- **IEC 61131-3 Standard `F_GT`**: This is a pure data comparison without an adapter and expects direct data inputs. `UDINT_AUDI_GT` encapsulates this standard block and extends it with adapter-based input/output.
- **Adapter-Based Comparison Blocks**: Other variants exist (e.g., `UDINT_AUDI_LT`, `UDINT_AUDI_EQ`) that are structured analogously but perform different comparison operations.
- **Convenience Advantage**: The user does not need to worry about internal event control; The adapters handle the synchronization of values and events.

## Conclusion
The **UDINT_AUDI_GT** function block offers a flexible and standardized way to perform a "greater than" comparison in adapter-based automation projects. Thanks to the encapsulation of the IEC comparison block and the use of standardized interfaces, it is particularly well-suited for modular and reusable control architectures.
